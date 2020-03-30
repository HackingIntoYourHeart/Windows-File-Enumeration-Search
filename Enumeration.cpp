#include <windows.h>
#include <iostream>
#include <sys/stat.h>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

bool isFile(const char* path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISREG(buf.st_mode);
}

bool isDir(const char* path) {
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}

bool in(string input, string command){

	if (input.find(command) != std::string::npos){
	
		return true;
	
	}else{
	
		return false;
	
	}

}

string tolower(string s) {
	transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
	return s;
}

bool parseFile(string path, string term){
	
	std::ifstream file(path);
	std::string str; 
	while (std::getline(file, str))
	{
		if ( in(str, term) ){
			return true;
		}
	}
	
	return false;

}

string enumerateFiles(string DIR, string term){

	string data = "";

	string File;
	
	string star = "*";
	string main = (DIR + star);

	WIN32_FIND_DATA file;
	HANDLE search_handle=FindFirstFile(main.c_str(),&file);

	if (search_handle){

		while( FindNextFile(search_handle,&file) ){

			File = DIR + file.cFileName;
			
			if ( (isFile( File.c_str() )) && (parseFile(File, term)) ){
			
				data += (File + "\n");
				cout << File << endl;
			
			}else if ( isDir( File.c_str() ) ){

				if ( (!(in(File, ".."))) ){
					data += enumerateFiles(File + "\\", term);
				}
			
			}

		}

		FindClose(search_handle);

	}
	
	return data;

}

string raw_input(string text){

	cout << text;
	string input;
	cin >> input;
	return input;

}
			
int main(){

	cout << enumerateFiles( raw_input("Dir: "), raw_input("Term: ") );

}
