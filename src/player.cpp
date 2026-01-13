#include "player.h"
#include "room.h"
#include <iostream>
#include <algorithm>

// Constructor
Player::Player(const std::string& name, 
               const std::string& description, 
               int hp)
    : Creature(name, description, hp),
      equippedItem(nullptr),
      lightOn(false),
      world(nullptr){
}

// Destructor
Player::~Player() {
    // Only clear inventory, don't delete items (World manages them)
    inventory.clear();
}

// Getters
const std::vector<Item*>& Player::GetInventory() const {
    return inventory;
}

Item* Player::GetEquippedItem() const {
    return equippedItem;
}

// Pick up item from room
bool Player::PickUp(const std::string& itemName) {
    // Check if in a room
    if (location == nullptr) {
        std::cout << "You are not in any room.\n";
        return false;
    }
    
    // Find item in room
    Entity* entity = location->FindEntity(itemName);
    if (entity == nullptr || entity->GetType() != EntityType::ITEM) {
        std::cout << itemName << " not found here.\n";
        return false;
    }
    
    // Cast to Item
    Item* item = static_cast<Item*>(entity);
    
    // Remove from room and add to inventory
    location->RemoveEntity(item);
    inventory.push_back(item);
    
    std::cout << "Picked up " << itemName << ".\n";
    return true;
}

// Drop item into room
bool Player::Drop(const std::string& itemName) {
    // Check if in a room
    if (location == nullptr) {
        std::cout << "You are not in any room.\n";
        return false;
    }
    
    // Find item in inventory
    Item* item = FindItemInInventory(itemName);
    if (item == nullptr) {
        std::cout << "You don't have " << itemName << ".\n";
        return false;
    }
    
    // If item is equipped, unequip it first
    if (item == equippedItem) {
        equippedItem->SetEquipped(false);
        equippedItem = nullptr;
    }
    
    // Remove from inventory
    auto it = std::find(inventory.begin(), inventory.end(), item);
    inventory.erase(it);
    
    // Add to room
    location->AddEntity(item);
    
    std::cout << "Dropped " << itemName << ".\n";
    return true;
}

// Equip item
bool Player::Equip(const std::string& itemName) {
    // Find item in inventory
    Item* item = FindItemInInventory(itemName);
    if (item == nullptr) {
        std::cout << "You don't have " << itemName << ".\n";
        return false;
    }
    
    // Check if equippable
    if (!item->IsEquippable()) {
        std::cout << itemName << " cannot be equipped.\n";
        return false;
    }
    
    // Unequip current item if any
    if (equippedItem != nullptr) {
        equippedItem->SetEquipped(false);
        std::cout << "Unequipped " << equippedItem->GetName() << ".\n";
    }
    
    // Equip new item
    equippedItem = item;
    item->SetEquipped(true);
    
    std::cout << "Equipped " << itemName << ".\n";
    return true;
}

// Unequip item
bool Player::Unequip() {
    if (equippedItem == nullptr) {
        std::cout << "Nothing equipped.\n";
        return false;
    }
    
    equippedItem->SetEquipped(false);
    std::cout << "Unequipped " << equippedItem->GetName() << ".\n";
    equippedItem = nullptr;
    
    return true;
}

// Find item in inventory
Item* Player::FindItemInInventory(const std::string& itemName) const {
    for (Item* item : inventory) {
        if (item->GetName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

// List inventory
void Player::ListInventory() const {
    if (inventory.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }
    
    std::cout << "Inventory:\n";
    for (const Item* item : inventory) {
        std::cout << "  - " << item->GetName();
        if (item->IsEquipped()) {
            std::cout << " [EQUIPPED]";
        }
        std::cout << "\n";
    }
}

void Player::SetLightOn(bool on) {
    lightOn = on;
}

bool Player::AreLightsOn() {
    return lightOn;
}

void Player::SetWorld(World* world) {
    this->world = world;
}

bool Player::Move(Direction direction) {
    // Call base class move
    if (!Creature::Move(direction)) {
        return false;
    }
    
    // Check special room triggers after moving
    if (location == nullptr) {
        return true;
    }
    
    std::string roomName = location->GetName();
    
    // ==========================================
    // TRIGGER: Contaminated Lab (Sala 2L)
    // ==========================================
    if (roomName == "Contaminated Lab") {
        // Check if wearing hazmat suit
        bool hasHazmat = false;
        
        if (equippedItem != nullptr && equippedItem->GetName() == "hazmat") {
            hasHazmat = true;
        }
        
        if (!hasHazmat) {
            std::cout << "\n*** You step into the toxic air! ***\n";
            std::cout << "The air burns your lungs!\n";
            std::cout << "You needed protective equipment!\n";
            
            if (world != nullptr) {
                world->GameOver("You were poisoned by toxic gas.");
            }
            return false;
        } else {
            std::cout << "\nThe hazmat suit protects you from the toxic air.\n";
        }
    }
    
    // ==========================================
    // TRIGGER: Analysis Lab (Sala 1D)
    // ==========================================
    if (roomName == "Analysis Lab") {
        if (!lightOn) {
            // Warning but don't kill immediately - give chance to turn on lights
            std::cout << "\n*** WARNING! ***\n";
            std::cout << "It's pitch black! You can't see anything!\n";
            std::cout << "You hear glass crunching under your feet...\n";
            std::cout << "You need to turn on the lights immediately!\n";
            std::cout << "Type 'light' before doing anything else!\n\n";
        } else {
            std::cout << "\nWith the lights on, you carefully avoid the broken glass.\n";
        }
    }
    
    return true;
}

void Player::AddPasswordDigit(int digit) {
    // no duplicates
    for (int d : passwordDigits) {
        if (d == digit) {
            return;
        }
    }
    passwordDigits.push_back(digit);
    std::cout << "You memorize the digit: " << digit << "\n";
}

const std::vector<int>& Player::GetPasswordDigits() const {
    return passwordDigits;
}

bool Player::HasAllPasswordDigits() const {
    return passwordDigits.size() >= 4;
}
