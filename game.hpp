/* This code was worked on by:
 * Joshua Johnson
 * Austin Jackson
 * Jerod Muilenburg
 */
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
public:
	Location pac;
    Location kirkoff;
    Location library;
    Location zumberge;
    Location clockTower;
    Location transLink;
    Location blueBridge;
    Location mak;
private:
	// Map of commands (command name -> function)

	
	std::map<std::string, std::function<void(std::vector<std::string>)>> commands;
	// Player's inventory and weight
	std::vector<Item> inventory;
	int currentWeight;

	// Locations in the world
	// using pointers so to not store by copy
	std::vector<std::reference_wrapper<Location>> locations;

	// Current location of the player
	Location* currentLocation;
	
	//location of the elf
	Location elfLocation;

	// Calories the player needs to collect
	int caloriesNeeded;

	// Game status
	bool gameInProgress;

	// Creates the world (locations, items, NPCs)
	void createWorld();

	//sets up all commands
	std::map<std::string, std::function<void(std::vector<std::string>)>> setupCommands();

	// Selects a random location
	Location& randomLocation();

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
