#include <iostream>
#include "world.h"

int main() {
    // Create world
    World world;
    
    // Initialize game world
    world.Initialize();
    
    // Run game loop
    world.Run();
    
    return 0;
}