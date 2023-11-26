# Datalogger using Dynamic Arrays - PRPR Assignment 1

## Description

This program works with records stored in the datalogger.txt file, containing entries from a measurement module. The program executes commands read from the standard input. Each command consists of a lowercase letter followed by a newline character:

- `v`: Upon activation, the program checks if the `datalogger.txt` file is open. If the file is not open, it attempts to open it. If unsuccessful, the program prints the message File not opened followed by a newline character. If the file is successfully opened (i.e., the 'v' command was previously pressed), the program checks if dynamic arrays have been created (i.e., the 'en' command was pressed before). If yes, the program prints individual records from dynamic arrays; otherwise, it prints individual records from the file. Each printed record is separated by an empty line, and each item in the record is named and placed on a separate line. The format for displaying records is as follows:

  - ID number of the measurement person: (space) 11-digit integer divisible by 11
  - Measurement module: (space) uppercase letter from the interval <A, Z> followed by a number from the interval <00, 99> (exactly 2 digits!)
  - Type of measurement quantity: (space) 2 characters from the set {R1, U1, A1, R2, U2, A2, R4, U4, A4}
  - Value: real number
  - Measurement time: (space) 4 characters (1st-2nd characters represent the hour in 24h format, 3rd-4th characters represent minutes in the range 00-59)
  - Date: (space) 8-digit integer in the format yyyymmdd (e.g., 20201030 for October 30, 2020)
  - (empty line)

  The `datalogger.txt` file will only contain values, not the types (names) of items. Individual records in the text file will be separated by an empty line.

- `n`: Upon activation, counts the number of records in the file, dynamically creates arrays for individual items from the input, writes them in the order they appear in the text file. If arrays were previously created, they are deallocated first, and then new ones are created. This command generates no output. If the file is not open (i.e., the 'v' command has not been executed yet), this option does nothing and prints the message “File not opened”.

- `c`: Upon activation, the program checks the data in the text file. As part of verifying the correctness of the input file, the program alerts the user which data is incorrect. For example, the program prints: “Incorrectly entered input: ID number of the measurement person” if the ID number of the measurement person does not meet the conditions specified above (similarly for other data such as "Module", "Type", "Time", and "Date"). If the data in the text file is all correct, it prints: “Data is correct”. If the file is not open (i.e., the 'v' command has not been executed yet), this option does nothing and prints the message “File not opened”.

- `s`: Upon activation, the program reads the measurement module (in the format of an uppercase letter and two numbers), the type of measurement quantity, and creates a new array of measured values sorted by date and time in ascending order. This command writes the sorted values to a text file named `output_S.txt` in the format date+time and the measured value rounded to 7 decimal places. Each record is on a separate line. After finishing the writing, the program prints the message “For the given input, a text file is created” followed by a newline character. If dynamic arrays are not created, it prints the message “Arrays are not created” followed by a newline character. If there are no records for the given input, it prints the message “For the given input, there are no records”.

- `h`: Upon activation, the program prints a histogram for the type of measurement quantity with the designation Ax in a 5-step interval (i.e., intervals (0.0 - 5.0>, (5.0 - 10.0>, (10.0 - 15.0>, …) regardless of other record items. The program prints the sample counts in each interval. Only intervals with a non-zero count will be printed. If dynamic arrays are not created, it prints the message "Arrays are not created” followed by a newline character.

- `r`: Upon activation, the program analyzes the measurement times and prints them in a reduced form (as if departure times of buses), separately with the representation of hours and minutes, regardless of other record items. If dynamic arrays are not created, it prints the message " Arrays are not created” followed by a newline character.

