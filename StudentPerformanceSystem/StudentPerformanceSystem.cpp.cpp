#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// ===== Base Class: Person =====
class Person {
protected:
    string name;
    int id;
public:
    Person() : name("Unknown"), id(0) {}
    Person(string n, int i) : name(n), id(i) {}
};

// ===== Base Class 1: Academic =====
class Academic {
protected:
    int marks;
public:
    Academic() : marks(0) {}
    void inputMarks(string subject) {
        while (true) {
            cout << "    Enter marks in " << subject << " (0-100): ";
            cin >> marks;
            if (cin.fail() || marks < 0 || marks > 100) {
                cout << "   Invalid marks! Enter a number between 0 and 100.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }
    }
    int getMarks() { return marks; }
};

// ===== Base Class 2: Attendance =====
class Attendance {
protected:
    float attendance;
public:
    Attendance(float a = 100.0) : attendance(a) {}
    void inputAttendance() {
        while (true) {
            cout << "    Enter attendance percentage (0-100): ";
            cin >> attendance;
            if (cin.fail() || attendance < 0 || attendance > 100) {
                cout << "    Invalid attendance! Enter valid % (0-100).\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }
    }
    float getAttendance() { return attendance; }

    // Unary Operator Overloading (boost attendance by 5%)
    void operator++() {
        attendance = (attendance + 5 > 100) ? 100 : attendance + 5;
    }
};

// ===== Derived Class: Student =====
class Student : public Person, public Academic, public Attendance {
    char grade;

public:
    Student() : Person(), Academic(), Attendance() {}
    Student(string n, int i, int m, float a)
        : Person(n, i), Academic(), Attendance(a) {
        marks = m;
        calculateGrade();
    }
    int getID() { return id; }


    // Function Overloading
    void calculateGrade() {
        if (marks >= 90) grade = 'A';
        else if (marks >= 75) grade = 'B';
        else if (marks >= 60) grade = 'C';
        else if (marks >= 40) grade = 'D';
        else grade = 'F';
    }
    void calculateGrade(float att) {
        if (marks >= 85 && att >= 80) grade = 'A';
        else if (marks >= 70) grade = 'B';
        else if (marks >= 55) grade = 'C';
        else if (marks >= 40) grade = 'D';
        else grade = 'F';
    }

    void inputDetails(string subject) {
        while (true) {
            cout << "    Enter Student ID (numeric): ";
            cin >> id;
            if (cin.fail() || id <= 0) {
                cout << "    Invalid ID! Enter a positive number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "    Enter Student Name: ";
        getline(cin, name);

        inputMarks(subject);
        inputAttendance();
        calculateGrade(attendance);
    }

    void displayReport(string subject) {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(12) << subject
             << setw(8) << marks
             << setw(8) << grade
             << setw(8) << attendance
             << "\n";
    }

    int getStudentMarks() { return marks; }
    float getStudentAttendance() { return attendance; }
    void boostAttendance() { ++(*this); calculateGrade(attendance); }
};

// ===== Class Report =====
class ClassReport {
    string className, subject, teacher;
    Student students[50];
    int n;

public:
    ClassReport(string cname = "") {
        className = cname;
        subject = "";
        teacher = "";
        n = 0;
    }

    void inputClassDetails() {
        cout << "\n========== Enter Class Report Details ==========\n";
        cout << "Class Name: " << className << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Subject: ";
        getline(cin, subject);

        cout << "Enter Teacher Name: ";
        getline(cin, teacher);

        while (true) {
            cout << "Enter number of students in " << className << ": ";
            cin >> n;
            if (cin.fail() || n <= 0 || n > 50) {
                cout << " Invalid number! Enter between 1 and 50.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        for (int i = 0; i < n; i++) {
            cout << "\n--- Student " << i + 1 << " ---\n";
            students[i].inputDetails(subject);
        }
    }

    void displayClassReport() {
        if (n == 0) {
            cout << "\n No class details available! Enter students first.\n";
            return;
        }

        cout << "\n\n==========  CLASS REPORT ==========\n";
        cout << "Class: " << className << " | Subject: " << subject
             << " | Teacher: " << teacher << "\n";
        cout << "----------------------------------------------------\n";
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(12) << "Subject"
             << setw(8) << "Marks"
             << setw(8) << "Grade"
             << setw(8) << "Att.%\n";
        cout << "----------------------------------------------------\n";

        for (int i = 0; i < n; i++) {
            students[i].displayReport(subject);
        }
    }

    void classSummary() {
        if (n == 0) {
            cout << "\n No class details available! Enter students first.\n";
            return;
        }

        int totalMarks = 0;
        float totalAttendance = 0;

        for (int i = 0; i < n; i++) {
            totalMarks += students[i].getStudentMarks();
            totalAttendance += students[i].getStudentAttendance();
        }

        cout << "\n========== SUMMARY ==========\n";
        cout << "Average Marks: " << (n > 0 ? (float)totalMarks / n : 0) << "\n";
        cout << "Average Attendance: " << (n > 0 ? totalAttendance / n : 0) << "%\n";
        cout << "================================\n";
    }

       void boostStudentAttendance() {
        if (n == 0) {
            cout << "\n No students available! Enter students first.\n";
            return;
        }

        int sid;
        cout << "Enter Student ID to boost attendance: ";
        cin >> sid;

        for (int i = 0; i < n; i++) {
            if (students[i].getID() == sid) {   // ? Now matches real ID
                students[i].boostAttendance();
                cout << " Attendance boosted for student ID " << sid << "!\n";
                return;
            }
        }
        cout << " Student with ID " << sid << " not found.\n";
    }

};

// ===== MAIN with Menu =====
int main() {
    ClassReport classA("BCA 1st Sem - A");
    int choice;

    do {
        cout << "\n==========  MENU ==========\n";
        cout << "1. Enter Class Details & Students\n";
        cout << "2. Display Class Report\n";
        cout << "3. View Summary\n";
        cout << "4. Boost Attendance of a Student\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: classA.inputClassDetails(); break;
            case 2: classA.displayClassReport(); break;
            case 3: classA.classSummary(); break;
            case 4: classA.boostStudentAttendance(); break;
            case 5: cout << "Exiting program...\n"; break;
            default: cout << " Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

