/**
 * Found an interesting c++ project at https://www.codewithc.com/c-projects-with-source-code/
 * Got a lot of help with CSV parsing at https://www.geeksforgeeks.org/csv-file-management-using-c/
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

bool included(vector<string> vector_arr, string value)
{
    return count(vector_arr.begin(), vector_arr.end(), value);
}

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
                       categories("firstName, lastName, type, amount, date") {};

    vector<string> parseCSVLine(string line);
    void initRecs();
    vector<string> categoryVector();
    void addEntry(string firstName, string lastName, string type, int amount, string date);
    void loadData();
    void readRecord(string category);
    void printData();
};
/**
 * @brief This takes a string in CSV format and returns a vector of the items
 * @param line {string}
 */
vector<string> RecordsManager::parseCSVLine(string line)
{
    vector<string> values;
    string currentWord = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ' && line[i] != ',')
        {
            currentWord += line[i];
        }
        else
        {
            values.push_back(currentWord);
            currentWord = "";
        }
    }
    // Adds last word
    values.push_back(currentWord);
    return values;
}

void RecordsManager::initRecs()
{
    recordWrite.open("records.csv");
    recordWrite << "firstName, lastName, type, amount, date";
    recordWrite.close();
}

vector<string> RecordsManager::categoryVector(){
    return parseCSVLine(categories);
}

void RecordsManager::addEntry(string firstName, string lastName, string type, int amount, string date)
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
 * @brief modified from source at https://www.geeksforgeeks.org/csv-file-management-using-c/
 * 
 */
void RecordsManager::readRecord(string category)
{
}

void printVector(vector<string> v, bool newLine, string sep){
    for (int i = 0; i < v.size(); i++)
    {
        if (i == v.size() -1){
            sep = "";
        }
        string element = v[i] + sep;
        if (newLine){
            cout << element << endl;
        }else
        {
            cout << element;
        }
    }
}
void RecordsManager::printData(){
    for (int i = 0; i < data.size(); i++)
    {   
       printVector(data[i], false, " ");
       cout << endl;
    }
    
    return;
}

int main()
{
    RecordsManager manage;
    // manage.addEntry("Andreia", "Biagioni", "Withdrawal", 1400, "10/19/2019");
    // manage.printData();
    manage.loadData();
    manage.printData();
    return 0;
}