// Header guard: prevents multiple inclusion of this file during compilation
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <list>

// Enum for entity types
enum class EntityType {
    ENTITY,
    ROOM,
    EXIT,
    ITEM,
    CREATURE,
    PLAYER,
    NPC
};

class Entity {
// Only subclasses can access these members
protected:
    EntityType type;
    std::string name;
    std::string description;
    std::list<Entity*> contents; // List of contained entities(room's itens, itens in itens, etc.)

public:
    /**
     * Constructor - initializes entity with given parameters
     * @param name Entity name
     * @param description Entity description  
     * @param type Type of entity
     */
    Entity(const std::string& name, const std::string& description, EntityType type);
    /**
     * Virtual destructor - required for proper polymorphic deletion
     * Ensures correct destructor is called when deleting derived objects
     * through base class pointer
     */
    virtual ~Entity();
    /**
     * Get entity name
     * @return Const reference to name
     */
    const std::string& GetName() const;
    /**
     * Get entity description
     * @return Const reference to description
     */
    const std::string& GetDescription() const;
    /**
     * Get entity type
     * @return EntityType enum value 
     */
    EntityType GetType() const;
    /**
     * Get list of contained entities
     * @return Const reference to contents list
     */
    const std::list<Entity*>& GetContents() const;

    /**
     * Virtual update method - called each game loop
     * Override in derived classes to implement entity-specific behavior
     */
    virtual void Update();

};

#endif