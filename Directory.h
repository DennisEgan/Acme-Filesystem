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
		void   setName();

		int    getSize();
		int    changeSize();

		string getFiles();

		// Methods
		vector<FCB*> getFiles();
		FCB*		 getFile();
		bool		 addFile();
		bool 		 removeFile();
		bool 		 containsFile(string name);

	private:
		int size;
		string name;
		vector<FCB*> files;
};

#endif