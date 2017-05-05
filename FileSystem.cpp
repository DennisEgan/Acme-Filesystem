/*
 * FileSystem.cpp
 *
 * Implementation of FileSystem class
 *
 * Lead author:
 *  Justin Lesko
 *
 * Contributors:
 *  Dennis Egan
 */
#include "FileSystem.h"
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define LOGGING false

/*
 * Constructor for class
 */
FileSystem::FileSystem():myDisk(BLOCK_SIZE, DISK_SIZE){
	//link blocks
	directory = new Directory();

	for (int i = 0; i <DISK_SIZE; i++){
		DiskBlockType *myBuffer = new DiskBlockType(BLOCK_SIZE);
		if (i < (DISK_SIZE-1))
			myBuffer->data[0] = (unsigned char)(i+1);
		else
			myBuffer->data[0] = (unsigned char)(-1);
		myDisk.write(i, myBuffer);
		delete myBuffer;
	}
	freespace = new FCB(0, 0, "freespace");
	freespace->setBlockSize(DISK_SIZE);
	freespace->setFileEnd(DISK_SIZE-1);
}

/*
 * Deconstructor
 */
FileSystem::~FileSystem(){
	delete freespace;
	delete directory;
}

/*
 * Create file with name fileName
 * Returns true if file not in directory already and created properly
 *
 * :param fileName: name to give to new file
 */
bool FileSystem::create(string fileName){
	return directory->createFile(fileName);
}

/*
 * Get file with name name
 * :param name: name of file to get in directory
 */
FCB* FileSystem::getFile(string name){
	return directory->getFile(name);
}

/*
 * Check if directory contains file of name name
 * :param name: name of file to check for in directory
 */
bool FileSystem::containsFile(string name){
	return directory->containsFile(name);
}

/*
 * Open file in specific mode
 * Returns handle of file if successfully opened in mode
 *
 * :param filename: name of file to open
 * :parm mode: mode to open file in
 */
int FileSystem::open(string filename, char mode){

    if(LOGGING){
        cout << "opening " << filename << "..." << endl;
    }

	if((mode == 'r' || mode == 'w') && directory->containsFile(filename)){

		// File already in FOT, update mode
		int idx = searchFOT(filename);
		if(idx != -1){
			FOT[idx]->setMode(mode);
		}

		// File not in FOT, put into FOT and change mode
		else{
			FCB* openFile = new FCB(*(directory->getFile(filename)));

            if(LOGGING) {
                cout << "Printing OPENFILE" << endl;
                openFile->print();
            }

            openFile->setMode(mode);

            FOT.push_back(openFile);
			idx = FOT.size()-1;
		}
		return idx;
	}

	else {
		if(LOGGING) {
            cerr << "Error when opening " << filename << endl;
        }
		return -1;
	}
}

/*
 * Wrapper for close function
 * :param fileName: name of file to open
 */
bool FileSystem::close(string fileName) {
    int handle = searchFOT(fileName);
    if (handle != -1) {
        return close(searchFOT(fileName));
    }
    else {
        if(LOGGING) {
            cerr << fileName << " is either already closed or does not exist.\n";
        }
        return -1;
    }
}

/*
 * Close file with handle
 * Returns true if properly closed
 *
 * :param handle: handle of file to close in FOT
 */
bool FileSystem::close(int handle){

    if(LOGGING){
        cout << "closing " << FOT[handle]->getFileName() << "..." << endl;
    }

	const string name = FOT[handle]->getFileName();

	// Copy the updated file to be added back to the directory
	FCB* updatedFile = new FCB(*FOT[handle]);

	updatedFile->setMode('c');

	// Delete the current version in the directory and it's entry in FOT
	directory->deleteFile(name);
	delete FOT[handle];
	FOT.erase(FOT.begin()+handle);

	// Add update version of file to directory
	directory->addFile(updatedFile);

	FCB* afterWriting = directory->getFile(name);

    if(LOGGING) {
        cout << "Is " << name << " in directory after closing? " << directory->containsFile(name) << endl;
    }

	return true;
}

/*
 * Wrapper for read
 * Open file of name fileName
 *
 * :param fileName: name of file to open
 * :param buffer: buffer to read into
 */
int FileSystem::read(string fileName){
    int handle = searchFOT(fileName);

    if(handle != -1) {
        int numChars = getNumChars(handle);
        char buffer[numChars];
        return read(searchFOT(fileName), numChars, buffer);

    }
    else{
        if(LOGGING) {
            cerr << fileName << " is not currently open!\n";
        }
        return -1;
    }
}

/*
 * Read file with handle handle in FOT
 * Returns number of chars read
 *
 * :param handle: handle of file in FOT
 * :param numchars: number of chars in buffer
 * :param buffer: buffer to read into
 */
int FileSystem::read(int handle, int numchars, char *buffer){

	if(LOGGING) {
		cout << "Block size of " << FOT[handle]->getFileName() << endl
			 << FOT[handle]->getBlockSize() << endl
			 << "File size of " << FOT[handle]->getSize();
	}

	if(FOT[handle]->getMode() != 'r'){
        if(LOGGING) {
            cerr << FOT[handle]->getFileName() << " is not in read mode!\n";
        }
        return -1;
	}

    if(LOGGING) {
        cout << "Number Of Chars to Read " << numchars << endl;
    }

    int nextBlockToRead = 0;
	int blockToRead = FOT[handle]->getBlockPointer();
	
	while (numchars > 0){
		DiskBlockType *readBuffer = new DiskBlockType(BLOCK_SIZE);
		int status = myDisk.read(blockToRead, readBuffer);
		
		if(status == -1){
            if(LOGGING) {
                cerr << "Error when reading from disk\n";
            }
            return -1;
		}

		nextBlockToRead = readBuffer->data[0];
		
		for (int i = 1; i < BLOCK_SIZE; i++)
		{
			if (numchars == 0)
				break;

			printf("%c", readBuffer->data[i]);
			numchars--;
		}
		
		if (nextBlockToRead != -1){
			blockToRead = nextBlockToRead;
		}
		
		delete readBuffer;
		readBuffer = NULL;	// ??
	}

	return numchars;

}

/*
 * Wrapper for write function
 * :param fileName: name of file to write to
 * :param buffer: buffer containing what to write to file
 */
int FileSystem::write(string fileName, char* buffer){
    int handle = searchFOT(fileName);
    if(handle != -1){
        return write(handle,strlen(buffer),buffer);
    }
    else{
        if(LOGGING){
            cerr << fileName << " is not open.\n";
        }
        return -1;
    }
}

/*
 * Write to file
 * :param handle: handle of file in FOT
 * :param numchars: number of characters to write to file
 * :param buffer: contains what to write to file
 */
int FileSystem::write(int handle, int numchars, char* buffer){
	
	if(FOT[handle]->getMode() != 'w'){
		if(LOGGING){
            cerr << "File is not in write mode!\n";
        }
		return -1;
	}

    if(LOGGING) {
        cout << "Writing to " << FOT[handle]->getFileName() << "..." << endl;
        cout << "Number of chars to write = " << numchars << endl;
    }

	int sentinel = -1,
	    blockToWrite = 0,
	    nextBlockToWrite = 0,
	    readChar = 0,
	    writeChar = 0,
	    offset = 0,
	    charsWritten = 0;

	bool blockFull = false;

	//first step: check if file is empty
	if (FOT[handle]->getSize() == 0){

		//File was empty, check if blocks are available
		if (freespace->getBlockSize() > 0){
			FOT[handle]->setBlockPointer(getFreeBlock());
			FOT[handle]->setFileEnd(FOT[handle]->getBlockPointer());
			FOT[handle]->setBlockSize(FOT[handle]->getBlockSize()+1);
			offset = 1;
		}
		else{
            if(LOGGING) {
                cout << "Error, no blocks available" << endl;
                cout << "\tChars Written = " << charsWritten << endl;
            }
            return charsWritten;
		}
	}

	// File is not empty, calculate offset
	//if (FOT[handle]->getSize() != 0){
	else{
		offset = (FOT[handle]->getSize()%(BLOCK_SIZE-1));

		// If offset is 0, that block is full
		if (offset == 0){

			// Check for available blocks
			if (freespace->getBlockSize() > 0){
				offset = 1;
				nextBlockToWrite = getFreeBlock();

				DiskBlockType *myBuffer = new DiskBlockType(BLOCK_SIZE);
				blockToWrite = FOT[handle]->getFileEnd();

				myDisk.read(blockToWrite,myBuffer);
				myBuffer->data[0] = nextBlockToWrite;

				myDisk.write(blockToWrite,myBuffer);
				blockToWrite = nextBlockToWrite;

				FOT[handle]->setFileEnd(blockToWrite);
				FOT[handle]->setBlockSize(FOT[handle]->getBlockSize()+1);

				nextBlockToWrite = -1;

				delete myBuffer;

				myBuffer = NULL;
			}
			else{
                if(LOGGING) {
                    cout << "Error, no blocks available" << endl;
                    cout << "\tChars Written = " << charsWritten << endl;
                }
                return charsWritten;
			}
		}
		else{
			offset++;
		}
	}
	while(numchars > 0){
		blockToWrite = FOT[handle]->getFileEnd();
		DiskBlockType *writeBuffer = new DiskBlockType(BLOCK_SIZE);

        if(LOGGING) {
            cout << "Writing to block ===== " << blockToWrite << endl;
        }

        if(offset > 1){
			myDisk.read(blockToWrite,writeBuffer);
		}
		for (int i = offset; i < BLOCK_SIZE; i++){
			if (numchars == 0)
				break;
			if (i == BLOCK_SIZE-1)
				blockFull = true;
			writeBuffer->data[i] = buffer[readChar];
			numchars--;
			readChar++;
			charsWritten++;
			FOT[handle]->setSize(FOT[handle]->getSize()+1);
		}

        if ((blockFull && numchars > 0)){
			if (freespace->getBlockSize() > 0){
				nextBlockToWrite = getFreeBlock();
				DiskBlockType *myBuffer = new DiskBlockType(BLOCK_SIZE);

				blockToWrite = FOT[handle]->getFileEnd();
				writeBuffer->data[0] = nextBlockToWrite;
				myDisk.write(blockToWrite,writeBuffer);

				delete myBuffer;
				myBuffer = NULL;

				blockToWrite = nextBlockToWrite;
				FOT[handle]->setFileEnd(blockToWrite);
				FOT[handle]->setBlockSize(FOT[handle]->getBlockSize()+1);

				offset = 1;
			}
			else{
				writeBuffer->data[0] = (char)(sentinel);
				myDisk.write(blockToWrite,writeBuffer);

                if(LOGGING) {
                    cout << "No blocks available" << endl;
                    cout << "\tChars Written = " << charsWritten << endl;
                }
                return charsWritten;
			}
		}else{
			writeBuffer->data[0] = (char)(sentinel);
			myDisk.write(blockToWrite,writeBuffer);
		}

		blockFull = false;
		delete writeBuffer;
		writeBuffer = NULL;
	}
    if(LOGGING){
	    cout << "\tChars Written = " << charsWritten << endl;
    }

	return charsWritten;

}

/*
 * Get free block of memory
 */
int FileSystem::getFreeBlock(){
	int blockIndex = 0;
	if (freespace->getBlockSize() != 0){
		blockIndex = freespace->getBlockPointer();//save block location

		DiskBlockType *readBuffer = new DiskBlockType(BLOCK_SIZE);
		myDisk.read(blockIndex, readBuffer);

		int nextBlockToRead = readBuffer->data[0];
		freespace->setBlockSize(freespace->getBlockSize()-1);//decrement freespace size
		freespace->setBlockPointer(nextBlockToRead);//move freespace pointer forward

		delete readBuffer;
	}
	else{
		blockIndex = -1;
	}

    if(LOGGING){
        cout << "popping block " << blockIndex << endl;
        cout << "freespace blocks left = " << freespace->getBlockSize() << "/" << DISK_SIZE << endl;
    }

	return blockIndex;
}

/*
 * Delete file of name filename in directory
 * Returns true if successfully deleted
 * :param filename: name of file to delete in directory
 */
bool FileSystem::deleteFile(string filename){

	// Get file
	FCB* toDelete = new FCB(*directory->getFile(filename));

	// File was found
	if(toDelete != NULL){

		if(freespace->getBlockSize() != -1){
			DiskBlockType *freeBuffer = new DiskBlockType(BLOCK_SIZE);
			myDisk.read(freespace->getFileEnd(), freeBuffer);

			freeBuffer->data[0] = toDelete->getBlockPointer();
			myDisk.write(freespace->getFileEnd(), freeBuffer);

			freespace->setFileEnd(toDelete->getFileEnd());
			freespace->setBlockSize(freespace->getBlockSize() + toDelete->getBlockSize());

			delete freeBuffer;
			freeBuffer = NULL;

			directory->deleteFile(filename);

		}
		else{
            if(LOGGING){
			    cout << "Freespace was empty" << endl;
            }

			delete freespace;

			freespace = new FCB(*(toDelete));
//			freespace->operator=(*(toDelete));

			directory->deleteFile(filename);

            if(LOGGING){
                cout << "PRINTING FREESPACE COPY" << endl;
                freespace->print();
                cout << "......................." << endl;
                freespace -> setFileName("freespace");
                freespace -> setSize(0);
                freespace->print();
            }
		}
		return true;
	}
	else{
        if(LOGGING){
		    cerr << "File not found. Cannot delete.\n";
        }
		return false;
	}
}

/*
 * Search FOT for file of name fileName
 * Returns index (aka the handle) of the file in FOT if found
 * Else, -1
 *
 * :param fileName: name of file to find in FOT
 */
int FileSystem::searchFOT(string fileName){

	int index = -1;
	if(!FOT.empty()){
		for (int i = 0; i < FOT.size(); i++) {
			if (FOT[i]->getFileName() == fileName) {
				index = i;
			}
		}
	}
	return index;
}

/*
 * Get number of characters in file
 * :param file: handle of file in FOT to get size of
 */
int FileSystem::getNumChars(int file){
	return FOT[file]->getSize();
}

void FileSystem::printDir(){
    vector<FCB*> files = directory->getFiles();

    string spacing = string(8*3, ' '),   // 3 tabs of 8 spaces each
           prompt  = "FILENAMESIZE(blks)";

    int lenStr = strlen(spacing.c_str()),
        maxLen = strlen(prompt.c_str())+lenStr;

    cout << "\tATOS-FS Directory Listing" << endl;
    cout << "\tFILENAME\t\t\tSIZE(blks)" << endl;

    for(int i = 0; i < files.size(); i++){
        string name    = files[i]->getFileName();
        int    nameLen = strlen(name.c_str());
        int    size    = files[i]->getBlockSize();

        int numSpaces = 1;
        if(nameLen < maxLen)
            numSpaces = maxLen-nameLen-1;

        cout << "\t" << name << string(numSpaces,' ') << size << "\n";

    }
    cout << "\tFREE SPACE blks: " << freespace->getBlockSize() << endl;
}