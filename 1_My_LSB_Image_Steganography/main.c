#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    DecodeInfo decInfo;
    if (argc < 2)
    {

        printf("\nERROR: Invalid arguments!\n");
        printf("\nUsage:\n");
        printf("For Encoding : %s -e <.bmp file> <.txt file> [output file] \n", argv[0]);
        printf("For Decoding : %s -d <.bmp file> [output file]  \n\n", argv[0]);
        return e_failure;
    }

    if (check_operation_type(argv) == e_encode)
    {
        if (read_and_validate_encode_args(argv, &encInfo) == e_success)
        {
            if (do_encoding(&encInfo) == e_success)
            {
                printf("\n==Encode Successfully completed==\n");
            }
            else
            {
                printf("\n==Encode not succesfull==\n");
            }
        }
        else
            return e_failure;

        return e_success;
    }
    else if (check_operation_type(argv) == e_decode)
    {
        if (argc < 3)
        {
            printf("\nERROR: Invalid arguments!\n");
            printf("\nUsage:\n");
            printf("For Decoding : %s -d <.bmp file> [output file]  \n\n", argv[0]);
            return e_failure;
        }
        if (read_and_validate_decode_args(argv, &decInfo) == e_success)
        {
            printf("\n==Decode Procedure started==\n\n");
            do_decoding(&decInfo);
            printf("\n==Decode Successfully completed==\n");
        }
        else
        {
            printf("ERROR: Arguments are not valid\n");
            return e_failure;
        }

        return e_success;
    }
    else
    {
        printf("\nERROR: Invalid arguments!\n");
        printf("\nUsage:\n");
        printf("For Encoding : %s -e <.bmp file> <.txt file> [output file] \n", argv[0]);
        printf("For Decoding : %s -d <.bmp file> [output file]  \n\n", argv[0]);
        return e_failure;
    }

    return 0;
}
