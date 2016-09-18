#include <iostream>
#include <fstream>
#include "include\bmp_file.h"

using namespace std;

/**< Function Prototypes */
void showHeaderData(char* infile);
void histogramEqualization(char* infile);
void imageOverlay(char* infile, char* overlay);
void printBits(unsigned char byte);
void showSyntaxMessage(char* cmd);
void writeTest();

/**< Main (CLI Argument Handler) */
int main(int argc, char *argv[]) {
    if (argc == 2) {                                    /**< File info syntax: milestone1 input.bmp */
        showHeaderData(argv[1]);
    } else if (argc == 3) {                             /**< Histogram syntax: milestone1 input.bmp output.bmp -h */
            histogramEqualization(argv[1]);
            imageOverlay(argv[1], argv[2]);
    } else {                                            /**< Default */
        showSyntaxMessage(argv[0]);
    }
    std::cout << endl << endl;
    return 0;
}

/**< Subroutine for displaying bitmap header and selected additional parameters
 *   This is the primary entry point for development/debugging procedures  */
void showHeaderData(char* infile) {
        std::cout << "\nShowing header data for " << infile << "...\n";
        bmp_file myFile(infile);
        myFile.printData();
        int a = myFile.getStartOfBitmap();
        std::cout << "\n";
        for (int i = a; i < (a + 16); ++i)
            printBits(myFile.getPixel(i));
}

/**< Subroutine for performing a histogram-equalization on the input file and writing the output */
void histogramEqualization(char* infile) {
    std::cout << "\nHistogram EQ";
    char* ResultingFileName = "output_he.bmp";
    bmp_file myFile(infile);
    myFile.histogram_equalization(ResultingFileName);
}

/**< Subroutine for overlaying the input file with the specified overlay and writing the output */
void imageOverlay(char* infile, char* overlay) {
    std::cout << "\n\nImage Overlay...";

    ///Overlay procedure goes here
    bmp_file in(infile);
    bmp_file ov(overlay);
    unsigned long inOffset = in.getStartOfBitmap();
    unsigned long ovOffset = ov.getStartOfBitmap();
    unsigned long pixels = in.getWidth() * in.getHeight();
    if (pixels != (ov.getWidth() * ov.getHeight())){
        std::cout << "\nImages are not the same size.";
        return;
    }
    for (unsigned long i = 0; i < pixels; ++i){
        if (ov.getPixel(ovOffset + i) == 0x00)
            in.setPixel(inOffset + i, 0xFF);
    }
    in.writeToNewFile("output_ov.bmp");
}

/**< Displays Command-Line Syntax */
void showSyntaxMessage(char* cmd) {
    std::cout << "\nBitmap processor for analysis, histogram equalization, and overlay of 8-bit .bmp images.\n";
    std::cout << "\n\tUsage:\t\t" << cmd << " <image.bmp> [<overlay.bmp>]"  ;
    std::cout << "\n\n\tExamples:\t" << cmd << " image.bmp";
    std::cout << "\n\t\t\t- Displays information about image.bmp.";
    std::cout << "\n\n\t\t\t" << cmd << " image.bmp overlay.bmp";
    std::cout << "\n\t\t\t- Performs histogram-equalization on image.bmp and\n\t\t\t  writes the image to image_he.bmp.";
    std::cout << "\n\t\t\t- Overlays image.bmp with overlay.bmp and writes the\n\t\t\t  output to image_io.bmp.\n\n";
}


/**< Displays the bits in a specified byte */
void printBits(unsigned char byte){
    for (int i = 7; i >= 0; i--)
        std::cout << ((byte >> i) & 0x1);
    std::cout << ' ';
}

/**< Test function to write A-Z to testfile.bbb */
void writeTest(){
    std::ofstream outFile;
    outFile.open("testfile.bbb", std::ofstream::out | std::ofstream::binary);
    vector<unsigned char> test;
    for (int i = 65; i < (65+26); ++i)
        test.push_back((char)i);
    char * buffer = new char [1];
    for (unsigned int i = 0; i < test.size(); i++){
        *buffer = test[i];
        outFile.write(buffer,1);
    }
}

/**< Graveyard */
