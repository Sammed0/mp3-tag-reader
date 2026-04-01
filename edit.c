/*Name:Sammed kuranagi
Date : 25-02-2026
Description: In this file edit functions are performed*/

// Edit Function

#include<stdio.h>      // standard input-output functions
#include<string.h>     // string handling functions (strcmp, strlen)
#include "header.h"    // user-defined header file
#include<unistd.h>     // for usleep()
#include<stdlib.h>     // for malloc(), free()

// Function to choose which tag to edit
void Mp3_edit(FILE *fptr)
{
    char option;            // stores user choice
    char new_data[100];     // stores new tag value entered by user

    printf("\nWhat you want to edit : \n");   // display options
    printf("-t. Title\n-a. Artist\n-A. Album\n-y. Year\n-g. Genre\n-c. Comment\n");
    printf("\nEnter your choice : ");
    scanf(" -%c",&option);  // read option

    switch(option)          // check selected option
    {
        case 't':
        printf("\nEnter what you want to edit in title : ");
        scanf(" %[^\n]",new_data);        // read new title
        edit_tag(fptr,"TIT2",new_data);   // call edit function for Title
        break;

        case 'a':
        printf("\nEnter what you want to edit in artist name : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TPE1",new_data);   // edit Artist
        break;

        case 'A':
        printf("\nEnter what you want to edit in album : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TALB",new_data);   // edit Album
        break;

        case 'y':
        printf("\nEnter what you want to edit in year : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TYER",new_data);   // edit Year
        break;

        case 'g':
        printf("\nEnter what you want to edit in genre : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"TCON",new_data);   // edit Genre
        break;

        case 'c':
        printf("\nEnter what you want to edit in comment : ");
        scanf(" %[^\n]",new_data);
        edit_tag(fptr,"COMM",new_data);   // edit Comment
        break;

        default:
            printf("\n-------> Invalid option <-------\n");  // invalid choice
    }
}


// Function to modify selected tag
void edit_tag(FILE *fptr,char *tag,char *new_data)
{
    FILE *new_file;   // file pointer for temporary file

    if((new_file = fopen("temp.mp3","w")) == NULL)  // create temp file
    {
        printf("\n------> File not found <------\n");
        return ;
    }

    rewind(fptr);   // move original file pointer to beginning

    char copy[100];

    fread(copy,10,1,fptr);              // copy first 10 bytes (ID3 header)
    fwrite(copy,10,1,new_file);         // write header to new file

    char name[5],flag[2];int size;

    // loop to read each frame
    while((fread(name,4,1,fptr)) == 1)
    {
        name[4] = '\0';   // null terminate frame ID

        // stop if frame ID is zero
        if(name[0]==0 && name[1]==0 && name[2]==0 && name[3]==0)
        {
            break;
        }

        fread(&size,4,1,fptr);   // read frame size
        fread(flag,2,1,fptr);    // read frame flags

        int new_len = bigtolittle(size);   // convert size from big endian

        char *data = malloc(new_len);      // allocate memory for frame data
        if (data == NULL)
        {
            printf("-----> Memory allocation failed <-----\n");
            return;
        }

        fread(data,new_len,1,fptr);   // read frame data

        // if current frame matches selected tag
        if((strcmp(name,tag)) == 0)
        {
            fwrite(name,4,1,new_file);   // write frame ID

            int len = strlen(new_data) + 1;   // length of new text (+null)
            int frame_size = len + 1;        // +1 for encoding byte

            int big_len = littletobig(frame_size);  // convert to big endian
            fwrite(&big_len,4,1,new_file);   // write new frame size

            fwrite(flag,2,1,new_file);       // write flags

            char enc = 0x00;                 // encoding type (ISO-8859-1)
            fwrite(&enc,1,1,new_file);       // write encoding byte

            fwrite(new_data,len,1,new_file); // write new data
        }
        else
        {
            // if not selected tag, copy original frame
            fwrite(name,4,1,new_file);
            fwrite(&size,4,1,new_file);
            fwrite(flag,2,1,new_file);
            fwrite(data,new_len,1,new_file);
        }

        free(data);   // free allocated memory
    }

    // ---- copy remaining audio part ----
    char buffer;

    while((fread(&buffer,1,1,fptr)) == 1)   // read remaining bytes
    {
        fwrite(&buffer,1,1,new_file);       // write to new file
    }   

    remove("sample.mp3");        // delete old file
    rename("temp.mp3","sample.mp3");   // rename temp to original
    fclose(new_file);            // close new file
    printf("\n");

    // editing animation
    for(int i = 0; i <= 100; i++)
    {
        printf("Editing..%d%%\r",i);
        fflush(stdout);
        usleep(5000);
    }
    printf("\rEdited successfully\n");
}


// Convert big-endian to little-endian
int bigtolittle(int num)
{
   return ((num & 0xFF000000) >> 24) |
    ((num & 0x00FF0000) >> 8)  |
    ((num & 0x0000FF00) << 8)  |
    ((num & 0x000000FF) << 24);
}


// Convert little-endian to big-endian
int littletobig(int num)
{
    return ((num & 0x000000FF) << 24) |
    ((num & 0x0000FF00) << 8)  |
    ((num & 0x00FF0000) >> 8)  |
    ((num & 0xFF000000) >> 24);
}