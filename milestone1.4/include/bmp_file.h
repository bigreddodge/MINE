#ifndef BMP_FILE_H
#define BMP_FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>


class bmp_file
{
    public:
        bmp_file();
        virtual ~bmp_file();

        bmp_file(std::string filepath);
        void writeToNewFile(std::string filepath);
        void histogram_equalization();
        unsigned long getFileSize();
        unsigned long getStartOfBitmap();
        unsigned long getWidth();
        unsigned long getHeight();
        void printData();

    protected:

    private:
        unsigned long get32(int LSBindex);
        std::vector<unsigned char> fileData;
};

bool ColorCompare(accumulator a, accumulator b)
{
    return (a.color > b.color);
}

struct accumulator
{
    public:
        accumulator(unsigned char _color)
        {
            color = _color;
            counter = 0;
        }
        int counter;
        uint8_t color;

    private:

};

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
