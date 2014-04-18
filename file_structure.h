/* 
 * File:   File_Structure.h
 * Author: Gowrima
 *
 * Created on March 2, 2013, 2:56 PM
 */

#ifndef FILE_STRUCTURE_H
#define	FILE_STRUCTURE_H
#include<iostream>
#include<string.h>
#include<stdlib.h>

//#define O_RDONLY 0
//#define O_WRONLY 1
//#define O_RDWR 2
//#define O_CREAT 00100
//#define S_IRUSR 00400 // user has read permission
//#define S_IWUSR 00200 //user has write permission
//#define S_IROTH 00004 //others have read permission 
//#define S_IWOTH 00002 //others have write permission


/*
 * Linkedlist of file desc nodes. 
 * file desc Node - read pointer , write pointer, pointer to struct FILE
 * Struct FILE - number of read pointers (read_count), number of write pointers (write_count), buffer (data of the file), R/W privileges 
 * 
 * Open int open(filename)
 * Read void read(fd, buf, size)
 * Delete void delete(fd)
 * Find 
 *      
 */


struct FD_node
{
    //pointer to a number (fd) which would match the fd passed in read call with the fd in the file desc node
    int oflag;
    char filename[50];
    int file_id;
    char* rd_p;                      //read pointer
    char* wr_p;                      //write pointer
    struct File *f_pntr;           //f_pntr is a pointer to struct file
    struct FD_node *next;
} *fd_head = NULL, *fd_temp = NULL;

struct File
{
    char filename[10];
    char data[1000];
    int rd_count;       //number of read
    int wr_count;       //number of writers
    int rw_mode;             //rw = mode
    File *next;
    int file_no;
}  *file_head = NULL;
struct File *file_temp = NULL;

//      http://pubs.opengroup.org/onlinepubs/000095399/functions/open.html
//      returns fd of type int

typedef unsigned int mode_t;
int open(const char *path, int oflags, mode_t mode);

//-----------------------------------------------------------------------------

//      read() attempts to read up to count bytes from file descriptor fd into the
//       buffer starting at buf.
//
//       If count is zero, read() returns zero and has no other results.  If count is
//       greater than SSIZE_MAX, the result is unspecified.
//       the number of bytes read is returned (zero indicates end of file),
//       and the file position is advanced by this number.
//      int read(int fd, char buf[], int size);

int read(int fd, void* buf, int size);

//-----------------------------------------------------------------------------

/*  TO CREATE a new file for writing only or rewrite a existing file
 * Success : return: lowest available integer file descpritor
 * Failure : returns -1
 * Arguments:
 * path is a character pointer to the file to be created
 * mode is a value of type mode_t for the access permissions
 */
//int creat(const char*path, mode_t mode);

//------------------------------------------------------------------------------

#endif	/* FILE_STRUCTURE_H */
