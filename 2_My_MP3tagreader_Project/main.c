/*
Name: Saminathan S
Date: 09-05-2025
Description: MP3 ID3v2.3 Tag Reader for displaying and modifying metadata
Features:
- Read ID3v2.3 tags from an MP3 file
- Display metadata (Title, Artist, Album, Year, Comment, Content)
- Modify metadata fields (Title, Artist, Album, Year, Comment, Content)
- Ensure proper validation of MP3 files
- Handle file errors (missing files, unsupported formats)
- Efficient parsing of ID3v2.3 frames

Sample Input:
1. View metadata from "song.mp3"
   Command: ./a.out -v song.mp3

2. Edit the title of "song.mp3"
   Command: ./a.out -e song.mp3 -t "New Song Title"

Sample Output:
============================================
    MP3 ID3v2.3 Tag Reader - MP3 Details
============================================

Title  : Sunny Sunny
Artist : Yo Yo Honey Singh - [SongsPk.CC]
Album  : Yaariyan
Year   : 2013
Content: Bollywood Music - [SongsPk.CC]
Comment: engishloaded From SongsPk.CC

============================================
*/

#include <stdio.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[])
{
    if (argc < 2) // Check if the user has provided enough arguments
    {
        display_invalid_arg(argv[0]); // Call function to handle missing arguments
        return 0;
    }

    if ((strcmp(argv[1], "-h") == 0) && (argc == 2))
    {
        id3_help_guide(); // Call function to display help guide
    }

    else if ((strcmp(argv[1], "-v") == 0) && (argc == 3))
    {
        int check = mp3file_check(argv[2]); // Check if the file is an MP3
        if (check)
        {
            FILE *fptr = fopen(argv[2], "r"); // open mp3 file
            if (fptr == NULL)
            {
                printf("\nError: File '%s' not found.\nCheck the filename and ensure the file exists.\n\n", argv[2]);
                return 0;
            }

            id3_view(argv[2], fptr); // call a funtion display ID3 metadata

            fclose(fptr); // close mp3 file
        }
        else // If the file is not an MP3, show an error message
        {
            printf("\nError: '%s' is not an MP3 file.\nOnly MP3 files with ID3v2.3 tags are supported.\n\nTry '%s -h' for help.\n\n", argv[2],argv[0]);
            return 0;
        }
    }

    else if ((strcmp(argv[1], "-e") == 0) && (argc == 5))
    {
        int check = mp3file_check(argv[2]); // Check if the file is an MP3
        if (check)
        {
            FILE *fptr = fopen(argv[2], "r"); // Check if the file is an MP3
            if (fptr == NULL)
            {
                printf("\nError: File '%s' not found.\nCheck the filename and ensure the file exists.\n\n", argv[2]);
                return 0;
            }

            id3_edit(argv[2],argv[3],argv[4],fptr); // call a funtion for modifying ID3 metadata

            fclose(fptr); //close mp3 file
        }
        else
        {
            printf("\nError: '%s' is not an MP3 file.\nOnly MP3 files with ID3v2.3 tags are supported.\n\nTry './a.out -h' for help.\n\n", argv[2]);
            return 0;
        }
    }

    else
    {
        display_invalid_arg(argv[0]); // Call function to handle missing arguments
        return 0;
    }

    return 0;
}
