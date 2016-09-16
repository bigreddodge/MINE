#include "../include/bmp_file.h"

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

bool ColorCompare(accumulator a, accumulator b)
{
    return ((unsigned int)a.color < (unsigned int)b.color);
};

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
    std::cout << "\n";
    while (!infile.eof())
    {
        infile.read(buffer, 1);
        //infile >> buffer;
        fileData.push_back(*buffer);
        counter++;
        //std::cout << buffer;
    }
    //get rid of extra byte
    fileData.pop_back();
}

void bmp_file::printColorPalette()
{
    /// Prints the color palette on the first 256 pixels of the image
    for (unsigned int i = getStartOfBitmap(); i < (getStartOfBitmap() + 256); i++)
    {
        fileData[i] = (uint8_t)i;
    }
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


void bmp_file::histogram_equalization(std::string filepath)
{
    ///Creating original histogram


    std::ofstream beforeFile;
    beforeFile.open("before.csv");
    std::ofstream afterFile;
    afterFile.open("after.csv");

    std::vector <accumulator> histogram;

    ///populate histogram with colors
    for (int i = 0; i < 256; i ++)
    {
        accumulator *temp = new accumulator(i);
            histogram.push_back(*temp);
    }

    for( unsigned int i = getStartOfBitmap(); i < fileData.size(); i++)
    {
        for (unsigned int j = 0; j < histogram.size(); j++)                 /// loop through file
        {
            if ( (unsigned int)histogram[j].color == (unsigned int)fileData[i] )                        /// if we have this color increment the count
            {
                histogram[j].counter++;
                break;
            }
        }
    }

    /*for(unsigned int i = 0; i < histogram.size(); i++)
    {
        outfile << i << "," << (unsigned int)histogram[i].color << "," << histogram[i].counter << std::endl;
    }*/

    /// Creating a cumulative histogram

    std::sort(histogram.begin(), histogram.end(), ColorCompare);

    /// i = 0 condition
    histogram[0].cCounter = histogram[0].counter;
    for(unsigned int i = 1; i < histogram.size(); i++)
    {
        histogram[i].cCounter = histogram[i].counter + histogram[i-1].cCounter;
    }               ///need to print in a file to plot

    for(unsigned int i = 0; i < histogram.size(); i++)
    {
        /// calculate cumulative percent
        histogram[i].cPercent = (double)histogram[i].cCounter / (double)histogram[histogram.size()-1].cCounter;
    }

    /// Histogram equalization

    for( unsigned int i = 0; i<histogram.size(); i++)
    {
        /// Calculate new color
        histogram[i].newColor = (uint8_t)floor(histogram[i].cPercent * 253) + 1 ; ///new color = percentile of cumulative * number of colors
    }

    for(unsigned int i = 0; i< histogram.size(); i++)
    {
        beforeFile << (unsigned int)histogram[i].color << ","
                << histogram[i].counter << std::endl;
        afterFile << (unsigned int)histogram[i].newColor << ","
                << histogram[i].counter << std::endl;
    }

    beforeFile.close();
    afterFile.close();

    ///write the Histogram Equalized data to this BMP_files data.
    for(unsigned int i = getStartOfBitmap(); i < fileData.size(); i++)
    {
        for (unsigned int j = 0; j < histogram.size(); j++)
        {
            if (fileData[i] == histogram[j].color)
            {
                fileData[i] = histogram[j].newColor;
                /*std::cout << "pixel: " << i << "\t"
                          << (unsigned int)fileData[i] << "\t"
                          << (unsigned int)histogram[j].color << "\t==>\t"
                          << (unsigned int)histogram[j].newColor << "\n";
                */
                break;
            }
        }
    }
    writeToNewFile(filepath);
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
