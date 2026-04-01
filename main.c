// Main funtion
/*Name:Sammed kuranagi
Date : 25-02-2026
Description: This main functions*/


#include<stdio.h>      // Includes standard input-output functions (printf, scanf, fopen, etc.)
#include<string.h>     // Includes string functions (strcmp)
#include "header.h"    // User-defined header file (contains Mp3_view, Mp3_edit declarations)
#include<unistd.h>     // For usleep() function (delay)

int main()
{
    // Welcome message
    printf("\n*********************************************************\n");
    printf("*            WELCOME TO MP3 TAG READER                  *\n");
    printf("*********************************************************\n");

    FILE *fptr;   // File pointer to handle MP3 file

    char choice;  // Variable to store user menu choice

    do   // Loop runs until user chooses Exit
    {
        // Display menu options
        printf("\nMp3 Tag Reader Menu:\n");
        printf("\n-v. For View\n");
        printf("-e. For Edit\n");
        printf("-E. Exit\n");
        printf("\nEnter your choice : ");

        scanf(" -%c",&choice);   // Reads option after '-' symbol

        switch(choice)   // Switch based on user input
        {
            case 'v':    // View MP3 tags
            {
                char file_name[20];   // To store file name

                printf("\nEnter the file name you want to view : ");
                scanf(" %[^\n]",file_name);   // Read full file name including spaces

                // Open file in read mode
                if((fptr = fopen(file_name,"r")) == NULL)
                {    
                    printf("\n------> File not found <------\n");
                    return 7;   // Exit if file not found
                }

                char buffer[4];   // Buffer to store first 3 bytes

                fread(buffer,3,1,fptr);   // Read first 3 bytes of file
                buffer[3] = '\0';         // Null terminate
    
                // Check if file starts with "ID3" (MP3 tag identifier)
                if(strcmp(buffer,"ID3") != 0)
                {
                    printf("\n------> It is not mp3 file <------\n");
                    return 0;   // Exit if not valid MP3
                }

                Mp3_view(fptr);   // Call function to display metadata
                fclose(fptr);     // Close file
                break;            // Exit case
            }

            case 'e':    // Edit MP3 tags
            {
                char file_name[20];   // To store file name

                printf("\nEnter the file name you want to view : ");
                scanf(" %[^\n]",file_name);   // Read file name

                // Open file in read mode
                if((fptr = fopen(file_name,"r")) == NULL)
                {    
                    printf("\n------> File not found <------\n");
                    return 7;   // Exit if file not found
                }

                char buffer[5];   // Buffer for header check

                fread(buffer,3,1,fptr);   // Read first 3 bytes
                buffer[3] = '\0';         // Null terminate
    
                // Validate MP3 file
                if(strcmp(buffer,"ID3") != 0)
                {
                    printf("\n-----> It is not mp3 file <------\n");
                    return 0;   // Exit if invalid
                }

                Mp3_edit(fptr);   // Call edit function
                fclose(fptr);     // Close file
                break;            // Exit case
            }

            case 'E':   // Exit option
                for(int i = 0; i <= 100; i++)   // Loop from 0 to 100
                {
                    printf("Exiting..%d%%\r",i);  // Show exit percentage
                    fflush(stdout);              // Clear output buffer
                    usleep(5000);                // Delay for smooth animation
                }
                printf("\rExited successfully\n");   // Final exit message
                break;

            default: 
                printf("\n-----> Invalid Option <-----\n");
                return 7;   // Exit if invalid choice
        }

    }while(choice != 'E');   // Repeat menu until 'E' is selected

    return 0;   // Successful program termination
}