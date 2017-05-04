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
	bool close(int);
	int  open(string, char);
	int  searchFOT(string);

	int read(int, int, char*);
	int write(int, int, char*);
	
	int getNumChars(int);
	int getFreeBlock();

	FCB*       getFile(string name);
	bool       deleteFile(string name);

	Directory* getDirectory();
	bool	   deleteDirectory();
private:

	DiskProcessType myDisk;
	FCB* freespace;		// ??
//	vector<FCB*>files;	// No more files, use directory in future
	Directory* directory;
	vector<FCB*>FOT;

};

#endif
