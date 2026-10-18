#include <iostream>
#include <string>
#include <vector>

// Forward Declaration
struct Item;

// Node for Inventory Linked List
struct ItemNode {
    std::string name;
    ItemNode* next;
    ItemNode(std::string itemName) : name(itemName), next(nullptr) {}
};

// Player Inventory Class (Singly Linked List)
class Inventory {
private:
    ItemNode* head;
public:
    Inventory() : head(nullptr) {}

    ~Inventory() {
        ItemNode* current = head;
        while (current != nullptr) {
            ItemNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addItem(const std::string& name) {
        ItemNode* newNode = new ItemNode(name);
        newNode->next = head;
        head = newNode;
        std::cout << "Picked up: " << name << "\n";
    }

    bool hasItem(const std::string& name) const {
        ItemNode* current = head;
        while (current != nullptr) {
            if (current->name == name) return true;
            current = current->next;
        }
        return false;
    }

    void display() const {
        if (!head) {
            std::cout << "Inventory: [Empty]\n";
            return;
        }
        std::cout << "Inventory: ";
        ItemNode* current = head;
        while (current != nullptr) {
            std::cout << "[" << current->name << "] ";
            current = current->next;
        }
        std::cout << "\n";
    }
};

// Room Node Structure
struct Room {
    std::string name;
    std::string description;
    std::string item; // Item available in room (empty string if none)
    bool isLocked;
    std::string requiredKey;

    // Navigation Pointers (Doubly-linked network structure)
    Room* north;
    Room* south;
    Room* east;
    Room* west;

    Room(std::string rName, std::string rDesc, bool locked = false, std::string keyNeeded = "")
        : name(rName), description(rDesc), item(""), isLocked(locked), requiredKey(keyNeeded),
          north(nullptr), south(nullptr), east(nullptr), west(nullptr) {}
};

// Game Manager Class
class EscapeRoomGame {
private:
    Room* currentRoom;
    Inventory playerInventory;
    std::vector<Room*> allRooms; // Keeps track of allocated rooms for cleanup

public:
    EscapeRoomGame() : currentRoom(nullptr) {
        setupMaze();
    }

    ~EscapeRoomGame() {
        // Free dynamically allocated Room memory
        for (Room* room : allRooms) {
            delete room;
        }
    }

    void setupMaze() {
        // Allocate Rooms Dynamically
        Room* foyer = new Room("Foyer", "A dimly lit entry room. Dust covers the old wooden floor.");
        Room* library = new Room("Library", "Shelves full of ancient books line the walls.");
        Room* armory = new Room("Armory", "Rusty swords and suits of armor hang from racks.");
        Room* dungeon = new Room("Dungeon Door", "A heavy iron door blocks the way outside.", true, "Brass Key");

        // Track allocations for destructor cleanup
        allRooms = { foyer, library, armory, dungeon };

        // Link Rooms (Directions)
        foyer->north = library;
        library->south = foyer;

        foyer->east = armory;
        armory->west = foyer;

        library->east = dungeon;
        dungeon->west = library;

        // Place Items
        armory->item = "Brass Key";

        currentRoom = foyer;
    }

    void play() {
        std::cout << "=======================================\n";
        std::cout << "    WELCOME TO THE ESCAPE ROOM GAME    \n";
        std::cout << "=======================================\n\n";

        std::string command;
        while (true) {
            std::cout << "\n---------------------------------------\n";
            std::cout << "Location: " << currentRoom->name << "\n";
            std::cout << currentRoom->description << "\n";

            if (!currentRoom->item.empty()) {
                std::cout << "You see an item here: " << currentRoom->item << "\n";
            }

            playerInventory.display();

            if (currentRoom->name == "Dungeon Door" && !currentRoom->isLocked) {
                std::cout << "\n*** CONGRATULATIONS! You unlocked the door and escaped! ***\n";
                break;
            }

            std::cout << "\nActions: [north, south, east, west, pick, exit]\n";
            std::cout << "Enter command: ";
            std::cin >> command;

            if (command == "exit") {
                std::cout << "Exiting game. Thanks for playing!\n";
                break;
            } else if (command == "pick") {
                if (!currentRoom->item.empty()) {
                    playerInventory.addItem(currentRoom->item);
                    currentRoom->item = "";
                } else {
                    std::cout << "Nothing here to pick up.\n";
                }
            } else if (command == "north" || command == "south" || command == "east" || command == "west") {
                move(command);
            } else {
                std::cout << "Invalid command!\n";
            }
        }
    }

private:
    void move(const std::string& direction) {
        Room* nextRoom = nullptr;

        if (direction == "north") nextRoom = currentRoom->north;
        else if (direction == "south") nextRoom = currentRoom->south;
        else if (direction == "east") nextRoom = currentRoom->east;
        else if (direction == "west") nextRoom = currentRoom->west;

        if (nextRoom == nullptr) {
            std::cout << "A solid stone wall blocks your path in that direction.\n";
            return;
        }

        if (nextRoom->isLocked) {
            std::cout << "The path to " << nextRoom->name << " is locked.\n";
            if (playerInventory.hasItem(nextRoom->requiredKey)) {
                std::cout << "You used the [" << nextRoom->requiredKey << "] to unlock " << nextRoom->name << "!\n";
                nextRoom->isLocked = false;
                currentRoom = nextRoom;
            } else {
                std::cout << "You need [" << nextRoom->requiredKey << "] to enter.\n";
            }
        } else {
            currentRoom = nextRoom;
        }
    }
};

int main() {
    EscapeRoomGame game;
    game.play();
    return 0;
}