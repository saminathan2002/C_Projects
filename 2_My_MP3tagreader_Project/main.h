#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

// ===============================
// OPERATIONS
// ===============================

// 1. Help Guide
void id3_help_guide(); 

// 2. View ID3 Metadata
void id3_view(char *, FILE *);         
void display_id3_details(char *, char *); 

// 3. Edit ID3 Metadata
void id3_edit(char *, char *, char *, FILE *); 
int check_frame_id(char *, char *);  

// ===============================
// ERROR HANDLING
// ===============================
void display_invalid_arg(char *); 
int mp3file_check(char *);        

// ===============================
// ENDIAN CONVERSION
// ===============================
unsigned int convert_big_to_little(const unsigned char *); 
void convert_little_to_big(char *, int);                   

#endif