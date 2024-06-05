Diabetes Data Analysis

This project involves analyzing diabetes data from Canadian provinces to calculate national and provincial averages across multiple years and age groups. 
The analysis is performed using a C program that processes a CSV file containing the relevant statistics.

Introduction

This project aims to provide a comprehensive analysis of diabetes prevalence across Canada, including breakdowns by province, year, and age group. 
The data is sourced from a CSV file (statscan_diabetes.csv) and processed to generate average values for various categories.

Features

Data Parsing: Reads and cleans data from a CSV file.
Statistical Calculations: Calculates national and provincial averages for diabetes prevalence.
Yearly Analysis: Computes yearly averages for Canada and specific provinces.
Age Group Analysis: Provides averages for different age groups within each province.

Prerequisites

To compile and run the C program, you need:

A C compiler (e.g., gcc)
A CSV file named statscan_diabetes.csv containing the diabetes data

Usage

Clone the repository:

bash
Copy code
git clone https://github.com/yourusername/diabetes-data-analysis.git
cd diabetes-data-analysis

Compile the C program:

bash
Copy code
gcc -o diabetes_analysis diabetes_analysis.c

Run the program:

bash
Copy code
./diabetes_analysis
Ensure that the statscan_diabetes.csv file is in the same directory as the compiled program.

Code Structure

Main Program (diabetes_analysis.c):
Opens and reads the CSV file.
Cleans and processes each line of data.
Calculates averages for national and provincial data, as well as for different age groups and years.
Outputs the calculated averages.

Results

After running the program, it calculates and prints the following results:

National average diabetes prevalence
Provincial averages for Ontario, Quebec, British Columbia, and Alberta
Yearly averages for Canada and the specified provinces
Age group averages for Canada and the specified provinces





