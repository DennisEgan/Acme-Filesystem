/*
 * UI.cpp
 *
 * Implementation of UI for Acme ATOS FileSystem class
 *
 * Lead authors:
 *  Dennis Egan & Justin Lesko
 *
 */
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include "UI.h"
using namespace std;

#define MAX_STRING 100 // Disk of 10 blocks, of size 10 chars there MAX_STRING = 100
#define MAX_ARGS 2

vector<string> splitbystring(string , string );

/*
 * Constructor
 */
UI::UI(){

}

/*
 * Deconstructor
 */
UI::~UI(){

}

/*
 * Print directory
 */
void UI::dir() {
	FS.printDir();
}

/*
 * Create file in FS of name fileName
 * :param fileName: name of file to create
 */
bool UI::create(string fileName) {
	FS.create(fileName);	
}

/*
 * Edit file of name fileName
 * :param fileName: name of file to edit
 */
bool UI::edit(string fileName) {

	if(!FS.containsFile(fileName))
		return false;
	
	cout << endl;                       // One line padding for input

	// Loop until EOF or MAX_STRING length exceeded
	string typeInput = "";
	while (!cin.eof()) {

		// Get input
		string newInput;
		getline(cin, newInput);

		// If within valid length, append to current string
		if (strlen(newInput.c_str()) + strlen(typeInput.c_str()) > MAX_STRING)
			break;
		else {
			if(typeInput == "")
				typeInput = newInput;
			else
				typeInput = typeInput + "\n" + newInput;

		}
	}

	// Clean up a bit
	cin.clear();
	cout << endl;

	// Write to file
	if (FS.open(fileName, 'w') != -1) {
		char *buffer = (char *) typeInput.c_str();
		int writtenChars = FS.write(fileName, buffer);

		buffer = NULL;

		if (!FS.close(fileName))
			cerr << "Error when closing " << fileName << endl;

	} else {
		cerr << "Error when opening " << fileName << endl;
	}
}

/*
 * Print out contents of file fileName
 * :param fileName: name of file to print contents of
 */
bool UI::type(string fileName) {
	
	if(!FS.containsFile(fileName))
		return false;
	
	// File opened successfully
	if (FS.open(fileName, 'r') != -1) {
	
		FS.read(fileName);	// Write to file

		cout << endl;			// Padding

		// Check if file closed properly
		if(!FS.close(fileName)){
			cerr << "Error when closing " << fileName << endl;
		}

	} 
		
	// Error when opening file
	else {
		cerr << "Error when opening " << fileName << " in read mode.\n";
	}	
}

/*
 * Delete file of name fileName
 * :param fileName: name of file to delete
 */
bool UI::deleteFile(string fileName) {
	if(!FS.deleteFile(fileName)) {
		cerr << "Error when deleting " << fileName << endl;
	}
}

/*
 * Main run loop for UI
 */
void UI::run() {

	/*
	 * Initialize variables
	 */
	char userInput[MAX_STRING];
	bool keepGoing = true;
	string input;
	vector<string> args;

//	FileSystem FS;

	/*
	 * Main input loop
	 */
	while (keepGoing && !cin.eof()){
		cout << "$$ ";
		getline(cin, input);
		cin.clear();
		args = splitbystring(input, " ");

		// Commands that take two arguments
		if (args[0] == "EXIT"){
			keepGoing = false;
		}
		else if (args[0] == "DIR") {
			dir();
		}

		// Commands that take two arguments
		else if(args.size() == 2) {
			if (args[0] == "CREATE") {
				create(args[1]);

			} else if (args[0] == "TYPE") {
				type(args[1]);

			} else  if(args[0] == "EDIT") {
				edit(args[1]);

			} else if(args[0] == "DELETE") {
				deleteFile(args[1]);
			}

		}
		else{
			cout << "Invalid input.\n";
		}
	}

}

vector<string> splitbystring(string token, string delim){
	int left = 0;
	vector<string>ret_vec;
	std::size_t found = token.find(delim);

	if (found > token.size() + 1){
		ret_vec.push_back(token);
		return ret_vec;
	}

	if(found != std::string::npos){
		ret_vec.push_back(token.substr(left, found-left));
		left = found+delim.size();
	}	
	while(found != std::string::npos){
		found = token.find(delim, found+1);
		ret_vec.push_back(token.substr(left, found-left));
		left = found+delim.size();
	}
	return ret_vec;
}
