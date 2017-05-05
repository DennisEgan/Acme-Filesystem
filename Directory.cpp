/*
 * Directory.cpp
 *
 * Implementation of Directory class in Directory.h
 *
 * Lead author:
 *  Dennis Egan
 *
 * Contributors:
 *  Justin Lesko
 */
#include "Directory.h"
#include "FCB.h"
#include <iostream>
#include <vector>
using namespace std;

/*
 * Default constructor
 */
Directory::Directory(){
	name = "";
}

/*
 * Constructor to set name of directory
 * :param dirName: name of directory
 */
Directory::Directory(string dirName){
    name = dirName;
}

/*
 * Deconstructor
 */
Directory::~Directory()
{
	for(auto it  = files.begin(); it != files.end(); it++)
		delete *it;
	
	files.clear();
}

// Setters and getters
string 		 Directory::getName(){ return name; }
void   		 Directory::setName(string newName){ name = newName;}
int    		 Directory::getSize(){ return files.size(); }
vector<FCB*> Directory::getFiles(){ return files; }

/*
 * Add file to directory
 * :param newFile: file to be added to directory
 */
bool Directory::addFile(FCB* newFile)
{
	if(!containsFile(newFile->getFileName()))
		files.push_back(newFile);
}

/*
 * Create file in directory
 * If fileName not in directory -> true
 * Else -> false
 *
 * :param fileName: name of file to create in directory
 */
bool Directory::createFile(string fileName){

    // File was not in directory
	if(!containsFile(fileName))
	{
		FCB* newFile = new FCB(fileName);
		files.push_back(newFile);
		return true;
	}

    // File was in directory
	else
		return false;
}

/*
 * Delete file of name name from directory
 * Returns true if found and deleted
 *
 * :param name: name of file to be deleted in directory
 */
bool Directory::deleteFile(string name)
{
	for (int i = 0; i < files.size(); i++){
		if (files[i]->getFileName() == name){
			delete files[i];
			files.erase(files.begin() + i);
			return true;
		}

		i++;
	}

	return false;
}

/*
 * Get file of name name from directory
 * :param name: name of file to get
 */
FCB* Directory::getFile(string name)
{
	if(!files.empty()){
		for(int i = 0; i < files.size(); i++){
			if(files[i]->getFileName() == name){
				FCB* tmp = new FCB(*files[i]);
				return tmp;
			}
		}
	}
	return NULL;
}

/*
 * Get size of file of name name
 * :param name: name of file to get size of
 */
int Directory::getFileSize(string name){

	for(int i = 0; i < files.size(); i++){
		if(files[i]->getFileName() == name)
			return files[i]->getSize();
	}

	return -1;
}

/*
 * Check if directory contains file of name name
 * :param name: name of file to check if in directory
 */
bool Directory::containsFile(string name)
{
	if(getFile(name) != NULL)
		return true;
	else
		return false;
}
