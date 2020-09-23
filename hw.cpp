/**
 * Found an interesting c++ project at https://www.codewithc.com/c-projects-with-source-code/
 * Got a lot of help with CSV parsing at https://www.geeksforgeeks.org/csv-file-management-using-c/
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream> //stringstream types
#include <fstream> // for file access
#include <stdlib.h> // for clearing system console screen
#include <iomanip> // for clean text printing to console
using namespace std;

bool included(vector<string> vector_arr, string value)
{
    return count(vector_arr.begin(), vector_arr.end(), value);
}


/** 
 * @brief Funcs for app that will handle database through terminal
 */
class RecordsManager
{
private:
    ofstream recordWrite;
    ifstream recordRead;
    string fileName;

public:
    vector<vector<string> > data;
    string categories;
    RecordsManager() : fileName("records.csv"),
                       categories("firstName, lastName, type, amount, date"){};

    vector<string> parseCSVLine(string line);
    void resetRecords();
    vector<string> categoryVector();
    void addEntry(string firstName, string lastName, string type, string amount, string date);
    void manualEntry();
    void loadData();
    void readRecord(string category);
    void printEntry(string firstName, string lastName, string type, string amount, string date);
    void printData();
    void clearConsole();
    void manualDeleteEntry();
    void deleteEntry(int entryIndex);
    void updateFromData();
    void MainMenu();
};
/**
 * @brief This takes a string in CSV format and returns a vector of the items
 * @param line {string}
 */
vector<string> RecordsManager::parseCSVLine(string line)
{
    vector<string> values;
    string currentWord = "";
    char lastChar = '/';
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ' && line[i] != ',')
        {
            // Add letters to current word
            currentWord += line[i];
        }
        else
        {
            if (lastChar != ' ' && lastChar != ','){
                // Save last word and continue
                values.push_back(currentWord);
            }
            currentWord = "";
        }
        lastChar = line[i];
    }
    // Adds last word
    values.push_back(currentWord);
    return values;
}

/**
 * @brief Print out a single row's worth of data from the `printData` Function
 */
void printVector(vector<string> v, bool newLine, string sep, int index)
{
    for (int i = 0; i < v.size(); i++)
    {
        // if there is some space between values
        if (v[i] == " "){continue;}
        // it is the last element in the array
        if (i == v.size() - 1){sep = "";}
        string element = v[i] + sep;
        if (i == 0){
            string count = index != 0? to_string(index)+") " : "   ";
            cout << count;
        }
        if (newLine)
        {
            cout << left         // Aligns Left (I found this solution at https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c)
                 << setw(6)      // sets width between elements on a line?
                 << setfill(' ') // fills the blank spaces
                 << element
                 << endl;
        }
        else
        {
            cout << left         // Aligns Left
                 << setw(12)      // sets width between elements on a line?
                 << setfill(' ') // fills the blank spaces
                 << element;
        }
    }
}

void RecordsManager::MainMenu(){
    loadData();
    cout << "Please type the number of the command you would like to execute:\n\n"
         << "1) View Database\n"
         << "2) Add Entry\n"
         << "3) Delete Entry\n"
         << "4) Exit\n";
    int response;
    cin >> response;
    switch (response)
    {
    case (1):
        printData();
        MainMenu();
        break;
    case (2):
        manualEntry();
        break;
    case (3):
        manualDeleteEntry();
        break;
    case (4):
        cout << "Goodbye!";
        break;
    default:
        break;
    }
}

/** 
 * @brief Reset database
 */
void RecordsManager::resetRecords()
{
    recordWrite.open(fileName);
    recordWrite << "firstName, lastName, type, amount, date";
    recordWrite.close();
}

/** 
 * @brief Converts category string from class to a vector
 */
vector<string> RecordsManager::categoryVector()
{
    return parseCSVLine(categories);
}

/** 
 * @brief adds an entry to the record database and writes to file
 */
void RecordsManager::addEntry(string firstName, string lastName, string type, string amount, string date)
{
    //  The Python in me wanted to do it this way, but I learned about sstream from the GeeksforGeeks below
    // string entry = firstName + ", " + lastName + ", " + type + ", " + amount + ", " + date + "\n";

    stringstream entry;
    entry << firstName + ", "
          << lastName + ", "
          << type + ", "
          << amount
          << ", "
          << date;

    //Open to Append
    recordWrite.open(fileName, ios::out | ios::app);
    recordWrite << endl
                << entry.str();
    recordWrite.close();
}

/** 
 * @brief User interface console oriented function to add a user through terminal
 */
void RecordsManager::manualEntry(){
    string firstName, lastName, type, date;
    int amount, typeEntry;
    cout << "New Entry\n"
         << "First Name: ";
    cin >> firstName;
    cout << endl << "Last Name: ";
    cin >> lastName;
    cout << endl << "Please pick the number corresponding to the action-type:"
         << "\n1) Withdrawal" 
         << "\n2) Deposit\n";
    cin >> typeEntry;
    type = typeEntry == 1? "Withdrawal" : "Deposit";
    cout << endl << type + " amount: ";
    cin >> amount;
    cout << "\nPlease enter date of transaction in \"mm/dd/yy\" format: ";
    cin >> date;

    int confirmation;
    cout << endl;
    printEntry(firstName, lastName, type, to_string(amount), date);
    cout << "\n\nPlease confirm that the above transaction looks correct"
         << "\n1) Looks good (entry WILL be saved)"
         << "\n2) Restart (entry will NOT be saved)"
         << "\n3) Exit (entry will NOT be saved)\n";
    cin >> confirmation;
    clearConsole();
    string exit;
    switch (confirmation)
    {
    case (1):
        addEntry(firstName, lastName, type, to_string(amount), date);
        cout << "Entry Saved!\n Press any button to return to the main screen";
        cin >> exit;
        clearConsole();
        MainMenu();
        break;
    case (2):
        manualEntry(); // Restart
        break;
    case (3):
        clearConsole();
        MainMenu();
        break;
    default:
        MainMenu();
    }

}

/**
 * @brief User can use this function to delete an entry from the console. 
 */
void RecordsManager::manualDeleteEntry(){
    loadData();
    printData();
    cout << "\nPlease enter the index of the entry you wish to delete\n";
    int response;
    cin >> response;
    vector<string> entry = data[response];
    string firstName, lastName, type, amount, date;
    firstName = entry[0],
    lastName = entry[1],
    type = entry[2],
    amount = entry[3],
    date = entry[4],
    printEntry(firstName, lastName, type, amount, date);
    cout << "\n\n Are you SURE that you would like to delete the entry above?"
         << "\n1) Yes"
         << "\n2) Cancel (Back to Main)\n";
    int confirmation;
    cin >> confirmation;
    clearConsole();
    string exit;
    switch (confirmation)
    {
        case (1):
            deleteEntry(response);
            cout << "\nEntry has been deleted, press any button to return to Main\n";
            cin >> exit;
            clearConsole();
            MainMenu();
            break;
        default:
            MainMenu();
            break;
    }
}

void RecordsManager::deleteEntry(int entryIndex){
    data.erase(data.begin() + entryIndex);
    updateFromData();
}

void RecordsManager::updateFromData(){
    resetRecords();
    string firstName, lastName, type, amount, date;
    for (int i = 1; i < data.size(); i++)
    {
        firstName = data[i][0],
        lastName = data[i][1],
        type = data[i][2],
        amount = data[i][3],
        date = data[i][4],
        addEntry(firstName, lastName, type, amount, date);
    }
    
}

/** 
 * @brief Prints an entry in the database in a pivot-table view
 */
void RecordsManager::printEntry(string firstName, string lastName, string type, string amount, string date){
    cout << left << setw(40) << setfill('_') << "First Name: " << firstName << endl
         << left << setw(40) << setfill('_') << "Last Name: " << lastName << endl
         << left << setw(40) << setfill('_') << "Transaction-type: " << type << endl
         << left << setw(40) << setfill('_') << "Amount: " << amount << endl
         << left << setw(40) << setfill('_') << "Date: " << date;
}

/** 
 * @brief loadData Initializes a data object array in the Class for use
 */
void RecordsManager::loadData()
{
    // Open the data
    recordRead.open(fileName, ios::in);

    string line;
    vector<string> row;
    vector<vector<string> > frame;
    // While there is still data to output
    while (!recordRead.eof())
    {
        getline(recordRead, line);
        row = parseCSVLine(line);
        frame.push_back(row);
    }
    recordRead.close();
    //load frame to data file.
    data = frame;
}

/** 
 * @brief Potenatially deprecated func that will search for a value in db
 * @param category {string} the category to look up - potentially deprectaed once app becomes more interactive
 */
void RecordsManager::readRecord(string category)
{
}

/**
 * @brief Prints out display of all data entries in console
 */
void RecordsManager::printData()
{
    for (int i = 0; i < data.size(); i++)
    {
        printVector(data[i], false, "", i);
        cout << endl;
    }
    return;
}

/**
 * @brief Clears Console screen (not working yet for my computer before exe created)
 */
void RecordsManager::clearConsole(){
    cout << flush;

}

int main()
{
    RecordsManager manage;
    cout << "Welcome to the Records Manager\n";
    manage.MainMenu();
    return 0;
}