#include <vector>
#include <iostream>
#include <string>
#include "FileSystem.h"
using namespace std;

#define MAX_STRING 100 // Disk of 10 blocks, of size 10 chars
#define MAX_ARGS 2


vector<string> splitbystring(string , string );
int main(){
	char userInput[MAX_STRING];
	char ch;
	bool cont = true;
	string input;
	vector<string> args;

	FileSystem acmeFS;

	while (cont){
		cout << "$$";
		getline(cin, input);
		cin.clear();
		if (input.find_first_not_of(" \t\n\v\f\r") != std::string::npos && (!cin.eof())){
			args = splitbystring(input, " ");
			for (int i = 0; i < args.size(); i++){
				cout << i << ": " << args[i] << endl;
			}
			if (args[0] == "EXIT"){
				cont = false;
			}
			else if (args[0] == "DIR") {
				acmeFS.printDir();
			}
			
			else if(args.size() == 2) {
				if (args[0] == "CREATE") {
					acmeFS.create(args[1]);
				}
				else if (args[0] == "TYPE") {
					acmeFS.read(args[1]);

				}
				else if (args[0] == "EDIT"){
				memset(userInput, 0, MAX_STRING);
				cout << endl;
				string typeInput;
				while(!cin.eof()){
					string newInput;
					getline(cin, newInput);

					if(strlen(newInput.c_str())+strlen(typeInput.c_str()) > MAX_STRING)
						break;
					else
						typeInput = typeInput + newInput;
					cout << "TYPEINPUT " << typeInput << endl;
				}
				cin.clear();
				//while(EOF != scanf("%s", userInput));
	    		cout << endl;
	    		cout << "TYPEINPUT " << typeInput << endl;
	    		//printf("YOU INPUT: %s\n", userInput);
	    		int opened = acmeFS.open(args[1], 'w');
	    		char* buffer = (char*)typeInput.c_str();
	    		int writtenChars = acmeFS.write(args[1], buffer);
	    		bool closed = acmeFS.close(args[1]);

	    		opened = acmeFS.open(args[1], 'r');
	    		int charsRead = acmeFS.read(args[1]);
	    		closed = acmeFS.close(args[1]);

	    		return 0;

	    		}
			}

		}
		else{
			cout << "Invalid\n";
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
	cout << "found = " << found << endl;
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
