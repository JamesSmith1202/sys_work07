#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int generate_random(){
  int fd = open("/dev/random", O_RDONLY);
  if(fd == -1){
    printf("%d: %s\n", errno, strerror(errno));
  }
  int i; 
  if(read(fd,&i, sizeof(i)) < sizeof(i)){
    printf("%d: %s\n", errno, strerror(errno));
  }
  if(close(fd) == -1){
    printf("%d: %s\n", errno, strerror(errno));
  }
  return i;
}

int main(){
  int size = 10;
  int counter = 0;
  int arr[size];
  int arr2[size];
  int fd;

  printf("Generating Random Numbers...\n");
  
  for(;counter < size; counter++){
    arr[counter] = generate_random();
    printf("random %d: %d\n", counter, arr[counter]);
  }

  printf("\nWriting numbers to file...\n");
  fd = open("numbers", O_CREAT | O_WRONLY, 0644);
  if (fd == -1){
    printf("%d: %s\n", errno, strerror(errno));
  }

  if(write(fd, arr, sizeof(size)*size) < sizeof(size)*size){
    printf("%d: %s\n", errno, strerror(errno));
  }

  if(close(fd) == -1){
    printf("%d: %s\n", errno, strerror(errno));
  }

  printf("\nReading numbers from file...\n");

  fd = open("numbers", O_RDONLY);
  if (fd == -1){
    printf("%d: %s\n", errno, strerror(errno));
  }

  if(read(fd,&arr2, sizeof(size)*size) < sizeof(size)*size){
    printf("%d: %s\n", errno, strerror(errno));
  }
  
  if(close(fd) == -1){
    printf("%d: %s\n", errno, strerror(errno));
  }

  printf("\nVerification that written values were the same:\n");
  for(counter=0;counter<size;counter++){
    printf("random %d: %d\n", counter, arr2[counter]);
  }
}
