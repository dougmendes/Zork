#ifndef PLAYER_H
#define PLAYER_H

#include "creature.h"
#include "item.h"
#include "world.h"
#include <vector>
#include <iostream>

/**
 * Player class - represents the player character
 * Inherits from Creature
 * 
 * Adds inventory management and item interactions:
 * - Carry items in inventory
 * - Pick up items from rooms
 * - Drop items into rooms
 * - Equip/unequip items
 */
class Player : public Creature {
private:
    std::vector<Item*> inventory;  // Items carried by player
    Item* equippedItem;            // Currently equipped item
    bool lightOn;                 // Control if the player has the light on at room 1D
    class World* world;           // Reference to the game world (for game over triggers)

public:
    /**
     * Constructor
     * @param name Player name
     * @param description Player description
     * @param hp Starting health points
     */
    Player(const std::string& name, 
           const std::string& description, 
           int hp);
    
    /**
     * Destructor
     */
    virtual ~Player();
    
    /**
     * Get player inventory
     * @return Const reference to inventory vector
     */
    const std::vector<Item*>& GetInventory() const;
    
    /**
     * Get equipped item
     * @return Pointer to equipped item or nullptr
     */
    Item* GetEquippedItem() const;
    
    /**
     * Pick up item from current room
     * @param itemName Name of item to pick up
     * @return true if successful, false otherwise
     */
    bool PickUp(const std::string& itemName);
    
    /**
     * Drop item from inventory into current room
     * @param itemName Name of item to drop
     * @return true if successful, false otherwise
     */
    bool Drop(const std::string& itemName);
    
    /**
     * Equip an item from inventory
     * @param itemName Name of item to equip
     * @return true if successful, false otherwise
     */
    bool Equip(const std::string& itemName);
    
    /**
     * Unequip currently equipped item
     * @return true if successful, false if nothing equipped
     */
    bool Unequip();
    
    /**
     * Find item in inventory by name
     * @param itemName Name to search for
     * @return Pointer to item if found, nullptr otherwise
     */
    Item* FindItemInInventory(const std::string& itemName) const;
    
    /**
     * List all items in inventory
     */
    void ListInventory() const;

    // Set light on for analysis lab
    void SetLightOn(bool on);

    // Check if lights are on
    bool AreLightsOn();

    /**
     * Override Move to add special room checks
     */
    bool Move(Direction direction) override;

    /**
     * Set world reference (needed for game over triggers)
     */
    void SetWorld(class World* world);

};

#endif // PLAYER_H