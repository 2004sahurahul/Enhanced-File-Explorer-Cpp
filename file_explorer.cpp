#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
using namespace std;

// Function to list all files in a directory
void listFiles(const char* path) {
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path)) != NULL) {
        cout << "\nContents of Directory: " << path << "\n";
        while ((entry = readdir(dir)) != NULL) {
            cout << entry->d_name << endl;
        }
        closedir(dir);
    } else {
        perror("Unable to open directory");
    }
}

// Function to create a new file
void createFile(string filename) {
    ofstream file(filename);
    if (file) cout << "File created successfully: " << filename << endl;
    else cout << "Error creating file.\n";
}

// Function to delete a file
void deleteFile(string filename) {
    if (remove(filename.c_str()) == 0) cout << "File deleted successfully.\n";
    else cout << "Unable to delete file.\n";
}

// Function to search for a file recursively
void searchFile(const char* path, string target) {
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(path)) == NULL) return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
                string newPath = string(path) + "/" + entry->d_name;
                searchFile(newPath.c_str(), target);
            }
        } else {
            if (strstr(entry->d_name, target.c_str()))
                cout << "Found: " << path << "/" << entry->d_name << endl;
        }
    }
    closedir(dir);
}

// Main program loop
int main() {
    cout << "---- File Explorer Application ----\n";
    string command, filename, path = ".";
    while (true) {
        cout << "\nEnter command (list/create/delete/search/exit): ";
        cin >> command;
        if (command == "list") listFiles(path.c_str());
        else if (command == "create") { 
            cout << "Enter filename: "; 
            cin >> filename; 
            createFile(filename); 
        }
        else if (command == "delete") { 
            cout << "Enter filename: "; 
            cin >> filename; 
            deleteFile(filename); 
        }
        else if (command == "search") { 
            cout << "Enter search keyword: "; 
            cin >> filename; 
            searchFile(path.c_str(), filename); 
        }
        else if (command == "exit") break;
        else cout << "Invalid command!\n";
    }
    return 0;
}
