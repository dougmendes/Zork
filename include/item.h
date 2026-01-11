#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

/** 
 * Item class - represents a collectable/usable item.
 * Inherits from Entity.
 * Itens can be:
 * - Equippable (weapons, armor, tools )
 * - Used (consumables)
 * - Containers (can hold other items)
 */
class Item : public Entity {
private:
    bool equippable; // Can this item be equipped?
    bool equipped; // Is this item currently equipped?
    bool isContainer; // Can this item contain other items?
    int maxCapacity; // Maximum number of items if container

public:
    /**
     * Constructor
     * @param name Name of the item
     * @param description Description of the item
     * @param equippable Is the item equippable?
     * @param isContainer Is the item a container?
     * @param maxCapacity Maximum capacity if container (-1 for unlimited)
     */
    Item(const std::string& name,
         const std::string& description,
         bool equippable = false,
         bool isContainer = false,
         int maxCapacity = -1);
    /**
     * Destructor
     */
    virtual ~Item();

    // Getters
    bool IsEquippable() const;
    bool IsEquipped() const;
    bool IsContainer() const;
    int GetMaxCapacity() const;

    // Setters
    void SetEquipped(bool equipped);

    /**
     * Put a item inside this container
     * @param item Item to put inside
     * @return true if successful, false if failed (not a container or full)
     */
    bool PutItem(Item* item);

    /**
     * Take an item from this container
     * @param itemName Name of the item to take
     * @return Pointer to item if found, nullptr otherwise
     */
    Item* TakeItem(const std::string& itemName);

    /**
     * Find an item inside this container by name
     * @param itemName Name of the item to find
     * @return Pointer to item if found, nullptr otherwise
     */
    Item* FindItem(const std::string& itemName) const;

    /**
     * List all items inside this container
     */
    void ListContents() const;

    /**
     * Check if container is full
     * @return true if full or not a container, false if has space
     */

    bool IsFull() const;
};

#endif /* ITEM_H */