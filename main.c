#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELD_LENGTH 256

void display_usage() {
  printf("Usage: csv [-frh] [-max field] [-min field] [-mean field] [-records field value] file\n");
}


//-f Display the number of fields in the first record of file.
void display_field_counts(FILE* csv_file) {
  char line[MAX_LINE_LENGTH];
  char field[MAX_FIELD_LENGTH];
  int field_count = 0;

  if (fgets(line, MAX_LINE_LENGTH, csv_file)) {
    char* token = strtok(line, ",");
    while (token != NULL) {
      field_count++;
      token = strtok(NULL, ",");
    }
    printf("Number of fields in the first record: %d\n", field_count);
  } else {
    printf("Error: Empty file\n");
  }
}


//-r Display the number of data records in file. If -h is not given this is the number of lines in the file. If -h is given this is one less than the number of lines in the file.
void display_record_count(FILE* csv_file, int ignore_header) {
  char line[MAX_LINE_LENGTH];
  int record_count = 0;

  while (fgets(line, MAX_LINE_LENGTH, csv_file)) {
    if (ignore_header) {
      ignore_header = 0;
      continue;
    }
    record_count++;
  }

  printf("Number of data records: %d\n", record_count);
}

//-max field Display the maximum value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.
void csv_max(FILE* fp,int max_field){

   
    char line[MAX_LINE_LENGTH];
    int max = 0;
    int first_field = 1;

    if (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char *field = strtok(line, ",");
        double fieldnum = atof(field);
        //printf("First field: %f\n", fieldnum);
        max=fieldnum;       
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char* token = strtok(line, ",");
        double num = atof(token);
        
        if (first_field || num > max) {
            max = num;
            first_field = 0;
        }
    }

    printf("Biggest number in the first field: %d\n", max);
    fclose(fp);
}

//-min field Display the minimum value in the indicated field of the data records. The first field is numbered 0. This option ignores non-numeric data in the indicated field. If there is no numeric data in the indicated field in any of the data records the program exits with error code EXIT_FAILURE. See how fields are identified when the -h option is used.
void csv_min(FILE* fp,int min_field){

   
    char line[MAX_LINE_LENGTH];
    int min = 0.0;
    int first_field = 1;

    if (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char *field = strtok(line, ",");
        double fieldnum = atof(field);
      //  printf("First field: %f\n", fieldnum);
        min=fieldnum;
        
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        char* token = strtok(line, ",");
        double num = atof(token);
        
        if (first_field || num < min) {
            min = num;
            first_field = 0;
        }
    }

    printf("Smallest number in the first field: %d\n", min);
    fclose(fp);

}

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
    exit(EXIT_FAILURE);
  }
  char buffer[1024]; //used to store data that fgets() reads
  double total = 0;
  double divisor = 0;
  
  if (!fgets(buffer, 1024, file)){
    printf("Empty File.\n");
    exit(EXIT_FAILURE);
  }

  while (fgets(buffer, sizeof buffer, file) != NULL){
    char *row = buffer;
    row = strtok(buffer, "\"");
    while (row != NULL){      
      //puts(row);
      total += atof(row);
      divisor++;
      row = strtok(NULL, "\"");
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


int main(int argc, char *argv[]) {
    int i;
    FILE* csv_file;
    int ignore_header = 0;
    int dataRecords=-1;
    int num_field=-1; //-f
    int max_field = -1;
    int min_field = -1; //-min
    int mean_field = -1;
    int records_field = -1;
    int records_value = -1;
    int minfieldindex=0;
    int maxfieldindex=0;
    
    if (argc < 2) {
        display_usage();
        return 1;
    }
    
    for (i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            ignore_header = 1;
            
        } else if (strcmp(argv[i], "-f") == 0) {
            num_field = 0;
           
        } else if (strcmp(argv[i], "-r") == 0) {
           
        }else if (strcmp(argv[i], "-max") == 0) {
           max_field = atoi(argv[i + 1]);
           maxfieldindex=atoi(argv[i + 1]);
           i++;
        } else if (strcmp(argv[i], "-min") == 0) {
           //printf("min_field args: %d%s\n",i,argv[i]);
            min_field = atoi(argv[i + 1]);
            minfieldindex=atoi(argv[i + 1]);
           // printf("min_field value: %d\n",minfieldindex);
            i++;
        } else if (strcmp(argv[i], "-mean") == 0) {
            mean_field = atoi(argv[i + 1]) - 1;
            i++;
        } else if (strcmp(argv[i], "-records") == 0) {
            records_field = atoi(argv[i + 1]) - 1;
            records_value = atoi(argv[i + 2]);
            i += 2;
        } else {
            printf("going here in dispkay usage: %d\n",max_field);
            display_usage();
            return 1;
        }
    }

    //opening file 
    csv_file = fopen(argv[argc - 1], "r");
    if (csv_file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }
    

//option to excecute
    if (num_field != -1) {
        display_field_counts(csv_file);
    }
    if (records_field != -1) {
        display_field_counts(csv_file);
    }  
    if (min_field != -1) {
        // Implement minimum field functionality
        csv_min(csv_file,minfieldindex);
    }
    if (max_field != -1) {
        // Implement minimum field functionality
        //printf("im here in the maxfield!=-1 \n");
        csv_max(csv_file,maxfieldindex);
    }
    if (mean_field != -1) {
        // Implement mean field functionality
        // ...
    }
    
    if (records_field != -1) {
        // Implement records field functionality
        // ...
    }
    
}
