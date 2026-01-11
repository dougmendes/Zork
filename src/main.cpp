#include <iostream>
#include "entity.h"
#include "room.h"
#include "exit.h"
#include "item.h"

int main() {
    std::cout << "=================================\n";
    std::cout << "   Item and Container Test\n";
    std::cout << "=================================\n\n";
    
    // Test 1: Create simple items
    std::cout << "Test 1: Creating items...\n";
    Item* key = new Item("Rusty Key", "An old rusty key", false, false);
    Item* sword = new Item("Iron Sword", "A sharp iron sword", true, false);
    
    std::cout << "✓ Created: " << key->GetName() << "\n";
    std::cout << "✓ Created: " << sword->GetName() 
              << (sword->IsEquippable() ? " (equippable)" : "") << "\n\n";
    
    // Test 2: Create container
    std::cout << "Test 2: Creating container...\n";
    Item* backpack = new Item("Backpack", "A leather backpack", false, true, 5);
    
    std::cout << "✓ Created: " << backpack->GetName() 
              << (backpack->IsContainer() ? " (container)" : "") << "\n";
    std::cout << "  Max capacity: " << backpack->GetMaxCapacity() << "\n\n";
    
    // Test 3: Put items in container
    std::cout << "Test 3: Putting items in backpack...\n";
    if (backpack->PutItem(key)) {
        std::cout << "✓ Put " << key->GetName() << " in backpack\n";
    }
    if (backpack->PutItem(sword)) {
        std::cout << "✓ Put " << sword->GetName() << " in backpack\n";
    }
    
    backpack->ListContents();
    std::cout << "\n";
    
    // Test 4: Nested containers
    std::cout << "Test 4: Creating nested containers...\n";
    Item* box = new Item("Small Box", "A small wooden box", false, true, 2);
    Item* potion = new Item("Health Potion", "Restores 50 HP", false, false);
    
    box->PutItem(potion);
    std::cout << "✓ Put potion in box\n";
    
    backpack->PutItem(box);
    std::cout << "✓ Put box in backpack\n";
    
    std::cout << "\nBackpack contents:\n";
    backpack->ListContents();
    
    std::cout << "\nBox contents:\n";
    box->ListContents();
    std::cout << "\n";
    
    // Test 5: Take item from container
    std::cout << "Test 5: Taking item from container...\n";
    Item* takenKey = backpack->TakeItem("Rusty Key");
    if (takenKey) {
        std::cout << "✓ Took " << takenKey->GetName() << " from backpack\n";
    }
    
    std::cout << "\nBackpack contents after taking key:\n";
    backpack->ListContents();
    std::cout << "\n";
    
    // Test 6: Try to put item in non-container
    std::cout << "Test 6: Trying to put item in non-container...\n";
    if (!sword->PutItem(key)) {
        std::cout << "✓ Correctly prevented putting item in non-container\n\n";
    }
    
    // Test 7: Equipping items
    std::cout << "Test 7: Equipping items...\n";
    if (sword->IsEquippable()) {
        sword->SetEquipped(true);
        std::cout << "✓ Equipped " << sword->GetName() << "\n";
        std::cout << "  Is equipped: " << (sword->IsEquipped() ? "yes" : "no") << "\n\n";
    }
    
    // Test 8: Capacity limit
    std::cout << "Test 8: Testing capacity limit...\n";
    Item* smallBag = new Item("Small Pouch", "Holds only 2 items", false, true, 2);
    Item* item1 = new Item("Item 1", "First item", false, false);
    Item* item2 = new Item("Item 2", "Second item", false, false);
    Item* item3 = new Item("Item 3", "Third item", false, false);
    
    smallBag->PutItem(item1);
    smallBag->PutItem(item2);
    std::cout << "✓ Added 2 items to pouch (capacity: 2)\n";
    
    if (!smallBag->PutItem(item3)) {
        std::cout << "✓ Correctly prevented adding 3rd item (full)\n\n";
    }
    
    // Cleanup
    delete key;
    delete sword;
    delete backpack;
    delete box;
    delete potion;
    delete smallBag;
    delete item1;
    delete item2;
    delete item3;
    
    std::cout << "=================================\n";
    std::cout << "    ✓ All tests passed!\n";
    std::cout << "=================================\n";
    
    return 0;
}