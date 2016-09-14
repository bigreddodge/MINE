/** BMP Header Information
 * Note: All element indices are 0-based
 * File Header:
 *   File size: bytes 2-5
 *   Offset: bytes 10-13
 * DIB Header:
 *   Width: bytes 18-21
 *   Height: bytes 22-25
 */

#include "../include/bmp_file.h"
#include <iostream>

bmp_file::bmp_file(){/**< Default Constructor */}
bmp_file::~bmp_file(){/**< Default Destructor */}

/**< Creates an instance of bmp_file containing the specified file */
bmp_file::bmp_file(char* filepath) {
    std::ifstream infile;
    infile.open(filepath, std::ifstream::in | std::ifstream::binary);
    if (!infile){
        std::cout << "\nFile " << filepath << " not found.";
        return;
    } else {
        std::cout << "\nOpening " << filepath << "...";
    }
    char * buffer = new char [1];
    int counter = -1;
    while (!infile.eof()) {
        infile.read(buffer, 1);
        fileData.push_back(*buffer);
        counter++;
    }
    fileData.pop_back();
    std::cout << "\nBytes read: " << counter << std::endl;
}


/**< Writes the data in the bmp_file instance to the specified file */
void bmp_file::writeToNewFile(char* filepath) {
    std::ofstream outFile;
    outFile.open(filepath, std::ofstream::out | std::ofstream::binary);
    if (!outFile){
        std::cout << "\nUnable to write to " << filepath << ".";
        return;
    } else {
        std::cout << "\nWriting " << filepath << "...";
    }
    char * buffer = new char [1];
    for (unsigned int i = 0; i < fileData.size(); i++) {
        *buffer = fileData[i];
        outFile.write(buffer,1);
    }
}

/**< Returns the pixel data located in the specified file byte */
unsigned char bmp_file::getPixel(int index){
    return fileData[index];
}

/**< Writes a byte to the specified pixel */
void bmp_file::setPixel(int index, unsigned char byte){
    fileData[index] = byte;
}

/**< Outputs header data to the console using the std::cout stream */
void bmp_file::printData() {
    std::cout << "\nHeader data:";
    std::cout << "\n  Filesize: " << getFileSize();
    std::cout << "\n  Offset: " << getStartOfBitmap();
    std::cout << "\n  Width: " << getWidth();
    std::cout << "\n  Height: " << getHeight();
    std::cout << "\n  Vector Size: " << fileData.size();
}

/**< The following functions extract data from the bitmap header */
unsigned long bmp_file::getFileSize(){return get32(2);}
unsigned long bmp_file::getStartOfBitmap(){return get32(10);}
unsigned long bmp_file::getWidth(){return get32(18);}
unsigned long bmp_file::getHeight(){return get32(22);}
unsigned long bmp_file::getNumberOfColorsInPalette(){return get32(50);}

/**< Extracts a 32-bit unsigned long value from fileData beginning with element LSBindex */
unsigned long bmp_file::get32(int LSBindex){
    unsigned long temp = 0;
    for (int i = 3; i >=0; --i) {
        temp = (fileData[LSBindex+i] | temp << 8);
        temp |= fileData[LSBindex + i];
    }
    return temp;
}

/**< Graveyard */
