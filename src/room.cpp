#include "room.h"
#include <iostream>

//constructor
Room::Room(const std::string& name, const std::string& description)
    : Entity(name, description, EntityType::ROOM) {}

//Destructor
Room::~Room() {
    exits.clear();
}

//Add exit
void Room::AddExit(Exit* exit) {
    exits.push_back(exit);
}

//Get exit in specific direction
Exit* Room::GetExit(Direction direction) const {
    for (Exit* exit : exits){
        if (exit->GetDirection() == direction){
            return exit;
        };
    }
    return nullptr;
}

//List all available exits
void Room::ListExits() const {
    if (exits.empty()) {
        std::cout << "No exits available.\n";
        return;
    }
    
    std::cout << "Available exits from " << GetName() << ":\n";
    for (const Exit* exit : exits) {
        std::cout << "  - " << Exit::DirectionToString(exit->GetDirection())
                  << ": leads to " << exit->GetDestination()->GetName() << "\n";
    }
}

//Get all exits
const std::vector<Exit*>& Room::GetExits() const {
    return exits;
}