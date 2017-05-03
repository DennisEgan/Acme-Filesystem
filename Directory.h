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

		// Methods
		vector<FCB*> getFiles();
		FCB*		 getFile(string name);
		bool		 addFile();
		bool 		 deleteFile();
		bool 		 containsFile(string name);

	private:
		string name;
		vector<FCB*> files;
};

#endif