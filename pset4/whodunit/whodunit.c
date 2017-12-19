#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit input_file output_file\n");
        return 1;
    }
    
    // record filenames passed in as command-line arguments
    char *ifile = argv[1];
    char *ofile = argv[2];
    
    // open input file
    FILE *inputfile = fopen(ifile, "r");
    if (inputfile == NULL)
    {
        fprintf(stderr, "Unable to open input file\n");
        return 2;
    }
    
    // open (or create) output file
    FILE *outputfile = fopen(ofile, "w");
    if (outputfile == NULL)
    {
        fclose(inputfile);
        fprintf(stderr, "Unable to open output file.\n");
        return 3;
    }
    
    // read inputfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputfile);
    
    // read inputfile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputfile);
    
    //ensure that the inputfile is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputfile);
        fclose(inputfile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputfile);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputfile);
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // iterate over inputfile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            
            fread(&triple, sizeof(RGBTRIPLE), 1, inputfile);
            // manipulate methods
            // green = 255, red = 255, blue = 255
            // if a colour = 255, set it to 0
            // if a colour = 255, set any other colour to 0
            // if a colour = 0, set any other colour to 255
            if (triple.rgbtRed == 0xff)
            {
                triple.rgbtGreen = 0x00;
            }
            // ans: IT WAS COLONEL MUSTARD WITH THE CANDLESTICK IN THE LIBRARY
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputfile);
        }
        
        // skip over padding, if any
        fseek(inputfile, padding, SEEK_CUR);
        
        // add padding, if any
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputfile);
        }
    }
    
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}