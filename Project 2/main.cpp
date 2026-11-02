#include "hospital.h"
#include <cstdlib>


// reads a number and keeps asking if the user writes letters
int read_int(string message) {

    int number;
    cout << message;
    cin >> number;
    while (cin.fail()) {
        if (cin.eof()) {
            exit(0);
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a number: ";
        cin >> number;
    }
    cin.ignore(1000, '\n');
    return number;
}

double read_double(string message) {

    double number;
    cout << message;
    cin >> number;
    while (cin.fail()) {
        if (cin.eof()) {
            exit(0);
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a number: ";
        cin >> number;
    }
    cin.ignore(1000, '\n');
    return number;
}

// reads a whole line so names can have spaces
string read_line(string message) {

    string line = "";
    while (line == "") {
        cout << message;
        if (!getline(cin, line)) {
            exit(0);
        }
    }
    return line;
}

// prints the departments and returns the index of the chosen one or -1
int choose_department(Hospital &hospital) {

    if (hospital.get_departments_count() == 0) {
        cout << "Add a department first" << endl;
        return -1;
    }
    hospital.print_departments();
    int choice = read_int("Choose department: ");
    if (choice < 1 || choice > hospital.get_departments_count()) {
        cout << "Wrong choice" << endl;
        return -1;
    }
    return choice - 1;
}

void load_sample_data(Hospital &hospital) {

    hospital.add_department("Emergency");
    hospital.add_department("Cardiology");
    hospital.add_department("Pediatrics");

    hospital.add_room(0, 101, "Ward", 4, 400);
    hospital.add_room(0, 102, "ICU", 2, 1500);
    hospital.add_room(1, 201, "Ward", 4, 500);
    hospital.add_room(1, 202, "Private", 1, 900);
    hospital.add_room(2, 301, "Ward", 6, 350);

    hospital.add_doctor(0, "Ahmed Hassan", 45, 25000, "Emergency Medicine", 300);
    hospital.add_doctor(0, "Sara Mahmoud", 38, 22000, "General Surgery", 400);
    hospital.add_doctor(1, "Mohamed Adel", 52, 30000, "Cardiologist", 600);
    hospital.add_doctor(2, "Mona Ibrahim", 41, 21000, "Pediatrician", 350);

    hospital.add_nurse(0, "Heba Samir", 29, 9000, "Morning");
    hospital.add_nurse(0, "Omar Khaled", 31, 9000, "Night");
    hospital.add_nurse(1, "Nour Ali", 27, 8500, "Morning");
    hospital.add_nurse(2, "Yara Tarek", 25, 8000, "Night");

    hospital.admit_patient(0, "Youssef Ashraf", 22, "Broken arm");
    hospital.admit_patient(0, "Karim Fathy", 60, "High fever");
    hospital.admit_patient(1, "Hassan Mostafa", 67, "Heart failure");
    hospital.admit_patient(1, "Laila Sherif", 58, "Chest pain");
    hospital.admit_patient(2, "Malak Hany", 6, "Asthma");
}

void print_menu(string name) {

    cout << "\n========== " << name << " ==========" << endl;
    cout << "1.  Show hospital topology" << endl;
    cout << "2.  Add department" << endl;
    cout << "3.  Add room" << endl;
    cout << "4.  Add doctor" << endl;
    cout << "5.  Add nurse" << endl;
    cout << "6.  Admit patient" << endl;
    cout << "7.  Discharge patient" << endl;
    cout << "8.  Transfer patient" << endl;
    cout << "9.  Search patient" << endl;
    cout << "10. Show staff and salaries" << endl;
    cout << "0.  Exit" << endl;
}


int main() {

    Hospital hospital("New Cairo Hospital");
    string answer = read_line("Load sample data? (y/n): ");
    if (answer == "y" || answer == "Y") {
        load_sample_data(hospital);
        cout << "Sample data loaded" << endl;
    }

    while (1) {

        print_menu(hospital.get_name());
        int choice = read_int("Choice: ");

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            hospital.print_topology();
        }
        else if (choice == 2) {
            string name = read_line("Department name: ");
            if (hospital.add_department(name)) {
                cout << "Department added" << endl;
            }
        }
        else if (choice == 3) {
            int dep = choose_department(hospital);
            if (dep == -1) {
                continue;
            }
            int number = read_int("Room number: ");
            string type = read_line("Room type (Ward / Private / ICU): ");
            int capacity = read_int("Number of beds (max 6): ");
            double price = read_double("Price per day: ");
            if (hospital.add_room(dep, number, type, capacity, price)) {
                cout << "Room added" << endl;
            }
        }
        else if (choice == 4) {
            int dep = choose_department(hospital);
            if (dep == -1) {
                continue;
            }
            string name = read_line("Doctor name: ");
            int age = read_int("Age: ");
            string specialty = read_line("Specialty: ");
            double salary = read_double("Salary: ");
            double fee = read_double("Fee per patient: ");
            int id = hospital.add_doctor(dep, name, age, salary, specialty, fee);
            if (id != -1) {
                cout << "Doctor added with id #" << id << endl;
            }
        }
        else if (choice == 5) {
            int dep = choose_department(hospital);
            if (dep == -1) {
                continue;
            }
            string name = read_line("Nurse name: ");
            int age = read_int("Age: ");
            double salary = read_double("Salary: ");
            string shift = read_line("Shift (Morning / Night): ");
            int id = hospital.add_nurse(dep, name, age, salary, shift);
            if (id != -1) {
                cout << "Nurse added with id #" << id << endl;
            }
        }
        else if (choice == 6) {
            int dep = choose_department(hospital);
            if (dep == -1) {
                continue;
            }
            string name = read_line("Patient name: ");
            int age = read_int("Age: ");
            string disease = read_line("Disease: ");
            int id = hospital.admit_patient(dep, name, age, disease);
            if (id != -1) {
                Patient* patient = hospital.find_patient(id);
                cout << "Patient admitted with id #" << id << endl;
                hospital.print_patient(patient);
            }
        }
        else if (choice == 7) {
            int id = read_int("Patient id: ");
            if (hospital.find_patient(id) == NULL) {
                cout << "Patient not found" << endl;
                continue;
            }
            int days = read_int("Number of days: ");
            if (days < 1) {
                days = 1;
            }
            hospital.discharge_patient(id, days);
        }
        else if (choice == 8) {
            int id = read_int("Patient id: ");
            if (hospital.find_patient(id) == NULL) {
                cout << "Patient not found" << endl;
                continue;
            }
            cout << "Transfer to:" << endl;
            int dep = choose_department(hospital);
            if (dep == -1) {
                continue;
            }
            if (hospital.transfer_patient(id, dep)) {
                cout << "Patient transferred" << endl;
                hospital.print_patient(hospital.find_patient(id));
            }
        }
        else if (choice == 9) {
            string search = read_line("Patient id or name: ");
            bool is_number = true;
            for (int i = 0; i < search.length(); i++) {
                if (!isdigit(search[i])) {
                    is_number = false;
                }
            }
            if (is_number && search.length() < 9) {
                Patient* patient = hospital.find_patient(stoi(search));
                if (patient == NULL) {
                    cout << "Patient not found" << endl;
                }
                else {
                    hospital.print_patient(patient);
                }
            }
            else if (hospital.search_by_name(search) == 0) {
                cout << "Patient not found" << endl;
            }
        }
        else if (choice == 10) {
            hospital.print_staff();
        }
        else {
            cout << "Wrong choice" << endl;
        }
    }

    return 0;
}
