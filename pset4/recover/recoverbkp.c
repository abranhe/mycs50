#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // ensure proper usage
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // open image file
    FILE *image = fopen(argv[1], "r");
    if (image == NULL)
    {
        fprintf(stderr, "Could not open image file.\n");
        return 2;
    }
    
    // check elements from fread
    int elements;
    int element;
    
    // set output file sequence
    char filename[7];
    int fileseq = 0;
    FILE *jpgfile = NULL;
    
    // temporarily store blocks of 512 bytes
    unsigned char mblock[512];
    
    while (1)
    {
        elements = fread(mblock, 1, 512, image);
        // to set elements to static value (somehow elements is not)
        element = elements;
        // eprintf("element: %i\n", element);
        
        if (mblock[0] == 0xff && 
            mblock[1] == 0xd8 && 
            mblock[2] == 0xff && 
            (mblock[3] & 0xf0) == 0xe0)  
        {
            // eprintf("found jpg file.\n");
            // close jpg file if it's open
            if (jpgfile != NULL)
            {
                // eprintf("closing jpg file.\n");
                fclose(jpgfile);
            }
            // open new jpg file
            sprintf(filename, "%03i.jpg", fileseq);
            jpgfile = fopen(filename, "w");
            // ensure jpg file could be created
            if (jpgfile == NULL)
            {
                fprintf(stderr, "Could not create jpg file.\n");
                return 2;
            }
            // set filename for next jpg file
            fileseq += 1;
            // write to the jpg file
            fwrite(mblock, 1, element, jpgfile);
        }
        else
        {
            if (jpgfile != NULL)
            {
                // eprintf("writing to jpg file (recurring). elements: %i\n", element);
                fwrite(mblock, 1, element, jpgfile);
            }
        }
        
        if (elements != 512)
        {
            // eprintf("reached end of file. elements: %i\n", elements);
            break;
        }
    }
    
    // eprintf("completed the recover process.\n");
    
    if (jpgfile != NULL)
        fclose(jpgfile);
    // if (image != NULL)
    //     fclose(image);
    return 0;
}
