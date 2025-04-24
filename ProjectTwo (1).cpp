#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Course structure
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Binary Search Tree Node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

class CourseBST {
private:
    Node* root;

    // Helper to print in order
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseName << endl;
            inOrder(node->right);
        }
    }

    // Helper to insert recursively
    Node* insert(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }
        if (course.courseNumber < node->course.courseNumber) {
            node->left = insert(node->left, course);
        } else {
            node->right = insert(node->right, course);
        }
        return node;
    }

    // Helper to search recursively
    Course search(Node* node, string courseNumber) {
        if (node == nullptr) {
            return Course();
        }
        if (node->course.courseNumber == courseNumber) {
            return node->course;
        } else if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        } else {
            return search(node->right, courseNumber);
        }
    }

public:
    CourseBST() {
        root = nullptr;
    }

    void insert(Course course) {
        root = insert(root, course);
    }

    void printInOrder() {
        inOrder(root);
    }

    Course search(string courseNumber) {
        return search(root, courseNumber);
    }
};

// Trim whitespace from both ends
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

vector<Course> parseCourses(const string& fileName) {
    vector<Course> courses;
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        if (!getline(ss, course.courseNumber, ',')) continue;
        if (!getline(ss, course.courseName, ',')) continue;

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(trim(token));
        }

        courses.push_back(course);
    }

    return courses;
}

void printCourse(const Course& course) {
    if (course.courseNumber.empty()) {
        cout << "Course not found." << endl;
        return;
    }
    cout << course.courseNumber << ", " << course.courseName << endl;
    if (!course.prerequisites.empty()) {
        sort(course.prerequisites.begin(), course.prerequisites.end());
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

int main() {
    CourseBST bst;
    vector<Course> courseList;
    string fileName;
    string courseKey;
    int choice = 0;

    while (choice != 9) {
        cout << "\nMenu:" << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            cin >> fileName;
            courseList = parseCourses(fileName);
            for (const auto& course : courseList) {
                bst.insert(course);
            }
            cout << "Courses loaded successfully." << endl;
            break;
        case 2:
            bst.printInOrder();
            break;
        case 3:
            cout << "Enter course number: ";
            cin >> courseKey;
            printCourse(bst.search(courseKey));
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}

