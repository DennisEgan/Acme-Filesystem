#include "FCB.h"
#include "diskprocess.h"

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
	int open(string, string);
	int search(string);
	int read(int, int, char*);
	int write(int, int, char*);
	int getNumChars(int);
	int getFreeBlock();
	bool deleteFile(string);

private:
	DiskProcessType myDisk;
	FCB* freespace;
	vector<FCB*>files;
	vector<FCB*>FOT;
};
#endif
