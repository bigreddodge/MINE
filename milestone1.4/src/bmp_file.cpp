#include "../include/bmp_file.h"
#include <iostream>

/** BMP Header Information
 * Note: All element indices are 0-based
 * File Header:
 *   File size: bytes 2-5
 *   Offset: bytes 10-13
 * DIB Header:
 *   Width: bytes 18-21
 *   Height: bytes 22-25
 */

bool ColorCompare(accumulator a, accumulator b)
{
    return ((unsigned int)a.color < (unsigned int)b.color);
};

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
    while (!infile.eof())
    {
        infile.read(buffer, 1);
        fileData.push_back(*buffer);
    }
    //get rid of extra byte
    fileData.pop_back();
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

/**< Gets count of all colors used [0 to 255] and then calculates a new color for each color, overwrites 
     this bitmap to the new colors pixel by pixel and out puts the resulting bitmap to filepath */
void bmp_file::histogram_equalization(std::string filepath)
{
    /// Preping files for csv output of data before and after algorithim runs
    /**
    std::ofstream beforeFile;
    beforeFile.open("before.csv");
    std::ofstream afterFile;
    afterFile.open("after.csv");
    */

    ///Creating histogram counting vector
    std::vector <accumulator> histogram;

    /// Populate histogram with greyscale colors, each count at 0
    for (int i = 0; i < 256; i ++)
    {
        accumulator *temp = new accumulator(i);
        histogram.push_back(*temp);
    }

    /// Populate the histogram with data from the bitmap, increment the appropriate counter for each pixel
    for( unsigned int i = getStartOfBitmap(); i < fileData.size(); i++)
    {
        for (unsigned int j = 0; j < histogram.size(); j++)                 /// loop through file
        {
            if ( (unsigned int)histogram[j].color == (unsigned int)fileData[i] )                        /// if we have this color increment the count
            {
                histogram[j].counter++;
                /// found, move on to next pixel
                break;
            }
        }
    }

    /// Sort by color 0 to 255
    std::sort(histogram.begin(), histogram.end(), ColorCompare);

    /// i = 0 condition: cumulative count = count of color 0
    histogram[0].cCounter = histogram[0].counter;
    for(unsigned int i = 1; i < histogram.size(); i++)
    {
        /// Each cumulative count is the colors count plus the previous cumulative count
        histogram[i].cCounter = histogram[i].counter + histogram[i-1].cCounter;
    }

    for(unsigned int i = 0; i < histogram.size(); i++)
    {
        /// calculate cumulative percent
        histogram[i].cPercent = (double)histogram[i].cCounter / (double)histogram[histogram.size()-1].cCounter;
    }

    /// Histogram equalization
    for(unsigned int i = 0; i<histogram.size(); i++)
    {
        /// New color = floor cumulative percent * number of available colors
        histogram[i].newColor = (uint8_t)floor(histogram[i].cPercent * 255) ; ///new color = percentile of cumulative * number of colors
    }

    /// Write to data files
    /**
    for(unsigned int i = 0; i< histogram.size(); i++)
    {
        beforeFile << (unsigned int)histogram[i].color << ","
                << histogram[i].counter << std::endl;
        afterFile << (unsigned int)histogram[i].newColor << ","
                << histogram[i].counter << std::endl;
    }

    beforeFile.close();
    afterFile.close(); */

    /// write the Histogram Equalized data to this BMP_files data.
    for(unsigned int i = getStartOfBitmap(); i < fileData.size(); i++)
    {
        for (unsigned int j = 0; j < histogram.size(); j++)
        {
            if ((uint8_t)fileData[i] == histogram[j].color)
            {
                fileData[i] = histogram[j].newColor;
                /// move to next pixel to only write new color once
                break;
            }
        }
    }
    /// Output results to new file
    writeToNewFile(filepath);
}