#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

bool included(vector<string> vector_arr, string value){
    bool exists = any_of(begin(vector_arr), end(vector_arr), [&](string s)
    {
        return s == value;
    });
}

class RecordsManager
{
private:
    ofstream recordWrite;
    ifstream recordRead;
    string fileName;

public:
    RecordsManager() : fileName("records.csv") {}

    // vector<string> parseCSVLine(string line){
    //     for (int i = 0; i < line.length(); i++)
    //     {

    //     }
        
    // }

    void initRecs()
    {
        recordWrite.open("records.csv");
        recordWrite << "firstName, lastName, type, amount, date";
        recordWrite.close();
    }

    void addEntry(string firstName, string lastName, string type, int amount, string date)
    {
        //  The Python in me wanted to do it this way, but I learned about sstream from the GeeksforGeeks below
        // string entry = firstName + ", " + lastName + ", " + type + ", " + amount + ", " + date + "\n";

        stringstream entry;
        entry << firstName + ", "
              << lastName + ", "
              << type + ", "
              << amount
              << ", "
              << date + "\n";

        //Open to Append
        recordWrite.open(fileName, ios::out | ios::app);
        recordWrite << endl
                    << entry.str();
        recordWrite.close();
    }

    vector<string> loadData()
    {
        vector<string> dataEntry;
        string item;
        recordRead.open(fileName);
        while (!recordRead.eof())
        {
            recordRead >> item;
            dataEntry.push_back(item);
        }
        recordRead.close();
        return dataEntry;
    }
    /** 
     * @brief modified from source at https://www.geeksforgeeks.org/csv-file-management-using-c/
     * 
     */
    void read_record()
    {
        // Open the data
        recordRead.open(fileName, ios::in);

        // Ask and pick which value to search for
        int rollnum, roll2, count = 0;
        // cout << "Enter the roll number "
        //      << "of the student to display details: ";
        // cin >> rollnum;

        // Read the Data from the file
        // as String Vector
        vector<string> row;
        string line, word, temp;

        // While there is still data to output
        while (!recordRead.eof())
        {

            // Empty the vector at the beginning of each loop
            row.clear();

            // read an entire row and
            // store it in a string variable 'line'
            getline(recordRead, line);
            // used for breaking words

            stringstream s;
            s << line;
            cout << s.str();
            return;

            // read every column data of a row and
            // store it in a string variable, 'word'
            // while (getline(s, word, ', '))
            // {

            //     // add all the column data
            //     // of a row to a vector
            //     row.push_back(word);
            // }

            // // convert string to integer for comparision
            // roll2 = stoi(row[0]);

            // // Compare the roll number
            // if (roll2 == rollnum)
            // {

            //     // Print the found data
            //     count = 1;
            //     cout << "Details of Roll " << row[0] << " : \n";
            //     cout << "Name: " << row[1] << "\n";
            //     cout << "Maths: " << row[2] << "\n";
            //     cout << "Physics: " << row[3] << "\n";
            //     cout << "Chemistry: " << row[4] << "\n";
            //     cout << "Biology: " << row[5] << "\n";
            //     break;
            // }
        }
        // if (count == 0)
        //     cout << "Record not found\n";
    }
};

int main()
{
    RecordsManager manage;
    // manage.initRecs();
    // manage.addEntry("David", "Corson", "Deposit", "1200", "9/22/20");
    // vector<string> data = manage.loadData();
    manage.read_record();

    return 0;
}