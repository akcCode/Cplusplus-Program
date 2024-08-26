#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Course structure to store course details
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Helper function to convert a string to uppercase (to normalize course numbers)
string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Function to load course data from a file into a hash table
void loadDataStructure(unordered_map<string, Course>& courses) {
    string filename;
    cout << "Enter the course data file name: ";
    cin >> filename;

    // Print the file path for debugging
    cout << "Attempting to open file: " << filename << endl;

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file. Please check the file path and permissions." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseName, prerequisite;

        // Read course number and name
        getline(ss, courseNumber, ',');
        getline(ss, courseName, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseName = courseName;

        // Read prerequisites (if any)
        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        // Store course in hash table
        courses[courseNumber] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}


// Function to print the course list in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courses) {
    vector<string> courseNumbers;

    // Collect course numbers
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    // Sort course numbers
    sort(courseNumbers.begin(), courseNumbers.end());

    // Print course list
    cout << "Here is a sample schedule:" << endl;
    for (const string& courseNumber : courseNumbers) {
        cout << courseNumber << ", " << courses.at(courseNumber).courseName << endl;
    }
}

// Function to print course information
void printCourse(const unordered_map<string, Course>& courses) {
    string courseNumber;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    // Normalize course number to uppercase
    courseNumber = toUpperCase(courseNumber);

    auto it = courses.find(courseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ", " << course.courseName << endl;

        // Print prerequisites
        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                cout << course.prerequisites[i];
                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites." << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}

// Main menu function
void menu() {
    unordered_map<string, Course> courses;  // Hash table to store courses
    string choice;

    while (true) {
        // Display menu options
        cout << endl;
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        if (choice == "1") {
            loadDataStructure(courses);  // Load course data into the hash table
        }
        else if (choice == "2") {
            printCourseList(courses);  // Print courses in alphanumeric order
        }
        else if (choice == "3") {
            printCourse(courses);  // Print detailed course information
        }
        else if (choice == "9") {
            cout << "Thank you for using the course planner!" << endl;
            break;  // Exit the program
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }
}

int main() {
    menu();  // Start the program by displaying the menu
    return 0;
}
