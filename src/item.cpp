#include "item.h"
#include <iostream>
#include <algorithm>

// Constructor
Item::Item(const std::string& name, 
           const std::string& description,
           bool equippable,
           bool isContainer,
           int maxCapacity)
    : Entity(name, description, EntityType::ITEM),
      equippable(equippable),
      equipped(false), 
      isContainer(isContainer),
      maxCapacity(maxCapacity) {
}

// Destructor
Item::~Item() {
    contents.clear();
}

// Getters
bool Item::IsEquippable() const {
    return equippable;
}

bool Item::IsEquipped() const {
    return equipped;
}

bool Item::IsContainer() const {
    return isContainer;
}

int Item::GetMaxCapacity() const {
    return maxCapacity;
}

// Setter
void Item::SetEquipped(bool equipped) {
    if (equippable){
        this->equipped = equipped;
    }
}

// Put item inside container
bool Item::PutItem(Item* item) {
    if (!isContainer) {
        return false; // Not a container
    }
    if (IsFull()) {
        return false; // Container is full
    }
    contents.push_back(item);
    return true;
}

// Take item from container
Item* Item::TakeItem(const std::string& itemName) {
    if (!isContainer) {
        return nullptr; // Not a container
    }
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        Entity* entity = *it;
        if (entity->GetName() == itemName && entity->GetType() == EntityType::ITEM) {
            Item* item = static_cast<Item*>(entity);
            contents.erase(it);  // Remove from list
            return item;
        }
    }
    return nullptr; // Not found
}

// Find item in container
Item* Item::FindItem(const std::string& itemName) const {
    if (!isContainer) {
        return nullptr; // Not a container
    }
    for (Entity* entity : contents) {
        if (entity->GetName() == itemName && entity->GetType() == EntityType::ITEM) {
            return static_cast<Item*>(entity);
        }
    }
    return nullptr; // Not found
}

// List contents
void Item::ListContents() const {
    if (!isContainer) {
        std::cout << this->GetName() << " is not a container.\n";
        return;
    }
    if (contents.empty()) {
        std::cout << this->GetName() << " is empty.\n";
        return;
    }
    std::cout << "Contents of " << this->GetName() << ":\n";
    for (Entity* entity : contents) {
        std::cout << "  - " << entity->GetName() << "\n";
    }    
}

// Check if full
bool Item::IsFull() const {
    if (!isContainer) {
        return true; // Not a container is considered "full"
    }
    if (maxCapacity == -1) {
        return false; // Unlimited capacity
    }
    return contents.size() >= static_cast<size_t>(maxCapacity);
}