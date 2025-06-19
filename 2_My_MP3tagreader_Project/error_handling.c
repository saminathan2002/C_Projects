#include<stdio.h>
#include<string.h>
#include "main.h"

// Function to display an error message when invalid arguments are provided
void display_invalid_arg(char *argv)
{
    printf("\n==========================================================\n");
    printf("           ERROR: Invalid arguments provided!\n");
    printf("==========================================================\n\n");

    printf("Usage: %s [option] <filename.mp3>\n\n",argv);

    printf("Example usage:\n");
    printf("  %s -h                             --> Show help guide\n",argv);
    printf("  %s -v song.mp3                    --> View ID3 details\n",argv);
    printf("  %s -e song.mp3 -t \"New Title\"   --> Edit Title\n\n",argv);

    printf("Need help? Use '%s -h' for more details.\n",argv);

    printf("==========================================================\n\n");
}

// Function to verify if the given filename is an MP3 file
int mp3file_check(char *file)
{
    char *res;
    if (res = strchr(file, '.'))
    {
        if (strcmp(res, ".mp3") == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
        return 0;
}