#ifndef BMP_FILE_H
#define BMP_FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <math.h>


class bmp_file
{
    public:
        bmp_file();
        virtual ~bmp_file();

        bmp_file(std::string filepath);
        void writeToNewFile(std::string filepath);
        void histogram_equalization(std::string filepath);
        unsigned long getFileSize();
        unsigned long getStartOfBitmap();
        unsigned long getWidth();
        unsigned long getHeight();
        void printData();
        void printColorPalette();

    protected:

    private:
        unsigned long get32(int LSBindex);
        std::vector<uint8_t> fileData;
};




struct accumulator
{
    public:
        accumulator(uint8_t _color)
        {
            color = _color;
            counter = 0;            ///first occurrence of that color so set to 1
        }
        int counter;
        int cCounter;   ///cumulative count
        uint8_t color;
        uint8_t newColor;
        double cPercent;       /// cumulative percent

    private:

};

/*bool ColorCompare(accumulator a, accumulator b)
{
    return (a.color > b.color);
};*/

#endif // BMP_FILE_H

//        unsigned long getHeaderSize();
//        void setFileSize(unsigned long fileSize);
//        void setStartOfBitmap(unsigned long startOfBitmap);
//        void setHeaderSize( unsigned long headerSize);
//        void setWidth(unsigned long width);
//        void setHeight(unsigned long height);
//
//        unsigned short getBM();
//
//        unsigned short getPlanes();
//        void setPlanes(unsigned short planes);
//
//        unsigned long getCompression();
//        void setCompression(unsigned long compression);
//
//        unsigned long getCompressionSize();
//        void setCompressionSize(unsigned long compressionSize);
//
//        unsigned long getHorizontalResolution();
//        void setHorizontalResolution(unsigned long horizontalResolution);
//
//        unsigned long getVerticalResolution();
//        void setVerticalResolution(unsigned long verticalResolution);
//
//        unsigned long getNumberOfColorsInPalette();
//        void setNumberOfColorsInPalette(unsigned long numberOfColorsInPalette);
//
//        unsigned long getImportantColors();
//        void setImportantColors(unsigned long importantColors);
