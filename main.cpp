#include <iostream>
#include <string>
#include <limits>
#include "CampusManager.h"
#include "Resource.h"

using namespace std;

// ============================================================
// Safe integer input – prevents infinite loop on bad input
// ============================================================
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear rest of line
            return value;
        }
        // Invalid type entered (letter, symbol, etc.)
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();  // clear the fail flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
    }
}

void showMainMenu() {
    cout << "\n========================================================\n";
    cout << "  CS3400 NUL CAMPUS RESOURCE & ACTIVITY MANAGEMENT\n";
    cout << "========================================================\n";
    cout << " 1. Resource Management          (Add / Remove / Display)\n";
    cout << " 2. Search Resources             (LinkedList + Hash + BST)\n";
    cout << " 3. Sort Resources               (Merge Sort)\n";
    cout << " 4. Resource Requests            (Queue + Priority Queue)\n";
    cout << " 5. Tree Operations              (BST + Category Tree)\n";
    cout << " 6. Hash Table Lookup\n";
    cout << " 7. Campus Navigation            (Graph BFS/DFS/Dijkstra)\n";
    cout << " 8. Timetable Management         (Admin only)\n";
    cout << " 9. Save All Data to File\n";
    cout << " 0. Exit\n";
    cout << "========================================================\n";
}

int main() {
    CampusManager system;

    // Load all pre-generated rooms + graph + timetable
    system.initialize();

    int choice;
    do {
        showMainMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
        case 1: { // Resource Management
            int sub = readInt("\n1. Add Resource\n2. Remove Resource\n3. Display All\nChoice: ");
            if (sub == 1) {
                string id, name, type, loc;
                int cap, st;
                cout << "ID: "; getline(cin, id);
                cout << "Name: "; getline(cin, name);
                cout << "Type (Lab / Lecture Room / Office ...): "; getline(cin, type);
                cout << "Location: "; getline(cin, loc);
                cap = readInt("Capacity: ");
                st  = readInt("Status (0=AVAILABLE 1=BOOKED 2=MAINTENANCE): ");
                Resource r(id, name, type, loc, cap, static_cast<Status>(st));
                system.addResource(r);
            } else if (sub == 2) {
                string id;
                cout << "ID to remove: "; getline(cin, id);
                system.removeResource(id);
            } else if (sub == 3) {
                system.displayAllResources();
            } else {
                cout << "Invalid sub-choice.\n";
            }
            break;
        }
        case 2: {
            string id;
            cout << "Enter Resource ID to search: ";
            getline(cin, id);
            system.searchResource(id);
            break;
        }
        case 3:
            system.sortResources();
            break;
        case 4:
            system.requestMenu();
            break;
        case 5:
            system.treeMenu();
            break;
        case 6:
            system.hashMenu();
            break;
        case 7:
            system.navigationMenu();
            break;
        case 8:
            system.timetableMenu();
            break;
        case 9:
            system.saveData();
            break;
        case 0:
            cout << "Saving data before exit...\n";
            system.saveData();
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 0 and 9.\n";
        }
    } while (choice != 0);

    return 0;
}
