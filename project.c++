#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
    string age;
};

void registerUser(const User& user) {
    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << user.username << " " << user.password << " " << user.age << endl;
        file.close();
        cout << "Registration successful!" << endl;
    } else {
        cout << "Failed to open file for registration." << endl;
    }
}

bool loginUser(const string& username, const string& password) {
    ifstream file("users.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string storedUsername, storedPassword, age;
            if (iss >> storedUsername >> storedPassword >> age) {
                if (storedUsername == username && storedPassword == password) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
    }
    return false;
}

void changePassword(const string& username, const string& oldPassword, const string& newPassword) {
    ifstream file("users.txt");
    ofstream tempFile("temp.txt");
    if (file.is_open() && tempFile.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string storedUsername, storedPassword, age;
            if (iss >> storedUsername >> storedPassword >> age) {
                if (storedUsername == username && storedPassword == oldPassword) {
                    tempFile << storedUsername << " " << newPassword << " " << age << endl;
                    cout << "Password changed successfully!" << endl;
                } else {
                    tempFile << line << endl;
                }
            }
        }
        file.close();
        tempFile.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
    } else {
        cout << "Failed to open file for changing password." << endl;
    }
}

int main() {
    int choice;
    string username, password, age;

    cout << "Security System" << endl;
    cout << "____________________" << endl;

    do {
        cout << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Change Password" << endl;
        cout << "4. Quit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Register" << endl;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                cout << "Age: ";
                cin >> age;

                User newUser{username, password, age};
                registerUser(newUser);
                break;
            }
            case 2: {
                cout << "Login" << endl;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (loginUser(username, password)) {
                    cout << "Login successful!" << endl;
                } else {
                    cout << "Invalid username or password." << endl;
                }
                break;
            }
            case 3: {
                cout << "Change Password" << endl;
                cout << "Username: ";
                cin >> username;
                cout << "Old Password: ";
                cin >> password;

                string newPassword;
                cout << "New Password: ";
                cin >> newPassword;

                changePassword(username, password, newPassword);
                break;
            }
            case 4: {
                cout << "Thank you! Exiting the program." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
