#ifndef BMP_FILE_H
#define BMP_FILE_H

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <math.h>

class bmp_file {
    public:
        bmp_file();                                  /**< Default constructor */
        virtual ~bmp_file();                         /**< Default destructor */

        /**< Creates an instance of bmp_file containing the specified file */
        bmp_file(char* filepath);

        /**< Writes the data in the bmp_file instance to the specified file */
        void writeToNewFile(char* filepath);
        /**< Histogram equalizes the image and writes it to the file specified in filepath */
        void histogram_equalization(char* filepath);


        /**< These functions Extract important values from the bitmap header */
        unsigned long getFileSize();
        unsigned long getStartOfBitmap();
        unsigned long getWidth();
        unsigned long getHeight();
        unsigned long getNumberOfColorsInPalette();

        /**< Outputs header data to the console using the std::cout stream */
        void printData();

        /**< Returns the pixel data located in the specified file byte */
        unsigned char getPixel(int index);

        /**< Writes a byte to the specified pixel */
        void setPixel(int index, unsigned char byte);

    private:
        /**< Extracts a 32-bit unsigned long from fileData element beginning with LSBindex */
        unsigned long get32(int LSBindex);

        /**< Contains the bitmap data */
        std::vector<unsigned char> fileData;
};

/**< Counts color occurrences and calculates new color in Histogram Equalization */
struct accumulator {
    public:
        accumulator(uint8_t _color) {
            color = _color;
            counter = 0;}       /**< first occurrence of that color so set to 1 */
        int counter;
        int cCounter;           /**< cumulative count */
        uint8_t color;
        uint8_t newColor;
        double cPercent;        /**< cumulative percent */
};

#endif // BMP_FILE_H
