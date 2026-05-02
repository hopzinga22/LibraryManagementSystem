#include <iostream>
#include <string>
#include <fstream>
#include <random>

using namespace std;

//Function Declarations
void viewCatalogue();
void requestBook();
int returnIDGenerator();
void returnBook();

//Global Variables
int returnID;


int main()
{
    int choice;
    while (true)
    {
        cout << "-----------SUKASUKA LIBRARY MANAGEMENT SYSTEM---------------" << endl;
        cout << "Select a choice to proceed" << endl;
        cout << "1. View Catalogue" << endl;
        cout << "2. Request Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice)
    {
    case 1:
        viewCatalogue();
        break;
    case 2:
        requestBook();
        break;
    case 3:
        returnBook();
        break;
    case 4:
        cout << "Exiting...";
        return 0;
        break;
    default:
        cout << "Enter valid choice";
        break;
    }
    }
    return 0;
}

void viewCatalogue(){
    string buffer;
    ifstream fileReader("library_catalogue.txt");

    //Valiadates if the file opened
     if (!fileReader.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return;
    }
    //Reads to the file and stores the files content in the buffer
    while (getline (fileReader, buffer)) {
        cout << buffer << endl;
    }
    fileReader.close();
    return;
}

int returnIDGenerator(){
    // 1. Obtain a random number from hardware to seed the generator
    random_device rd; 
    
    // 2. Initialize a generator
    mt19937 gen(rd()); 

    // 3. Define the range [min, max] (inclusive)
    uniform_int_distribution<> distr(1, 50); 

    // 4. Generate the number
    return distr(gen);
}

void requestBook(){
    string searchID;
    cout << "Enter Book ID to search (e.g. LIB001): ";
    cin >> searchID;

    ifstream file("library_catalogue.txt");
    string line;
    bool found = false;
    bool printing = false;
    int dashCount = 0;
    returnID = returnIDGenerator();

    if (!file.is_open()) {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    while (getline(file, line)) {

        // Detect the start of a book block by checking if the line contains the search ID
        if (line.find("Book ID") != string::npos && line.find(searchID) != string::npos) {
            found = true;
            printing = true;
            dashCount = 0;
        }

        // Print lines once we found our book
        if (printing) {
            cout << line << endl;

            // Count the dashed separator lines to know when the book block ends
            if (line.find("---") != string::npos) {
                dashCount++;
                if (dashCount >= 2) {
                    cout << "Your unique return ID is " << returnID << "\n"; 
                    break; // Stop after the closing separator
                }
            }        }
    }

    if (!found) {
        cout << "\n  Book with ID \"" << searchID << "\" was not found in the catalogue." << endl;
    }

    file.close();
    return;
}


void returnBook(){
    int validateReturnID;
    cout << "Please input your return ID: ";
    cin >> validateReturnID;
    if(validateReturnID == returnID){
        cout << "Book Has been Returned" << endl;
    }else{
        cout << "Please Enter the correct return ID or pay up" << endl;
    }
    return; 
}
