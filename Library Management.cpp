#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Book {
    string bno;  // Book number
    string bname;  // Book name
    string aname;  // Author name

public:
    void createBook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter Book No.: ";
        cin >> bno;
        cin.ignore();  // Clear input buffer
        cout << "Enter Book Name: ";
        getline(cin, bname);
        cout << "Enter Author Name: ";
        getline(cin, aname);
        cout << "\nBook Created..\n";
    }

    void showBook() {
        cout << "\nBook Number: " << bno;
        cout << "\nBook Name: " << bname;
        cout << "\nAuthor Name: " << aname << endl;
    }

    void modifyBook() {
        cout << "\nBook Number: " << bno;
        cout << "\nEnter New Book Name: ";
        getline(cin, bname);
        cout << "Enter New Author Name: ";
        getline(cin, aname);
    }

    string getBno() {
        return bno;
    }

    void report() {
        cout << setw(10) << bno << setw(30) << bname << setw(20) << aname << endl;
    }
};

class Student {
    string admno;  // Admission number
    string name;  // Student name
    string stbno;  // Student book number
    int token;  // Total books issued

public:
    void createStudent() {
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "Enter Admission No.: ";
        cin >> admno;
        cin.ignore();  // Clear input buffer
        cout << "Enter Student Name: ";
        getline(cin, name);
        token = 0;
        stbno = "";
        cout << "\nStudent Record Created...\n";
    }

    void showStudent() {
        cout << "\nAdmission Number: " << admno;
        cout << "\nStudent Name: " << name;
        cout << "\nNo of Books Issued: " << token;
        if (token == 1) {
            cout << "\nBook Number: " << stbno;
        }
    }

    void modifyStudent() {
        cout << "\nAdmission Number: " << admno;
        cout << "\nEnter New Student Name: ";
        getline(cin, name);
    }

    string getAdmno() {
        return admno;
    }

    string getStbno() {
        return stbno;
    }

    int getToken() {
        return token;
    }

    void addToken() {
        token = 1;
    }

    void resetToken() {
        token = 0;
    }

    void setStbno(string t) {
        stbno = t;
    }

    void report() {
        cout << setw(10) << admno << setw(30) << name << setw(10) << token << endl;
    }
};

fstream fp, fp1;
Book bk;
Student st;

void writeBook() {
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do {
        system("cls");  // Clear screen
        bk.createBook();
        fp.write((char*)&bk, sizeof(Book));
        cout << "\nDo you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writeStudent() {
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do {
        system("cls");  // Clear screen
        st.createStudent();
        fp.write((char*)&st, sizeof(Student));
        cout << "\nDo you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displaySpecificBook(string n) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char*)&bk, sizeof(Book))) {
        if (bk.getBno() == n) {
            bk.showBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\nBook does not exist\n";
    }
    cin.get();
}

void displaySpecificStudent(string n) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(Student))) {
        if (st.getAdmno() == n) {
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\nStudent does not exist\n";
    }
    cin.get();
}

void modifyBookRecord() {
    string n;
    int found = 0;
    system("cls");
    cout << "\nMODIFY BOOK RECORD...\n";
    cout << "\nEnter the Book Number: ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&bk, sizeof(Book)) && found == 0) {
        if (bk.getBno() == n) {
            bk.showBook();
            cout << "\nEnter the new details:\n";
            bk.modifyBook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk, sizeof(Book));
            cout << "\nRecord Updated\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\nRecord Not Found\n";
    }
    cin.get();
}

void modifyStudentRecord() {
    string n;
    int found = 0;
    system("cls");
    cout << "\nMODIFY STUDENT RECORD...\n";
    cout << "\nEnter the Admission Number: ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student)) && found == 0) {
        if (st.getAdmno() == n) {
            st.showStudent();
            cout << "\nEnter the new details:\n";
            st.modifyStudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(Student));
            cout << "\nRecord Updated\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\nRecord Not Found\n";
    }
    cin.get();
}

void bookIssue() {
    string admno, bno;
    int found = 0, flag = 0;
    system("cls");
    cout << "\nBOOK ISSUE...\n";
    cout << "\nEnter the Admission Number: ";
    cin >> admno;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student)) && found == 0) {
        if (st.getAdmno() == admno) {
            found = 1;
            if (st.getToken() == 0) {
                cout << "\nEnter the Book Number: ";
                cin >> bno;
                while (fp1.read((char*)&bk, sizeof(Book)) && flag == 0) {
                    if (bk.getBno() == bno) {
                        bk.showBook();
                        flag = 1;
                        st.addToken();
                        st.setStbno(bk.getBno());
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(Student));
                        cout << "\nBook Issued Successfully!\n";
                    }
                }
                if (flag == 0) {
                    cout << "\nBook Number does not exist!\n";
                }
            } else {
                cout << "\nYou have already issued a book!\n";
            }
        }
    }
    if (found == 0) {
        cout << "\nStudent Record Not Found!\n";
    }
    fp.close();
    fp1.close();
}

void bookDeposit() {
    string admno, bno;
    int found = 0, flag = 0, days, fine;
    system("cls");
    cout << "\nBOOK DEPOSIT...\n";
    cout << "\nEnter the Admission Number: ";
    cin >> admno;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(Student)) && found == 0) {
        if (st.getAdmno() == admno) {
            found = 1;
            if (st.getToken() == 1) {
                while (fp1.read((char*)&bk, sizeof(Book)) && flag == 0) {
                    if (bk.getBno() == st.getStbno()) {
                        bk.showBook();
                        flag = 1;
                        st.resetToken();
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(Student));
                        cout << "\nEnter the number of days after which book is being deposited: ";
                        cin >> days;
                        if (days > 15) {
                            fine = (days - 15) * 10; // Assuming a fine of Rs.10 per day
                            cout << "\nYou have to pay a fine of Rs." << fine << endl;
                        }
                        cout << "\nBook Deposited Successfully!\n";
                    }
                }
                if (flag == 0) {
                    cout << "\nBook Number does not exist!\n";
                }
            } else {
                cout << "\nNo book is issued to this student!\n";
            }
        }
    }
    if (found == 0) {
        cout << "\nStudent Record Not Found!\n";
    }
    fp.close();
    fp1.close();
}

void adminMenu() {
    int choice;
    do {
        system("cls");
        cout << "\nADMINISTRATOR MENU";
        cout << "\n1. CREATE STUDENT RECORD";
        cout << "\n2. DISPLAY ALL STUDENTS RECORD";
        cout << "\n3. DISPLAY SPECIFIC STUDENT RECORD";
        cout << "\n4. MODIFY STUDENT RECORD";
        cout << "\n5. DELETE STUDENT RECORD";
        cout << "\n6. CREATE BOOK RECORD";
        cout << "\n7. DISPLAY ALL BOOKS";
        cout << "\n8. DISPLAY SPECIFIC BOOK";
        cout << "\n9. MODIFY BOOK RECORD";
        cout << "\n10. DELETE BOOK RECORD";
        cout << "\n11. BACK TO MAIN MENU";
        cout << "\nPlease Enter Your Choice (1-11): ";
        cin >> choice;
        switch (choice) {
            case 1:
                writeStudent();
                break;
            case 2:
                // Function to display all student records
                break;
            case 3:
                // Function to display specific student record
                break;
            case 4:
                modifyStudentRecord();
                break;
            case 5:
                // Function to delete student record
                break;
            case 6:
                writeBook();
                break;
            case 7:
                // Function to display all book records
                break;
            case 8:
                // Function to display specific book record
                break;
            case 9:
                modifyBookRecord();
                break;
            case 10:
                // Function to delete book record
                break;
            case 11:
                return;
            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }
        cin.ignore();
        cin.get();
    } while (choice != 11);
}


int main() {
    char ch;
    do {
        system("cls");
        cout << "\nMAIN MENU";
        cout << "\n1. BOOK ISSUE";
        cout << "\n2. BOOK DEPOSIT";
        cout << "\n3. ADMINISTRATOR MENU";
        cout << "\n4. EXIT";
        cout << "\nPlease Enter Your Choice (1-4): ";
        cin >> ch;
        switch (ch) {
            case '1':
                bookIssue();
                break;
            case '2':
                bookDeposit();
                break;
            case '3':
                adminMenu();
                break;
            case '4':
                cout << "\nExiting the program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }
        cin.ignore();
        cin.get();
    } while (ch != '4');
    return 0;
}