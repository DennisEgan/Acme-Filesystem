#include <string>
using std::string;

#ifndef FCB_H
#define FCB_H

class FCB{
public:
	FCB();
	FCB(const FCB &);
	const FCB& operator=(const FCB &);
	FCB(int, int, string);
	void setFileName(string);
	string getFileName();
	int getBlockPointer();
	void setBlockPointer(int);
	int getSize();
	void setSize(int);
	int getBlockSize();
	void setBlockSize(int);
	int getFileEnd();
	void setFileEnd(int);
	void print();


private:
	int size;
	int blockSize;
	int blockPointer;
	int fileEnd;
	string fileName;

};
#endif
