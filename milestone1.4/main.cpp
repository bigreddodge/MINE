#include <iostream>
#include <fstream>
#include <bmp_file.h>
void writeTest();
using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 2) {
        cout << "opening " << argv[1] << "...\n";
        bmp_file myFile(argv[1]);
        myFile.printData();
        myFile.writeToNewFile("output.bmp");
    }
    else if (argc == 3){    /// Primary function
        cout << "processing " << argv[1] << "...\n";
        bmp_file myFile(argv[1]);
        cout << "saving to " << argv[2] << "...\n";
        myFile.writeToNewFile(argv[2]);
        cout << "complete.\n";
    }
    else if (argc > 3) {
        //process command line options
    }
    else {
        //cout << "\nSyntax: " << argv[0] << " <inputfile.bmp> <overlay.bmp>";
        //cout << "\n  Operation will create input inputfile_io.bmp & inputfile_he.bmp.\n";
        cout << "\nWriting test file...\n";
        writeTest();
    }
    return 0;
}
void writeTest()
{
    std::ofstream outFile;
    outFile.open("testfile.bbb", std::ofstream::out | std::ofstream::binary);
    vector<unsigned char> test;

    for (int i = 65; i < (65+26); ++i)
        test.push_back((char)i);


    char * buffer = new char [1];
    for (unsigned int i = 0; i < test.size(); i++)
    {
        *buffer = test[i];
        outFile.write(buffer,1);
    }
}
