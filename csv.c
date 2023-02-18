#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//mean field Display the arithmetic mean (average) value in
//the indicated field of the data records. The first field is
//numbered 0. This option ignores non-numeric data in the indicated
//field. If there is no numeric data in the indicated field in any
//of the data records the program exits with error code EXIT_FAILURE.
//See how fields are identified when the -h option is used.

void mean_field(int col, char *inFile){
  FILE *file = fopen(inFile, "r");
  if (inFile == NULL) {
    printf("Error opening file %s\n", inFile);
    return;
  }
  char buffer[1024]; //used to store data that fgets() reads
  double total = 0;
  double divisor = 0;
  
  if (!fgets(buffer, 1024, file)){
    printf("Empty File.\n");
  }

  while (fgets(buffer, sizeof buffer, file) != NULL){
    char *row = buffer;
    row = strtok(buffer, "\",");
    while (row != NULL){      
      //puts(row);
      //printf("%d\n", row[0]);
      total += atof(row);
      divisor++;
      row = strtok(NULL, "\",");
     }	   
  }//end while 
  
  printf("%f\n", total/divisor);
  fclose(file);
 }//end mean_field

//-records field value Display the records from file containing
//value in the the indicated field. The first field is numbered 0.
//Value is formatted according to the same rules as data in fields.
//See how fields are identified when the -h option is used.
 
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

