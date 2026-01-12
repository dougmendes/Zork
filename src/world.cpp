#include "world.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// Constructor
World::World() 
    : player(nullptr), gameRunning(false) {
}

// Destructor - delete all entities
World::~World() {
    // Delete all entities (World owns them)
    for (Entity* entity : entities) {
        delete entity;
    }
    entities.clear();
}

// Add entity to world
void World::AddEntity(Entity* entity) {
    entities.push_back(entity);
}

// Set player
void World::SetPlayer(Player* player) {
    this->player = player;
    // Player is also an entity, add to entities list
    AddEntity(player);
}

// Get player
Player* World::GetPlayer() const {
    return player;
}

// Initialize world
void World::Initialize() {
    std::cout << "Initializing game world...\n";
    
    // Create rooms
    Room* lab = new Room("Laboratory", "A dark abandoned laboratory with flickering lights.");
    Room* corridor = new Room("Corridor", "A long corridor with concrete walls.");
    Room* storage = new Room("Storage Room", "A small storage room filled with old equipment.");
    
    AddEntity(lab);
    AddEntity(corridor);
    AddEntity(storage);
    
    // Create exits
    Exit* labToNorth = new Exit(Direction::NORTH, lab, corridor);
    Exit* corridorToSouth = new Exit(Direction::SOUTH, corridor, lab);
    Exit* corridorToEast = new Exit(Direction::EAST, corridor, storage);
    Exit* storageToWest = new Exit(Direction::WEST, storage, corridor);
    
    lab->AddExit(labToNorth);
    corridor->AddExit(corridorToSouth);
    corridor->AddExit(corridorToEast);
    storage->AddExit(storageToWest);
    
    AddEntity(labToNorth);
    AddEntity(corridorToSouth);
    AddEntity(corridorToEast);
    AddEntity(storageToWest);
    
    // Create items
    Item* key = new Item("key", "A rusty old key", false, false);
    Item* flashlight = new Item("flashlight", "A heavy flashlight", true, false);
    Item* backpack = new Item("backpack", "A sturdy backpack", false, true, 5);
    Item* note = new Item("note", "A crumpled note with strange symbols", false, false);
    
    // Place items in rooms
    lab->AddEntity(key);
    lab->AddEntity(flashlight);
    corridor->AddEntity(backpack);
    storage->AddEntity(note);
    
    AddEntity(key);
    AddEntity(flashlight);
    AddEntity(backpack);
    AddEntity(note);
    
    // Create player
    Player* hero = new Player("Hero", "A brave adventurer", 100);
    hero->SetLocation(lab);
    SetPlayer(hero);
    
    std::cout << "World initialized!\n\n";
}

// Run game loop
void World::Run() {
    gameRunning = true;
    
    std::cout << "=================================\n";
    std::cout << "       ZORK GAME - UPC\n";
    std::cout << "=================================\n\n";
    std::cout << "Type 'help' for available commands.\n\n";
    
    // Show initial room
    LookAround();
    
    // Main game loop
    while (gameRunning) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        ParseCommand(input);
        
        // Update all entities
        Update();
    }
    
    std::cout << "\nThanks for playing!\n";
}

// Parse command
void World::ParseCommand(const std::string& input) {
    // Convert to lowercase for easier parsing
    std::string cmd = input;
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    std::istringstream iss(cmd);
    std::string command;
    iss >> command;
    
    // Movement commands
    if (command == "go" || command == "move") {
        std::string direction;
        iss >> direction;
        
        Direction dir;
        if (direction == "north" || direction == "n") dir = Direction::NORTH;
        else if (direction == "south" || direction == "s") dir = Direction::SOUTH;
        else if (direction == "east" || direction == "e") dir = Direction::EAST;
        else if (direction == "west" || direction == "w") dir = Direction::WEST;
        else if (direction == "up" || direction == "u") dir = Direction::UP;
        else if (direction == "down" || direction == "d") dir = Direction::DOWN;
        else {
            std::cout << "Invalid direction.\n";
            return;
        }
        
        if (player->Move(dir)) {
            LookAround();
        }
    }
    // Shorthand movement
    else if (command == "north" || command == "n") {
        if (player->Move(Direction::NORTH)) LookAround();
    }
    else if (command == "south" || command == "s") {
        if (player->Move(Direction::SOUTH)) LookAround();
    }
    else if (command == "east" || command == "e") {
        if (player->Move(Direction::EAST)) LookAround();
    }
    else if (command == "west" || command == "w") {
        if (player->Move(Direction::WEST)) LookAround();
    }
    // Look command
    else if (command == "look" || command == "l") {
        LookAround();
    }
    // Inventory
    else if (command == "inventory" || command == "inv" || command == "i") {
        player->ListInventory();
    }
    // Pick up
    else if (command == "take" || command == "get" || command == "pickup") {
        std::string itemName;
        std::getline(iss, itemName);
        // Remove leading spaces
        itemName.erase(0, itemName.find_first_not_of(" \t"));
        
        if (itemName.empty()) {
            std::cout << "Take what?\n";
        } else {
            player->PickUp(itemName);
        }
    }
    // Drop
    else if (command == "drop" || command == "leave") {
        std::string itemName;
        std::getline(iss, itemName);
        itemName.erase(0, itemName.find_first_not_of(" \t"));
        
        if (itemName.empty()) {
            std::cout << "Drop what?\n";
        } else {
            player->Drop(itemName);
        }
    }
    // Equip
    else if (command == "equip" || command == "wield") {
        std::string itemName;
        std::getline(iss, itemName);
        itemName.erase(0, itemName.find_first_not_of(" \t"));
        
        if (itemName.empty()) {
            std::cout << "Equip what?\n";
        } else {
            player->Equip(itemName);
        }
    }
    // Unequip
    else if (command == "unequip" || command == "unwield") {
        player->Unequip();
    }
    // Help
    else if (command == "help" || command == "h" || command == "?") {
        ShowHelp();
    }
    // Quit
    else if (command == "quit" || command == "exit" || command == "q") {
        gameRunning = false;
    }
    // Unknown command
    else {
        std::cout << "Unknown command. Type 'help' for available commands.\n";
    }
}

// Look around current room
void World::LookAround() {
    if (player->GetLocation() == nullptr) {
        std::cout << "You are nowhere!\n";
        return;
    }
    
    Room* room = player->GetLocation();
    
    std::cout << "\n=== " << room->GetName() << " ===\n";
    std::cout << room->GetDescription() << "\n";
    
    // List items in room
    const std::list<Entity*>& contents = room->GetContents();
    if (!contents.empty()) {
        std::cout << "\nYou see:\n";
        for (Entity* entity : contents) {
            if (entity->GetType() == EntityType::ITEM) {
                std::cout << "  - " << entity->GetName() << "\n";
            }
        }
    }
    
    // List exits
    std::cout << "\n";
    room->ListExits();
}

// Show help
void World::ShowHelp() {
    std::cout << "\n=== Available Commands ===\n";
    std::cout << "Movement:\n";
    std::cout << "  go <direction>, north/n, south/s, east/e, west/w\n";
    std::cout << "Actions:\n";
    std::cout << "  look/l - Look around\n";
    std::cout << "  take <item> - Pick up an item\n";
    std::cout << "  drop <item> - Drop an item\n";
    std::cout << "  inventory/i - Show inventory\n";
    std::cout << "  equip <item> - Equip an item\n";
    std::cout << "  unequip - Unequip current item\n";
    std::cout << "Other:\n";
    std::cout << "  help/h - Show this help\n";
    std::cout << "  quit/q - Quit game\n";
}

// Update all entities
void World::Update() {
    for (Entity* entity : entities) {
        entity->Update();
    }
}