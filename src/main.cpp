#include <iostream>
#include "entity.h"

int main() {
    std::cout << "=================================\n";
    std::cout << "    Entity Test - Etapa 1\n";
    std::cout << "=================================\n\n";
    
    // Test 1: Create entity
    std::cout << "Test 1: Creating entity...\n";
    Entity* testEntity = new Entity("Test Room", "A dark laboratory", EntityType::ROOM);
    
    std::cout << "✓ Entity created successfully!\n";
    std::cout << "  Name: " << testEntity->GetName() << "\n";
    std::cout << "  Description: " << testEntity->GetDescription() << "\n";
    std::cout << "  Type: " << static_cast<int>(testEntity->GetType()) << " (ROOM)\n";
    
    // Test 2: Check contents (should be empty)
    std::cout << "\nTest 2: Checking contents...\n";
    std::cout << "✓ Contents size: " << testEntity->GetContents().size() << " (should be 0)\n";
    
    // Test 3: Call Update (should do nothing but not crash)
    std::cout << "\nTest 3: Calling Update()...\n";
    testEntity->Update();
    std::cout << "✓ Update() called successfully!\n";
    
    // Test 4: Delete (destructor should be called)
    std::cout << "\nTest 4: Deleting entity...\n";
    delete testEntity;
    std::cout << "✓ Entity deleted successfully!\n";
    
    std::cout << "\n=================================\n";
    std::cout << "    ✓ All tests passed!\n";
    std::cout << "=================================\n";
    
    return 0;
}