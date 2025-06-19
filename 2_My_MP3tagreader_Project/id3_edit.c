#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

// Function to convert a little-endian integer into a big-endian 4-byte
void convert_litte_to_big(char *new_s, int new_size)
{
    new_s[0] = new_size >> 24 & 0xFF;
    new_s[1] = new_size >> 16 & 0xFF;
    new_s[2] = new_size >> 8 & 0xFF;
    new_s[3] = new_size & 0xFF;
}

void id3_edit(char *file, char *modifier, char *new_data, FILE *fptr)
{
    FILE *temp = fopen("temp.mp3", "w"); // Create a temporary file to store modified metadata

    if (temp == NULL)
    {
        printf("\nError!: Unable to create file\n");
        return;
    }

    char user_frame_id[5];
    int check = check_frame_id(modifier, user_frame_id); // Validate modifier and retrieve frame ID
    if (check == 1)
        return; // Exit if modifier is invalid

    char header[10];
    fread(header, 1, 10, fptr);  // Read first 10 bytes (ID3 tag header)
    fwrite(header, 1, 10, temp); // Copy header to temporary file

    for (int i = 0; i < 6; i++) // Loop to scan and edit metadata frames
    {
        char OG_frame_id[4];
        unsigned char size_bytes[4];
        char flag[3] = "00";
        fread(OG_frame_id, 1, 4, fptr); // Read frame ID

        fread(size_bytes, 1, 4, fptr);                // Read 4-byte size of content
        int size = convert_big_to_little(size_bytes); // Convert size from big-endian to little-endian

        fread(flag, 1, 3, fptr); // Read frame flags 2 bytes and 1 byte for null

        char *content = malloc(size - 1);             // Allocate memory for content
        fread(content, sizeof(char), size - 1, fptr); // Read content

        // If the current frame matches the user-specified frame, modify the data
        if (strcmp(user_frame_id, OG_frame_id) == 0)
        {
            fwrite(OG_frame_id, 1, 4, temp);     // Write frame ID
            int new_size = strlen(new_data) + 1; // Calculate new data size
            unsigned char new_s[4];
            convert_litte_to_big(new_s, new_size); // Convert new size little endian to big endian format

            fwrite(new_s, 1, 4, temp);               // Write updated size
            fwrite(flag, 1, 2, temp);                // Write flag bytes
            fwrite("\0", 1, 1, temp);                // Write null
            fwrite(new_data, 1, new_size - 1, temp); // Write modified data content
        }
        else // If the frame  does not need modification, keep it the same in the new file.
        {

            fwrite(OG_frame_id, 1, 4, temp);
            fwrite(size_bytes, 1, 4, temp);
            fwrite(flag, 1, 2, temp);
            fwrite("\0", 1, 1, temp);
            fwrite(content, 1, size - 1, temp);
        }
        free(content); // Free allocated memory
    }

    // Copy remaining file content (audio data)
    char ch;
    while (fread(&ch, 1, 1, fptr) > 0)
    {
        fwrite(&ch, 1, 1, temp);
    }

    fclose(temp); // Close the temp file

    remove(file);             // Delete original MP3 file
    rename("temp.mp3", file); // Rename temp file back to original name
    printf("Success! Your MP3 metadata has been updated.\n");
}

// Function to validate metadata modifier and assign correct frame ID
int check_frame_id(char *modifier, char *frame_id)
{
    if (strcmp(modifier, "-t") == 0)
    {
        printf("Modifying Title...\n");
        strcpy(frame_id, "TIT2");
    }
    else if (strcmp(modifier, "-a") == 0)
    {
        printf("Modifying Album...\n");
        strcpy(frame_id, "TALB");
    }
    else if (strcmp(modifier, "-ar") == 0)
    {
        printf("Modifying Artist...\n");
        strcpy(frame_id, "TPE1");
    }
    else if (strcmp(modifier, "-y") == 0)
    {
        printf("Modifying Year...\n");
        strcpy(frame_id, "TYER");
    }
    else if (strcmp(modifier, "-cm") == 0)
    {
        printf("Modifying Comment...\n");
        strcpy(frame_id, "COMM");
    }
    else if (strcmp(modifier, "-cn") == 0)
    {
        printf("Modifying Content...\n");
        strcpy(frame_id, "TCON");
    }
    else
    {
        printf("Invalid modifiers\n");
        return 1;
    }
}
