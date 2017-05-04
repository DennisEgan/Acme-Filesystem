#include <iostream>
#include "Directory.h"

int main()
{
	Directory* d = new Directory("dummy");
	Directory* dd = new Directory();

	cout << d->getSize() << endl;
	cout << dd->getName() << endl;
	dd->setName("DUH");
	cout << dd->getName() << endl;

	// Test simple setters and getters
	cout << "Hello " << d->getName() << endl;

	d->setName("new dummy");
	cout << "Hello " << d->getName() << " & " << d->getSize() << endl;

	string file_name = "fresh_file.txt";
	cout << d->createFile(file_name) << endl;
	cout << d->getSize() << endl;
	cout << d->containsFile(file_name) << endl;

	cout << "Attempting to re-add " << file_name
		 << " : " << d->createFile(file_name) << endl;

	d->deleteFile(file_name);
	cout << d->getSize() << endl;
	cout << d->containsFile(file_name) << endl;

	d->createFile(file_name);
	FCB* fromDir = d->getFile(file_name);
	cout << fromDir->getFileName() << endl;

	int size = 4;
	string dummies[size] = {"a", "b", "c", "d"};
	for(int i = 0; i < size; i++)
		d->createFile(dummies[i]);

	vector<FCB*> files = d->getFiles();
	for(auto it = files.begin(); it != files.end(); it++)
		cout << (*it)->getFileName() << endl;

	cout << "\nDeleting b...\n";
	d->deleteFile("b");
	cout << d->containsFile("b") << endl;
	files = d->getFiles();
	for(auto it = files.begin(); it != files.end(); it++)
		cout << (*it)->getFileName() << endl;


	cout << "GOT: " << d->getFile("a")->getFileName() << endl;
	delete d;
}

