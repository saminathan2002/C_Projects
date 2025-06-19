#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

typedef struct _DecodeInfo
{
    /* Stego Image info */
    char *stego_image_fname;
    FILE *fptr_stego_image;

    /* Output file info */
    char output_fname[20];
    FILE *fptr_ouput_data;
    uint magic_size;
    uint extrn_size;
    uint sec_size;
    char magic_data[1000];
    char extrn_data[1000];
    char sec_data[1000];

    /*magic string*/
    char magic_str[100];

} DecodeInfo;

/* Decoding function prototype */

/* Read and validate decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status dec_open_files(DecodeInfo *decInfo);

/* magic str size*/
Status decode_magic_string_size(uint *size,DecodeInfo *decInfo);

Status decode_magic_string(uint size,char *data,DecodeInfo *decInfo);

Status decode_secret_file_extn_size(uint *size, DecodeInfo *decInfo);

Status decode_secret_file_extn(uint size,char *data, DecodeInfo *encInfo);

Status decode_secret_file_size(uint *size, DecodeInfo *decInfo);

Status decode_secret_file_data(uint size,char *data ,DecodeInfo *decInfo);


uint decode_lsb_to_size(DecodeInfo *decInfo);
Status decode_lsb_to_byte(uint size,char *data, DecodeInfo *decInfo);

#endif
