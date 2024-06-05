#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
  
#define MAX_LINE_LEN 1024

int main(void) {
    FILE *fp;
    char line[MAX_LINE_LEN];
    char *token;
    int line_count = 0;

    // Initialize variables for calculating averages
    double national_total = 0.0;
    int national_count = 0;
    double prov_totals[4] = {0.0};
    int prov_counts[4] = {0};
    double canada_year_totals[7] = {0.0};
    int canada_year_counts[7] = {0};
    double quebec_year_totals[7] = {0.0};
    int quebec_year_counts[7] = {0};
    double ontario_year_totals[7] = {0.0};
    int ontario_year_counts[7] = {0};
    double alberta_year_totals[7] = {0.0};
    int alberta_year_counts[7] = {0};
    double british_columbia_year_totals[7] = {0.0};
    int british_columbia_year_counts[7] = {0};
    double canada_age_totals[3] = {0.0};
    int canada_age_counts[3] = {0};
    double quebec_age_totals[3] = {0.0};
    int quebec_age_counts[3] = {0};
    double ontario_age_totals[3] = {0.0};
    int ontario_age_counts[3] = {0};
    double alberta_age_totals[3] = {0.0};
    int alberta_age_counts[3] = {0};
    double british_columbia_age_totals[3] = {0.0};
    int british_columbia_age_counts[3] = {0};

    // Open file
    fp = fopen("statscan_diabetes.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    // Read file line by line
    while (fgets(line, MAX_LINE_LEN, fp)) {
        // Skip the header line
        if (line_count == 0) {
            line_count++;
            continue;
        }

        // Parse the line
        token = strtok(line, ",");
        int col_count = 0;
        char *ref_date, *geo, *age_group, *sex, *value;
        while (token != NULL) {
            switch (col_count) {
                case 0:
                    ref_date = token;
                    //printf("%s", ref_date);
                    break;
                case 1:
                    geo = token;
                    //printf("%s", geo);
                    break;
                case 3:
                    age_group = token;
                    //printf("%s", age_group);
                    break;
                case 4:
                    sex = token;
                    //printf("%s", sex);
                    break;
                case 13:
                    value = token;
                    //printf("%s\n", value);
                    break;
            }
            token = strtok(NULL, ",");
            col_count++;
        }
        
        // Remove double quotations from ref_date
        char cleaned_ref_date[MAX_LINE_LEN];
        int ten = strlen(ref_date);
        if (ten >= 2 && ref_date[0] == '"' && ref_date[ten-1] == '"') {
          strncpy(cleaned_ref_date, ref_date+1, ten-2);
          cleaned_ref_date[ten-2] = '\0';
        } else {
          strcpy(cleaned_ref_date, ref_date);
        }
        //printf("%s",cleaned_ref_date);
      
        // Remove double quotations from geo
        char cleaned_geo[MAX_LINE_LEN];
        int ren = strlen(geo);
        if (ren >= 2 && geo[0] == '"' && geo[ren-1] == '"') {
          strncpy(cleaned_geo, geo+1, ren-2);
          cleaned_geo[ren-2] = '\0';
        } else {
          strcpy(cleaned_geo, geo);
        }
        //printf("%s",cleaned_geo);
      
        // Remove double quotations from age_group
        char cleaned_age_group[MAX_LINE_LEN];
        int gen = strlen(age_group);
        if (gen >= 2 && age_group[0] == '"' && age_group[gen-1] == '"') {
          strncpy(cleaned_age_group, age_group+1, gen-2);
          cleaned_age_group[gen-2] = '\0';
        } else {
          strcpy(cleaned_age_group, age_group);
        }
        //printf("%s",cleaned_age_group);
      
        // Remove double quotations from value
        char cleaned_value[MAX_LINE_LEN];
        int len = strlen(value);
        if (len >= 2 && value[0] == '"' && value[len-1] == '"') {
          strncpy(cleaned_value, value+1, len-2);
          cleaned_value[len-2] = '\0';
        } else {
          strcpy(cleaned_value, value);
        }

        // Convert cleaned_value to a double using atof()
        double d_value = atof(cleaned_value);
        //printf("%.1f\n", d_value);
      
      // Calculate provincial and national averages
      if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
        if (d_value > 0) {
            national_total += d_value;
            national_count++;
          }
      } else if (strcmp(cleaned_geo, "Ontario") == 0) {
        if (d_value > 0) {
            prov_totals[0] += d_value;
            prov_counts[0]++;
          }
      } else if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            prov_totals[1] += d_value;
            prov_counts[1]++;
          }
      } else if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            prov_totals[2] += d_value;
            prov_counts[2]++;
          }
      } else if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            prov_totals[3] += d_value;
            prov_counts[3]++;
          }
      }

      // Update Canada's year totals
      if (strcmp(cleaned_ref_date, "2015") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[0] += d_value;
            canada_year_counts[0]++;
          }
        }
          
      } else if (strcmp(cleaned_ref_date, "2016") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[1] += d_value;
            canada_year_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2017") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[2] += d_value;
            canada_year_counts[2]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2018") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[3] += d_value;
            canada_year_counts[3]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2019") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[4] += d_value;
            canada_year_counts[4]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2020") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[5] += d_value;
            canada_year_counts[5]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2021") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_year_totals[6] += d_value;
            canada_year_counts[6]++;
          }
        }
      }
      
      // Update Quebec's year totals
      if (strcmp(cleaned_ref_date, "2015") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[0] += d_value;
            quebec_year_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2016") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[1] += d_value;
            quebec_year_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2017") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[2] += d_value;
            quebec_year_counts[2]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2018") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[3] += d_value;
            quebec_year_counts[3]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2019") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[4] += d_value;
            quebec_year_counts[4]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2020") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[5] += d_value;
            quebec_year_counts[5]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2021") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_year_totals[6] += d_value;
            quebec_year_counts[6]++;
          }
        }
      }

      // Update Ontario's year totals
      if (strcmp(cleaned_ref_date, "2015") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[0] += d_value;
            ontario_year_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2016") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[1] += d_value;
            ontario_year_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2017") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[2] += d_value;
            ontario_year_counts[2]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2018") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[3] += d_value;
            ontario_year_counts[3]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2019") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[4] += d_value;
            ontario_year_counts[4]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2020") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[5] += d_value;
            ontario_year_counts[5]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2021") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_year_totals[6] += d_value;
            ontario_year_counts[6]++;
          }
        }
      }

      // Update Alberta's year totals
      if (strcmp(cleaned_ref_date, "2015") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[0] += d_value;
            alberta_year_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2016") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[1] += d_value;
            alberta_year_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2017") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[2] += d_value;
            alberta_year_counts[2]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2018") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[3] += d_value;
            alberta_year_counts[3]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2019") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[4] += d_value;
            alberta_year_counts[4]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2020") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[5] += d_value;
            alberta_year_counts[5]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2021") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_year_totals[6] += d_value;
            alberta_year_counts[6]++;
          }
        }
      }
      
      // Update British Columbia's year totals
      if (strcmp(cleaned_ref_date, "2015") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[0] += d_value;
            british_columbia_year_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2016") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[1] += d_value;
            british_columbia_year_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2017") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[2] += d_value;
            british_columbia_year_counts[2]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2018") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[3] += d_value;
            british_columbia_year_counts[3]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2019") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[4] += d_value;
            british_columbia_year_counts[4]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2020") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[5] += d_value;
            british_columbia_year_counts[5]++;
          }
        }
      } else if (strcmp(cleaned_ref_date, "2021") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_year_totals[6] += d_value;
            british_columbia_year_counts[6]++;
          }
        }
      }
  
      // Update Canada's age group totals
      if (strcmp(cleaned_age_group, "35 to 49 years") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_age_totals[0] += d_value;
            canada_age_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "50 to 64 years") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_age_totals[1] += d_value;
            canada_age_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "65 years and over") == 0) {
        if (strcmp(cleaned_geo, "Canada (excluding territories)") == 0) {
          if (d_value > 0) {
            canada_age_totals[2] += d_value;
            canada_age_counts[2]++;
          }
        }
      }

      // Update Quebec's age group totals
      if (strcmp(cleaned_age_group, "35 to 49 years") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_age_totals[0] += d_value;
            quebec_age_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "50 to 64 years") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_age_totals[1] += d_value;
            quebec_age_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "65 years and over") == 0) {
        if (strcmp(cleaned_geo, "Quebec") == 0) {
          if (d_value > 0) {
            quebec_age_totals[2] += d_value;
            quebec_age_counts[2]++;
          }
        }
      }

      // Update Ontario's age group totals
      if (strcmp(cleaned_age_group, "35 to 49 years") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_age_totals[0] += d_value;
            ontario_age_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "50 to 64 years") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_age_totals[1] += d_value;
            ontario_age_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "65 years and over") == 0) {
        if (strcmp(cleaned_geo, "Ontario") == 0) {
          if (d_value > 0) {
            ontario_age_totals[2] += d_value;
            ontario_age_counts[2]++;
          }
        }
      }

      // Update Alberta's age group totals
      if (strcmp(cleaned_age_group, "35 to 49 years") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_age_totals[0] += d_value;
            alberta_age_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "50 to 64 years") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_age_totals[1] += d_value;
            alberta_age_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "65 years and over") == 0) {
        if (strcmp(cleaned_geo, "Alberta") == 0) {
          if (d_value > 0) {
            alberta_age_totals[2] += d_value;
            alberta_age_counts[2]++;
          }
        }
      }

      // Update British Columbia's age group totals
      if (strcmp(cleaned_age_group, "35 to 49 years") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_age_totals[0] += d_value;
            british_columbia_age_counts[0]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "50 to 64 years") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_age_totals[1] += d_value;
            british_columbia_age_counts[1]++;
          }
        }
      } else if (strcmp(cleaned_age_group, "65 years and over") == 0) {
        if (strcmp(cleaned_geo, "British Columbia") == 0) {
          if (d_value > 0) {
            british_columbia_age_totals[2] += d_value;
            british_columbia_age_counts[2]++;
          }
        }
      }
    }

// Calculations
double national_avg = 0;
if (national_count > 0) {
    national_avg = national_total / national_count;
}

double prov_avgs[4];
for (int i = 0; i < 4; i++) {
    double prov_avg = 0;
    if (prov_counts[i] > 0) {
        prov_avg = prov_totals[i] / prov_counts[i];
    }
    prov_avgs[i] = prov_avg;
}

double canada_year_avgs[7];
for (int i = 0; i < 7; i++) {
    double canada_year_avg = 0;
    if (canada_year_counts[i] > 0) {
        canada_year_avg = canada_year_totals[i] / canada_year_counts[i];
    }
    canada_year_avgs[i] = canada_year_avg;
}

double quebec_year_avgs[7];
for (int i = 0; i < 7; i++) {
    double quebec_year_avg = 0;
    if (quebec_year_counts[i] > 0) {
        quebec_year_avg = quebec_year_totals[i] / quebec_year_counts[i];
    }
    quebec_year_avgs[i] = quebec_year_avg;
}

double ontario_year_avgs[7];
for (int i = 0; i < 7; i++) {
    double ontario_year_avg = 0;
    if (ontario_year_counts[i] > 0) {
        ontario_year_avg = ontario_year_totals[i] / ontario_year_counts[i];
    }
    ontario_year_avgs[i] = ontario_year_avg;
}

double alberta_year_avgs[7];
for (int i = 0; i < 7; i++) {
    double alberta_year_avg = 0;
    if (alberta_year_counts[i] > 0) {
        alberta_year_avg = alberta_year_totals[i] / alberta_year_counts[i];
    }
    alberta_year_avgs[i] = alberta_year_avg;
}

double british_columbia_year_avgs[7];
for (int i = 0; i < 7; i++) {
    double british_columbia_year_avg = 0;
    if (british_columbia_year_counts[i] > 0) {
        british_columbia_year_avg = british_columbia_year_totals[i] / british_columbia_year_counts[i];
    }
    british_columbia_year_avgs[i] = british_columbia_year_avg;
}

double canada_age_avgs[3];
for (int i = 0; i < 3; i++) {
    double canada_age_avg = 0;
    if (canada_age_counts[i] > 0) {
        canada_age_avg = canada_age_totals[i] / canada_age_counts[i];
    }
    canada_age_avgs[i] = canada_age_avg;
}

double quebec_age_avgs[3];
for (int i = 0; i < 3; i++) {
    double quebec_age_avg = 0;
    if (quebec_age_counts[i] > 0) {
        quebec_age_avg = quebec_age_totals[i] / quebec_age_counts[i];
    }
    quebec_age_avgs[i] = quebec_age_avg;
}

double ontario_age_avgs[3];
for (int i = 0; i < 3; i++) {
    double ontario_age_avg = 0;
    if (ontario_age_counts[i] > 0) {
        ontario_age_avg = ontario_age_totals[i] / ontario_age_counts[i];
    }
    ontario_age_avgs[i] = ontario_age_avg;
}

double alberta_age_avgs[3];
for (int i = 0; i < 3; i++) {
    double alberta_age_avg = 0;
    if (alberta_age_counts[i] > 0) {
        alberta_age_avg = alberta_age_totals[i] / alberta_age_counts[i];
    }
    alberta_age_avgs[i] = alberta_age_avg;
}

double british_columbia_age_avgs[3];
for (int i = 0; i < 3; i++) {
    double british_columbia_age_avg = 0;
    if (british_columbia_age_counts[i] > 0) {
        british_columbia_age_avg = british_columbia_age_totals[i] / british_columbia_age_counts[i];
    }
    british_columbia_age_avgs[i] = british_columbia_age_avg;
}

// Print Results
printf("-------------Question 1-------------\n\n");
printf("National Percent Average: %0.3f\n\n", national_avg);
printf("---Province-Wise Percent Averages---\n\n");
printf("Ontario: %0.3f\n", prov_avgs[0]);
printf("Quebec: %0.3f\n", prov_avgs[1]);
printf("British Columbia: %0.3f\n", prov_avgs[2]);
printf("Alberta: %0.3f\n\n\n", prov_avgs[3]);

printf("|--------------------------Year-Wise Percent Averages--------------------------|\n\n");
printf("|----Canada----|----Quebec----|---Ontario----|----Alberta---|-British Columbia-|\n");
printf("|              |              |              |              |                  |\n");
printf("| 2015: %0.3f | 2015: %0.3f | 2015: %0.3f | 2015: %0.3f  | 2015: %0.3f      |\n", canada_year_avgs[0], quebec_year_avgs[0], ontario_year_avgs[0], alberta_year_avgs[0], british_columbia_year_avgs[0]);
printf("| 2016: %0.3f | 2016: %0.3f  | 2016: %0.3f | 2016: %0.3f  | 2016: %0.3f      |\n", canada_year_avgs[1], quebec_year_avgs[1], ontario_year_avgs[1], alberta_year_avgs[1], british_columbia_year_avgs[1]);
printf("| 2017: %0.3f | 2017: %0.3f  | 2017: %0.3f | 2017: %0.3f | 2017: %0.3f     |\n", canada_year_avgs[2], quebec_year_avgs[2], ontario_year_avgs[2], alberta_year_avgs[2], british_columbia_year_avgs[2]);
printf("| 2018: %0.3f | 2018: %0.3f | 2018: %0.3f | 2018: %0.3f | 2018: %0.3f      |\n", canada_year_avgs[3], quebec_year_avgs[3], ontario_year_avgs[3], alberta_year_avgs[3], british_columbia_year_avgs[3]);
printf("| 2019: %0.3f | 2019: %0.3f | 2019: %0.3f | 2019: %0.3f | 2019: %0.3f     |\n", canada_year_avgs[4], quebec_year_avgs[4], ontario_year_avgs[4], alberta_year_avgs[4], british_columbia_year_avgs[4]);
printf("| 2020: %0.3f | 2020: %0.3f | 2020: %0.3f | 2020: %0.3f | 2020: %0.3f      |\n", canada_year_avgs[5], quebec_year_avgs[5], ontario_year_avgs[5], alberta_year_avgs[5], british_columbia_year_avgs[5]);
printf("| 2021: %0.3f | 2021: %0.3f | 2021: %0.3f | 2021: %0.3f  | 2021: %0.3f     |\n\n", canada_year_avgs[6], quebec_year_avgs[6], ontario_year_avgs[6], alberta_year_avgs[6], british_columbia_year_avgs[6]);

printf("|---------------------------------------------------------Age-Wise Percent Averages---------------------------------------------------------|\n\n");
printf("|----------Canada-----------|----------Quebec-----------|---------Ontario-----------|---------Alberta-----------|-----British Columbia------|\n");
printf("|  35 to 49 years: %0.3f    |   35 to 49 years: %0.3f   |  35 to 49 years: %0.3f    |  35 to 49 years: %0.3f    |  35 to 49 years: %0.3f    |\n", canada_age_avgs[0], quebec_age_avgs[0], ontario_age_avgs[0], alberta_age_avgs[0], british_columbia_age_avgs[0]);
printf("|  50 to 64 years: %0.3f   |   50 to 64 years: %0.3f   |  50 to 64 years: %0.3f   |  50 to 64 years: %0.3f   |  50 to 64 years: %0.3f    |\n", canada_age_avgs[1], quebec_age_avgs[1], ontario_age_avgs[1], alberta_age_avgs[1], british_columbia_age_avgs[1]);
printf("| 65 years and over: %0.3f | 65 years and over: %0.3f | 65 years and over: %0.3f | 65 years and over: %0.3f | 65 years and over: %0.3f |\n\n", canada_age_avgs[2], quebec_age_avgs[2], ontario_age_avgs[2], alberta_age_avgs[2], british_columbia_age_avgs[2]);

// Close file
fclose(fp);

printf("--------------Question 2--------------\n\n");

// Create string array to store province names
char* province_names[4] = {"Ontario", "Quebec", "British Columbia", "Alberta"};

// Determine which province has the highest and lowest average percentage of diabetes
double prov_indices[4];
for (int i = 0; i < 4; i++) {
    double prov_avg = 0;
    if (prov_counts[i] > 0) {
        prov_avg = prov_totals[i] / prov_counts[i];
    }
    prov_avgs[i] = prov_avg;
    prov_indices[i] = (prov_avg - national_avg) / national_avg; // Calculate province index
}

// Sort provinces based on province index
int max_index, min_index;
max_index = min_index = 0;
for (int i = 1; i < 4; i++) {
    if (prov_indices[i] > prov_indices[max_index]) {
        max_index = i;
    }
    if (prov_indices[i] < prov_indices[min_index]) {
        min_index = i;
    }
}

// Print sorted list of provinces
for (int i = 0; i < 4; i++) {
    printf("%s: Average diabetes percentage = %.2f, Province index = %.2f\n", province_names[i], prov_avgs[i], prov_indices[i]);
}

// Print province with highest and lowest diabetes percentage
printf("\nThe province with the highest average percentage of diabetes is %s and the province\nwith the lowest average percentage of diabetes is %s.\n\n", province_names[max_index], province_names[min_index]);

printf("--------------Question 3--------------\n\n");

// Determine which provinces are above and below the national average
int above_count = 0, below_count = 0;
for (int i = 0; i < 4; i++) {
    if (prov_avgs[i] > national_avg) {
        above_count++;
    } else {
        below_count++;
    }
}

// Print provinces above and below the national average
printf("The provinces that have a higher average diabetes percentage than the national average are ");
for (int i = 0; i < 4; i++) {
    if (prov_avgs[i] > national_avg) {
        printf("%s, ", province_names[i]);
    }
}
printf("\b\b; \n");

printf("the provinces that are below the national average are ");
for (int i = 0; i < 4; i++) {
    if (prov_avgs[i] <= national_avg) {
        printf("%s, ", province_names[i]);
    }
}
printf("\b\b.\n\n");

printf("--------------Question 4--------------\n\n");

// Declare and initialize province names array
const char* PROVINCE_NAMES[] = {"Ontario", "Quebec", "British Columbia", "Alberta"};

// Declare and initialize year list array
const int YEAR_LIST[] = {2015, 2016, 2017, 2018, 2019, 2020, 2021};

// Initialize variables
int highest_province = 0;
int highest_year = 0;
float highest_percentage = 0.0;
int lowest_province = 0;
int lowest_year = 0;
float lowest_percentage = 100.0;

// Calculate provincial and national averages
for (int i = 0; i < 4; i++) {
  float province_total = prov_totals[i];
  int province_count = prov_counts[i];
  float province_percentage = (province_total / province_count);
  
  // Check if this province has the highest percentage of diabetes
  if (province_percentage > highest_percentage) {
    highest_province = i;
    highest_percentage = province_percentage;
  }
  
  // Check if this province has the lowest percentage of diabetes
  if (province_percentage < lowest_percentage) {
    lowest_province = i;
    lowest_percentage = province_percentage;
  }
}

// Calculate national averages for each year
for (int i = 0; i < 7; i++) {
  float year_total = canada_year_totals[i];
  int year_count = canada_year_counts[i];
  float year_percentage = (year_total / year_count);
  
  // Check if this year has the highest percentage of diabetes
  if (year_percentage > highest_percentage) {
    highest_year = i;
    highest_percentage = year_percentage;
  }
  
  // Check if this year has the lowest percentage of diabetes
  if (year_percentage < lowest_percentage) {
    lowest_year = i;
    lowest_percentage = year_percentage;
  }
}

// Print the results
printf("The province with the highest percentage of diabetes is %s in %d with %.1f%%.\n", PROVINCE_NAMES[highest_province], YEAR_LIST[highest_year], highest_percentage);
printf("The province with the lowest percentage of diabetes is %s in %d with %.1f%%.\n", PROVINCE_NAMES[lowest_province], YEAR_LIST[lowest_year], lowest_percentage);

return 0;
}
