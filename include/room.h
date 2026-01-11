#ifndef ROOM_H
#define ROOM_H

#include "entity.h"
#include "exit.h"
#include <vector>

/**
 * @class Room
 * @brief Represents a room in the game world.
 */

class Room : public Entity {
private:
    std::vector<Exit*> exits; // Exits leading out of the room
public:
    /**
     * constructor 
     * @param name The name of the room.
     * @param description The description of the room.
     */
    Room(const std::string& name, const std::string& description);

    /**
     * Destructor
     */
    virtual ~Room();

    /**
     * Adds an exit to the room.
     * @param exit The exit to add.
     */
    void AddExit(Exit* exit);

    /**
     * Gets the exits in a specific direction.
     * @param direction The direction to look for exits.
     * @return Exit pointer or null if no exit exists in that direction.
     */

     Exit* GetExit(Direction direction) const;

     /**
      * List all available exits
      */
     void ListExits() const;

     /**
      * Get all exits
      */
     const std::vector<Exit*>& GetExits() const;
};

#endif // ROOM_H