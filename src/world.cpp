#include "world.h"
#include "player.h" 
#include <iostream>
#include <sstream>
#include <algorithm>

// Constructor
World::World() 
    : player(nullptr), gameRunning(false), monster(nullptr)  {
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
    
    // Corridor -> Contaminated Lab  (Up)
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
    NPC* mutant = new NPC(
        "Mutant Creature",
        "A horrifying genetic experiment. Subject #4.",
        50,  // HP
        15   // Attack damage
    );

    mutant->SetLocation(containment);
    monster = mutant;
    AddEntity(mutant);
    
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
        
        // Auto-start combat if player enters room with living monster
        if (monster != nullptr && 
            monster->GetLocation() == player->GetLocation() && 
            monster->IsAlive() && 
            !monster->IsDefeated()) {
            
            StartCombat(monster);
            
            // After combat, show room again
            if (gameRunning && player->IsAlive()) {
                LookAround();
            }
        }   
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

         // ========================================
        // AUTO-UNLOCK: Containment Room Door
        // ========================================
        if (dir == Direction::DOWN && 
            player->GetLocation()->GetName() == "Main Corridor") {
            
            Exit* containmentDoor = player->GetLocation()->GetExit(Direction::DOWN);
            
            if (containmentDoor != nullptr && containmentDoor->IsLocked()) {
                // Check if has axe equipped
                Item* equipped = player->GetEquippedItem();
                
                if (equipped != nullptr && equipped->GetName() == "axe") {
                    // Force door open automatically!
                    std::cout << "\n*** The door is jammed! ***\n";
                    std::cout << "You jam your axe into the door frame...\n";
                    std::cout << "*** CRACK! ***\n";
                    std::cout << "The door breaks open!\n\n";
                    
                    containmentDoor->SetLocked(false);
                } else {
                    std::cout << "\nThe door is jammed tight.\n";
                    std::cout << "You need something to force it open.\n";
                    return;
                }
            }
        }
        
        if (player->Move(dir)) {
            LookAround();
        }
        return;
    }
    // Shorthand movement
    else if (command == "north" || command == "n") {
        if (player->Move(Direction::NORTH)) LookAround();
        return;
    }
    else if (command == "south" || command == "s") {
        if (player->Move(Direction::SOUTH)) LookAround();
        return;
    }
    else if (command == "east" || command == "e") {
        if (player->Move(Direction::EAST)) LookAround();
        return;
    }
    else if (command == "west" || command == "w") {
        if (player->Move(Direction::WEST)) LookAround();
        return;
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
        // Check if trying to take item in dark Analysis Lab - instant death
        if (player->GetLocation()->GetName() == "Analysis Lab" && !player->AreLightsOn()) {
            std::cout << "\n*** CRUNCH! ***\n";
            std::cout << "You reach out in the darkness and step forward...\n";
            std::cout << "Your foot lands on broken glass tubes!\n";
            std::cout << "Toxic chemicals burn through your skin!\n";
            GameOver("You were killed by toxic chemicals in the dark.");
            return;
        }
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
    // Quit/Exit
    else if (command == "exit") {
    // Check if trying to exit with password
    std::string password;
    iss >> password;
    
    // If no password provided, just quit
    if (password.empty()) {
        gameRunning = false;
        return;
    }
    
    // Trying to use exit door with password
    if (player->GetLocation()->GetName() != "Main Corridor") {
        std::cout << "You need to be at the exit door to use the password.\n";
        return;
    }
    
    std::cout << "\nYou approach the EXIT door.\n";
    std::cout << "A digital panel glows: [____]\n";
    std::cout << "You enter: " << password << "\n\n";
    
    // Check password
    if (password == "0412") {
        // VICTORY!
        std::cout << "===========================================\n";
        std::cout << "           *** SUCCESS! ***\n";
        std::cout << "===========================================\n\n";
        std::cout << "The panel beeps and turns GREEN!\n";
        std::cout << "The heavy door slides open with a hiss.\n\n";
        std::cout << "Sunlight floods in. You're FREE!\n\n";
        std::cout << "You stumble out of the laboratory into the fresh air.\n";
        std::cout << "Behind you, alarms start blaring.\n";
        std::cout << "You run and don't look back.\n\n";
        std::cout << "===========================================\n";
        std::cout << "        YOU ESCAPED THE LABORATORY!\n";
        std::cout << "===========================================\n\n";
        
        gameRunning = false;
    } else {
        // Wrong password
        std::cout << "*** BEEP BEEP BEEP ***\n";
        std::cout << "The panel flashes RED!\n";
        std::cout << "INCORRECT PASSWORD.\n\n";
        
        if (!player->HasAllPasswordDigits()) {
            std::cout << "Hint: You need to find all 4 digits first.\n";
            std::cout << "Explore the rooms and READ the items carefully.\n";
        }
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
                std::cout << "\nYou fumble for the light switch in the darkness...\n";
                std::cout << "Click!\n";
                std::cout << "The lights flicker on, revealing broken glass tubes scattered across the floor!\n";
                std::cout << "You were about to step on them! That was close!\n\n";
            } 
        }
    }
    // Help
    else if (command == "help" || command == "h" || command == "?") {
        ShowHelp();
    }
    // Quit game
    else if (command == "quit" || command == "q") {
        gameRunning = false;
    }
    // Combine items
    else if (command == "combine") {
        // Check if player has gauze, alcohol, and tape
        Item* gauze = player->FindItemInInventory("gauze");
        Item* alcohol = player->FindItemInInventory("alcohol");
        Item* tape = player->FindItemInInventory("tape");

        if (gauze == nullptr || alcohol == nullptr || tape == nullptr) {
            std::cout << "You need gauze, alcohol, and tape to make a medical kit.\n";
            return;
        }

        // Check if already has medkit
        if (player->FindItemInInventory("medkit") != nullptr) {
            std::cout << "You already have a medical kit.\n";
            return;
        }

        std::cout << "\nYou carefully combine the medical supplies...\n";
        std::cout << "Gauze + Alcohol + Tape = Medical Kit!\n";
        std::cout << "A makeshift medical kit that can heal 20 HP.\n\n";

        // Create medkit
        Item* medkit = new Item("medkit", "A makeshift medical kit. Can restore 20 HP.", false, false);
        AddEntity(medkit);
        auto& inv = const_cast<std::vector<Item*>&>(player->GetInventory());
        inv.push_back(medkit);

        std::cout << "Medical kit added to inventory.\n";
    }
    // Read command (to discover password digits)
    else if (command == "read" || command == "examine" || command == "inspect") {
    std::string itemName;
    std::getline(iss, itemName);
    itemName.erase(0, itemName.find_first_not_of(" \t"));
    
    if (itemName.empty()) {
        std::cout << "Read what?\n";
        return;
    }
    
    // Check if item is in inventory
    Item* item = player->FindItemInInventory(itemName);
    
    // If not in inventory, check current room
    if (item == nullptr) {
        Entity* entity = player->GetLocation()->FindEntity(itemName);
        if (entity != nullptr && entity->GetType() == EntityType::ITEM) {
            item = static_cast<Item*>(entity);
        }
    }
    
    if (item == nullptr) {
        std::cout << "You don't see any " << itemName << " here.\n";
        return;
    }
    
    // Show item description
    std::cout << item->GetDescription() << "\n";
    
    // Check for password digits
    std::string name = item->GetName();
    if (name == "card") {
        player->AddPasswordDigit(0);
    } else if (name == "computer") {
        player->AddPasswordDigit(4);
    } else if (name == "axe") {
        player->AddPasswordDigit(1);
    } else if (name == "photo") {
        player->AddPasswordDigit(1);
        player->AddPasswordDigit(2);
    }
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
    std::cout << "  read <item> - Read/examine an item\n";         
    std::cout << "  inventory/i - Show inventory\n";
    std::cout << "  equip <item> - Equip an item\n";
    std::cout << "  unequip - Unequip current item\n";
    std::cout << "  light - Turn on lights (if available)\n";
    std::cout << "Other:\n";
    std::cout << "  help/h - Show this help\n";
    std::cout << "  exit <password> - Try to exit (needs 4-digit code)\n"; 
    std::cout << "  quit/q - Quit game\n";
}
// Update all entities
void World::Update() {
    for (Entity* entity : entities) {
        entity->Update();
    }
}

void World::StartCombat(NPC* npc) {
    std::cout << "\n===========================================\n";
    std::cout << "           *** COMBAT START ***\n";
    std::cout << "===========================================\n\n";
    std::cout << "You enter the room and find: " << npc->GetName() << "!\n";
    std::cout << npc->GetDescription() << "\n";
    std::cout << "The creature spots you and ATTACKS!\n\n";
    
    // Combat loop - fully automatic
    int turn = 1;
    bool usedMedkit = false;
    
    while (player->IsAlive() && npc->IsAlive()) {
        std::cout << "--- Turn " << turn << " ---\n";
        std::cout << "Your HP: " << player->GetHP() << "/" << player->GetMaxHP() << "\n";
        std::cout << npc->GetName() << " HP: " << npc->GetHP() << "/" << npc->GetMaxHP() << "\n\n";
        
        // Player attacks first
        std::cout << "You swing your weapon!\n";
        int playerDamage = 20;
        
        // Check if has axe equipped (more damage)
        if (player->GetEquippedItem() != nullptr && 
            player->GetEquippedItem()->GetName() == "axe") {
            playerDamage = 30;
            std::cout << "The axe cuts deep!\n";
        }
        
        npc->TakeDamage(playerDamage);
        std::cout << "You deal " << playerDamage << " damage!\n";
        
        // Check if monster died
        if (!npc->IsAlive()) {
            std::cout << "\n*** VICTORY! ***\n";
            std::cout << npc->GetName() << " collapses to the ground!\n";
            npc->SetDefeated(true);
            std::cout << "\nThe room is now safe to explore.\n\n";
            return;
        }
        
        std::cout << "\n";
        
        // Monster attacks back
        std::cout << npc->GetName() << " lunges at you!\n";
        int monsterDamage = npc->GetAttackDamage();
        player->TakeDamage(monsterDamage);
        std::cout << "You take " << monsterDamage << " damage!\n";
        
        // Check if player died
        if (!player->IsAlive()) {
            std::cout << "\n*** DEFEAT! ***\n";
            GameOver("You were killed by " + npc->GetName() + ".");
            return;
        }
        
        std::cout << "\n";
        
        // Auto-use medkit if HP is low and has medkit
        if (player->GetHP() <= 50 && 
            !usedMedkit && 
            player->FindItemInInventory("medkit") != nullptr) {
            
            std::cout << "*** CRITICAL CONDITION! ***\n";
            std::cout << "You stumble backwards and duck behind a table!\n";
            std::cout << "You quickly open your medical kit...\n\n";
            
            player->Heal(20);
            std::cout << "Healed 20 HP! Current HP: " << player->GetHP() << "/" << player->GetMaxHP() << "\n";
            
            // Remove medkit from inventory
            auto& inv = const_cast<std::vector<Item*>&>(player->GetInventory());
            Item* medkit = player->FindItemInInventory("medkit");
            auto it = std::find(inv.begin(), inv.end(), medkit);
            if (it != inv.end()) {
                inv.erase(it);
            }
            
            usedMedkit = true;
            std::cout << "\nYou stand up, ready to continue fighting!\n\n";
        }
        
        turn++;
        
        // Small pause for readability
        std::cout << "Press Enter to continue...";
        std::cin.get();
        std::cout << "\n";
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
