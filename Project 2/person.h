#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

#define MAX_DOCTOR_PATIENTS 10      // a doctor can't take more than 10 patients


// base class for everyone in the hospital
class Person {

    public:
        Person(): id{0}, name{""}, age{0} {}
        Person(int id, string name, int age): id{id}, name{name}, age{age} {}
        virtual ~Person() {}

        int get_id() {
            return id;
        }
        string get_name() {
            return name;
        }
        int get_age() {
            return age;
        }
        void set_name(string name) {
            this->name = name;
        }
        void set_age(int age) {
            this->age = age;
        }

        virtual string get_role() = 0;      // every class has to say what it is
        virtual void print() {
            cout << get_role() << "\t#" << id << "\t" << name << "\t" << age << " years";
        }

        bool operator==(Person &other) {
            return this->id == other.id;
        }
        friend ostream& operator<<(ostream &out, Person &person) {
            person.print();
            return out;
        }
    protected:
        int id;
        string name;
        int age;
};


// doctors and nurses are staff so they take a salary
class Staff : public Person {

    public:
        Staff(): Person(), salary{0} {}
        Staff(int id, string name, int age, double salary): Person(id, name, age), salary{salary} {}

        double get_salary() {
            return salary;
        }
        void set_salary(double salary) {
            this->salary = salary;
        }
        virtual double get_monthly_pay() {
            return salary;
        }
    protected:
        double salary;
};


class Doctor : public Staff {

    public:
        Doctor(): Staff(), specialty{""}, fee{0}, patients_count{0} {}
        Doctor(int id, string name, int age, double salary, string specialty, double fee):
            Staff(id, name, age, salary), specialty{specialty}, fee{fee}, patients_count{0} {}

        string get_role() {
            return "Doctor";
        }
        string get_specialty() {
            return specialty;
        }
        double get_fee() {
            return fee;
        }
        int get_patients_count() {
            return patients_count;
        }
        bool is_full() {
            return patients_count == MAX_DOCTOR_PATIENTS;
        }
        bool add_patient(int patient_id) {
            if (is_full()) {
                return false;
            }
            patients[patients_count] = patient_id;
            patients_count++;
            return true;
        }
        bool remove_patient(int patient_id) {
            for (int i = 0; i < patients_count; i++) {
                if (patients[i] == patient_id) {
                    for (int j = i; j < patients_count - 1; j++) {
                        patients[j] = patients[j + 1];
                    }
                    patients_count--;
                    return true;
                }
            }
            return false;
        }
        // doctors take 200 extra for every patient they have
        double get_monthly_pay() {
            return salary + 200 * patients_count;
        }
        void print() {
            Person::print();
            cout << "\t" << specialty << "\t" << patients_count << "/" << MAX_DOCTOR_PATIENTS << " patients";
        }
    private:
        string specialty;
        double fee;
        int patients[MAX_DOCTOR_PATIENTS];
        int patients_count;
};


class Nurse : public Staff {

    public:
        Nurse(): Staff(), shift{"Morning"} {}
        Nurse(int id, string name, int age, double salary, string shift):
            Staff(id, name, age, salary), shift{shift} {}

        string get_role() {
            return "Nurse";
        }
        string get_shift() {
            return shift;
        }
        void set_shift(string shift) {
            this->shift = shift;
        }
        // night shift takes 20% more
        double get_monthly_pay() {
            if (shift == "Night") {
                return salary * 1.2;
            }
            return salary;
        }
        void print() {
            Person::print();
            cout << "\t" << shift << " shift";
        }
    private:
        string shift;
};


class Patient : public Person {

    public:
        Patient(): Person(), disease{""}, department_index{-1}, room_number{0}, doctor_id{0} {}
        Patient(int id, string name, int age, string disease):
            Person(id, name, age), disease{disease}, department_index{-1}, room_number{0}, doctor_id{0} {}

        string get_role() {
            return "Patient";
        }
        string get_disease() {
            return disease;
        }
        int get_department_index() {
            return department_index;
        }
        int get_room_number() {
            return room_number;
        }
        int get_doctor_id() {
            return doctor_id;
        }
        void set_place(int department_index, int room_number, int doctor_id) {
            this->department_index = department_index;
            this->room_number = room_number;
            this->doctor_id = doctor_id;
        }
        void print() {
            Person::print();
            cout << "\t" << disease;
        }
    private:
        string disease;
        int department_index;
        int room_number;
        int doctor_id;
};

#endif
