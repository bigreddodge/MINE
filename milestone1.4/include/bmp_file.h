#ifndef BMP_FILE_H
#define BMP_FILE_H

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <vector>

class bmp_file {
    public:
        bmp_file();                                     /**< Default constructor */
        virtual ~bmp_file();                            /**< Default destructor */
        bmp_file(char* filepath);                      /**< Creates an instance of bmp_file containing the specified file */

        void writeToNewFile(char* filepath);           /**< Writes the data in the bmp_file instance to the specified file */
        unsigned long getFileSize();                    /**< Extracts the file size from the bitmap header */
        unsigned long getStartOfBitmap();               /**< Extracts the image offset from the bitmap header */
        unsigned long getWidth();                       /**< Extracts the image width from the bitmap header */
        unsigned long getHeight();                      /**< Extracts the image height from the bitmap header */
        unsigned long getNumberOfColorsInPalette();     /**< Extracts the bits/px value from the bitmap header */
        void printData();                               /**< Outputs header data to the console using the std::cout stream */

        unsigned char getPixel(int index);              /**< Returns the pixel data located in the specified file byte */
        void setPixel(int index, unsigned char byte);   /**< Writes a byte to the specified pixel */
    private:
        unsigned long get32(int LSBindex);              /**< Extracts a 32-bit unsigned long value from fileData beginning with element LSBindex */
        std::vector<unsigned char> fileData;            /**< Contains the bitmap data */
};

#endif // BMP_FILE_H

/**< Graveyard */
