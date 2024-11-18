#ifndef __H__GAME__
#define __H__GAME__

#include "item.hpp"    
#include "location.hpp"
#include "npc.hpp"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <ctime>



class Game {
private:
	// Map of commands (command name -> function)
	
	
	
	std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
	// Player's inventory and weight
	std::vector<Item> inventory;
	int currentWeight;

	// Locations in the world
	std::vector<Location> locations;

	// Current location of the player
	Location currentLocation;

	// Calories the player needs to collect
	int caloriesNeeded;

	// Game status
	bool gameInProgress;

	// TODO ---- Create helper function to set up commands aka setupCommands()

	// Creates the world (locations, items, NPCs)
	void createWorld();

	// Selects a random location
	Location randomLocation();

	// Command functions
	void showHelp(std::vector<std::string> target);
	void talk(std::vector<std::string> target);
	void meet(std::vector<std::string> target);
	void take(std::vector<std::string> target);
	void give(std::vector<std::string> target);
	void go(std::vector<std::string> target);
	void showItems(std::vector<std::string> target);
	void look(std::vector<std::string> target);
	void quit(std::vector<std::string> target);

public:
    Game(); // Constructor
    void play(); // Main game loop
};

#endif
