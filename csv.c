#include <stdio.h>
#include <string.h>

  //reading from file with fscanf() or fgets()
  //don't forget to close file with fclose(newFile)
  int mean(char *file){
    printf("inside mean\n");
    printf("%s\n", file);
    FILE *inputFile = fopen("file", "r");
    /*
    int row = 0;
    int column = 0;
    char buffer[1024]; //used to store data that fgets() reads
    
     while (fgets(buffer, 1024, inputFile)){
       //row++;
       //char* rowValue = strtok(buffer, ","); //strtok splite the input on the comma
       //printf("%s\n", buffer);
       puts(buffer);
     }//end while
    */ 
     fclose(inputFile);     
     return 0;
 }//end mean

int main(int argc, char *argv[]){
  //printf("argc is %d\n", argc);
  //printf("argv -1 is %s\n", argv[argc - 1]);

  for (int i = 0; i < argc; i++){
    if (strcmp("-mean", argv[i]) == 0){  //strcmp compares str values, ret 0 if match
      mean(argv[argc-1]);
    }
  }//end for

  return 0;
}//end main

