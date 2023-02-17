#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mean_field(int col, char *inFile){
  FILE *file = fopen(inFile, "r");
  if (inFile == NULL) {
    printf("Error opening file %s\n", inFile);
    return;
  }
  char buffer[1024]; //used to store data that fgets() reads
  double total = 0;
  double divisor = 0;
  size_t index = col;

  if (!fgets(buffer, 1024, file)){
    printf("Empty File.\n");
  }
  while (fgets(buffer, 1024, file)){
    //char *rowValue = strtok(buffer, ","); //strtok split the input on the comma
    char *row = buffer;
    size_t i = 0;
    //total += atoi(rowValue);
    //divisor++;
    for (row = strtok(row, ","); row && i < index; row = strtok(NULL, ",")){
      i++;
      if (i == index && row){
	puts(row);
      }
    }//end for		   
  }//end while 
  
  //printf("%f\n", total/divisor);
  fclose(file);
 }//end mean_field

void records_field(int field, double value, char *inFile){
  FILE *file = fopen(inFile, "r");
  if (inFile == NULL) {
    printf("Error opening file %s\n", inFile);
    return;
  }
  printf("test\n");
  fclose(file);
}//end records_field

int main(int argc, char *argv[]){
  for (int i = 0; i < argc; i++){
    if (strcmp("-mean", argv[i]) == 0){  //strcmp compares str values, ret 0 if match
      mean_field(atoi(argv[i+1]), argv[argc-1]);
    }else{
    if (strcmp("-records", argv[i]) == 0){
      records_field(atoi(argv[i+1]), atoi(argv[i+2]), argv[argc-1]);
		   }
	    }//end else
    }//end for
  return 0;
}//end main

