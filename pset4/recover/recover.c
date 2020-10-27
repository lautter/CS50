#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 666;
    }
	//initiate files
	FILE *img = NULL;
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 667;
    }
	//array of bytes used as a buffer to read blocks of 512 bytes
	//at time because the size of blocks in filesystem
    BYTE buffer[512];
	//counter will increase and will name files sequentially
	int count = 0;
	// array that will be used to name the new jpeg files
	char filename[10];
	//loop that will iterate over the raw file searching for jpg files
    while (fread(buffer, sizeof(buffer), 1, raw) == 1)
    {
		// if is the header of a jpeg file
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && 
				buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
		{	// if it is a header of a new jpeg so close old one
			if (img)
			{
				fclose(img);
			}
			sprintf(filename,"%03i.jpg", count);	
			count++;
			img = fopen(filename, "w");
			fwrite(buffer, 512, 1, img);
		}
		else if(img)
		{
			fwrite(buffer, 512, 1, img);
		}
    }
	//fclose(img);
    fclose(raw);
}
