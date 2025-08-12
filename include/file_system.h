#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

// #include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME 50
#define MAX_FILESIZE 1024

typedef struct {
    char name[MAX_FILENAME];
    char data[MAX_FILESIZE];
    int size;
} File;

typedef struct {
    File *files[MAX_FILES];
    int file_count;
    pthread_mutex_t mutex;
} FileSystem;

// Function prototypes
FileSystem* create_file_system();
void create_file(FileSystem *fs, const char *name, const char *data);
void read_file(FileSystem *fs, const char *name);
void delete_file(FileSystem *fs, const char *name);
void append_file(FileSystem *fs, const char *name, const char *content);
void free_file_system(FileSystem *fs);
void rename_file(FileSystem *fs, const char *name, const char *newname);
void list(FileSystem *fs);

#endif // FILE_SYSTEM_H
