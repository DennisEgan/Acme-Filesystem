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

	FileSystem F1;
	F1.create("hello.txt");
	F1.create("GOODBYE.txt");
	F1.open("hello.txt", 'w');
	char test1[] = "Hello";
	char test2[] = ", my name is Justin Lesko";
	char test3[] = "This is a test sentence.";
	char test4[] = ". \n";
	char test5[] = "Still Appending to a fi";
	char test6[] = "le. Bye! And now I am trying to cause the disk to run out of space itshouldstophere blaaaaaaaaaa";
	char test7[] = "bitshouldstop";
	char test[256];
	int num1 = F1.write(0, strlen(test1), test1);
	int num2 = F1.write(0, strlen(test2), test2);
	F1.close(0);
	
	F1.open("GOODBYE.txt", 'w');
	int num3 = F1.write(0, strlen(test3), test3);
	F1.close(0);
	
	F1.open("hello.txt", 'w');
	int num4 = F1.write(0, strlen(test4), test4);
	int num5 = F1.write(0, strlen(test5), test5);
	int num6 = F1.write(0, strlen(test6), test6);
	int num7 = F1.write(0, strlen(test7), test7);
	//num3 = F1.write(0, strlen(test3), test3);
	//cout << endl << endl;
	//cout << "number of chars " << F1.getNumChars(0) << endl;
	int num = F1.read(0, F1.getNumChars(0), test);
	F1.close(0);
	memset(test, 0, 256);


	F1.open("GOODBYE.txt", 'w');
	int g = F1.read(0, F1.getNumChars(0), test);
	F1.close(0);

	// cout << "chars written = " << num << endl;



}
