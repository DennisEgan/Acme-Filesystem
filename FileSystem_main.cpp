#include "FileSystem.h"
#include <iostream>
#include "string.h"
using namespace std;
int main(){
	//link blocks
	// for (int i = 0; i <DISK_SIZE; i++){
	// 	DiskBlockType *myBuffer = new DiskBlockType(BLOCK_SIZE);
	// 	myDisk.read(i, myBuffer);
	// 	for (int j = 0; j < BLOCK_SIZE; j++)
	// 		printf("%d\n", myBuffer->data[j]);
	// 	delete myBuffer;
	// }

	FileSystem FS;

	// Create two files
	string file1 = "hello.txt",
		   file2 = "goodbye.txt",
		   file3 = "hola.txt";

	cout << FS.create(file1) << " & "
	     << FS.create(file2) << " & "
		 << FS.create(file3) << endl;
	
	/*
	 * Test writing to files
	 */
	
	char test1[] = "Hello";
	char test2[] = ", We are group 1. ";
	char test3[] = "This is a test sentence.";
	// char test4[] = ". \n";
	// char test5[] = "Still Appending to a fi";
	// char test6[] = "le. Bye! And now I am trying to cause the disk to run out of space itshouldstophere blaaaaaaaaaa";
	// char test7[] = "bitshouldstop";
	char test[256];
	
	FS.open(file1, 'w');
	int num1 = FS.write(0, strlen(test1), test1);
	FS.close(0);

	FS.open(file2, 'w');
	int num2 = FS.write(0, strlen(test2), test2);
	FS.close(0);

	FS.open(file3, 'w');
	int num3 = FS.write(0, strlen(test3), test3);
	FS.close(0);

	/*
	 * Test writing again (???)
	 */
	// int num4 = FS.write(0, strlen(test4), test4);
	// int num5 = FS.write(0, strlen(test5), test5);
	// int num6 = FS.write(0, strlen(test6), test6);
	// int num7 = FS.write(0, strlen(test7), test7);

	FS.open(file1, 'w');
	num3 = FS.write(0, strlen(test3), test3);
	//cout << endl << endl;
	//cout << "number of chars " << FS.getNumChars(0) << endl;
	FS.close(0);

	/*
	 * Test reading
	 */
	FS.open(file1, 'r');
	//int num = FS.read(0, strlen(test1), test1);
	// TODO what's going on here?
    int num = FS.read(0, strlen(test3), test);
	FS.close(0);

	memset(test, 0, 256);

	FS.open(file2, 'r');
	//int g = FS.read(0, strlen(test1), test1);
	// TODO what's going on here?
	int g = FS.read(0, strlen(test1), test);
	FS.close(0);
	cout << "\nclosing\n" << endl;
	/*
	 * Test deleting files
	 */
	FS.deleteFile(file2);
	cout << "Deleted first file" << endl;
	FS.deleteFile(file1);
	cout << "Deleted another file" << endl;
//
//	/*
//	 * Write again (???)
//	 */
//	memset(test1, 0, 256);
//
//	FS.open(file3, 'w');
//	num1 = FS.write(0, strlen(test1), test1);
//	num2 = FS.write(0, strlen(test2), test2);
//
//	FS.open(file3, 'r');
//	num = FS.read(0, FS.getNumChars(0), test1);
//	FS.close(0);
//
//	FS.open(file1, 'w');
//
//
//	 cout << "chars written = " << num << endl;



}
