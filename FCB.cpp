/*
 * FCB.cpp
 *
 * File Control Block implementation file
 *
 * Lead author:
 *  Justin Lesko
 *
 * Contributors:
 *  Dennis Egan
 */

#include "FCB.h"
#include <iostream>
using namespace std;

/*
 * Constructor for class
 */
FCB::FCB(){
	size = 0;
	blockSize = 0;
	blockPointer = -1;
	fileEnd = -1;
	fileName = "";
	mode = 'c';
}

/*
 * Constructor to name FCB
 * :param name: name to give to FCB
 */
FCB::FCB(string name){
	size = 0;
	blockSize = 0;
	blockPointer = -1;
	fileEnd = -1;
	fileName = name;
	mode = 'c';
}

/*
 * Copy constructor
 */
FCB::FCB(const FCB &toCopy){
	*this = toCopy;
}

/*
 * Constructor to set name, size, and block pointer
 * :param s: size of FCB
 * :param b: block pointer size
 * :param name: name of FCB
 */
FCB::FCB(int s, int b, string name){
	size = s;
	blockSize = 0;
	blockPointer = b;
	fileEnd = -1;
	fileName = name;
	mode = 'c';
}

/*
 * Deconstructor
 */
FCB::~FCB()
{

}

/*
 * Overload of = operator
 */
const FCB& FCB::operator=(const FCB &right){
	this->size = right.size;
	this->blockPointer = right.blockPointer;
	this->blockSize = right.blockSize;
	this->fileName = right.fileName;
	this->fileEnd = right.fileEnd;
	this->mode = right.mode;
	return (*this);
}

/*
 * Setters and getters
 */
int    FCB::getBlockPointer(){ return blockPointer; };
void   FCB::setBlockPointer(int a){ blockPointer = a; };
int    FCB::getBlockSize(){ return blockSize; };
void   FCB::setBlockSize(int a){ blockSize = a; };
int    FCB::getSize(){ return size; };
void   FCB::setSize(int a){ size = a; };
int    FCB::getFileEnd(){ return fileEnd; };
void   FCB::setFileEnd(int a){ fileEnd = a; };
string FCB::getFileName(){ return fileName; };
void   FCB::setFileName(string name){ fileName = name; }

char FCB::getMode(){ return mode; };
bool FCB::setMode(char fMode)
{
	if(fMode == 'r' || fMode == 'w' || fMode == 'c')
	{
		mode = fMode;
		return true;
	}
	else
		return false;
};

/*
 * Print function for class
 */
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
