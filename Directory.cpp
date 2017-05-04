#include "Directory.h"
#include "FCB.h"
#include <iostream>
#include <vector>
using namespace std;

Directory::Directory(){
	name = "";
}

Directory::Directory(string name){ name = name; }

// Delete all files in directory
Directory::~Directory()
{
	for(auto it  = files.begin(); it != files.end(); it++)
		delete *it;
	
	files.clear();
}


string 		 Directory::getName(){ return name; }
void   		 Directory::setName(string name){ name = name;}
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
		FCB* newFile = new FCB();
		newFile->setFileName(fileName);
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
			files.erase(files.begin()+1);
			delete *it;
			return true;
		}
	}

	return false;
}

// Methods
FCB* Directory::getFile(string name)
{
	for(auto it = files.begin(); it != files.end(); it++)
	{
		if((*it)->getFileName() == name)
			return *it;
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
