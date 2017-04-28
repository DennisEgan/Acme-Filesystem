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
	blockPointer = b;
	fileName = name;
}
const FCB& FCB::operator=(const FCB &right){
	this->size = right.size;
	this->blockPointer = right.blockPointer;
	this->fileName = right.fileName;
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
	cout << "size = " << size << endl;
	cout << "blockPointer:" << blockPointer << endl;
	cout << "fileName: " << fileName << endl;
}
