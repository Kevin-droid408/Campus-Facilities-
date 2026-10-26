# CS3400 Final Integrated Campus System (NUL)

Complete system integrating **Student A + Student B + Student C**.

## Features

| Feature | Status |
|---------|--------|
| Pre-loaded campus rooms (dataGenerator) | Yes – hundreds of rooms loaded on start |
| Add / Remove rooms | Fully supported |
| Search (LinkedList + HashTable + BST) | Yes |
| Sort (Merge Sort) | Yes |
| Requests (Queue + Priority Queue + Stack) | Yes |
| BST + Category Tree | Yes |
| Hash Table | Yes |
| Graph (pre-loaded + editable) | Yes – BFS, DFS, Dijkstra |
| Timetable (saved to file, admin only) | Yes |

## Admin Password for Timetable

```
admin123
```

## How to Compile (Windows)

```powershell
g++ -std=c++17 -Iinclude main.cpp src/Resource.cpp src/LinkedList.cpp src/ResourceManager.cpp src/Sorting.cpp src/FileHandler.cpp src/Request.cpp src/RequestProcessor.cpp src/Tree.cpp src/HashTable.cpp src/Graph.cpp src/Booking.cpp src/BookingManager.cpp src/TimetableParser.cpp src/dataGenerator.cpp src/CampusManager.cpp -o campus_system.exe
```

## How to Run

```powershell
.\campus_system.exe
```

On start the program will:
1. Generate all campus buildings and rooms
2. Pre-load the campus map (Graph)
3. Load any previously saved timetable

## Main Menu

```
1. Resource Management          (Add / Remove / Display)
2. Search Resources             (LinkedList + Hash + BST)
3. Sort Resources               (Merge Sort)
4. Resource Requests            (Queue + Priority Queue)
5. Tree Operations              (BST + Category Tree)
6. Hash Table Lookup
7. Campus Navigation            (Graph – also allows adding locations/pathways)
8. Timetable Management         (Admin only – password: admin123)
9. Save All Data to File
0. Exit
```

## Timetable Example

When adding a timetable entry (option 8 → 3):

```
Room ID       : FTF-105
Day           : Monday
Start time    : 08:00
End time      : 10:10
Course code   : M2504
```

Entries are saved automatically to `data/timetable.txt`.

## Team Ownership (for report)

| Module                              | Owner   |
|-------------------------------------|---------|
| Resource + LinkedList + Sorting     | A       |
| dataGenerator + Booking/Timetable   | A       |
| Queue + Stack + PriorityQueue       | B       |
| BST + Category Tree                 | C       |
| Hash Table                          | C       |
| Graph                               | C       |
| Integration + Main Menu             | All     |

TEAM MEMBERS:
REALEBOHA MAKHALEME  202322669
KOBO TS'EPO RAMOSOEU 202322608
BAHLAKOANA MOSOLA    202321284

BANNA BA THATA BA CS!
