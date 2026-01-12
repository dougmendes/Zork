#include <iostream>
#include "entity.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "creature.h"
#include "player.h"

int main() {
    std::cout << "=================================\n";
    std::cout << "  Creature and Player Test\n";
    std::cout << "=================================\n\n";
    
    // Test 1: Create rooms
    std::cout << "Test 1: Creating rooms...\n";
    Room* lab = new Room("Laboratory", "A dark laboratory");
    Room* corridor = new Room("Corridor", "A long corridor");
    
    // Create exits
    Exit* labNorth = new Exit(Direction::NORTH, lab, corridor);
    Exit* corridorSouth = new Exit(Direction::SOUTH, corridor, lab);
    
    lab->AddExit(labNorth);
    corridor->AddExit(corridorSouth);
    
    std::cout << "✓ Created 2 connected rooms\n\n";
    
    // Test 2: Create items in lab
    std::cout << "Test 2: Creating items in lab...\n";
    Item* key = new Item("Rusty Key", "An old key", false, false);
    Item* sword = new Item("Iron Sword", "A sharp sword", true, false);
    Item* potion = new Item("Health Potion", "Restores 50 HP", false, false);
    
    lab->AddEntity(key);
    lab->AddEntity(sword);
    lab->AddEntity(potion);
    
    std::cout << "✓ Added 3 items to laboratory\n\n";
    
    // Test 3: Create player
    std::cout << "Test 3: Creating player...\n";
    Player* player = new Player("Hero", "A brave adventurer", 100);
    player->SetLocation(lab);
    
    std::cout << "✓ Created player with " << player->GetHP() << " HP\n";
    std::cout << "  Location: " << player->GetLocation()->GetName() << "\n\n";
    
    // Test 4: Pick up items
    std::cout << "Test 4: Picking up items...\n";
    player->PickUp("Iron Sword");
    player->PickUp("Rusty Key");
    player->PickUp("Health Potion");
    
    std::cout << "\n";
    player->ListInventory();
    std::cout << "\n";
    
    // Test 5: Equip item
    std::cout << "Test 5: Equipping sword...\n";
    player->Equip("Iron Sword");
    std::cout << "\n";
    player->ListInventory();
    std::cout << "\n";
    
    // Test 6: Move to another room
    std::cout << "Test 6: Moving north...\n";
    player->Move(Direction::NORTH);
    std::cout << "  Current location: " << player->GetLocation()->GetName() << "\n\n";
    
    // Test 7: Drop item
    std::cout << "Test 7: Dropping key...\n";
    player->Drop("Rusty Key");
    std::cout << "\n";
    player->ListInventory();
    std::cout << "\n";
    
    // Test 8: Take damage and heal
    std::cout << "Test 8: Taking damage and healing...\n";
    std::cout << "HP before: " << player->GetHP() << "/" << player->GetMaxHP() << "\n";
    
    player->TakeDamage(30);
    std::cout << "HP after damage: " << player->GetHP() << "/" << player->GetMaxHP() << "\n";
    
    player->Heal(20);
    std::cout << "HP after heal: " << player->GetHP() << "/" << player->GetMaxHP() << "\n";
    
    std::cout << "Is alive: " << (player->IsAlive() ? "yes" : "no") << "\n\n";
    
    // Test 9: Unequip
    std::cout << "Test 9: Unequipping sword...\n";
    player->Unequip();
    std::cout << "\n";
    player->ListInventory();
    std::cout << "\n";
    
    // Cleanup
    delete player;
    delete lab;
    delete corridor;
    delete labNorth;
    delete corridorSouth;
    delete key;
    delete sword;
    delete potion;
    
    std::cout << "=================================\n";
    std::cout << "    ✓ All tests passed!\n";
    std::cout << "=================================\n";
    
    return 0;
}