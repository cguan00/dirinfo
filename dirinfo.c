#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>


int main(){
  // Have the program scan the current directory
  printf("Statistics for directory: .\n");
  DIR *d = opendir(".");
  if (errno > 0){
    printf("Errno: %s\n", strerror(errno));
  }

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
