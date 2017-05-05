/*
 * UI_main.cpp
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
#include "FileSystem.h"
using namespace std;

#define MAX_STRING 100 // Disk of 10 blocks, of size 10 chars there MAX_STRING = 100
#define MAX_ARGS 2


vector<string> splitbystring(string , string );
int main(){

	/*
	 * Initialize variables
	 */
	char userInput[MAX_STRING];
	bool keepGoing = true;
	string input;
	vector<string> args;

	FileSystem acmeFS;

	/*
	 * Main input loop
	 */
	while (keepGoing && !cin.eof()){
		cout << "$$ ";
		getline(cin, input);
		cin.clear();
		args = splitbystring(input, " ");

//		for (int i = 0; i < args.size(); i++){
//			cout << i << ": " << args[i] << endl;
//		}

		// Commands that take two arguments
		if (args[0] == "EXIT"){
			keepGoing = false;
		}
		else if (args[0] == "DIR") {
			acmeFS.printDir();
		}

		// Commands that take two arguments
		else if(args.size() == 2) {
			if (args[0] == "CREATE") {
				acmeFS.create(args[1]);

			} else if (args[0] == "TYPE" && acmeFS.containsFile(args[1])) {
				if (acmeFS.open(args[1], 'r') != -1) {
					acmeFS.read(args[1]);

					if(!acmeFS.close(args[1])){
						cerr << "Error when closing " << args[1] << endl;
					}

				} else {
					cerr << "Error when opening " << args[1] << " in read mode.\n";
				}

			} else  if(args[0] == "EDIT" && acmeFS.containsFile(args[1])) {

				cout << endl;                       // One line padding for input

				// Loop until EOF or MAX_STRING length exceeded
				string typeInput;
				while (!cin.eof()) {

					// Get input
					string newInput;
					getline(cin, newInput);

					// If within valid length, append to current string
					if (strlen(newInput.c_str()) + strlen(typeInput.c_str()) > MAX_STRING)
						break;
					else
						typeInput = typeInput + "\n" + newInput;
				}

				// Clean up a bit
				cin.clear();
				cout << endl;

				// Write to file
				if (acmeFS.open(args[1], 'w') != -1) {
					char *buffer = (char *) typeInput.c_str();
					int writtenChars = acmeFS.write(args[1], buffer);

					buffer = NULL;

					if (!acmeFS.close(args[1]))
						cerr << "Error when closing " << args[1] << endl;
				} else {
					cerr << "Error when opening " << args[1] << endl;
				}

			} else if(args[0] == "DELETE" && acmeFS.containsFile(args[1])) {
				if(!acmeFS.deleteFile(args[1])) {
					cerr << "Error when deleting " << args[1] << endl;
				}
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
