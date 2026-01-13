#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "room.h"
#include "exit.h"
#include "npc.h"
#include "item.h"
#include <vector>
#include <string>

// Forward declaration
class Player; 

/**
 * * World class - manages the entire game world
 * 
 * Responsibilities:
 * - Own all entities (rooms, items, exits, players)
 * - Manage memory
 * - Runs the game loop
 *  - Process player commands
 */

 class World {
 protected:
    std::vector<Entity*> entities; // All entities in the world
    Player* player;                // The player character
    bool gameRunning;          // Is the game running?
    NPC* monster;                  // Main NPC/monster in the game

    /**
     * Parse and execute a player command
     * @param input User input string
     */
    void ParseCommand(const std::string& input);

    /**
     * Display current room description and contents
     */
    void LookAround();

    /**
     * Show available commands
     */
    void ShowHelp();
public:
    /**
     * Constructor
     */
    World();

    /**
     * Destructor
     */
    virtual ~World();

    /**
     * Add entity to world
     * World takes ownership and will delete it
     * @param entity Entity to add
     */
    void AddEntity(Entity* entity);

    /**
     * Set the player character
     * @param player Player to set
     */
    void SetPlayer(Player* player);

    /**
     * Get the player
     * @return Pointer to player
     */
    Player* GetPlayer() const;

    /**
     * Initialize the game world with rooms, items, etc.
     */
    void Initialize();

    /**
     * Run the main game loop
     */
    void Run();

     /**
     * Update all entities (call Update() on each)
     */
    void Update();

    /**
     * Trigger game over
     * @param reason Reason for game over
     */
    void GameOver(const std::string& reason);
    
    /**
     * Start combat with NPC
     * @param npc Enemy to fight
     */
    void StartCombat(NPC* npc); 

};

#endif