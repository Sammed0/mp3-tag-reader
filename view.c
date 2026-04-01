// Edit Function
/*Name:Sammed kuranagi
Date : 25-02-2026
Description: In this file view funtions are performed*/

#include<stdio.h>          // Standard input-output functions (printf, fread, etc.)
#include<string.h>         // String handling functions (strcmp)
#include"header.h"         // User-defined header file

// Function to display MP3 metadata
void Mp3_view(FILE *fptr)  // Takes file pointer of opened MP3 file
{
    fseek(fptr,7,SEEK_CUR);   // Skip first 7 bytes of ID3 header (version, flags, partial size)

    int count = 0;            // Variable declared (currently unused)
    char tag[5];              // To store 4-character frame ID + null character

    while(1)                  // Infinite loop to read frames one by one
    {

        // Read 4 bytes (Frame ID like TIT2, TALB, etc.)
        if(fread(tag,4,1,fptr) != 1)   // If reading fails
            break;                     // Exit loop

        tag[4] = '\0';        // Add null terminator to make it a string


        // If frame ID is all zeros, metadata section ended
        if(tag[0]==0 && tag[1]==0 &&tag[2]==0 && tag[3]==0)
            break;            // Exit loop

        int size;             // Variable to store frame size

        fread(&size,4,1,fptr);  // Read 4-byte frame size

        // Convert big-endian size to little-endian
        int len =
            ((size & 0xFF000000) >> 24) |  // Extract highest byte and move to lowest
            ((size & 0x00FF0000) >> 8)  |  // Extract second byte
            ((size & 0x0000FF00) << 8)  |  // Extract third byte
            ((size & 0x000000FF) << 24);   // Extract lowest byte and move to highest
    
        fseek(fptr, 2, SEEK_CUR);   // Skip 2 bytes of frame flags

        char data[len + 1];   // Create buffer to store frame data (+1 for '\0')

        fread(data,len,1,fptr);   // Read actual frame content

        data[len] = '\0';     // Null terminate to make it string

        // If frame is Title (TIT2)
        if((strcmp(tag,"TIT2")) == 0)
        {
            printf("\nTITLE   : %s\n",data + 1);   // Print title (skip encoding byte)
        }

        // If frame is Year (TYER)
        else if (strcmp(tag, "TYER") == 0)
        {
            printf("YEAR    : %s\n", data + 1);    // Print year
        }

        // If frame is Artist (TPE1)
        else if (strcmp(tag, "TPE1") == 0)
        {
            printf("ARTIST  : %s\n", data + 1);    // Print artist name
        }

        // If frame is Album (TALB)
        else if (strcmp(tag, "TALB") == 0)
        {
            printf("ALBUM   : %s\n", data + 1);    // Print album name
        }

        // If frame is Genre (TCON)
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("GENRE   : %s\n", data + 1);    // Print genre
        }

        // If frame is Comment (COMM)
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("COMMENT : %s\n", data + 1);    // Print comment
        }

    }  // End of while loop
}      // End of function