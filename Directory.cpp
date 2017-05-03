#include "Directory.h"
#include "FCB.h"
#include <iostream>
#include <vector>
using namespace std;

Directory::Directory(){
	size = 0;
}

Directory::Directory(string name)
{
	name = name;
	size = 0;
}

// Delete all files in directory
Directory::~Directory()
{
	for(auto iter  = files.begin(); iter != files.end(); iter++)
		delete *iter;
	
	files.clear();
}


string 		 Directory::getName(){ return name; }
void   		 Directory::setName(string name){ name = name;}
int    		 Directory::getSize(){ return files.size(); }
vector<FCB*> Directory::getFiles(){ return files; }

bool Directory::addFile(FCB* new_file)
{
	if(!containsFile(new_file->getName()))
		files.push_back(new_file);
}

bool Directory::deleteFile(string name)
{
	int i = 0;
	for(auto iter = files.begin(); iter != files.end(); iter++)
	{
		if(*iter->getName() == name)
		{
			files.erase(files.begin()+1);
			delete *iter;
			return true;
		}
	}

	return false
}

// Methods
FCB* Directory::getFile(string name)
{
	for(auto iter = files.begin(); iter != files.end(); iter++)
	{
		if(*iter->name == name)
			return *iter
	}

	return NULL;
}

bool Directory::containsFile(string name)
{
	if(getFile(name) != NULL)
		return true;
	else:
		return false;
}
