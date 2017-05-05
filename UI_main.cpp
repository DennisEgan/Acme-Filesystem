#include <vector>
#include <iostream>
#include <string>
#include "FileSystem.h"
using namespace std;

#define MAX_STRING 128
#define MAX_ARGS 2


vector<string> splitbystring(string , string );
int main(){
	bool cont = true;
	string input;
	vector<string> args;

	FileSystem acmeFS;

	while (cont){
		cout << "$$";
		getline(cin, input);
		args = splitbystring(input, " ");
		for (int i = 0; i < args.size(); i++){
			cout << i << ": " << args[i] << endl;
		}

		if (args[0] == "EXIT"){
			cont = false;
		}else if (args[0] == "DIR") {
			acmeFS.printDir();

		} else if(args[0] == "EDIT") {

		}
		else if(args.size() == 2) {
			if (args[0] == "CREATE") {
				acmeFS.create(args[1]);

			} else if (args[0] == "TYPE") {
				acmeFS.read(args[1]);

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
