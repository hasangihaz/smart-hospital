# MEDICARE — Smart Hospital & Resource Allocation System

MEDICARE is a menu-driven hospital management system developed using the C programming language.

This project was created for the **CSC 1012 — Introduction to Computer Programming** individual assignment.

The system helps manage patients, hospital beds, emergency priority, medical fees, and hospital reports. It uses arrays to store and manage data.

---

## Features

Patient Registration - Register a patient with their name, age, emergency level, medical specialty, and ward admission details.

Specialty Selection-Supports 4 medical specialties:

  - General Practice / OPD
  - Paediatrics
  - Cardiology
  - Neurology

Ward Management- Supports 4 hospital wards:

  - General Ward
  - Paediatric Ward
  - Surgical Ward
  - ICU

Bed Management-Shows available and occupied beds in each ward.

Patient Billing- Calculates consultation fees, emergency charges, ward costs, discounts, and the final amount to pay.

Emergency Priority-Patients are given three priority levels:

   Level 3 - Critical
   Level 2 - Urgent
   Level 1 - Normal

Waiting Time - Calculates the estimated waiting time based on the number of patients waiting and the consultation time.

Priority Sorting -Patients are sorted from Critical to Urgent to Normal using Bubble Sort. If two patients have the same priority, their registration order is kept.

Hospital Report- Displays patient numbers, emergency levels, total income, total discounts, bed usage, and the patient with the highest payment.

File Saving - Saves bed information and patient billing records into text files. The saved data can be used again when the program is opened.

---

## System Requirements

To run this program, you need:

 A C compiler such as **GCC**
 Works on **Windows, Linux, and macOS**
 No external libraries are required
 Uses only standard C libraries:

  -stdio.h
  -string.h

---

## Compilation

Clone the repository:

```bash
git clone :https://github.com/hasangihaz/smart-hospital.git
```

Go to the project folder:

```bash
cd smart-hospital
```

Compile the program using GCC:

```bash
gcc main.c -o medicare
```

After compilation, GCC automatically creates the executable file.

On Windows:

```text
medicare.exe
```

---

## Run the Program

### Windows

```bash
medicare.exe
```

### Linux / macOS

```bash
./medicare
```

---

## Main Menu

The program provides the following main menu:

```text
01 - Register Patient
02 - Display Bed Availability
03 - Patient Bill Statement
04 - Display Patient Priority
05 - Generate Hospital Summary Report
06 - Update Bed Occupancy
07 - Save Patient Records
08 - Exit
```

---

## Data Files

The program creates and uses two text files to store important information.

 
   beds_status.txt     - Stores the current bed occupancy information.                                             
   patient_records.txt - Stores patient billing records such as patient ID, patient name, and final payment amount. 

These files are created automatically by the program when they are needed. They do not need to be created manually.

The bed information is loaded when the program starts, and the bed status is saved when the relevant menu option is selected or when the program exits.

---

## Project Structure

```text
smart-hospital/

- main.c
- beds_status.txt
- patient_records.txt
- README.md
```

### File Description

main.c -Contains the complete C program and its functions.

beds_status.txt -Stores the current bed occupancy information.

patient_records.txt - Stores patient billing records.

README.md -Contains information about the project, its features, requirements, compilation, and usage.

---

## Technologies Used

  C Programming Language
  Code::Blocks
  GCC Compiler
  Git
  GitHub

---

## Data Structures

The program mainly uses:

  1D arrays for patient information
  2D arrays for bed information
  Variables for patient, billing, and hospital data


---

## Sorting Method

The program uses **Bubble Sort** to arrange patients according to their emergency priority.

The priority order is:

```text

1. Level 3 — Critical
       
2. Level 2 — Urgent
       
3. Level 1 — Normal
```

If two patients have the same emergency level, their original registration order is kept.

---

## Conclusion

MEDICARE provides a simple way to manage important hospital tasks such as patient registration, bed management, patient priority, billing, and hospital reporting.

The project demonstrates the use of C programming concepts including arrays, functions, loops, conditional statements, file handling, searching, sorting, and menu-driven programming.
