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

	string eqBuf = string(50,'=');
	cout << eqBuf << "\n\nCreating files\n\n" << eqBuf << "\n\n";
	// Create files
	string hello = "hello.txt",
		   goodbye = "goodbye.txt",
		   hola = "HOLA.txt";

	cout << FS.create(hello) << " & "
	     << FS.create(goodbye) << " & "
		 << FS.create(hola) << endl;
		
	/*
	 * Test writing to files
	 */
	char test1[] = "Hello";
	char test2[] = ", We are group 1. ";
	char test3[] = "This is a test sentence.";
	char test4[] = ". \n";
	char test5[] = "Still Appending to a fi";
	char test6[] = "le. Bye! And now I am trying to cause the disk to run out of space itshouldstophere blaaaaaaaaaa";
	char test7[] = "bitshouldstop";
	char test[256];

	cout << "\n\n" << eqBuf << "\n\nTest writing files\n\n" << eqBuf << "\n\n";

	cout << "\nOpening and writing to " << hello << endl;

	if(FS.open(hello, 'w') != -1) {
		int num1 = FS.write(0, strlen(test1), test1);
		FS.close(0);
	}
	else
		cerr << "Error when opening and writing to " << hello << endl;

	cout << "\nOpening and writing to " << goodbye << endl;
	if(FS.open(goodbye, 'w') != -1) {
		int num2 = FS.write(0, strlen(test2), test2);
		FS.close(0);
	}
	else
		cerr << "Error when opening and writing to " << goodbye << endl;

	cout << "\nOpening and writing to " << hola << endl;
	if(FS.open(hola, 'w') != -1) {
		int num3 = FS.write(0, strlen(test3), test3);
		FS.close(0);
	}
	else
		cerr << "Error when opening and writing to "<< hola << endl;
	/*
	 * Test writing again (???)
	 */

	cout << "\n\n" << eqBuf << "\n\nTest writing to files (again) \n\n" << eqBuf << "\n\n";

	cout << "\nOpening and writing to " << hola << endl;
	if(FS.open(hola, 'w') != -1) {
		int num4 = FS.write(0, strlen(test4), test4);
		int num5 = FS.write(0, strlen(test5), test5);
		int num6 = FS.write(0, strlen(test6), test6);
		int num7 = FS.write(0, strlen(test7), test7);
		FS.close(0);
	}
	else
		cerr << "Error opening and writing to " << hola << endl;

	cout << "\nOpening and writing to " << hello << endl;
	if(FS.open(hello, 'w') != -1) {
		int num3 = FS.write(0, strlen(test3), test3);
		FS.close(0);
	}
	else
		cerr << "Error when opening and writing to " << hello << endl;
	/*
	 * Test reading
	 */

	cout << "\n\n" << eqBuf << "\n\nTest reading from files\n\n" << eqBuf << "\n\n";

	cout << "\nOpening and reading " << hello << endl;
	if(FS.open(hello, 'r') != -1){
		int num = FS.read(0, strlen(test1), test1);
		FS.close(0);
	}
	else
		cerr << "Error opening " << hello << endl;

	// TODO what's going on here?
//     int num = FS.read(0, FS.getNumChars(0), test);

	memset(test, 0, 256);

	cout << "\nOpening and reading " << goodbye << endl;
	FS.open(goodbye, 'r');
	int g = FS.read(0, strlen(test1), test1);
	// TODO what's going on here?
	g = FS.read(0, strlen(test1), test);
	FS.close(0);
	cout << "\nclosing\n" << endl;
	/*
	 * Test deleting files
	 */

	cout <<"\n\n" << eqBuf << "\n\nTest deleting files\n\n" << eqBuf << "\n\n";
	FS.deleteFile(goodbye);
	cout << "Deleted first file" << endl;
	FS.deleteFile(hello);
	cout << "Deleted another file" << endl;

//
//	/*
//	 * Write again (???)
//	 */
//	memset(test1, 0, 256);
//
//	FS.open(hola, 'w');
//	num1 = FS.write(0, strlen(test1), test1);
//	num2 = FS.write(0, strlen(test2), test2);
//
//	FS.open(hola, 'r');
//	num = FS.read(0, FS.getNumChars(0), test1);
//	FS.close(0);
//
//	FS.open(hello, 'w');
//
//
//	 cout << "chars written = " << num << endl;



}
