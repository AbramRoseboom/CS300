// Title : ProjectTwo.cpp
// Author : Abram Roseboom


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Structure used to store course information
struct Course {
    string courseId;
    string courseName;
    vector<string> preList; // Stores zero, one, or multiple prerequisites
};

// Binary Search Tree used to keep courses sorted by course ID
class BinarySearchTree {
private:

    // Node used by the Binary Search Tree
    struct Node {
        Course course;
        Node* right;
        Node* left;

        Node(Course aCourse) {
            course = aCourse;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    // Recursively prints courses in alphabetical order
    void inOrder(Node* node) {
        if (node == nullptr) {
            return;
        }

        inOrder(node->left);
        cout << node->course.courseId << ", " << node->course.courseName << endl;
        inOrder(node->right);
    }

    // Recursively deletes all nodes to free memory
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:

    // Creates an empty tree
    BinarySearchTree() {
        root = nullptr;
    }

    // Cleans up all allocated memory when the tree is destroyed
    ~BinarySearchTree() {
        deleteTree(root);
    }

    // Prints all courses in sorted order
    void InOrder() {
        inOrder(root);
    }

    // Adds a course to the Binary Search Tree
    void Insert(Course aCourse) {
        if (root == nullptr) {
            root = new Node(aCourse);
        }
        else {
            Node* curr = root;

            while (curr != nullptr) {

                // Move left if the new course ID comes before the current course
                if (aCourse.courseId < curr->course.courseId) {

                    // Insert the course if an empty spot is found
                    if (curr->left == nullptr) {
                        curr->left = new Node(aCourse);
                        break;
                    }

                    curr = curr->left;
                }
                else {

                    // Move right if the new course ID comes after the current course
                    if (curr->right == nullptr) {
                        curr->right = new Node(aCourse);
                        break;
                    }

                    curr = curr->right;
                }
            }
        }
    }

    // Searches for a course by course ID
    Course Search(string courseId) {
        Node* curr = root;

        while (curr != nullptr) {

            // Course found
            if (curr->course.courseId == courseId) {
                return curr->course;
            }

            // Search the left side of the tree
            else if (courseId < curr->course.courseId) {
                curr = curr->left;
            }

            // Search the right side of the tree
            else {
                curr = curr->right;
            }
        }

        // Returns an empty course if no match is found
        return Course();
    }
};

// Loads the sample courses into the Binary Search Tree
void loadCourses(BinarySearchTree* bst) {

    // Temporary course object reused for each course
    Course c;

    c.courseId = "CSCI100";
    c.courseName = "Introduction to Computer Science";
    c.preList.clear();
    bst->Insert(c);

    c.courseId = "CSCI101";
    c.courseName = "Introduction To Programming in C++";
    c.preList = { "CSCI100" };
    bst->Insert(c);

    c.courseId = "CSCI200";
    c.courseName = "Data Structures";
    c.preList = { "CSCI101" };
    bst->Insert(c);

    c.courseId = "MATH201";
    c.courseName = "Discrete Mathematics";
    c.preList.clear();
    bst->Insert(c);

    c.courseId = "CSCI300";
    c.courseName = "Introduction to Algorithms";
    c.preList = { "CSCI200", "MATH201" };
    bst->Insert(c);

    c.courseId = "CSCI301";
    c.courseName = "Advanced Programming in C++";
    c.preList = { "CSCI101" };
    bst->Insert(c);

    c.courseId = "CSCI350";
    c.courseName = "Operating Systems";
    c.preList = { "CSCI300" };
    bst->Insert(c);

    c.courseId = "CSCI400";
    c.courseName = "Large Software Development";
    c.preList = { "CSCI301", "CSCI350" };
    bst->Insert(c);

    cout << "Courses loaded successfully." << endl;
}

// Displays course information and prerequisites
void displayCourse(Course c) {
    cout << c.courseId << ", " << c.courseName << endl;
    cout << "Prerequisites: ";

    if (c.preList.empty()) {
        cout << "none" << endl;
    }
    else {
        for (size_t i = 0; i < c.preList.size(); i++) {
            cout << c.preList[i];

            if (i < c.preList.size() - 1) {
                cout << ", ";
            }
        }

        cout << endl;
    }
}

// Converts user input to uppercase so searches are not case-sensitive
void convertCase(string& s) {
    for (char& c : s) {
        c = toupper(c);
    }
}

// Main program
int main() {

    // Create the Binary Search Tree that will store all courses
    BinarySearchTree* bst = new BinarySearchTree();

    string choiceStr;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    // Continue showing the menu until the user exits
    while (choice != 9) {

        cout << "\n1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        cin >> choiceStr;

        // Check that the menu option entered is a number
        bool isNumeric =
            !choiceStr.empty() &&
            all_of(choiceStr.begin(), choiceStr.end(), ::isdigit);

        if (isNumeric) {
            choice = stoi(choiceStr);
        }
        else {
            choice = -1;
        }

        switch (choice) {

            // Load all courses into the tree
        case 1:
            loadCourses(bst);
            break;

            // Print all courses in alphabetical order
        case 2:
            cout << "Here is a sample schedule:" << endl;
            bst->InOrder();
            break;

            // Search for and display a specific course
        case 3: {
            string searchId;

            cout << "What course do you want to know about? ";
            cin >> searchId;

            convertCase(searchId);

            Course c = bst->Search(searchId);

            if (!c.courseId.empty()) {
                displayCourse(c);
            }
            else {
                cout << "Course ID " << searchId << " not found." << endl;
            }

            break;
        }

              // Exit the program
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

            // Handle invalid menu selections
        default:
            cout << choiceStr << " is not a valid option." << endl;
            break;
        }
    }

    // Free memory used by the Binary Search Tree
    delete bst;

    return 0;
}