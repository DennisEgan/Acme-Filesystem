Directory::Directory(){
	size = 0;
}

Directory::Directory(string name)
{
	name = name;
	size = 0;
}

Directory::~Directory()
{
	vector<FCB*>::iterator iter;
	for(iter  = files.begin(); iter != files.end(); iter++)
		delete *iter;
	
	files.clear();
}


string 		 Directory::getName(){ return name; }
void   		 Directory::setName(string name){ name = name;}
int    		 Directory::getSize(){ return size; }
vector<FCB*> Directory::getFiles(){ return files; }

// If bytes < 0 then decrement. Else, increment
int Directory::changeSize(int bytes){ size += bytes; }

// Methods
FCB* Director::getFile(string name)
{
	vector<FCB*>::iterator iter;
	for(iter = files.begin(); iter != files.end(); iter++)
	{
		if(*iter->name == name)
			return *iter
	}
}

bool Directory::addFile(FCB* new_file)
{
	// Use getFile to determine if new file should be added
	vector<FCB*>::iterator iter;
	for(iter = files.begin(); iter != files.end(); iter++)
	{
		if(*iter->name == new_file->name)
			return false

	}

	files.push_back(new_file);
}

bool removeFile(string name)
{
	for(int i = 0; i < files.size(); i++)
	{
		if(files[i]->getName() == name)
		{
			files.erase(files.begin()+i);
			return true
		}
	}

	return false
}

bool containsFile(string name)
{
	if(getFile(name) != files.end())
		return true;
	else:
		return false;
}
