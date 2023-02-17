//Import Libraries
#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
#include <vector>
using namespace std; 

//Structure Definition
struct BstNode{
    public: 
        int course;
        string courseName;
        string courseInfo;
        BstNode* left;
        BstNode* right; 

        BstNode(int course, string courseName, string courseInfo){
            this -> course = course;
            this -> courseName = courseName; 
            this -> courseInfo = courseInfo;
            this -> left = NULL;
            this -> right = NULL; 
    }
};
//Function to print tree in-order
void PrintInOrder(BstNode* root){
    if (root == NULL) {
        return; 
    }
    //Recursive calls to print left subtree
    PrintInOrder(root -> left);
    //Print course name
    cout << root -> courseName << ", "; 
    //Create a vector to split course info
    vector <string> SplitCourseInfo;
    stringstream s(root-> courseInfo);
    string courseDescription;
    //Split course info by commas and store in a vector. 
    while (getline(s, courseDescription, ',')){
        SplitCourseInfo.push_back(courseDescription);
    }
    //Print first element in vector (course title)
    cout << SplitCourseInfo[0] << endl;
    //Recursive call to print right subtree
    PrintInOrder(root -> right); 
}
//Function to create new BST Node
BstNode* GetNewNode(int course, string courseName, string courseInfo){
    BstNode* newNode = new BstNode(course, courseName, courseInfo);
    newNode -> courseInfo = courseInfo; 
    newNode -> courseName = courseName; 
    newNode -> course = course; 
    newNode -> left = newNode -> right = NULL; 
    return newNode;
}
//Function to insert new node in BST
BstNode* Insert(BstNode* root, int course, string courseName, string courseInfo){
    if (root == NULL) {
        root = GetNewNode(course, courseName, courseInfo);

    } else if (course <= root -> course){
        root -> left = Insert(root->left, course, courseName, courseInfo);
    } else {
        root -> right = Insert(root-> right, course, courseName, courseInfo); 
    }
    return root;
}
//Function to search for a node in the BST
BstNode* Search(BstNode* root, int inputNum){
    if(root == NULL){
        return NULL;
    }
    else if (inputNum == root -> course) {
        return root; 
    }
    else if (inputNum <= root -> course){
        return Search(root ->left, inputNum);
    }
    else {
        return Search(root->right, inputNum); 
    }
}
//Function to split a string by commas and print
void SplitString(string splitInput){
    vector<string> SplitString; 
    stringstream ss(splitInput);
    string token;
    //Split string by commas and store in vector
    while (getline(ss, token, ',')){
        SplitString.push_back(token);
    }
    //Print first element in vector (course title)
    cout << SplitString[0] << endl; 
    cout << "Prerequisites: "; 
    //Print remaining elements in vector
    for (int i = 1; i < SplitString.size(); i++){
        cout << SplitString[i] << " "; 
    }

    cout << endl; 

}


int main(){
    
    BstNode* root = NULL; 
    int course_num;
    string courseInfo;
    string courseName; 
    string line;  
    string str_course_num;

    cout << "Welcome to Course Planner" << endl; 
    //Set boolean variables to track program state
    bool quit = false;
    bool exception_caught = false; 
    //Read course data from file and build binary search tree
    ifstream file("ABCU_Input.txt"); 
        if (file.is_open()){
            while (getline(file, line)){
                try {
                        //Parse course data from each line in the file
                        str_course_num = line.substr(4,3);
                        courseInfo = line.substr(8);   
                        courseName = line.substr(0, 7);
                        course_num = stoi(str_course_num);
                        //Insert course data into binary search tree
                        root = Insert(root, course_num, courseName, courseInfo);
                //Catch invalid data types in file
                } catch (const invalid_argument& e){
                    cerr << "Invalid Integer in file:" << e.what() << '\n';
                    file.close();
                    exception_caught = true;
                    break;
                }
            }
        file.close();
    }
    //Display menu and handle user input
while (!quit) {
    cout << "Menu:" << endl;
    cout << "1. Load Data Structure" << endl;
    cout << "2. Print Course List" << endl;
    cout << "3. Print Course" << endl;
    cout << "4. Exit" << endl;
    cout << "What would you like to do?" << endl; 
    int option;
    cin >> option;

    switch (option) {

        case 1: 
        {
            cout << "Data Structure Loaded" << endl; 
            break;
        }

        case 2:
        {
            //Print list of all courses in the binary search tree
            cout << "Here is a sample schedule: " << endl; 
            PrintInOrder(root); 
            break; 
        }
        case 3:
        {
            string cInfo, courseTitle;
            int inputNum;
            bool invalidEntry = false;

            cout << "What course do you want to know about? "<< endl;
            //Read user input and parse course number
            cin >> cInfo;
            inputNum = stoi(cInfo.substr(4));
            //Search for course in binary search tree
            BstNode* result = Search(root, inputNum);    
            if (result != NULL){ 
                //Print course name and prerequisites. 
                cout << result-> courseName << ", ";  
                SplitString(result-> courseInfo); 

            } else {
                //Handle invalid entry
                cout << "Didn't find that course. Please try again." << endl; 
                invalidEntry = true; 
            }
            if (invalidEntry){
                break;
            }
            break;
        }
        case 4: 
        {
            //Exit program
            quit = true;
            cout << "Thank you for using course planner!" << endl; 
            break; 
        }
        default: 
            //Handle invalid menu option
            cout << "Invalid option. Try again." << endl; 
            break;
    } 
}
return 0;
}
