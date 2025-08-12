/*
 Author: Anujna Attigadde Jagadish
 Description: A simple in-memory file system operations such as creating,
 * reading, appending, renaming, deleting, and listing files. Each file
 * is stored in memory and managed by a central FileSystem structure.
 */
#include "file_system.h"
#include <pthread.h>
#include <string.h>

/// Creates and initializes a new file system
FileSystem* create_file_system() {
    FileSystem *fs = (FileSystem *)malloc(sizeof(FileSystem));
    fs->file_count = 0;
    pthread_mutex_init(&fs->mutex, NULL); // Initialize the mutex for thread safety
    return fs;
}

/// Creates a new file with the given name and data
void create_file(FileSystem *fs, const char *name, const char *data) {
    pthread_mutex_lock(&fs->mutex); // Lock the mutex to ensure thread-safe access

    if (fs->file_count >= MAX_FILES) {
        printf("File system is full!\n");
        pthread_mutex_unlock(&fs->mutex);
        return;
    }

    // Check if file already exists
    for (int i = 0; i < fs->file_count; i++) {
        if (strcmp(fs->files[i]->name, name) == 0) {
            printf("File '%s' already exists\n\n", name);
            pthread_mutex_unlock(&fs->mutex);
            return;
        }
    }

    // Allocate memory and copy file details
    File *file = (File *)malloc(sizeof(File));
    strncpy(file->name, name, MAX_FILENAME);
    strncpy(file->data, data, MAX_FILESIZE);
    file->size = strlen(data);

    fs->files[fs->file_count++] = file;
    printf("File '%s' created.\n", name);

    pthread_mutex_unlock(&fs->mutex);
}

/// Reads and prints the contents of a file
void read_file(FileSystem *fs, const char *name) {
    pthread_mutex_lock(&fs->mutex);

    // Search for the file
    for (int i = 0; i < fs->file_count; i++) {
        if (strcmp(fs->files[i]->name, name) == 0) {
            printf("Contents of '%s': %s\n", name, fs->files[i]->data);
            pthread_mutex_unlock(&fs->mutex);
            return;
        }
    }

    pthread_mutex_unlock(&fs->mutex);
    printf("File '%s' not found.\n", name);
}

/// Appends content to an existing file
void append_file(FileSystem *fs, const char *name, const char *content) {
    pthread_mutex_lock(&fs->mutex);

    // Search for the file
    for (int i = 0; i < fs->file_count; i++) {
        if (strcmp(fs->files[i]->name, name) == 0) {
            // Append the content to existing data
            strncpy(fs->files[i]->data, strcat(fs->files[i]->data, content), MAX_FILESIZE);
            printf("Contents of '%s': %s\n", name, fs->files[i]->data);
            pthread_mutex_unlock(&fs->mutex);
            return;
        }
    }

    printf("Could not find the file %s\n\n", name);
    pthread_mutex_unlock(&fs->mutex);
}

/// Renames a file by creating a new one and deleting the old
void rename_file(FileSystem *fs, const char *name, const char *newname) {
    for (int i = 0; i < fs->file_count; i++) {
        if (strcmp(fs->files[i]->name, name) == 0) {
            // Create a new file with the new name and copy data
            create_file(fs, newname, fs->files[i]->data);
            // Delete the old file
            delete_file(fs, fs->files[i]->name);
            printf("Contents of '%s': %s\n", name, fs->files[i]->data);
            return;
        }
    }

    printf("Could not find the file %s\n\n", name);
}

/// Deletes a file from the file system
void delete_file(FileSystem *fs, const char *name) {
    pthread_mutex_lock(&fs->mutex);

    for (int i = 0; i < fs->file_count; i++) {
        if (strcmp(fs->files[i]->name, name) == 0) {
            // Free the file's memory
            free(fs->files[i]);
            // Replace it with the last file in the list to avoid shifting
            fs->files[i] = fs->files[--fs->file_count];
            printf("File '%s' deleted.\n", name);
            pthread_mutex_unlock(&fs->mutex);
            return;
        }
    }

    printf("File '%s' not found.\n", name);
    pthread_mutex_unlock(&fs->mutex);
}

/// Lists all files in the file system
void list(FileSystem *fs) {
    pthread_mutex_lock(&fs->mutex);

    if (fs->file_count == 0) {
        printf("No files are present\n");
        pthread_mutex_unlock(&fs->mutex);
        return;
    }

    printf("Files: \n");
    for (int i = 0; i < fs->file_count; i++) {
        printf("%s ", fs->files[i]->name);
    }

    pthread_mutex_unlock(&fs->mutex);
    printf("\n");
}

/// Frees all memory used by the file system
void free_file_system(FileSystem *fs) {
    for (int i = 0; i < fs->file_count; i++) {
        free(fs->files[i]); // Free individual files
    }
    free(fs); // Free file system struct itself
}

