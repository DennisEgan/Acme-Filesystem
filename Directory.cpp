/*
 * Directory.cpp
 *
 * Implementation of Directory class in Directory.h
 *
 * Lead author:
 *  Dennis Egan
 *
 * Contributors:
 *  Justin Lesko
 *  Armando Califano
 */
#include "Directory.h"
#include "FCB.h"
#include <iostream>
#include <vector>
using namespace std;

Directory::Directory(){
	name = "";
}

Directory::Directory(string dirName){
    name = dirName;
}

// Delete all files in directory
Directory::~Directory()
{
	for(auto it  = files.begin(); it != files.end(); it++)
		delete *it;
	
	files.clear();
}


string 		 Directory::getName(){ return name; }
void   		 Directory::setName(string newName){ name = newName;}
int    		 Directory::getSize(){ return files.size(); }
vector<FCB*> Directory::getFiles(){ return files; }

bool Directory::addFile(FCB* newFile)
{
	if(!containsFile(newFile->getFileName()))
		files.push_back(newFile);
}

bool Directory::createFile(string fileName){

	if(!containsFile(fileName))
	{
		FCB* newFile = new FCB(fileName);

		files.push_back(newFile);
		return true;
	}
	else
		return false;
}

bool Directory::deleteFile(string name)
{
	int i = 0;
	for(auto it = files.begin(); it != files.end(); it++)
	{
		if((*it)->getFileName() == name)
		{
			files.erase(files.begin()+i);
			delete *it;
			return true;
		}

		i++;
	}

	return false;
}

// Methods
FCB* Directory::getFile(string name)
{
	if(!files.empty()){
		for (auto it = files.begin(); it != files.end(); it++) {
            if ((*it)->getFileName() == name){
				return *it;
			}
		}
	}
	return NULL;
}

bool Directory::containsFile(string name)
{
	if(getFile(name) != NULL)
		return true;
	else
		return false;
}
