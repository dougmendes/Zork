#ifndef EXIT_H
#define EXIT_H

#include "entity.h"

class Room;

/** 
 * Direction enumeration
 * Defines possible directions for exits
 */

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    UP,
    DOWN
};

/** 
 * Exit class - represents an exit entity connecting rooms
 * Inherits from Entity base class
 */
class Exit : public Entity {
private:
    Direction direction; // Direction of the exit
    Room* source;       // Source room pointer
    Room* destination;  // Destination room pointer
    bool locked;      // Lock status of the exit

public:
    /** 
     * Constructor
     * @param direction Direction of the exit
     * @param source Pointer to source room
     * @param destination Pointer to destination room
     */
    Exit(Direction direction, Room* source, Room* destination);

    //Destructor
    virtual ~Exit();

    //Get direction
    Direction GetDirection() const;

    //Get source room
    Room* GetSource() const;

    //Get destination room
    Room* GetDestination() const;

    //Check if exit is locked
    bool IsLocked() const;

    //Set lock status
    void SetLocked(bool locked);

    //Get direction as string
    static std::string DirectionToString(Direction dir);
    
};
#endif