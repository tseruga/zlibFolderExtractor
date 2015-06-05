#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include "/usr/include/zlib-1.2.8/zlib.h"

using namespace std;

vector<string> getFiles(string exeDir, string folderToUncomp);
void uncompressFile(string filepath, string filename, string folderToUncomp);

int main()
{

	//////////////FILL IN DIRECTORY OF YOUR EXECUTABLE HERE!///////////////
	string exeDir = "/home/tyler/Desktop/removeZ/";
	//////////////FILL IN NAME OF FOLDER TO UNCOMPRESS HERE!////////////////
	string folderToUncomp = "CrossSection";
	
	vector<string> files = getFiles(exeDir, folderToUncomp);

	if(files.size() == 0)
		return 0; //Exit if no files found in folder to uncompress

	for(auto i = 0; i < files.size(); i++) {
		uncompressFile(exeDir + folderToUncomp + "/", files[i], folderToUncomp);
	}
	cout << "Uncompression completed successfully :)" << endl;
}

vector<string> getFiles(string exeDir, string folderToUncomp) {
	vector<string> files;
	DIR *dir;
	struct dirent *ent;
	dir = opendir((exeDir+folderToUncomp).c_str());
	if ( dir != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			files.push_back(ent->d_name);
			if(files.back() == "." || files.back() == "..")
				files.pop_back();
		}
	closedir (dir);
	} else {
		cout << "ERROR! DIRECTORY COULD NOT BE LOCATED!" << endl;
	}

	return files;
}

void uncompressFile(string filepath, string filename, string folderToUncomp) {
	//Open stream at end and get length
	ifstream in((filepath+filename).c_str(), ios::binary | ios::ate);
	int compLength = in.tellg();

	//Reset ifstream
	in.seekg(0, in.beg);

	//Grab the compressed data
	Byte* compressed = new Byte[compLength];
	while(in.good()) {
		in.read((char*)compressed , compLength );
	}

	unsigned long int compSize = (unsigned long int) ( compLength*4 );
	Byte* uncompressed = new Byte[compSize];

	while (Z_OK != uncompress (uncompressed, &compSize , compressed , compLength)) {
		delete[] uncompressed;
		compSize *= 2; //Grow until big enough
		uncompressed = new Byte[compSize];
  	}
  	delete[] compressed;

	//Convert buffer to string
	string data( (char*)uncompressed , (long)compSize );
	
	//Get new filename
	string newFolder = folderToUncomp + "_";
	mkdir(newFolder.c_str(), S_IRWXU);

	//Erase the extension from the compressed filename (.z)
	filename.erase(filename.end()-1);
	filename.erase(filename.end()-1);

	//Print uncompressed to a new file
	string path = "./" + newFolder + "/" + filename;
	ofstream out(path);
	out << data;
}
