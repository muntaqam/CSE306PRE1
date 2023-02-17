int csv_get_num_fields(char *filename, int display_fields);
int count_records(FILE *fp, bool header);
double get_max(char *filename, bool header, int field);
double get_min(char *filename, bool header, int field);
double get_mean(char *filename, bool header, int field);
void print_records(char *filename, bool header, int field, char *value);

int csv_get_num_fields(char *filename, int display_fields) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    char line[1024];
    if (fgets(line, 1024, fp)) {
        int num_fields = 0;
        char *field = strtok(line, ",");
        while (field != NULL) {
            num_fields++;
            field = strtok(NULL, ",");
        }
        if (display_fields) {
            printf("Number of fields in first record: %d\n", num_fields);
        }
    }

    fclose(fp);
}