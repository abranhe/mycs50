#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor input_file output_file\n");
        return 1;
    }
    
    float f = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];
    
    // restrict f to (0.0, 100.0]
    if (f <= 0.0 || f > 100.0)
    {
        fprintf(stderr, "factor = (0.0, 100.0] only\n");
        return 1;
    }
    
    // open input file
    FILE *input_file = fopen(infile, "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "Could not open input file.\n");
        return 2;
    }
    
    // create output file
    FILE *output_file = fopen(outfile, "w");
    if (output_file == NULL)
    {
        fclose(input_file);
        fprintf(stderr, "Could not create output file.\n");
        return 3;
    }
    
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, input_file);
    
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, input_file);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(output_file);
        fclose(input_file);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // copy original values to inbf & inbi
    // BITMAPFILEHEADER inbf = bf;
    BITMAPINFOHEADER inbi = bi;
    
    // determine input_file's padding for scanlines
    int inpadding = (4 - (inbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // modifying bf & bi for output_file
    bi.biWidth = f * inbi.biWidth;
    bi.biHeight = f * inbi.biHeight;
    
    if (bi.biWidth < 1 || abs(bi.biHeight) < 1)
    {
        // fprintf(stdout, "biWidth:%i biHeight:%i", bi.biWidth, bi.biHeight);
        fprintf(stderr, "Too small.\n");
        return 5;
    }
    
    // determine output_file's padding for scanlines
    int outpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // modifying bf & bi for output_file
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + outpadding) * (abs(bi.biHeight));
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;
    
    // write output_file's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, output_file);
    
    // write output_file's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, output_file);
    
    // fprintf(stdout, "original biWidth = %i\n", inbi.biWidth);
    // fprintf(stdout, "original biHeight = %i\n", inbi.biHeight);
    // fprintf(stdout, "original biSizeImage = %i\n", inbi.biSizeImage);
    // fprintf(stdout, "original bfSize = %i\n", inbf.bfSize);
    
    // fprintf(stdout, "new biWidth = %i\n", bi.biWidth);
    // fprintf(stdout, "new biHeight = %i\n", bi.biHeight);
    // fprintf(stdout, "new biSizeImage = %i\n", bi.biSizeImage);
    // fprintf(stdout, "new bfSize = %i\n", bf.bfSize);
    
    // fprintf(stdout, "%i\n", outpadding);
    
    // printf("bfType: 0x%x\n", bf.bfType);
    // printf("bfSize: %i\n", bf.bfSize); // to change. tbc bfOffBits 54 + biSizeImage ?
    // printf("bfReserved1: %i\n", bf.bfReserved1);
    // printf("bfReserved2: %i\n", bf.bfReserved2);
    // printf("bfOffBits: %i\n\n", bf.bfOffBits);
    
    // printf("biSize: %i\n", bi.biSize); 
    // printf("biWidth: %i\n", bi.biWidth);  // to change by a factor
    // printf("biHeight: %i\n", bi.biHeight); // to change by a factor
    // printf("biPlanes: %i\n", bi.biPlanes);
    // printf("biBitCount: %i\n", bi.biBitCount);
    // printf("biCompression: %i\n", bi.biCompression);
    // printf("biSizeImage: %i\n", bi.biSizeImage); // ((biWidth+buffer)*(biHeight) * 3 bytes (RGB)
    // printf("biXPelsPerMeter: %i\n", bi.biXPelsPerMeter);
    // printf("biYPelsPerMeter: %i\n", bi.biYPelsPerMeter);
    // printf("biClrUsed: %i\n", bi.biClrUsed);
    // printf("biClrImportant: %i\n", bi.biClrImportant);
    
    // printf("BITMAPFILEHEADER size: %lu\n", sizeof(BITMAPFILEHEADER));
    // printf("BITMAPINFOHEADER size: %lu\n", sizeof(BITMAPINFOHEADER));
    
    // set factoring index for height & width
    float fheight = 0;
    float fwidth = 0;
    
    // create variable to store scanlines
    RGBTRIPLE triple[inbi.biWidth];
    
    // iterate over input_file's scanlines
    for (int i = 0, n = abs(inbi.biHeight); i < n; i++)
    {
        // reading input_file's scanline
        for (int j = 0; j < inbi.biWidth; j++)
        {  
            fread(&triple[j], sizeof(RGBTRIPLE), 1, input_file);
        }
        // skip over padding if any
        fseek(input_file, inpadding, SEEK_CUR);
        
        // add factor for height i
        fheight = fheight + (1 * f);
        // fprintf(stdout, "%i: fheight: %f\n", i, fheight);
        
        // writing to output_file
        while (fheight >= 1)
        {
            // initialise factor for each RGB
            fwidth = 0;
            
            // iterate over RGB in input_file's scanline i
            for (int j = 0; j < inbi.biWidth; j++)
            {
                // add factor for width j
                fwidth = fwidth + (1 * f);
                // fprintf(stdout, "%i: fwidth: %f\n", j, fwidth);
                
                while (fwidth >= 1)
                {
                    fwrite(&triple[j], sizeof(RGBTRIPLE), 1, output_file);
                    // fprintf(stdout, "%i writing\n", j);
                    fwidth -= 1;
                }
            }
            // skip over padding in output file if any
            for (int k = 0; k < outpadding; k++)
            {
                fputc(0x00, output_file);
            }
            
            fheight -= 1;
        }
    }
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}