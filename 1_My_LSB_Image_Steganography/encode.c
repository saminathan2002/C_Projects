#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"

/* Function Definitions */

OperationType check_operation_type(char *argv[])
{
    if (strcmp(argv[1], "-e") == 0)
    {
        return e_encode;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        return e_decode;
    }
    else
        return e_unsupported;
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    // Check if enough arguments are provided
    if (argv[2] == NULL || strstr(argv[2], ".bmp") == NULL)
    {
        printf("\nERROR: Invalid input file! Expected a .bmp file.\n");
        printf("\nUsage:\n");
        printf("For Encoding : %s -e <.bmp file> <.txt file> [output file] \n\n", argv[0]);

        return e_failure;
    }
    encInfo->src_image_fname = argv[2];

    if (argv[3] == NULL || strstr(argv[3], ".txt") == NULL)
    {
        printf("\nERROR: Invalid secret file! Expected a .txt file.\n");
        printf("\nUsage:\n");
        printf("For Encoding : %s -e <.bmp file> <.txt file> [output file] \n\n", argv[0]);
        return e_failure;
    }
    encInfo->secret_fname = argv[3];

    // Set default output file if not provided
    if (argv[4] == NULL)
    {
        printf("\nINFO: Output file not specified. Creating 'stego_img.bmp' as default.\n");
        encInfo->stego_image_fname = "stego_img.bmp";
    }
    else if (strstr(argv[4], ".bmp") == NULL)
    {
        printf("\nERROR: Invalid output file format! Expected .bmp\n");
        return e_failure;
    }
    else
    {
        encInfo->stego_image_fname = argv[4];
    }

    return e_success;
}

Status do_encoding(EncodeInfo *encInfo)
{
    if (open_files(encInfo) == e_success)
    {
        printf("INFO: All files are opened successfully\n");
    }
    else
    {
        printf("ERROR: Failed to open the file\n");
        return e_failure;
    }

    printf("Enter magic string: ");
    scanf(" %[^\n]", encInfo->magic_str);

    printf("\n==ENCODE PROCEDURE STARTED==\n");
    if (check_capacity(encInfo) == e_success)
    {
        printf("INFO: Successfully check capacity of file.\n");
    }
    else
    {
        printf("ERROR:  capacity of file is more.\n");
        return e_failure;
    }

    if (copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
    {
        printf("INFO: Done. Header successfully copied\n");
    }
    else
    {
        printf("ERROR: Faild to copy .BMP Header\n");
        return e_failure;
    }

    // 1.Magic string size
    if (encode_magic_string_size(strlen(encInfo->magic_str), encInfo) == e_success)
    {
        printf("INFO: Encoded Magic String Size Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to encode magic string size\n");
        return e_failure;
    }

    // 1.1 Magic string data
    if (encode_magic_string(encInfo->magic_str, encInfo) == e_success)
    {
        printf("INFO: Encoded Magic String Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to encode magic string...\n");
        return e_failure;
    }

    // 2. Extrn size
    strcpy(encInfo->extn_secret_file, strchr(encInfo->secret_fname, '.'));
    if (encode_secret_file_extn_size(strlen(encInfo->extn_secret_file), encInfo) == e_success)
    {
        printf("INFO: Encode extrn size succesfully\n");
    }
    else
    {
        printf("ERROR: Failed to encode size...\n");
        return e_failure;
    }
    // 2.1 Extrn data
    if (encode_secret_file_extn(strchr(encInfo->secret_fname, '.'), encInfo) == e_success)
    {
        printf("INFO: Encode extrn data succesfully\n");
    }
    else
    {
        printf("ERROR: Failed to encode data...\n");
        return e_failure;
    }

    if (encode_secret_file_size(encInfo->size_secret_file, encInfo) == e_success)
    {
        printf("INFO: Encode secret data size successfully\n");
    }
    else
    {
        printf("ERROR: Failed to encode size...\n");
        return e_failure;
    }

    if (encode_secret_file_data(encInfo) == e_success)
    {
        printf("INFO: Encode secret data successfully\n");
    }
    else
    {
        printf("ERROR: Failed to encode data...\n");
        return e_failure;
    }

    if (copy_remaining_img_data(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_success)
    {
        printf("INFO: Remaining data copied succesfully\n");
    }
    else
    {
        printf("ERROR: Failed to remain copied data...\n");
        return e_failure;
    }

    fclose(encInfo->fptr_secret);
    fclose(encInfo->fptr_src_image);
    fclose(encInfo->fptr_stego_image);

    return e_success;
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    printf("INFO: Opening... required files\n");

    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
        return e_failure;
    }
    printf("INFO: Opened %s \n", encInfo->src_image_fname);

    // Secret file

    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }
    printf("INFO: Opened %s \n", encInfo->secret_fname);

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }
    printf("INFO: Opened %s \n", encInfo->stego_image_fname);

    // No failure return e_success
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    encInfo->image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);

    printf("INFO: Checking for %s\n", encInfo->secret_fname);
    if (encInfo->size_secret_file == 0)
    {
        printf("ERROR: No data available in secret file\n");
        return e_failure;
    }
    printf("INFO: Done. Not empty\n");

    printf("INFO: Checking for %s capacity to handle %s\n", encInfo->src_image_fname, encInfo->secret_fname);
    if ((strlen(encInfo->magic_str) * 8 + 32 + 32 + 32 + (encInfo->size_secret_file * 8)) > (encInfo->image_capacity))
    {
        printf("ERROR: Secret file size is greater than image file\n");
        return e_failure;
    }
    printf("INFO: Done. Found OK\n");

    return e_success;
}

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    // printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    // printf("height = %u\n", height);

    // printf("Total : %d\n", width * height * 3);
    // Return image capacity
    rewind(fptr_image);
    return width * height * 3;
}

uint get_file_size(FILE *fptr)
{
    // Seek to end character
    fseek(fptr, 0, SEEK_END);
    uint file_size = ftell(fptr);
    rewind(fptr);
    // printf("%d\n", file_size);

    return file_size;
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    printf("INFO: Copying... BMP header\n");
    char buffer[54];
    if (fread(buffer, 1, 54, fptr_src_image) != 54)
    {
        printf("Error in reading Header\n");
        return e_failure;
    }
    if (!(buffer[0] == 'B' && buffer[1] == 'M'))
    {
        printf("ERROR :It is not a .BMP file\n");
        return e_failure;
    }
    if (fwrite(buffer, 1, 54, fptr_dest_image) != 54)
    {
        printf("ERROR: While writeing Header\n");
        return e_failure;
    }

    return e_success;
}

Status encode_size_to_lsb(uint size, EncodeInfo *encInfo)
{
    char buffer[32];
    fread(buffer, 32, 1, encInfo->fptr_src_image);
    for (int i = 0; i <= 31; i++)
    {
        buffer[i] = (buffer[i] & 0xFE) | ((size >> i) & 1);
    }
    fwrite(buffer, 32, 1, encInfo->fptr_stego_image);
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for (int i = 0; i < 8; i++)
    {
        image_buffer[i] = (image_buffer[i] & 0xFE) | ((data >> i) & 1);
    }
}

Status encode_magic_string_size(uint size, EncodeInfo *encInfo)
{
    printf("INFO: Encoding magic string size\n");
    encode_size_to_lsb(size, encInfo);
    return e_success;
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    printf("INFO: Encoding magic string data\n");
    char image_buffer[8];
    for (int i = 0; i < strlen(encInfo->magic_str); i++)
    {
        fread(image_buffer, 8, 1, encInfo->fptr_src_image);
        encode_byte_to_lsb(magic_string[i], image_buffer);
        fwrite(image_buffer, 8, 1, encInfo->fptr_stego_image);
    }
    return e_success;
}

Status encode_secret_file_extn_size(uint size, EncodeInfo *encInfo)
{
    printf("INFO: Encoding extn size\n");
    encode_size_to_lsb(size, encInfo);
    return e_success;
}

Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    printf("INFO: Encoding extrn data\n");
    char image_buffer[8];
    for (int i = 0; i < strlen(file_extn); i++)
    {
        fread(image_buffer, 8, 1, encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i], image_buffer);
        fwrite(image_buffer, 8, 1, encInfo->fptr_stego_image);
    }
    return e_success;
}

Status encode_secret_file_size(uint file_size, EncodeInfo *encInfo)
{
    printf("INFO: Encoding secret file size\n");
    encode_size_to_lsb(file_size, encInfo);
    return e_success;
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    printf("INFO: Encoding secret data\n");
    char image_buffer[8];
    fread(encInfo->secret_data, encInfo->size_secret_file, 1, encInfo->fptr_secret);
    for (int i = 0; i < encInfo->size_secret_file; i++)
    {
        fread(image_buffer, 8, 1, encInfo->fptr_src_image);
        encode_byte_to_lsb(encInfo->secret_data[i], image_buffer);
        fwrite(image_buffer, 8, 1, encInfo->fptr_stego_image);
    }
    return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char ch[8];
    while (fread(ch, 8, 1, fptr_src) > 0)
    {
        fwrite(ch, 8, 1, fptr_dest);
    }
    return e_success;
}
