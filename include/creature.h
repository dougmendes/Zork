#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h" 
#include "exit.h"

class Room; // Forward declaration

/** 
 * Creature class
 * Inherits from Entity.
 * Represents any living entity that can:
 * - Have health points (HP)
 * - Be located in a room
 * - Move between rooms
 * - Take damage and heal
 */
class Creature : public Entity {
protected:
    int hp; // Current health points
    int maxHp; // Maximum health points
    Room* location; // Pointer to the room where the creature is located
public:
    /** Constructor
     * @param name Name of the creature
     * @param description Description of the creature
     * @param hp Initial and maximum health points
     */
    Creature(const std::string& name,
             const std::string& description,
             int hp);
    /** 
     * Destructor
     */
    virtual ~Creature();

    // Getters
    int GetHP() const;
    int GetMaxHP() const;
    Room* GetLocation() const;

    /**
     * Check if creature is alive
     * @return true if hp > 0, false otherwise
     */
    bool IsAlive() const;

    /**
     * Take damage
     * @param damage Amount of damage to take
     */
    void TakeDamage(int damage);

    /** Heal the creature
     * @param amount Amount of HP to heal
     */
    void Heal(int amount);

    /**
     * Set creature location
     * @param room Room to set as location
     */
    void SetLocation(Room* room);
    /**
     * Set creature location
     * @param direction Direction to move
     * @return true if move successful, false otherwise
     */
    bool Move(Direction direction);
};

#endif // CREATURE_H