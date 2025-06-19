int comment_size; // Global variable to store the size of the comment frame
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

// Function to convert a 4-byte big-endian value to little-endian integer
unsigned int convert_big_to_little(const unsigned char *bigEndian)
{
    return ((bigEndian[0] << 24) | (bigEndian[1] << 16) | (bigEndian[2] << 8) | (bigEndian[3]));
}

void id3_view(char *filename, FILE *fptr)
{

    fseek(fptr, 10, SEEK_SET); // skip header 10 bytes

    printf("\n============================================\n");
    printf("    MP3 ID3v2.3 Tag Reader - MP3 Details\n");
    printf("============================================\n\n");
    for (int i = 0; i < 6; i++) // Loop for 6 ID3v2.3 frames
    {
        char frame_id[5], size_bytes[4];
        fread(frame_id, sizeof(char), 4, fptr); // Read the frame ID
        frame_id[4] = '\0';                     // Null-terminate

        fread(size_bytes, sizeof(char), 4, fptr);     // read size of content
        int size = convert_big_to_little(size_bytes); // convert big endian value to little endian

        fseek(fptr, 3, SEEK_CUR);          // skip flag 2 bytes and 1 byte null
        if (strcmp(frame_id, "COMM") == 0) // If the frame ID is "COMM" (comment frame), store the size globally
        {
            comment_size = size;
        }
        char *content = malloc(size);                 // Allocate memory dynamically for frame content
        fread(content, sizeof(char), size - 1, fptr); // Read the content
        content[size - 1] = '\0';                     // Null-terminate

        display_id3_details(frame_id, content); // call a Function to display ID3 metadata based on frame IDs

        free(content); // Free allocated memory
    }
    printf("\n\n============================================\n\n");
}

// Function to display ID3 metadata based on frame IDs
void display_id3_details(char *frame_id, char *content)
{
    if (strcmp(frame_id, "TIT2") == 0)
    {
        printf("Title  : %s\n", content);
    }
    if (strcmp(frame_id, "TPE1") == 0)
    {
        printf("Artist : %s\n", content);
    }
    if (strcmp(frame_id, "TALB") == 0)
    {
        printf("Album  : %s\n", content);
    }
    if (strcmp(frame_id, "TYER") == 0)
    {
        printf("Year   : %s\n", content);
    }
    if (strcmp(frame_id, "TCON") == 0)
    {
        printf("Content: %s\n", content);
    }

    // Special handling for the comment frame ("COMM")
    if (strcmp(frame_id, "COMM") == 0)
    {
        printf("Comment: ");
        for (int i = 0; i < comment_size; i++)
            printf("%c", content[i]); // Print full comment content character by character
    }
}