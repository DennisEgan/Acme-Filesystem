#include "FileSystem.h"
#include "diskprocess.h"
#include <iostream>

#define DISK_SIZE 10
#define BLOCK_SIZE 5

using namespace std;
int main(){
	DiskProcessType myDisk(BLOCK_SIZE, DISK_SIZE);
	//link blocks
	for (int i = 0; i <DISK_SIZE; i++){
		DiskBlockType *myBuffer = new DiskBlockType(BLOCK_SIZE);
		if (i < (DISK_SIZE-1))
			myBuffer->data[0] = (unsigned char)(i+1);
		else
			myBuffer->data[0] = (unsigned char)(-1);
		myDisk.write(i, myBuffer);
		delete myBuffer;
	}

	for (int i = 0; i <DISK_SIZE; i++){
		DiskBlockType *myBuffer = new DiskBlockType(BLOCK_SIZE);
		myDisk.read(i, myBuffer);
		for (int j = 0; j < BLOCK_SIZE; j++)
			printf("%d\n", myBuffer->data[j]);
		delete myBuffer;
	}

	FCB freeSpace(DISK_SIZE, BLOCK_SIZE);


	FCB file1(1,BLOCK_SIZE);



	FCB file2(1,BLOCK_SIZE);





}
