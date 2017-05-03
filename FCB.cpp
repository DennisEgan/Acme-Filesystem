//Author: Justin Lesko
//File Control Block implementation file

#include "FCB.h"
#include <iostream>
using namespace std;

FCB::FCB(){
	size = 0;
	blockSize = 0;
	blockPointer = -1;
	fileEnd = -1;
	fileName = "";
}
FCB::FCB(const FCB &toCopy){
	*this = toCopy;
}
FCB::FCB(int s, int b, string name){
	size = s;
	blockSize = 0;
	blockPointer = b;
	fileEnd = -1;
	fileName = name;
}
const FCB& FCB::operator=(const FCB &right){
	this->size = right.size;
	this->blockPointer = right.blockPointer;
	this->blockSize = right.blockSize;
	this->fileName = right.fileName;
	this->fileEnd = right.fileEnd;
	return (*this);
}
int FCB::getBlockPointer(){ return blockPointer; };
void FCB::setBlockPointer(int a){ blockPointer = a; };
int FCB::getBlockSize(){ return blockSize; };
void FCB::setBlockSize(int a){ blockSize = a; };
int FCB::getSize(){ return size; };
void FCB::setSize(int a){ size = a; };
int FCB::getFileEnd(){ return fileEnd; };
void FCB::setFileEnd(int a){ fileEnd = a; };
string FCB::getFileName(){ return fileName; };

void FCB::print(){
	cout << "------------------------" << endl;
	cout << "fileName: " << fileName << endl;
	cout << "------------------------" << endl;
	cout << "size: " << size << endl;
	cout << "blockPointer: " << blockPointer << endl;	
	cout << "fileEnd: " << fileEnd << endl;
	cout << "number of blocks: " << blockSize << endl;
	cout << "------------------------" << endl;
	cout << endl;

	
}
