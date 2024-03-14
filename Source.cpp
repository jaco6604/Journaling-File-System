#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>


namespace fileSystem = boost::filesystem;

using namespace std;

#pragma warning(disable : 4996)


// This is a function that records to a journal file
void recordJournal(const string& journalLocation, const string& line) {
    ofstream journalFile(journalLocation, ios::app);
    if (journalFile.is_open()) {
        journalFile << line << endl;
        journalFile.close();
    }
}
// This is a function to get the current time and date
string timeAndDate() {
    time_t cur = time(0);
    struct tm timeStruct;
    char st[100];
    timeStruct = *localtime(&cur);
    strftime(st, sizeof(st), "%m-%d-%y %X", &timeStruct);
    return st;
}


// This is a function responsible for monitoring changes within a folder
void monitorFolder(const string& folderLocation, const string& journalFolder) {
    fileSystem::path folder(folderLocation);

    auto entry = fileSystem::directory_iterator(folder);
    while (entry != fileSystem::directory_iterator()) {
        const auto& currentEntry = *entry;

        if (fileSystem::is_regular_file(currentEntry) && currentEntry.path().extension() == ".txt") {
            string fileLocation = currentEntry.path().string();
            string journalPath = journalFolder + "/j1_" + currentEntry.path().filename().stem().string() +
                "_" + to_string(rand()) + ".DAT";

            // This is the first entry in the journal
            string timeStamp = timeAndDate();
            string line = timeStamp + " + " + "l1:" + "File created";
            recordJournal(journalPath, line);

            // This is to read the first contain of the file
            ifstream file(fileLocation);
            string fileContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();

            // This is to record the lines in the journal
            istringstream iss(fileContent);
            string fileLine;
            int lineNum = 1;

            while (getline(iss, fileLine)) {
                timeStamp = timeAndDate();
                line = timeStamp + " + l" + boost::lexical_cast<string>(lineNum++) + ":" + fileLine;
                recordJournal(journalPath, line);
            }

        }

        ++entry;
    }


}

int main() {
    string folderPath = "C:/Users/asus/source/repos/Journaling File System Oper/Journaling File System Oper/myFolder";
    string journalFolder = "C:/Users/asus/source/repos/Journaling File System Oper/Journaling File System Oper/JournalFolder";


    while (true) {
        //This is to make sure that the journal folder exists
        cout << "Checking for folder\n";
        if (!fileSystem::exists(journalFolder))
        {
            fileSystem::create_directory(journalFolder);
        }

        // This is to monitor the folder to see if changes have been made

        cout << "Listening for events\n";
        monitorFolder(folderPath, journalFolder);

        string endLoop;
        cout << "Type 'stop' to stop monitoring folder: ";
        cin >> endLoop;
        if (endLoop == "stop") {
            cout << "Monitoring halted.";
            break;
        }
        else {
            cout << "Please enter a valid input.";
        }
    }



            return 0;
        }
    
