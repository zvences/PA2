// CS 3377.0W1 Programming Assignment 2
// zxv160130
// Zoraida Vences

// This program accepts the absolute path of a directory
// in a UNIX file system. It will traverse the given
// directory and separately count 1) the total number of
// directories (including given directory), 2) the total
// number of plain files, and 3) the total number of
// bytes occupied by those plain files. After traversing
// the directory, it will the display the results in the
// following format:
// The total number of directories in directory <given directory> is: aaa.
// The total number of files in directory <given directory> is:  bbb.
// The total number of bytes occupied by all files in directory <given directory> is:  ccc.

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// function traverses directories and stores names of files found
int getdir (string dir, vector<string> &files)
{
    // variables
    DIR *dp;
    struct dirent *dirp;

    // returns error if directory can't be opened
    if((dp  = opendir(dir.c_str())) == NULL) {
        return errno;
    }

    // separates results of opening directories
    while ((dirp = readdir(dp)) != NULL) {
        if (string(dirp->d_name)== "."){
                // ignores '.' files
        }else if (string(dirp->d_name)== ".."){
            // ignores '..' files
        }else{
            // appends '/' to create full path name
            string pathName = (dir +"/"+ string(dirp->d_name));
            // adds name to vector of files/directories
            files.push_back(pathName);
        }

    }
    closedir(dp);
    return 0;
}

// function calculates file size
long GetFileSize(string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

int main(int argc, char* argv[])
{
    // variables
    string dir = string(".");
    vector<string> files = vector<string>();

    int fileCount = 0;
    int dirCount = 0;
    long fileSize = 0;

    // determines whether argument is passed
        // during execution or after
    if (argc >= 2){
        dir = argv[1];
    }
    else{
        getline(cin, dir);
    }

    // getdir returns errors in opening
        // directories. if no error is found,
        // path checked was a directory
        // otherwise it is a file
    if (getdir(dir,files) == 0)
    {
        dirCount++;
    }else{
        fileCount++;
    }

    // recursively searches all available directories
        // and their files
    for (unsigned int i = 0;i < files.size(); i++) {
        // dirVal determines if directory or not
        int dirVal = getdir(files[i], files);

        if (dirVal == 0)
        {
            dirCount++;
        }
        else{ // if path is a file, increase count
                // and determine size
            fileSize += GetFileSize(files[i]);
            fileCount++;
        }

    }

    // display result

    cout << "The total number of directories in directory " << dir << " is " << dirCount << endl;

    cout << "The total number of files in directory " << dir << " is " << fileCount << endl;

    cout << "The total number of bytes occupied by all file in directory " << dir << " is " << fileSize << endl;


    return 0;
}
