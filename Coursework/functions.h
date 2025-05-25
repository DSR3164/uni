#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct Data
{
    int day;
    int month;
    int year;
} data;


int find_and_write_dates(char *filename);
bool is_date_exist(data found);
int has_interesting_property(data found);

#endif