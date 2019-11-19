#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

// Your program should handle user input as follows:
// If a command line argument is entered, use that as the directory to scan.
// If not, the program should ask the user to enter a directory to scan.
// In either case, don't assume your user knows what they are doing, if an invalid directory is entered, take reasonable action (*ahem* errno *cough cough*)


int main(int argc, char *argv[]){
  DIR *d;

  char input[100];
  if (argc == 1){
    printf("Please enter directory name:\n");
    fgets(input, sizeof input, stdin);
    input[strlen(input) - 1] = '\0';
    d = opendir(input);
  } else{
    d = opendir(argv[1]);
  }
  if (errno > 0){
    printf("Errno: %s\n", strerror(errno));
  }

  chdir(input);

  printf("Statistics for directory: \n");

  // show the total size of all the regular files the directory
  struct dirent *file = readdir(d);
  int dirSize = 0;
  while (file != NULL){
    struct stat info;
    stat(file->d_name, &info);
    if (errno > 0){
      printf("Errno: %s\n", strerror(errno));
    }
    dirSize += info.st_size;
    file = readdir(d);
  }
  printf("Total Directory Size: %d Bytes\n", dirSize);

  // specify which files are directories (if any)
  printf("Directories:\n");
  rewinddir(d);
  file = readdir(d);
  while (file != NULL){
    if (file->d_type == DT_DIR){
      printf("\t%s\n", file->d_name);
    }
    file = readdir(d);
  }

  // list all the files in the directory
  printf("Regular files:\n");
  rewinddir(d);
  file = readdir(d);
  while (file != NULL){
    if (file->d_type == DT_REG){
      printf("\t%s\n", file->d_name);
    }
    file = readdir(d);
  }

  return 0;
}
