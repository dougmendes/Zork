#include "entity.h"
#include <iostream>

//Constructor implementation
Entity::Entity(const std::string& name, const std::string& description, EntityType type)
    : name(name), description(description), type(type) {}

//Destructor implementation
Entity::~Entity() {
    contents.clear();
}

//Getter implementations
const std::string&  Entity::GetName() const {
    return name;
}

const std::string& Entity::GetDescription() const {
    return description;
}

const std::list<Entity*>& Entity::GetContents() const {
    return contents;
}
EntityType Entity::GetType() const {
    return type;
}
// Virtual update method
// Default implementation does nothing, subclasses can override
void Entity::Update() {

}