#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  //don't forget to close file with fclose(newFile)
int mean(int col, char *file){
    FILE *inputFile = fopen(file, "r"); 
    char buffer[1024]; //used to store data that fgets() reads
    double total = 0;
    double divisor = 0;
    
     while (fgets(buffer, 1024, inputFile)){
       char *rowValue = strtok(buffer, ","); //strtok split the input on the comma
       //total += atoi(buffer);
       //divisor++;
       //puts(buffer);
       while (rowValue != NULL){
	 
       printf("%s\n", rowValue);
       rowValue = strtok(NULL, ",");
       }
     }//end while

     fclose(inputFile);
     //printf("mean is %f\n", total/divisor);
     return total/divisor;
 }//end mean

int main(int argc, char *argv[]){
  for (int i = 0; i < argc; i++){
    if (strcmp("-mean", argv[i]) == 0){  //strcmp compares str values, ret 0 if match
      mean(atoi(argv[i+1]), argv[argc-1]);
    }
  }//end for

  return 0;
}//end main
