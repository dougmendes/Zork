#ifndef NPC_H
#define NPC_H

#include "creature.h"

/**
 * NPC class - represents non-player characters (enemies)
 * Inherits from Creature
 */
class NPC : public Creature {
private:
    int attackDamage;  // Damage dealt per attack
    bool defeated;     // Has this NPC been defeated?

public:
    /**
     * Constructor
     * @param name NPC name
     * @param description NPC description
     * @param hp Health points
     * @param attackDamage Damage per attack
     */
    NPC(const std::string& name,
        const std::string& description,
        int hp,
        int attackDamage);
    
    /**
     * Destructor
     */
    virtual ~NPC();
    
    /**
     * Get attack damage
     */
    int GetAttackDamage() const;
    
    /**
     * Check if defeated
     */
    bool IsDefeated() const;
    
    /**
     * Mark as defeated
     */
    void SetDefeated(bool defeated);
};

#endif // NPC_H