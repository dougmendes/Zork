#include "creature.h"
#include "room.h"
#include <iostream>

// Constructor
Creature::Creature(const std::string& name,
                   const std::string& description,
                    int hp)
    : Entity(name, description, EntityType::CREATURE), 
      hp(hp), 
      maxHp(hp), 
      location(nullptr) {

}

// Destructor
Creature::~Creature() {}

int Creature::GetHP() const {
    return hp;
}

int Creature::GetMaxHP() const {
    return maxHp;
}

Room* Creature::GetLocation() const {
    return location;
}

bool Creature::IsAlive() const {
    return hp > 0;
}

void Creature::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) {
        hp = 0;
    }

    if (!IsAlive()) {
        std::cout << GetName() << " has died.\n";
    }
}

void Creature::Heal(int amount) {
    hp += amount;
    if (hp > maxHp) {
        hp = maxHp;
    }
}

void Creature::SetLocation(Room* room) {
    location = room;
}

bool Creature::Move(Direction direction) {
    // Check if has a location
    if (location == nullptr) {
        std::cout << "Not in any room.\n";
        return false;
    }
    
    // Find exit in specified direction
    Exit* exit = location->GetExit(direction);
    if (exit == nullptr) {
        std::cout << "No exit in that direction.\n";
        return false;
    }
    
    // Check if exit is locked
    if (exit->IsLocked()) {
        std::cout << "The exit is locked.\n";
        return false;
    }
    
    // Move to destination room
    location = exit->GetDestination();
    std::cout << GetName() << " moved to " << location->GetName() << ".\n";
    return true;
}