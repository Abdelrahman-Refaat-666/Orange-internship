# Project 2 - Hospital Topology

A console program that builds a hospital as a tree: the hospital has departments, every department has doctors, nurses and rooms, and patients are placed in the rooms.
The point of this project was to practice **OOP** (classes, inheritance, virtual functions, abstract classes, operator overloading and pointers).

## Build and run

```
g++ main.cpp -o main
./main
```

## Files

- `person.h` -> `Person`, `Staff`, `Doctor`, `Nurse`, `Patient`
- `hospital.h` -> `Room`, `Department`, `Hospital`
- `main.cpp` -> the menu

## Classes

```
Person (abstract)
|-- Staff
|   |-- Doctor
|   `-- Nurse
`-- Patient

Hospital
`-- Department (max 10)
    |-- Doctor (max 20)
    |-- Nurse  (max 30)
    `-- Room   (max 20)
        `-- Patient (max 6 beds)
```

What I used:
- **Inheritance**: `Doctor` and `Nurse` inherit from `Staff`, and `Staff` and `Patient` inherit from `Person`
- **Abstract class**: `Person` has `get_role()` as a pure virtual function
- **Polymorphism**: the staff list is an array of `Staff*` and `print()` and `get_monthly_pay()` call the right version (doctors take 200 extra for every patient and night shift nurses take 20% more)
- **Operator overloading**: `<<` for `Person` and `Room`, `==` for `Person`
- **Composition and pointers**: `Hospital` owns the departments and patients and deletes them in its destructor

## Menu

```
1.  Show hospital topology
2.  Add department
3.  Add room
4.  Add doctor
5.  Add nurse
6.  Admit patient
7.  Discharge patient
8.  Transfer patient
9.  Search patient
10. Show staff and salaries
0.  Exit
```

- **Admit**: the patient goes to the first room with a free bed and gets the doctor with the least patients
- **Discharge**: prints the bill (days x room price + doctor fee) and frees the bed
- **Transfer**: moves the patient to another department (new room and new doctor)
- **Search**: by id or by part of the name

At the start it asks if you want to load sample data so you can try it fast.

## Example (topology)

```
New Cairo Hospital  (3 departments, 5 patients)
|
|-- [1] Emergency  (2 doctors, 2 nurses, 2 rooms, 2/6 beds used)
|   |-- Doctors
|   |   |-- #1 Ahmed Hassan - Emergency Medicine - 1/10 patients
|   |   `-- #2 Sara Mahmoud - General Surgery - 1/10 patients
|   |-- Nurses
|   |   |-- #5 Heba Samir - Morning shift
|   |   `-- #6 Omar Khaled - Night shift
|   `-- Rooms
|       |-- Room 101 (Ward, 400/day) 2/4 beds
|       |   |-- #1001 Youssef Ashraf - Broken arm - Dr. Ahmed Hassan
|       |   `-- #1002 Karim Fathy - High fever - Dr. Sara Mahmoud
|       `-- Room 102 (ICU, 1500/day) 0/2 beds
|
|-- [2] Cardiology  (1 doctors, 1 nurses, 2 rooms, 2/5 beds used)
|   |-- Doctors
|   |   `-- #3 Mohamed Adel - Cardiologist - 2/10 patients
|   |-- Nurses
|   |   `-- #7 Nour Ali - Morning shift
|   `-- Rooms
|       |-- Room 201 (Ward, 500/day) 2/4 beds
|       |   |-- #1003 Hassan Mostafa - Heart failure - Dr. Mohamed Adel
|       |   `-- #1004 Laila Sherif - Chest pain - Dr. Mohamed Adel
|       `-- Room 202 (Private, 900/day) 0/1 beds
|
`-- [3] Pediatrics  (1 doctors, 1 nurses, 1 rooms, 1/6 beds used)
    |-- Doctors
    |   `-- #4 Mona Ibrahim - Pediatrician - 1/10 patients
    |-- Nurses
    |   `-- #8 Yara Tarek - Night shift
    `-- Rooms
        `-- Room 301 (Ward, 350/day) 1/6 beds
            `-- #1005 Malak Hany - Asthma - Dr. Mona Ibrahim
```

## Example (discharge)

```
------------- Bill -------------
Patient:     #1001 Youssef Ashraf
Department:  Emergency
Room 101:    3 days x 400 = 1200
Doctor fee:  300 (Dr. Ahmed Hassan)
Total:       1500
--------------------------------
```
