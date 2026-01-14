#include "entity.h"
#include <iostream>

//Constructor implementation
Entity::Entity(const std::string& name, const std::string& description, EntityType type)
    : type(type), name(name), description(description) {}

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

// Add entity to contents
void Entity::AddEntity(Entity* entity) {
    contents.push_back(entity);
}

//Remove entity from contents
bool Entity::RemoveEntity(Entity* entity) {
    for (auto it = contents.begin(); it != contents.end(); ++it) {
        if (*it == entity) {
            contents.erase(it);
            return true;
        }
    }
    return false;
}

// Find entity in contents by name
Entity* Entity::FindEntity(const std::string& name) const{
    for (Entity* entity : contents) {
        if (entity->GetName() == name) {
            return entity;
        }
    }
    return nullptr; // Not found
}
// Virtual update method
// Default implementation does nothing, subclasses can override
void Entity::Update() {

}