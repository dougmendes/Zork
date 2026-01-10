#include "exit.h"
#include "room.h"

Exit::Exit(Direction direction, Room* source, Room* destination)
    : Entity("Exit " + DirectionToString(direction),
        "An exit leading " + DirectionToString(direction),
        EntityType::EXIT),
      direction(direction), 
      source(source), 
      destination(destination), 
      locked(false) {}

Exit::~Exit() {}

Direction Exit::GetDirection() const {
    return direction;
}

Room* Exit::GetDestination() const {
    return destination;
}

Room* Exit::GetSource() const {
    return source;
}

bool Exit::IsLocked() const {
    return locked;
}

void Exit::SetLocked(bool locked) {
    this->locked = locked;
}

std::string Exit::DirectionToString(Direction dir) {
    switch (dir) {
        case Direction::NORTH: return "north";
        case Direction::SOUTH: return "south";
        case Direction::EAST:  return "east";
        case Direction::WEST:  return "west";
        case Direction::UP:    return "up";
        case Direction::DOWN:  return "down";
        default:               return "unknown";
    }
}