#include "npc.h"
#include <iostream>

// Constructor
NPC::NPC(const std::string& name,
         const std::string& description,
         int hp,
         int attackDamage)
    : Creature(name, description, hp),
      attackDamage(attackDamage),
      defeated(false) {
}

// Destructor
NPC::~NPC() {
}

// Get attack damage
int NPC::GetAttackDamage() const {
    return attackDamage;
}

// Check if defeated
bool NPC::IsDefeated() const {
    return defeated;
}

// Set defeated
void NPC::SetDefeated(bool defeated) {
    this->defeated = defeated;
}