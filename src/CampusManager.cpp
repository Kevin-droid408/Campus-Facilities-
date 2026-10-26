#include "CampusManager.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Safe integer input – prevents infinite loop when user types letters
static int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

CampusManager::CampusManager() : isAdminAuthenticated(false) {
    categoryTree.buildDefaultHierarchy();
}

// ============================================================
// Startup
// ============================================================
void CampusManager::initialize() {
    cout << "\nInitializing Campus System...\n";

    // 1. Generate all buildings / rooms from dataGenerator
    generateAllBuildings(resourceMgr);
    rebuildIndexes();
    cout << "Resources loaded into LinkedList, BST and HashTable.\n";

    // 2. Pre-load realistic campus map
    loadDefaultGraph();
    cout << "Campus map (Graph) pre-loaded.\n";

    // 3. Load any previously saved timetable
    loadTimetable();

    cout << "System ready.\n";
}

void CampusManager::rebuildIndexes() {
    // Clear and rebuild BST + HashTable from the LinkedList
    // (simple approach: re-insert everything)
    for (int i = 0; i < resourceMgr.count(); i++) {
        Resource* r = resourceMgr.getList().getAt(i);
        if (r) {
            bst.insert(*r);
            hashTable.insert(*r);
        }
    }
}

void CampusManager::loadDefaultGraph() {
    // Pre-populate with realistic NUL-style locations
    campusMap.addVertex("Library");
    campusMap.addVertex("CS Building");
    campusMap.addVertex("Academic Building");
    campusMap.addVertex("Science Building");
    campusMap.addVertex("Labs");
    campusMap.addVertex("Administration");
    campusMap.addVertex("Student Affairs");
    campusMap.addVertex("Sports Complex");
    campusMap.addVertex("Cafeteria");
    campusMap.addVertex("BTM");
    campusMap.addVertex("FTF");
    campusMap.addVertex("Netherlands Hall");

    campusMap.addEdge("Library", "CS Building", 20);
    campusMap.addEdge("CS Building", "Academic Building", 30);
    campusMap.addEdge("Academic Building", "Labs", 15);
    campusMap.addEdge("Library", "Administration", 45);
    campusMap.addEdge("Administration", "Student Affairs", 25);
    campusMap.addEdge("CS Building", "Student Affairs", 35);
    campusMap.addEdge("Academic Building", "Sports Complex", 50);
    campusMap.addEdge("Science Building", "Labs", 10);
    campusMap.addEdge("Science Building", "Academic Building", 25);
    campusMap.addEdge("Cafeteria", "Library", 30);
    campusMap.addEdge("BTM", "FTF", 40);
    campusMap.addEdge("FTF", "Academic Building", 35);
    campusMap.addEdge("Netherlands Hall", "Administration", 20);
    campusMap.addEdge("Sports Complex", "Cafeteria", 45);
}

// ============================================================
// Resource operations (keep all three structures in sync)
// ============================================================
bool CampusManager::addResource(Resource& r) {
    if (resourceMgr.idExists(r.getID())) {
        cout << "Resource ID already exists.\n";
        return false;
    }
    resourceMgr.addResource(r);
    bst.insert(r);
    hashTable.insert(r);
    cout << "Resource added to LinkedList, BST and HashTable.\n";
    return true;
}

bool CampusManager::removeResource(const string& id) {
    Resource removed;
    if (!resourceMgr.removeResource(id, &removed)) {
        cout << "Resource not found.\n";
        return false;
    }
    bst.remove(id);
    hashTable.remove(id);
    cout << "Resource removed from all structures.\n";
    return true;
}

void CampusManager::displayAllResources() {
    resourceMgr.displayAll();
}

void CampusManager::searchResource(const string& id) {
    cout << "\n--- Search Results for \"" << id << "\" ---\n";

    Resource r;
    if (resourceMgr.findResource(id, r)) {
        cout << "[LinkedList] Found:\n";
        r.display();
    } else {
        cout << "[LinkedList] Not found.\n";
    }

    Resource* hp = hashTable.search(id);
    if (hp) {
        cout << "[HashTable] Found:\n";
        hp->display();
    } else {
        cout << "[HashTable] Not found.\n";
    }

    if (bst.search(id)) {
        cout << "[BST] Found.\n";
    } else {
        cout << "[BST] Not found.\n";
    }
}

void CampusManager::sortResources() {
    int n = resourceMgr.count();
    if (n == 0) {
        cout << "No resources to sort.\n";
        return;
    }
    Resource* arr = resourceMgr.toArray();
    int c = readInt("1. Sort by ID\n2. Sort by Name\n3. Sort by Capacity\nChoice: ");
    if (c == 1) mergeSort(arr, n, Resource::compareByID);
    else if (c == 2) mergeSort(arr, n, Resource::compareByName);
    else mergeSort(arr, n, Resource::compareByCapacity);

    cout << "\n--- Sorted Resources (first 30 shown) ---\n";
    int limit = (n < 30) ? n : 30;
    for (int i = 0; i < limit; i++) arr[i].display();
    if (n > 30) cout << "... (" << n - 30 << " more)\n";
    delete[] arr;
}

// ============================================================
// Tree Menu
// ============================================================
void CampusManager::treeMenu() {
    int choice;
    do {
        cout << "\n--- Tree Operations ---\n";
        cout << "1. BST Inorder (sorted by ID)\n";
        cout << "2. BST Preorder\n";
        cout << "3. BST Postorder\n";
        cout << "4. BST Level-order\n";
        cout << "5. Display Category Hierarchy\n";
        cout << "6. Add Category\n";
        cout << "0. Back\n";
        choice = readInt("Choice: ");

        if (choice == 1) bst.inorder();
        else if (choice == 2) bst.preorder();
        else if (choice == 3) bst.postorder();
        else if (choice == 4) bst.levelOrder();
        else if (choice == 5) categoryTree.display();
        else if (choice == 6) {
            string parent, neu;
            cout << "Parent category: "; getline(cin, parent);
            cout << "New category   : "; getline(cin, neu);
            categoryTree.addCategory(parent, neu);
        }
    } while (choice != 0);
}

// ============================================================
// Hash Table Menu
// ============================================================
void CampusManager::hashMenu() {
    int choice;
    do {
        cout << "\n--- Hash Table ---\n";
        cout << "1. Search by ID\n";
        cout << "2. Display table (non-empty buckets)\n";
        cout << "3. Show load factor\n";
        cout << "0. Back\n";
        choice = readInt("Choice: ");

        if (choice == 1) {
            string id;
            cout << "Resource ID: "; getline(cin, id);
            Resource* r = hashTable.search(id);
            if (r) r->display();
            else cout << "Not found.\n";
        } else if (choice == 2) {
            hashTable.display();
        } else if (choice == 3) {
            cout << "Load Factor: " << hashTable.loadFactor()
                 << " | Elements: " << hashTable.getSize() << endl;
        }
    } while (choice != 0);
}

// ============================================================
// Navigation / Graph Menu
// ============================================================
void CampusManager::navigationMenu() {
    int choice;
    do {
        cout << "\n--- Campus Navigation (Graph) ---\n";
        cout << "1. Display map\n";
        cout << "2. BFS\n";
        cout << "3. DFS\n";
        cout << "4. Shortest Path (Dijkstra)\n";
        cout << "5. Check reachable\n";
        cout << "6. Connected Components\n";
        cout << "7. Add new location\n";
        cout << "8. Add new pathway\n";
        cout << "0. Back\n";
        choice = readInt("Choice: ");

        if (choice == 1) campusMap.display();
        else if (choice == 2) {
            string s; cout << "Start location: "; getline(cin, s);
            campusMap.BFS(s);
        } else if (choice == 3) {
            string s; cout << "Start location: "; getline(cin, s);
            campusMap.DFS(s);
        } else if (choice == 4) {
            string from, to;
            cout << "From: "; getline(cin, from);
            cout << "To  : "; getline(cin, to);
            campusMap.Dijkstra(from, to);
        } else if (choice == 5) {
            string from, to;
            cout << "From: "; getline(cin, from);
            cout << "To  : "; getline(cin, to);
            cout << (campusMap.isReachable(from, to) ? "Yes, reachable.\n" : "No, not reachable.\n");
        } else if (choice == 6) {
            campusMap.connectedComponents();
        } else if (choice == 7) {
            string name;
            cout << "New location name: "; getline(cin, name);
            campusMap.addVertex(name);
        } else if (choice == 8) {
            string from, to;
            int w;
            cout << "From: "; getline(cin, from);
            cout << "To  : "; getline(cin, to);
            w = readInt("Distance (metres): ");
            campusMap.addEdge(from, to, w);
        }
    } while (choice != 0);
}

// ============================================================
// Request Menu (Student B)
// ============================================================
void CampusManager::requestMenu() {
    int choice;
    do {
        cout << "\n--- Request Management ---\n";
        cout << "1. Submit normal request\n";
        cout << "2. Submit priority request\n";
        cout << "3. Process normal request\n";
        cout << "4. Process priority request\n";
        cout << "5. Display pending requests\n";
        cout << "0. Back\n";
        choice = readInt("Choice: ");

        if (choice == 1 || choice == 2) {
            int id; string desc; int p;
            id = readInt("Request ID: ");
            cout << "Description: "; getline(cin, desc);
            p = readInt("Priority (1=LOW 2=NORMAL 3=HIGH 4=EMERGENCY): ");
            if (p < 1) p = 1; if (p > 4) p = 4;
            Request req(id, desc, static_cast<Priority>(p), RequestStatus::PENDING);
            if (choice == 1) requestProcessor.submitNormalRequest(req);
            else requestProcessor.submitPriorityRequest(req);
        } else if (choice == 3) {
            requestProcessor.processNormalRequest();
        } else if (choice == 4) {
            requestProcessor.processPriorityRequest();
        } else if (choice == 5) {
            requestProcessor.displayPendingRequests();
        }
    } while (choice != 0);
}

// ============================================================
// Admin authentication (simple password for student project)
// ============================================================
bool CampusManager::authenticateAdmin() {
    if (isAdminAuthenticated) return true;

    string password;
    cout << "Admin password: ";
    getline(cin, password);

    // Simple password for the project demonstration
    if (password == "admin123") {
        isAdminAuthenticated = true;
        cout << "Admin access granted.\n";
        return true;
    }
    cout << "Incorrect password. Access denied.\n";
    return false;
}

// ============================================================
// Timetable Menu (Admin protected)
// ============================================================
void CampusManager::timetableMenu() {
    if (!authenticateAdmin()) return;

    int choice;
    do {
        cout << "\n--- Timetable / Booking Management (Admin) ---\n";
        cout << "1. View all bookings\n";
        cout << "2. View timetable for a specific room\n";
        cout << "3. Add new timetable entry\n";
        cout << "4. Check if a room is free\n";
        cout << "5. Save timetable to file\n";
        cout << "0. Back\n";
        choice = readInt("Choice: ");

        if (choice == 1) {
            bookingMgr.displayAll();
        }
        else if (choice == 2) {
            string room;
            cout << "Room ID (e.g. FTF-105): "; getline(cin, room);
            bookingMgr.displayForRoom(room);
        }
        else if (choice == 3) {
            string room, day, start, end, course;
            cout << "Room ID       : "; getline(cin, room);
            cout << "Day           : "; getline(cin, day);
            cout << "Start time    : "; getline(cin, start);
            cout << "End time      : "; getline(cin, end);
            cout << "Course code   : "; getline(cin, course);

            // Create a booking (isUniversity = false means user/admin entry)
            Booking b(room, day, start, end, course, "COURSE", course, false);
            if (bookingMgr.addUserBooking(b)) {
                cout << "Timetable entry added successfully.\n";
                saveTimetable();   // auto-save
            } else {
                cout << "Failed. Room may already be occupied at that time.\n";
            }
        }
        else if (choice == 4) {
            string room, day, time;
            cout << "Room ID   : "; getline(cin, room);
            cout << "Day       : "; getline(cin, day);
            cout << "Time      : "; getline(cin, time);
            if (bookingMgr.isFree(room, day, time))
                cout << "Room is FREE at that time.\n";
            else
                cout << "Room is OCCUPIED at that time.\n";
        }
        else if (choice == 5) {
            saveTimetable();
        }
    } while (choice != 0);
}

// ============================================================
// Persistence
// ============================================================
void CampusManager::saveData() {
    if (FileHandler::saveResources("data/resources.txt", resourceMgr)) {
        cout << "Resources saved to data/resources.txt\n";
    } else {
        cout << "Failed to save resources.\n";
    }
    saveTimetable();
}

void CampusManager::loadTimetable() {
    int n = bookingMgr.loadUser("data/timetable.txt");
    cout << "Loaded " << n << " timetable entries.\n";
}

void CampusManager::saveTimetable() {
    if (bookingMgr.saveUser("data/timetable.txt")) {
        cout << "Timetable saved to data/timetable.txt\n";
    } else {
        cout << "Failed to save timetable.\n";
    }
}
