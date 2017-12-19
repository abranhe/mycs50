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
    
    // for output file
    int fileseq = 0;
    char filename[8];
    filename[7] = '\0';
    FILE *jpgfile = NULL;
    
    // temporarily store blocks of 512 bytes
    unsigned char mblock[512];
    
    while (1)
    {
        // determine number of bytes that can be read 
        elements = fread(mblock, 1, 512, image);
        
        // check if it's a new jpg file
        if (mblock[0] == 0xff && 
            mblock[1] == 0xd8 && 
            mblock[2] == 0xff && 
            (mblock[3] & 0xf0) == 0xe0)  
        {
            // close previous jpg file
            if (jpgfile != NULL)
            {
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
            // write to jpg file
            fwrite(mblock, 1, elements, jpgfile);
        }
        else
        {
            // write to jpg file if it's open
            if (jpgfile != NULL)
            {
                fwrite(mblock, 1, elements, jpgfile);
            }
        }
        
        // stop the loop if reaching end of file
        if (elements != 512)
        {
            break;
        }
    }
    
    if (jpgfile != NULL)
    {
        fclose(jpgfile);
    }
    else
    {
        fprintf(stderr, "Could not retrieve any foresenic image.\n");
        return 3;
    }
    fclose(image);
    return 0;
}
