// declaration of functions used in MP3 Tag Reader project

#include<stdio.h>        // Required for FILE data type

#ifndef HEADER_H         // If HEADER_H is not defined
#define HEADER_H         // Define HEADER_H (Header Guard start)

void Mp3_view(FILE *fptr);  
// Declaration of function to view MP3 metadata

void Mp3_edit(FILE *fptr);  
// Declaration of function to edit MP3 metadata

void edit_tag(FILE *fptr,char *tag,char *new_data);  
// Function to modify a specific tag (like TIT2, TPE1 etc.)

int bigtolittle(int num);  
// Function to convert big-endian integer to little-endian

int littletobig(int num);  
// Function to convert little-endian integer to big-endian

#endif   // End of header guard