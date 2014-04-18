//#define O_RDONLY 0
//#define O_WRONLY 1
//#define O_RDWR 2
//#define O_CREAT 00100
//#define S_IRUSR 00400 // user has read permission
//#define S_IWUSR 00200 //user has write permission
//#define S_IROTH 00004 //others have read permission 
//#define S_IWOTH 00002 //others have write permission

#include "file_structure.h"
#include<string.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

int test=0;

int getNewFileId()
{
    static int file_id = 1;
    return file_id++;
}


int open(const char *path, int oflags) {

    int f_compare=1;
    bool found = false;
    FD_node *fd1 = fd_head;
    File *temp = file_head;
    if (temp == NULL) {
        return open(path, oflags, 00200);
    } else {
        cout << "Here at open else"<<endl;
        while (temp != NULL) {
         //file_head->next = file_scan; // file_scan is a pointer to File
            //f_compare = strcmp(file_scan->filename,path);
            // determine whether the file is there or not
            f_compare = strcmp(temp->filename, path);
            if (f_compare == 0) {
                found = true;
             //   fd1->oflag = oflags;
                return temp->file_no;
            } else {
                temp = temp->next;
            }
        } 
   }
      return open(path, oflags, 00200);
}

File* getNewFileNode(int fileId, mode_t mode, const char *path)
{
    File *new_file = new File;
    new_file->rd_count = 0;
    new_file->wr_count = 0;
    new_file->rw_mode = mode;
    new_file->next = NULL;
    new_file->file_no = fileId;
     //source:path, destination: file1->filename
    strcpy(new_file->filename, path);
    return (new_file);
}

FD_node* getNewFdNode(int fileId, const char* path, int oflags, File *file)
{
    if (file == NULL) {
        //print error
    }
    FD_node *new_fd = new FD_node;
    new_fd->oflag = oflags;
    strcpy(new_fd->filename, path);
    new_fd->file_id = fileId; 
    new_fd->rd_p = 0;
    new_fd->wr_p = 0;
    new_fd->f_pntr = file;
    new_fd->next = NULL;
}

int open(const char* path, int oflags, mode_t mode) {
    
    int newFileId = getNewFileId();
    File *new_file = getNewFileNode(newFileId, mode, path);
    
    //new_file->data = ""; //data to be written using write()call   
    //Always add at head
    if (file_head != NULL) {
        new_file->next = file_head;
        file_head = new_file;
    } else {
        file_head = new_file;
    }
        // creates new fd node and always adds at the head
    FD_node *new_fd = getNewFdNode(newFileId, path, oflags, new_file);
    //Always add at head
    if (fd_head != NULL) {
        new_fd->next = fd_head;
        fd_head = new_fd;
    } else {
        fd_head = new_fd;
    }
    return newFileId;
}



ssize_t read(int fildes, void *buf, size_t nbyte)
{
    /*fildes - fildes of a file to be read
    void *buf - pointer to void, reads the data to buf
    nbyte is the size of data to be read. 
     * scenarios: 
     * 1. check if fildes is valid (0/neg)
     * 2. nbyte shouldn't be 0 or greater than the actual file size
    */
}

size_t write(int fildes, const void *buf, size_t nbytes)
{
   /* fd It is the file descriptor
    * void *buf  points to a character array, which can be used to store content obtained from the file pointed to by fd.
    * nbytes specifies the number of bytes to be written from the file into the character array.
    * 
    */
    if(fildes!=0)
    {
        //traverse through fd node
    }
}

int main() {
    int file_desc1 = 0, file_desc2 = 0, file_desc3 = 0, file_desc4 = 0, file_desc5 = 0;
    
    file_desc2 = open("mars.txt", 2);
    cout << "mars.txt " << file_desc2 << endl;
    
   // file_desc5 = open("mars.txt", 2);
    cout << "mars.txt " << open("mars.txt", 2) << endl;

    file_desc3 = open("venus.txt", 2);
    cout << "venus.txt " << file_desc3 << endl;
    
    file_desc1 = open("earth.txt", 2);
    cout << "earth.txt " << file_desc1 << endl;

    file_desc4 = open("pluto.txt", 2);
    cout << "pluto.txt " << file_desc4 << endl;
    return 0; 
}
