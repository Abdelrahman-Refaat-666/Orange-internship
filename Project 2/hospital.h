#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "person.h"

#define MAX_BEDS 6
#define MAX_ROOMS 20
#define MAX_DOCTORS 20
#define MAX_NURSES 30
#define MAX_DEPARTMENTS 10
#define MAX_PATIENTS 200


class Room {

    public:
        Room(): number{0}, type{""}, capacity{0}, price{0}, patients_count{0} {}
        Room(int number, string type, int capacity, double price): number{number}, type{type}, price{price}, patients_count{0} {
            if (capacity > MAX_BEDS) {
                capacity = MAX_BEDS;
            }
            if (capacity < 1) {
                capacity = 1;
            }
            this->capacity = capacity;
        }

        int get_number() {
            return number;
        }
        string get_type() {
            return type;
        }
        int get_capacity() {
            return capacity;
        }
        double get_price() {
            return price;
        }
        int get_patients_count() {
            return patients_count;
        }
        Patient* get_patient(int i) {
            return patients[i];
        }
        bool is_full() {
            return patients_count == capacity;
        }
        bool add_patient(Patient* patient) {
            if (is_full()) {
                return false;
            }
            patients[patients_count] = patient;
            patients_count++;
            return true;
        }
        bool remove_patient(int patient_id) {
            for (int i = 0; i < patients_count; i++) {
                if (patients[i]->get_id() == patient_id) {
                    for (int j = i; j < patients_count - 1; j++) {
                        patients[j] = patients[j + 1];
                    }
                    patients_count--;
                    return true;
                }
            }
            return false;
        }
        friend ostream& operator<<(ostream &out, Room &room) {
            out << "Room " << room.number << " (" << room.type << ", " << room.price << "/day) " << room.patients_count << "/" << room.capacity << " beds";
            return out;
        }
    private:
        int number;
        string type;
        int capacity;
        double price;
        Patient* patients[MAX_BEDS];        // the room doesn't delete them, the hospital does
        int patients_count;
};


class Department {

    public:
        Department(string name): name{name}, rooms_count{0}, doctors_count{0}, nurses_count{0} {}
        ~Department() {
            for (int i = 0; i < rooms_count; i++) {
                delete rooms[i];
            }
            for (int i = 0; i < doctors_count; i++) {
                delete doctors[i];
            }
            for (int i = 0; i < nurses_count; i++) {
                delete nurses[i];
            }
        }

        string get_name() {
            return name;
        }
        int get_rooms_count() {
            return rooms_count;
        }
        int get_doctors_count() {
            return doctors_count;
        }
        int get_nurses_count() {
            return nurses_count;
        }
        Room* get_room(int i) {
            return rooms[i];
        }
        Doctor* get_doctor(int i) {
            return doctors[i];
        }
        Nurse* get_nurse(int i) {
            return nurses[i];
        }

        bool add_room(Room* room) {
            if (rooms_count == MAX_ROOMS) {
                return false;
            }
            rooms[rooms_count] = room;
            rooms_count++;
            return true;
        }
        bool add_doctor(Doctor* doctor) {
            if (doctors_count == MAX_DOCTORS) {
                return false;
            }
            doctors[doctors_count] = doctor;
            doctors_count++;
            return true;
        }
        bool add_nurse(Nurse* nurse) {
            if (nurses_count == MAX_NURSES) {
                return false;
            }
            nurses[nurses_count] = nurse;
            nurses_count++;
            return true;
        }

        Room* find_room(int number) {
            for (int i = 0; i < rooms_count; i++) {
                if (rooms[i]->get_number() == number) {
                    return rooms[i];
                }
            }
            return NULL;
        }
        Doctor* find_doctor(int id) {
            for (int i = 0; i < doctors_count; i++) {
                if (doctors[i]->get_id() == id) {
                    return doctors[i];
                }
            }
            return NULL;
        }
        // first room that has an empty bed
        Room* find_free_room() {
            for (int i = 0; i < rooms_count; i++) {
                if (!rooms[i]->is_full()) {
                    return rooms[i];
                }
            }
            return NULL;
        }
        // the doctor with the least patients so the work is divided between them
        Doctor* find_free_doctor() {
            Doctor* best = NULL;
            for (int i = 0; i < doctors_count; i++) {
                if (doctors[i]->is_full()) {
                    continue;
                }
                if (best == NULL || doctors[i]->get_patients_count() < best->get_patients_count()) {
                    best = doctors[i];
                }
            }
            return best;
        }
        int get_beds_count() {
            int beds = 0;
            for (int i = 0; i < rooms_count; i++) {
                beds += rooms[i]->get_capacity();
            }
            return beds;
        }
        int get_used_beds_count() {
            int beds = 0;
            for (int i = 0; i < rooms_count; i++) {
                beds += rooms[i]->get_patients_count();
            }
            return beds;
        }

        // prints the department as a tree
        // last is true if it's the last department so the line doesn't continue under it
        void print_topology(int number, bool last) {

            string line = "|   ";
            if (last) {
                line = "    ";
            }
            cout << (last ? "`-- " : "|-- ") << "[" << number << "] " << name;
            cout << "  (" << doctors_count << " doctors, " << nurses_count << " nurses, " << rooms_count << " rooms, ";
            cout << get_used_beds_count() << "/" << get_beds_count() << " beds used)" << endl;

            cout << line << "|-- Doctors" << endl;
            if (doctors_count == 0) {
                cout << line << "|   `-- (no doctors)" << endl;
            }
            for (int i = 0; i < doctors_count; i++) {
                cout << line << "|   " << (i == doctors_count - 1 ? "`-- " : "|-- ");
                cout << "#" << doctors[i]->get_id() << " " << doctors[i]->get_name() << " - " << doctors[i]->get_specialty();
                cout << " - " << doctors[i]->get_patients_count() << "/" << MAX_DOCTOR_PATIENTS << " patients" << endl;
            }

            cout << line << "|-- Nurses" << endl;
            if (nurses_count == 0) {
                cout << line << "|   `-- (no nurses)" << endl;
            }
            for (int i = 0; i < nurses_count; i++) {
                cout << line << "|   " << (i == nurses_count - 1 ? "`-- " : "|-- ");
                cout << "#" << nurses[i]->get_id() << " " << nurses[i]->get_name() << " - " << nurses[i]->get_shift() << " shift" << endl;
            }

            cout << line << "`-- Rooms" << endl;
            if (rooms_count == 0) {
                cout << line << "    `-- (no rooms)" << endl;
            }
            for (int i = 0; i < rooms_count; i++) {
                bool last_room = (i == rooms_count - 1);
                cout << line << "    " << (last_room ? "`-- " : "|-- ") << *rooms[i] << endl;
                string patient_line = line + "    " + (last_room ? "    " : "|   ");
                for (int j = 0; j < rooms[i]->get_patients_count(); j++) {
                    Patient* patient = rooms[i]->get_patient(j);
                    Doctor* doctor = find_doctor(patient->get_doctor_id());
                    cout << patient_line << (j == rooms[i]->get_patients_count() - 1 ? "`-- " : "|-- ");
                    cout << "#" << patient->get_id() << " " << patient->get_name() << " - " << patient->get_disease();
                    if (doctor != NULL) {
                        cout << " - Dr. " << doctor->get_name();
                    }
                    cout << endl;
                }
            }
        }
    private:
        string name;
        Room* rooms[MAX_ROOMS];
        int rooms_count;
        Doctor* doctors[MAX_DOCTORS];
        int doctors_count;
        Nurse* nurses[MAX_NURSES];
        int nurses_count;
};


class Hospital {

    public:
        Hospital(string name): name{name}, departments_count{0}, patients_count{0}, next_staff_id{1}, next_patient_id{1001} {}
        ~Hospital() {
            for (int i = 0; i < departments_count; i++) {
                delete departments[i];
            }
            for (int i = 0; i < patients_count; i++) {
                delete patients[i];
            }
        }

        string get_name() {
            return name;
        }
        int get_departments_count() {
            return departments_count;
        }
        int get_patients_count() {
            return patients_count;
        }
        Department* get_department(int i) {
            return departments[i];
        }

        bool add_department(string name) {
            if (departments_count == MAX_DEPARTMENTS) {
                cout << "The hospital can't have more than " << MAX_DEPARTMENTS << " departments" << endl;
                return false;
            }
            for (int i = 0; i < departments_count; i++) {
                if (departments[i]->get_name() == name) {
                    cout << "There is already a department called " << name << endl;
                    return false;
                }
            }
            departments[departments_count] = new Department(name);
            departments_count++;
            return true;
        }

        bool add_room(int dep, int number, string type, int capacity, double price) {
            // room numbers can't repeat in the whole hospital
            for (int i = 0; i < departments_count; i++) {
                if (departments[i]->find_room(number) != NULL) {
                    cout << "Room " << number << " already exists in " << departments[i]->get_name() << endl;
                    return false;
                }
            }
            Room* room = new Room(number, type, capacity, price);
            if (!departments[dep]->add_room(room)) {
                cout << "This department is full of rooms" << endl;
                delete room;
                return false;
            }
            return true;
        }

        // returns the id of the new doctor or -1
        int add_doctor(int dep, string name, int age, double salary, string specialty, double fee) {
            Doctor* doctor = new Doctor(next_staff_id, name, age, salary, specialty, fee);
            if (!departments[dep]->add_doctor(doctor)) {
                cout << "This department can't take more doctors" << endl;
                delete doctor;
                return -1;
            }
            next_staff_id++;
            return doctor->get_id();
        }

        int add_nurse(int dep, string name, int age, double salary, string shift) {
            Nurse* nurse = new Nurse(next_staff_id, name, age, salary, shift);
            if (!departments[dep]->add_nurse(nurse)) {
                cout << "This department can't take more nurses" << endl;
                delete nurse;
                return -1;
            }
            next_staff_id++;
            return nurse->get_id();
        }

        // puts the patient in a free room and gives him the doctor with the least patients
        // returns the patient id or -1 if there is no place
        int admit_patient(int dep, string name, int age, string disease) {
            if (patients_count == MAX_PATIENTS) {
                cout << "The hospital is full" << endl;
                return -1;
            }
            Room* room = departments[dep]->find_free_room();
            if (room == NULL) {
                cout << "No free beds in " << departments[dep]->get_name() << endl;
                return -1;
            }
            Doctor* doctor = departments[dep]->find_free_doctor();
            if (doctor == NULL) {
                cout << "No available doctors in " << departments[dep]->get_name() << endl;
                return -1;
            }
            Patient* patient = new Patient(next_patient_id, name, age, disease);
            next_patient_id++;
            room->add_patient(patient);
            doctor->add_patient(patient->get_id());
            patient->set_place(dep, room->get_number(), doctor->get_id());
            patients[patients_count] = patient;
            patients_count++;
            return patient->get_id();
        }

        // the bill = days * room price + doctor fee
        // returns -1 if the patient is not found
        double discharge_patient(int patient_id, int days) {
            int index = find_patient_index(patient_id);
            if (index == -1) {
                return -1;
            }
            Patient* patient = patients[index];
            Department* dep = departments[patient->get_department_index()];
            Room* room = dep->find_room(patient->get_room_number());
            Doctor* doctor = dep->find_doctor(patient->get_doctor_id());

            double bill = days * room->get_price() + doctor->get_fee();
            cout << "------------- Bill -------------" << endl;
            cout << "Patient:     #" << patient->get_id() << " " << patient->get_name() << endl;
            cout << "Department:  " << dep->get_name() << endl;
            cout << "Room " << room->get_number() << ":    " << days << " days x " << room->get_price() << " = " << days * room->get_price() << endl;
            cout << "Doctor fee:  " << doctor->get_fee() << " (Dr. " << doctor->get_name() << ")" << endl;
            cout << "Total:       " << bill << endl;
            cout << "--------------------------------" << endl;

            room->remove_patient(patient_id);
            doctor->remove_patient(patient_id);
            delete patient;
            for (int i = index; i < patients_count - 1; i++) {
                patients[i] = patients[i + 1];
            }
            patients_count--;
            return bill;
        }

        bool transfer_patient(int patient_id, int new_dep) {
            Patient* patient = find_patient(patient_id);
            if (patient == NULL) {
                cout << "Patient not found" << endl;
                return false;
            }
            if (patient->get_department_index() == new_dep) {
                cout << "The patient is already in " << departments[new_dep]->get_name() << endl;
                return false;
            }
            Room* new_room = departments[new_dep]->find_free_room();
            Doctor* new_doctor = departments[new_dep]->find_free_doctor();
            if (new_room == NULL || new_doctor == NULL) {
                cout << "No free bed or doctor in " << departments[new_dep]->get_name() << endl;
                return false;
            }
            Department* old_dep = departments[patient->get_department_index()];
            old_dep->find_room(patient->get_room_number())->remove_patient(patient_id);
            old_dep->find_doctor(patient->get_doctor_id())->remove_patient(patient_id);
            new_room->add_patient(patient);
            new_doctor->add_patient(patient_id);
            patient->set_place(new_dep, new_room->get_number(), new_doctor->get_id());
            return true;
        }

        Patient* find_patient(int patient_id) {
            int index = find_patient_index(patient_id);
            if (index == -1) {
                return NULL;
            }
            return patients[index];
        }

        void print_patient(Patient* patient) {
            Department* dep = departments[patient->get_department_index()];
            Doctor* doctor = dep->find_doctor(patient->get_doctor_id());
            cout << *patient << endl;
            cout << "\t" << dep->get_name() << " - Room " << patient->get_room_number() << " - Dr. " << doctor->get_name() << endl;
        }

        // searches with a part of the name, and the small and capital letters don't matter
        int search_by_name(string name) {
            int found = 0;
            for (int i = 0; i < patients_count; i++) {
                if (to_lower(patients[i]->get_name()).find(to_lower(name)) != string::npos) {
                    print_patient(patients[i]);
                    found++;
                }
            }
            return found;
        }

        void print_departments() {
            for (int i = 0; i < departments_count; i++) {
                cout << i + 1 << ". " << departments[i]->get_name() << endl;
            }
        }

        void print_topology() {
            cout << endl << name << "  (" << departments_count << " departments, " << patients_count << " patients)" << endl;
            if (departments_count == 0) {
                cout << "`-- (no departments yet)" << endl;
            }
            for (int i = 0; i < departments_count; i++) {
                cout << "|" << endl;
                departments[i]->print_topology(i + 1, i == departments_count - 1);
            }
            cout << endl;
        }

        // every staff member is printed with the same pointer type (Staff*)
        // and print() and get_monthly_pay() call the right function for doctors and nurses (virtual)
        void print_staff() {
            Staff* staff[MAX_DEPARTMENTS * (MAX_DOCTORS + MAX_NURSES)];
            int staff_count = 0;
            for (int i = 0; i < departments_count; i++) {
                for (int j = 0; j < departments[i]->get_doctors_count(); j++) {
                    staff[staff_count] = departments[i]->get_doctor(j);
                    staff_count++;
                }
                for (int j = 0; j < departments[i]->get_nurses_count(); j++) {
                    staff[staff_count] = departments[i]->get_nurse(j);
                    staff_count++;
                }
            }
            double total = 0;
            for (int i = 0; i < staff_count; i++) {
                cout << *staff[i] << "\tpay: " << staff[i]->get_monthly_pay() << endl;
                total += staff[i]->get_monthly_pay();
            }
            cout << "Staff count = " << staff_count << "\t\tTotal salaries = " << total << endl;
        }

    private:
        string name;
        Department* departments[MAX_DEPARTMENTS];
        int departments_count;
        Patient* patients[MAX_PATIENTS];
        int patients_count;
        int next_staff_id;
        int next_patient_id;

        int find_patient_index(int patient_id) {
            for (int i = 0; i < patients_count; i++) {
                if (patients[i]->get_id() == patient_id) {
                    return i;
                }
            }
            return -1;
        }
        string to_lower(string word) {
            for (int i = 0; i < word.length(); i++) {
                word[i] = tolower(word[i]);
            }
            return word;
        }
};

#endif
