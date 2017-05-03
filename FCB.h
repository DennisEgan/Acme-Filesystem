#include <string>
using std::string;

#ifndef FCB_H
#define FCB_H

#define F_CLOSE -1
#define F_READ	 0
#define F_WRITE  1

class FCB{
public:
	FCB();
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
	
	void print();


private:
	int size;
	int blockSize;
	int blockPointer;
	int fileEnd;
	int mode;
	string fileName;
};

#endif
