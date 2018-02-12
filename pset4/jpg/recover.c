/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 #include <stdio.h>
 #include <stdint.h>
 
 const int BLOCK_SIZE = 512;

int main(int argc, char* argv[])
{
    int num = 0; 
    FILE* inFile = fopen("card.raw", "r");
    FILE* outFile = NULL;
    uint8_t bytes[512];
    if(inFile  == NULL)
    {
        printf("Error in opening file.");
        return 1;
    }
    while(fread(bytes, BLOCK_SIZE, 1, inFile))
    {
        if(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2]== 0xff && (bytes[3] == 0xe0 || bytes[3] == 0xe1))
        {
            if(outFile != NULL)
            {
                fclose(outFile);
            }
            char title[8];
            sprintf(title, "%03d.jpg", num);
            outFile = fopen(title, "w");
            // iterate over infile's scanlines
           
            num++;
        }
        if(outFile != NULL)
        {
            fwrite(bytes, BLOCK_SIZE, 1, outFile);
        }
    }
    if(outFile != NULL)
    {
        fclose(outFile);
    }
    fclose(inFile);
    return 0;
}
