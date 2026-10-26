#ifndef CAMPUSMANAGER_H
#define CAMPUSMANAGER_H

#include "Resource.h"
#include "ResourceManager.h"
#include "FileHandler.h"
#include "Sorting.h"
#include "Tree.h"
#include "HashTable.h"
#include "Graph.h"
#include "Request.h"
#include "RequestProcessor.h"
#include "Booking.h"
#include "BookingManager.h"
#include "dataGenerator.h"
#include <string>

// ============================================================
// CampusManager - Central controller
// Integrates Student A + B + C
// + Pre-loaded campus rooms (dataGenerator)
// + Timetable stored in file (admin protected)
// + Pre-loaded Graph that can still be edited
// ============================================================

class CampusManager {
private:
    ResourceManager resourceMgr;
    BST bst;
    HashTable hashTable;
    CategoryTree categoryTree;
    Graph campusMap;
    RequestProcessor requestProcessor;
    BookingManager bookingMgr;

    bool isAdminAuthenticated;

    void rebuildIndexes();
    void loadDefaultGraph();

public:
    CampusManager();

    void initialize();   // generate rooms + load graph + load timetable

    bool addResource(Resource& r);
    bool removeResource(const std::string& id);
    void displayAllResources();
    void searchResource(const std::string& id);
    void sortResources();

    void treeMenu();
    void hashMenu();
    void navigationMenu();
    void requestMenu();
    void timetableMenu();

    bool authenticateAdmin();

    void saveData();
    void loadTimetable();
    void saveTimetable();
};

#endif
