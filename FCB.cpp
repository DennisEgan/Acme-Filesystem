//Author: Justin Lesko
//File Control Block implementation file

#include "FCB.h"
#include <iostream>
using namespace std;

#define F_CLOSE -1
#define F_READ	 0
#define F_WRITE  1

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

FCB::~FCB()
{

}

const FCB& FCB::operator=(const FCB &right){
	this->size = right.size;
	this->blockPointer = right.blockPointer;
	this->blockSize = right.blockSize;
	this->fileName = right.fileName;
	this->fileEnd = right.fileEnd;
	return (*this);
}

int    FCB::getBlockPointer(){ return blockPointer; };
void   FCB::setBlockPointer(int a){ blockPointer = a; };
int    FCB::getBlockSize(){ return blockSize; };
void   FCB::setBlockSize(int a){ blockSize = a; };
int    FCB::getSize(){ return size; };
void   FCB::setSize(int a){ size = a; };
int    FCB::getFileEnd(){ return fileEnd; };
void   FCB::setFileEnd(int a){ fileEnd = a; };
string FCB::getFileName(){ return fileName; };

char getMode(){ return mode; }
bool setMode(char mode)
{
	if(mode == 'r'){
		mode = F_READ;
		return true;
	}
	else if(mode == 'w'){
		mode = F_WRITE;
		return true;
	}
	else if(mode == 'c'){
		mode = F_CLOSE;
		return true
	}
	else
		return false

}

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
