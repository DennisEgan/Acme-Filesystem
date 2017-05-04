#include <string>
#include <iostream>
using namespace std;
// using std::string;

#ifndef FCB_H
#define FCB_H

class FCB{

public:
	FCB();
	FCB(string name);
	FCB(const FCB &);
	~FCB();

	const FCB& operator=(const FCB &);

	FCB(int, int, string);

	string getFileName();
	
	int  getBlockPointer();
	void setBlockPointer(int);
	
	int  getSize();
	void setSize(int);
	
	int  getBlockSize();
	void setBlockSize(int);
	
	int  getFileEnd();
	void setFileEnd(int);
	
	bool setMode(char);
	char getMode();

	void setFileName(string);
	void print();


private:
	char mode;
	int size;
	int blockSize;
	int blockPointer;
	int fileEnd;
	string fileName;
};

#endif
