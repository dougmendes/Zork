#include "world.h"
#include "player.h" 
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
    player->SetWorld(this);
    // Player is also an entity, add to entities list
    AddEntity(player);
}

// Get player
Player* World::GetPlayer() const {
    return player;
}

// Initialize world
void World::Initialize() {
    //---------------------------------
    // ROOMS
    //---------------------------------

    //Starting room - where the player wakes up
    Room* labStart = new Room(
        "Starting room",
        "You wake up on a gurney in a dimly lit room. The lights flicker.\n"
        "Your wrists, ankles and neck were tied down, but your right hand is loose.\n"
        "Medical instruments lie on a small table to your left."
    );
    
    // Main corridor
    Room* corridor = new Room(
        "Main Corridor",
        "A long corridor with 5 doors. Two on the left, two on the right,\n"
        "and one at the end marked 'EXIT' with a digital panel.\n"
        "You hear distant footsteps coming from one of the rooms on the right."
    );

    // Room 1L - Locker Room
    Room* locker = new Room(
        "Locker Room",
        "A locker room where scientists change clothes.\n"
        "You see lockers with lab coats and protective equipment."
    );

    // Room 2L - Contamined Room
    Room* contaminated = new Room(
        "Contaminated Lab",
        "Through the window you see scientists collapsed near the door,\n"
        "wearing protective suits. The air looks thick and toxic.\n"
        "WARNING: DO NOT ENTER WITHOUT PROTECTION!"
    );
    
    //Room 1D - Analysis Lab
    Room* analysis = new Room(
        "Analysis Lab",
        "The door is ajar, lights flickering. You can't see clearly inside.\n"
        "Broken glass tubes litter the floor."
    );

    // Room 2D - Containment Room
    Room* containment = new Room(
        "Containment Room",
        "The door is jammed, only opening 5cm.\n"
        "You need something to force it open."
    );

    AddEntity(labStart);
    AddEntity(corridor);
    AddEntity(locker);
    AddEntity(contaminated);
    AddEntity(analysis);
    AddEntity(containment);
    
    //---------------------------------
    // EXITS
    //---------------------------------

    // Lab Start -> Corridor (North)
    Exit* startToNorth = new Exit(Direction::NORTH, labStart, corridor);
    Exit* corridorToSouth = new Exit(Direction::SOUTH, corridor, labStart);

    labStart->AddExit(startToNorth);
    corridor->AddExit(corridorToSouth);

    AddEntity(startToNorth);
    AddEntity(corridorToSouth);

    // Corridor -> Locker Room (West)
    Exit* corridorToWest1 = new Exit(Direction::WEST, corridor, locker);
    Exit* lockerToEast = new Exit(Direction::EAST, locker, corridor);
    
    corridor->AddExit(corridorToWest1);
    locker->AddExit(lockerToEast);
        
    AddEntity(corridorToWest1);
    AddEntity(lockerToEast);
    
    // Corridor -> Contaminated Lab 
    Exit* corridorToUp = new Exit(Direction::UP, corridor, contaminated);
    Exit* contaminatedToDown = new Exit(Direction::DOWN, contaminated, corridor);
    
    corridor->AddExit(corridorToUp);
    contaminated->AddExit(contaminatedToDown);
    
    AddEntity(corridorToUp);
    AddEntity(contaminatedToDown);

    // Corridor -> Analysis Lab (EAST)
    Exit* corridorToEast1 = new Exit(Direction::EAST, corridor, analysis);
    Exit* analysisToWest = new Exit(Direction::WEST, analysis, corridor);
    
    corridor->AddExit(corridorToEast1);
    analysis->AddExit(analysisToWest);
    
    AddEntity(corridorToEast1);
    AddEntity(analysisToWest);

    // Analysis Lab -> Containment Room (West)
    // This door is locked initially
    Exit* corridorToContainment = new Exit(Direction::DOWN, corridor, containment);
    Exit* containmentToCorridor = new Exit(Direction::UP, containment, corridor);
    
    // Lock the door - need the axe to open
    corridorToContainment->SetLocked(true);
    
    corridor->AddExit(corridorToContainment);
    containment->AddExit(containmentToCorridor);
    
    AddEntity(corridorToContainment);
    AddEntity(containmentToCorridor);
    
    // ==========================================
    // ITEMS - Starting Room
    // ==========================================
    
    Item* scalpel = new Item("scalpel", "A sharp surgical scalpel", false, false);
    Item* gauze = new Item("gauze", "Medical gauze", false, false);
    Item* alcohol = new Item("alcohol", "Disinfecting alcohol", false, false);
    Item* tape = new Item("tape", "Medical tape", false, false);
    Item* painkillers = new Item("painkillers", "Pain relief pills", false, false);
    
    labStart->AddEntity(scalpel);
    labStart->AddEntity(gauze);
    labStart->AddEntity(alcohol);
    labStart->AddEntity(tape);
    labStart->AddEntity(painkillers);
    
    AddEntity(scalpel);
    AddEntity(gauze);
    AddEntity(alcohol);
    AddEntity(tape);
    AddEntity(painkillers);
    
    // ==========================================
    // ITEMS - Locker Room (1L)
    // ==========================================
    
    Item* hazmatSuit = new Item(
        "hazmat", 
        "A yellow hazmat suit with a gas mask. Protects against toxic environments.",
        true,   // equippable
        false   // not a container
    );
    
    Item* accessCard = new Item(
        "card",
        "An access card. On the back it says: 'Digit 1: 0'",
        false,
        false
    );
    
    locker->AddEntity(hazmatSuit);
    locker->AddEntity(accessCard);
    
    AddEntity(hazmatSuit);
    AddEntity(accessCard);
    
    // ==========================================
    // ITEMS - Contaminated Lab (2L)
    // ==========================================
    
    Item* computer = new Item(
        "computer",
        "A computer with a report: 'SUBJECT #4: Genetic hybrid. CONTAINMENT BREACHED.'\n"
        "A sticky note on the keyboard says: 'Digit 2: 4'",
        false,
        false
    );
    
    contaminated->AddEntity(computer);
    AddEntity(computer);
    
    // ==========================================
    // ITEMS - Analysis Lab (1D)
    // ==========================================
    
    Item* axe = new Item(
        "axe",
        "A fire axe covered in blood. Near it, the number '1' is written in blood on the wall.",
        true,   // equippable
        false
    );
    
    analysis->AddEntity(axe);
    AddEntity(axe);
    
    // ==========================================
    // ITEMS - Containment Room (2D)
    // ==========================================
    
    Item* photo = new Item(
        "photo",
        "A photo of scientists in front of 'LABORATORY 2'.\n"
        "A document on the table says: 'Digit 3: 1'\n"
        "The number '2' is scratched deeply into the wall. (Digit 4: 2)",
        false,
        false
    );
    
    containment->AddEntity(photo);
    AddEntity(photo);
    
    // ==========================================
    // PLAYER
    // ==========================================
    
    Player* hero = new Player("You", "A test subject trying to escape", 100);
    hero->SetLocation(labStart);
    SetPlayer(hero);
    
    std::cout << "World initialized!\n\n";
    std::cout << "===========================================\n";
    std::cout << "  LABORATORY ESCAPE - ZORK GAME\n";
    std::cout << "===========================================\n\n";
    std::cout << "You wake up strapped to a gurney...\n";
    std::cout << "Something terrible has happened here.\n";
    std::cout << "You need to find a way out.\n\n";
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
    else if (command == "light" || command == "lights" || command == "switch") {
        if (player->GetLocation()->GetName() == "Analysis Lab") {
            if (!player->AreLightsOn()) {
                player->SetLightOn(true);
                std::cout << "You flip the light switch.\n";
                std::cout << "The lights flicker on, revealing broken glass tubes all over the floor.\n";
                std::cout << "Good thing you didn't step in there!\n";
            } else {
                std::cout << "The lights are already on.\n";
            }
        } else {
            std::cout << "There's no light switch here.\n";
        }
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
    std::cout << "  go <direction>, north/n, south/s, east/e, west/w, up/u, down/d\n";
    std::cout << "Actions:\n";
    std::cout << "  look/l - Look around\n";
    std::cout << "  take <item> - Pick up an item\n";
    std::cout << "  drop <item> - Drop an item\n";
    std::cout << "  inventory/i - Show inventory\n";
    std::cout << "  equip <item> - Equip an item\n";
    std::cout << "  unequip - Unequip current item\n";
    std::cout << "  light - Turn on lights (if available)\n";  // ← ADICIONAR
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

void World::GameOver(const std::string& reason) {
    std::cout << "\n===========================================\n";
    std::cout << "           GAME OVER\n";
    std::cout << "===========================================\n\n";
    std::cout << reason << "\n\n";
    std::cout << "You have died.\n\n";
    
    gameRunning = false;
}