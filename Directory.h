/*
 * Directory.h
 *
 */
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <vector>
#include "FCB.h"

using namespace std;

class Directory
{
	public:

		// Constructors and Deconstructor
		Directory();
		Directory(string name);
		~Directory();

		// Getters and setters
		string getName();
		void   setName(string name);

		// Methods
		int 		 getSize();
		vector<FCB*> getFiles();
		FCB*		 getFile(string fileName);
		bool		 addFile(FCB* newFile);
		bool		 createFile(string fileName);
		bool 		 deleteFile(string fileName);
		bool 		 containsFile(string);

	private:
		string name;
		vector<FCB*> files;
};

#endif