#include <stdio.h>
#include <string.h>
#include "decode.h"
#include "types.h"

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{

    if (argv[3] == NULL)
    {
        strcpy(decInfo->output_fname, "output");
    }
    else
    {
        strcpy(decInfo->output_fname, argv[3]);
    }
    if (strstr(argv[2], ".bmp") == NULL)
    {
        printf("ERROR: File is not .bmp\n");
        return e_failure;
    }
    decInfo->stego_image_fname = argv[2];

    return e_success;
}

Status do_decoding(DecodeInfo *decInfo)
{
    if (dec_open_files(decInfo) == e_success)
    {
        printf("INFO: All files are opened successfully\n");
    }
    else
    {
        printf("ERROR: Failed to open the file\n");
        return e_failure;
    }

    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);
    printf("INFO: Header skip\n");

    printf("Enter magic string: ");
    scanf(" %[^\n]", decInfo->magic_str);

    uint magic_size;
    if (decode_magic_string_size(&magic_size, decInfo) == e_success)
    {
        printf("INFO: Decoded Magic String Size Successfully\n");
        // printf("%u\n",magic_size);
    }

    else
    {
        printf("ERROR: Failed to Decode magic string size\n");
        return e_failure;
    }
    decInfo->magic_size = magic_size;

    if (decode_magic_string(decInfo->magic_size, decInfo->magic_data, decInfo) == e_success)
    {
        printf("INFO: Decoded Magic String data Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to decode magic data\n ");
    }

    if (strcmp(decInfo->magic_str, decInfo->magic_data) == 0)
    {
        printf("INFO: Correct magic string\n");
    }

    else
    {
        printf("ERROR: Magic string not mated!!\n");
        return e_failure;
    }

    uint ext_size;
    if (decode_secret_file_extn_size(&ext_size, decInfo) == e_success)
    {
        printf("INFO: Decoded Extrn Size Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to Decode extrn size\n");
        return e_failure;
    }
    decInfo->extrn_size = ext_size;

    // printf("Size-----%d\n",decInfo->extrn_size);

    if (decode_secret_file_extn(decInfo->extrn_size, decInfo->extrn_data, decInfo) == e_success)
    {
        printf("INFO: Decoded Extrn data Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to decode Extrn data\n ");
    }

    strcat(decInfo->output_fname, decInfo->extrn_data);
    decInfo->fptr_ouput_data = fopen(decInfo->output_fname, "w");

    uint sec_size;
    if (decode_secret_file_size(&sec_size, decInfo) == e_success)
    {
        printf("INFO: Decoded Sec_file Size Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to Decode file size\n");
        return e_failure;
    }
    decInfo->sec_size = sec_size;
    // printf("Size-----%d\n",decInfo->sec_size);

    if (decode_secret_file_extn(decInfo->sec_size, decInfo->sec_data, decInfo) == e_success)
    {
        printf("INFO: Decoded sec data Successfully\n");
    }
    else
    {
        printf("ERROR: Failed to decode sec data\n ");
    }

    // printf("sec data --- %s\n",decInfo->sec_data);
    int i = 0;
    while (decInfo->sec_data[i] != '\0')
    {
        putc(decInfo->sec_data[i], decInfo->fptr_ouput_data);
        i++;
    }
    fclose(decInfo->fptr_ouput_data);
    fclose(decInfo->fptr_stego_image);
}

Status dec_open_files(DecodeInfo *decInfo)
{
    printf("INFO: Opening required files\n");

    // Src Image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    // Do Error handling
    if (decInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname);
        return e_failure;
    }
    printf("INFO: Opened %s \n", decInfo->stego_image_fname);

    return e_success;
}

uint decode_lsb_to_size(DecodeInfo *decInfo)
{
    char int_buffer[32];
    fread(int_buffer, 32, 1, decInfo->fptr_stego_image);
    uint int_size = 0;
    for (int i = 0; i <= 31; i++)
    {
        int_size = (int_buffer[i] & 1) << i | int_size;
    }
    return int_size;
}
Status decode_lsb_to_byte(uint size, char *data, DecodeInfo *decInfo)
{
    char data_buffer[8];
    int i;
    for (i = 0; i < size; i++)
    {
        fread(data_buffer, 8, 1, decInfo->fptr_stego_image);
        char ch = 0;
        for (int i = 0; i < 8; i++)
        {
            ch = (data_buffer[i] & 1) << i | ch;
        }
        data[i] = ch;
    }
    data[i] = '\0';
}

Status decode_magic_string_size(uint *size, DecodeInfo *decInfo)
{
    printf("INFO: Decoding magic string size\n");
    *size = decode_lsb_to_size(decInfo);
    return e_success;
}
Status decode_magic_string(uint size, char *data, DecodeInfo *decInfo)
{
    printf("INFO: Decoding magic string data\n");
    decode_lsb_to_byte(size, data, decInfo);
    return e_success;
}

Status decode_secret_file_extn_size(uint *size, DecodeInfo *decInfo)
{
    printf("INFO: Decoding extern size\n");
    *size = decode_lsb_to_size(decInfo);
    return e_success;
}

Status decode_secret_file_extn(uint size, char *data, DecodeInfo *decInfo)
{
    printf("INFO: Decoding secret data\n");
    decode_lsb_to_byte(size, data, decInfo);
    return e_success;
}

Status decode_secret_file_size(uint *size, DecodeInfo *decInfo)
{
    printf("INFO: Decoding secret file size\n");
    *size = decode_lsb_to_size(decInfo);
    return e_success;
}

Status decode_secret_file_data(uint size, char *data, DecodeInfo *decInfo)
{
    printf("INFO: Decoding sec_data data\n");
    decode_lsb_to_byte(size, data, decInfo);
    return e_success;
}
