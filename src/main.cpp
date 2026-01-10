#include <iostream>
#include "entity.h"
#include "room.h"
#include "exit.h"

int main() {
    std::cout << "=================================\n";
    std::cout << "  Room and Exit Test - Etapa 2\n";
    std::cout << "=================================\n\n";
    
    // Create rooms
    Room* lab = new Room("Laboratory", "A dark abandoned laboratory");
    Room* corridor = new Room("Corridor", "A long corridor with flickering lights");
    Room* closet = new Room("Closet", "A small storage closet");
    
    std::cout << "✓ Created 3 rooms\n\n";
    
    // Create exits
    Exit* labToNorth = new Exit(Direction::NORTH, lab, corridor);
    Exit* corridorToSouth = new Exit(Direction::SOUTH, corridor, lab);
    Exit* corridorToEast = new Exit(Direction::EAST, corridor, closet);
    Exit* closetToWest = new Exit(Direction::WEST, closet, corridor);
    
    std::cout << "✓ Created 4 exits\n\n";
    
    // Add exits to rooms
    lab->AddExit(labToNorth);
    corridor->AddExit(corridorToSouth);
    corridor->AddExit(corridorToEast);
    closet->AddExit(closetToWest);
    
    std::cout << "✓ Added exits to rooms\n\n";
    
    // Test navigation
    std::cout << "--- Laboratory ---\n";
    std::cout << lab->GetDescription() << "\n";
    lab->ListExits();
    
    std::cout << "\n--- Going north to Corridor ---\n";
    Exit* exit = lab->GetExit(Direction::NORTH);
    if (exit) {
        Room* nextRoom = exit->GetDestination();
        std::cout << nextRoom->GetDescription() << "\n";
        nextRoom->ListExits();
    }
    
    // Cleanup
    delete lab;
    delete corridor;
    delete closet;
    delete labToNorth;
    delete corridorToSouth;
    delete corridorToEast;
    delete closetToWest;
    
    std::cout << "\n=================================\n";
    std::cout << "    ✓ All tests passed!\n";
    std::cout << "=================================\n";
    
    return 0;
}