#include "bmp_file.h"

#include <iostream>

/** BMP Header Information
 * Note: All element indices are 0-based
 * File Header:
 *   Filesize: bytes 2-5
 *   Offset: bytes 10-13
 * DIB Header:
 *   Width: bytes 18-21
 *   Height: bytes 22-25
 */

bmp_file::bmp_file()
{
    //ctor
}

bmp_file::bmp_file(std::string filepath)
{
    std::ifstream infile;
    infile.open(filepath.c_str(), std::ifstream::in | std::ifstream::binary);

    char * buffer = new char [1];
    int counter = 0;
    std::cout << "\n\n";
    while (!infile.eof())
    {
        infile.read(buffer, 1);
        //infile >> buffer;
        fileData.push_back(*buffer);
        counter++;
        std::cout << buffer;
    }
    std::cout << "\n\nLoop counter: " << counter << std::endl;
}

bmp_file::~bmp_file()
{
    //dtor
}

void bmp_file::writeToNewFile(std::string filepath)
{
    std::ofstream outFile;
    outFile.open(filepath.c_str(), std::ofstream::out | std::ofstream::binary);

    char * buffer = new char [1];
    for (unsigned int i = 0; i < fileData.size(); i++)
    {
        *buffer = fileData[i];
        outFile.write(buffer,1);
    }
}

void bmp_file::printData()
{
    std::cout << "\nFilesize: " << getFileSize();
    std::cout << "\nOffset: " << getStartOfBitmap();
    std::cout << "\nWidth: " << getWidth();
    std::cout << "\nHeight: " << getHeight();
    std::cout << "\nVector Size: " << fileData.size();


}

unsigned long bmp_file::getFileSize(){return get32(2);}
unsigned long bmp_file::getStartOfBitmap(){return get32(10);}
unsigned long bmp_file::getWidth(){return get32(18);}
unsigned long bmp_file::getHeight(){return get32(22);}

unsigned long bmp_file::get32(int LSBindex)
{
    return (unsigned long) (((unsigned long)fileData[LSBindex + 3]) << 24) | (((unsigned long)fileData[LSBindex + 2]) << 16) | (((unsigned long)fileData[LSBindex + 1]) << 8) | ((unsigned long)fileData[LSBindex]);
}

//unsigned long bmp_file::getHeaderSize(){}
//
//unsigned short bmp_file::getPlanes(){}
//void bmp_file::setPlanes(unsigned short planes){}
//
//unsigned long bmp_file::getCompression(){}
//void bmp_file::setCompression(unsigned long compression){}
//
//unsigned long bmp_file::getCompressionSize(){}
//void bmp_file::setCompressionSize(unsigned long compressionSize){}
//
//unsigned long bmp_file::getHorizontalResolution(){}
//void bmp_file::setHorizontalResolution(unsigned long horizontalResolution){}
//
//unsigned long bmp_file::getVerticalResolution(){}
//void bmp_file::setVerticalResolution(unsigned long verticalResolution){}
//
//unsigned long bmp_file::getNumberOfColorsInPalette(){}
//void bmp_file::setNumberOfColorsInPalette(unsigned long numberOfColorsInPalette){}
//
//unsigned long bmp_file::getImportantColors(){}
//void bmp_file::setImportantColors(unsigned long importantColors){}
