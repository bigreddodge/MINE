#include <iostream>
#include <fstream>
#include "include\bmp_file.h"

using namespace std;

/**< Function Prototypes */
void showHeaderData(char* infile);
void histogramEqualization(char* infile);
void imageOverlay(char* infile, char* overlay);
void showSyntaxMessage(char* cmd);

/**< Main (CLI Argument Handler) */
int main(int argc, char *argv[]) {
    if (argc == 2) {              /**< File info syntax: milestone1 input.bmp */
        showHeaderData(argv[1]);
    } else if (argc == 3) {       /**< Histogram syntax: milestone1 input.bmp output.bmp -h */
            histogramEqualization(argv[1]);
            imageOverlay(argv[1], argv[2]);
    } else {                      /**< Default */
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
}

/**< Subroutine: performs histogram-equalization on the input file and writes the output */
void histogramEqualization(char* infile) {
    std::cout << "\nHistogram EQ";
<<<<<<< HEAD
    char* ResultingFileName = "histogram_equalized.bmp";
    //cout << "opening " << infile << "...\n";
    bmp_file myFile(infile);
    std::cout << "\nPerforming Histogram Equalization...";
    myFile.histogram_equalization(ResultingFileName);
    std::cout << "\nCompleted.\n";
=======
    char* ResultingFileName = "output_he.bmp";
    bmp_file myFile(infile);
    myFile.histogram_equalization(ResultingFileName);
>>>>>>> refs/remotes/origin/master
}

/**< Subroutine: overlays the input file with the specified overlay and writes the output */
void imageOverlay(char* infile, char* overlay) {
<<<<<<< HEAD
    std::cout << "\nImage Overlay";
=======
    std::cout << "\n\nImage Overlay...";
>>>>>>> refs/remotes/origin/master

    ///Overlay procedure goes here
    bmp_file in(infile);
    bmp_file ov(overlay);
    std::cout << "\nOverlaying images...";
    unsigned long inOffset = in.getStartOfBitmap();
    unsigned long ovOffset = ov.getStartOfBitmap();
    unsigned long pixels = in.getWidth() * in.getHeight();
    if (pixels != (ov.getWidth() * ov.getHeight())){
        std::cout << "\nImages are not the same size. Aborting...";
        return;
    }
    for (unsigned long i = 0; i < pixels; ++i){
        if (ov.getPixel(ovOffset + i) == 0x00)
            in.setPixel(inOffset + i, 0xFF);
    }
    in.writeToNewFile("image_overlay.bmp");
    std::cout << "\nCompleted.\n";
}

/**< Displays Command-Line Syntax */
void showSyntaxMessage(char* cmd) {
    std::cout << "\nBitmap processor for analysis, histogram equalization,"
              <<" and overlay of 8-bit .bmp images.\n";
    std::cout << "\n\tUsage:\t\t" << cmd << " <image.bmp> [<overlay.bmp>]"  ;
    std::cout << "\n\n\tExamples:\t" << cmd << " image.bmp";
    std::cout << "\n\t\t\t- Displays information about image.bmp.";
    std::cout << "\n\n\t\t\t" << cmd << " image.bmp overlay.bmp";
    std::cout << "\n\t\t\t- Performs histogram-equalization on image.bmp and"
              << "\n\t\t\t  writes the image to histogram_equalized.bmp.";
    std::cout << "\n\t\t\t- Overlays image.bmp with overlay.bmp and writes the"
              <<"\n\t\t\t  output to image_overlay.bmp.\n\n";
}
