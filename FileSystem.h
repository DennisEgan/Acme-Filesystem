/*
 * FileSystem.h
 *
 * Header file for ATOS FileSystem class
 *
 * Lead author:
 *  Justin Lesko
 *
 * Contributors:
 *  Dennis Egan
 */
#include "FCB.h"
#include "diskprocess.h"
#include "Directory.h"

#define DISK_SIZE 10
#define BLOCK_SIZE 20

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

class FileSystem{

public:
	FileSystem();
	~FileSystem();

	bool create(string);
	int  open(string, char);
	int  searchFOT(string);

	// Close, read, write functions and wrappers
	bool close(string);
	bool close(int);

	int read(string);
	int read(int, int, char*);

	int write(string, char*);
	int write(int, int, char*);
	
	int getNumChars(int);
	int getFreeBlock();

	FCB*       getFile(string name);
	bool       deleteFile(string name);

	Directory* getDirectory();
	bool	   deleteDirectory();

	void printDir();
	bool containsFile(string);

private:

	DiskProcessType myDisk;
	FCB* freespace;
	Directory* directory;
	vector<FCB*>FOT;

};

#endif
