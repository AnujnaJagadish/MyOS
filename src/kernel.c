/*
 Author: Anujna Attigadde Jagadish
 Description: Kernel simulator
 This is tasked to initialize and load the file system. Also allows user interaction
 */
#include <stdio.h>
#include <file_system.h>
#include <pthread.h>

enum UserInput {
  CREATE_FILE,
  DELETE_FILE,
  RENAME_FILE,
  APPEND_FILE,
  READ_FILE,
  LIST,
  EXIT,
  INVALID
};

enum UserInput mapInputToEnum(const char *input) {
  if (strcmp(input, "cr") == 0) {
    return CREATE_FILE;
  } else if (strcmp(input, "d") == 0) {
    return DELETE_FILE;
  } else if (strcmp(input, "rn") == 0) {
    return RENAME_FILE;
  } else if (strcmp(input, "a") == 0) {
    return APPEND_FILE;
  } else if (strcmp(input, "r") == 0) {
    return READ_FILE;
  } else if (strcmp(input, "ls") == 0) {
    return LIST;
  } else if (strcmp(input, "exit") == 0) {
    return EXIT;
  } else {
    return INVALID;
  }
};

typedef struct {
    FileSystem *fs;
    char name[MAX_FILENAME];
    char data[MAX_FILESIZE];
} ThreadArgs;

// Wrapper function to call create_file
void* thread_create_file(void* arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    create_file(args->fs, args->name, args->data);
    free(args); 
    return NULL;
}

int main() {
  printf("Hello, this is a simulation for an OS\n");

  printf("This operating system supports file system operations and can"
         " handle concurrent requests, by protecting the file system using mutex just for"
         " simulation.\n");

  printf("For demonstration, first step is to show the concurrent operation\n");

  FileSystem *fsdemo = create_file_system();

  pthread_t threads[10]; 

  for (int i = 0; i < 10; i++) {
      ThreadArgs *args = malloc(sizeof(ThreadArgs));
      snprintf(args->name, sizeof(args->name), "file_%d.txt", i);
      snprintf(args->data, sizeof(args->data), "file content %d.txt", i);
      args->fs = fsdemo;
      pthread_create(&threads[i], NULL, thread_create_file, args);
  }

  for (int i = 0; i < 10; i++) {
      pthread_join(threads[i], NULL);
  }

  free_file_system(fsdemo);

  printf("\n\nNext, we ask the user to test the file system\n\n");

  int to_exit = 1;
  FileSystem *fs = create_file_system();
  while (to_exit) {

    printf("\n\nEnter one of the operations \n"
           "1. cr -> creates a File\n"
           "2. d -> deletes an existing file\n"
           "3. rn -> renames an existing file\n"
           "4. a -> appends given file's contents\n"
           "5. r -> reads the given file and outputs to console\n"
           "6. ls -> lists all the existing files in the file system\n"
           "7. exit -> Exit from the OS\n"
           );

    char input[50];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    enum UserInput selection = mapInputToEnum(input);
    switch (selection) {
      case CREATE_FILE:
        printf("Enter the file name\n");
        char file_name[MAX_FILENAME];
        char content[200];
        fgets(file_name, sizeof(file_name), stdin);
        file_name[strcspn(file_name, "\n")] = 0;
        printf("Enter the file content\n");
        fgets(content, sizeof(content), stdin);
        content[strcspn(content, "\n")] = 0;
        create_file(fs, file_name, content);
        break;
      case DELETE_FILE:
        printf("Enter the file name to delete\n");
        char file_name_deletion[50];
        fgets(file_name_deletion, sizeof(file_name_deletion), stdin);
        file_name_deletion[strcspn(file_name_deletion, "\n")] = 0;
        delete_file(fs, file_name_deletion);
        break; 
      case APPEND_FILE:
        printf("Enter the file name to be appended\n");
        char file_name_append[50];
        char file_cont_append[50];
        fgets(file_name_append, sizeof(file_name_append), stdin);
        file_name_append[strcspn(file_name_append, "\n")] = 0;
        printf("Enter the file content to append\n");
        fgets(file_cont_append, sizeof(file_cont_append), stdin);
        file_cont_append[strcspn(file_cont_append, "\n")] = 0;
        append_file(fs, file_name_append, file_cont_append);
        break;
      case RENAME_FILE:
        printf("Enter the file name to rename\n");
        char file_name_rename[50];
        char new_file_name[50];
        fgets(file_name_rename, sizeof(file_name_rename), stdin);
        file_name_rename[strcspn(file_name_rename, "\n")] = 0;
        printf("Enter a new name\n");
        fgets(new_file_name, sizeof(new_file_name), stdin);
        new_file_name[strcspn(new_file_name, "\n")] = 0;
        rename_file(fs, file_name_rename, new_file_name);
        break;
      case READ_FILE:
        printf("Enter the name of the file\n");
        char filename[50];
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = 0;
        read_file(fs,filename);
        break;
      case LIST:
        list(fs);
        break;
      case INVALID:
        printf("Invalid entry\n");
        break;
      case EXIT:
        printf("Exiting\n");
        to_exit = 0;
    }
  }

  free_file_system(fs);
  return 0;
}

