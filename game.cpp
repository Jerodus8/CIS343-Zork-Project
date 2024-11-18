/* add name here
 Joshua Johnson



*/

#include <sstream> // for the tokenizer
#include <iostream>
#include <stdexcept>
#include "item.hpp"    
#include "location.hpp"
#include "npc.hpp"     
#include "game.hpp"




int main(){


}

//################ Items ################## 

//Constructors
Item::Item(){
	this->name = "Default";
	this->desc = "This is a default item.";
	this->cal = 0;
	this->weight = 0.0f;
}
Item::Item(const std::string &name, const std::string &desc, int cal, float weight){
	setName(name);
	setDescription(desc);
	setCalories(cal);
	setWeight(weight);
}

//Getters
std::string Item::getName() const{
	return this->name;
}

std::string Item::getDescription() const{
	return this->desc;
}

int Item::getCalories() const{
	return this->cal;
}

float Item::getWeight() const{
	return this->weight;
}

//Setters
void Item::setName(const std::string &newName){
	if (newName.empty()){
		throw std::invalid_argument("Item name cannot be blank");  
	}
	this->name = newName;
}
void Item::setDescription(const std::string &newDesc){
		if (newDesc.empty()){
		throw std::invalid_argument("Item description cannot be blank");  
	}
	this->desc = newDesc;
}
void Item::setWeight(float w){
	if (w < 0 || w > 500){
		throw std::out_of_range("Item  weight must be between 0 and 500");
	}
	this->weight = w;
}
void Item::setCalories(int c){
	if (c < 0 || c > 1000){	
		throw std::out_of_range("Item calorie variable cannot be less than 0 or more than 1000");
	}
	this->cal = c;
}

//################ NPCs ################## 

//Constructors
NPC::NPC(){
	this->name = "Default";
	this->desc = "This is a default NPC";
	std::vector<std::string> m;
	this->messages = m;
}

NPC::NPC(const std::string &name, const std::string &desc){
	this->name = name;
	this->desc = desc;
	std::vector<std::string> m;
	this->messages = m;
	this->message_num = 0;
}


//getters
std::string NPC::getName() const{return this->name;}
std::string NPC::getDescription() const{return this->desc;}
std::string NPC::getMessage() const{
	std::string m = this->messages[this->message_num++];
	if (this->message_num >= this->messages.size()){
		this->message_num = 0;
	}
	return m;
}
//setters
void NPC::setName(const std::string &newName){
	if (newName.empty()){
		throw std::invalid_argument("NPC name cannot be blank");  
	}
	this->name = newName;
}
void NPC::setDescription(const std::string &newDesc){
	if (newDesc.empty()){
		throw std::invalid_argument("NPC description cannot be blank");  
	}
	this->desc = newDesc;
}
void NPC::addMessage(const std::string &message){
	if (message.empty()){
		throw std::invalid_argument("NPC messages cannot be blank");  
	}
	this->messages.push_back(message);
}
void NPC::updateMessage(int i, const std::string &newMessage){
	if (messages.empty()){
		throw std::invalid_argument("NPC messages cannot be blank");  
	}
	if(i < 0 || i >= messages.size()){
		throw std::out_of_range("Message index out of range");
	}
	this->messages[i] = newMessage;
}



//################ Locations ###############
Location::Location(){
	this->name = "Default location";
	this->desc = "This is the default location";
	this->visited = false;
    //map<direction, Location>, very similar to dict
    std::map<std::string, Location> neighbors;
    std::vector<Item> items;
    std::vector<NPC> npcs;
   	this->neighbors = neighbors;
   	this->items = items;
   	this->npcs = npcs;
}	
//getters
std::string Location::getName() const{
	return this->name;
}
std::string Location::getDescription() const{
	return this->desc;
}
bool Location::getVisited() const{
	return this->visited;
}
std::map<std::string, Location> Location::getLocations (){
	return this->neighbors;
}
std::vector<Item> Location::getItems(){
	return this->items;
}
        
//setters
void Location::setName(const std::string &name){
	this->name = name;
}
void Location::setDescription(const std::string &desc){
	this->desc = desc;
}
void Location::setVisited(bool v){
	this->visited = v;
}
void Location::addItem(Item item){
	this->items.push_back(item);
}
void Location::addNPC(NPC npc){
	this->npcs.push_back(npc);
}




/*
* Adds the location into the map with the provided direction string.
* If the string is blank, it raises an exception.
* If the key already exists in the map, it raises an exception.
*/
void Location::addLocation(std::string direction, Location location) {
    if (direction.empty()) {
        throw std::invalid_argument("Direction cannot be blank.");
    }

    // Check if the direction already exists in the map
    if (neighbors.find(direction) != neighbors.end()) {
        throw std::invalid_argument("Direction already exists in the map.");
    }

    // Add the new direction and location to the map
    neighbors[direction] = location;
}



//################ Game ###############


Game::Game() {
    // Initialize the map of commands
    //
    //
    // TODO --- uncomment this line when setupCommands() is done
    //commands = setupCommands();

    // Create the world and set the initial values for game variables
    createWorld();

    // Set default values
    currentLocation = randomLocation();
    currentWeight = 0;
    caloriesNeeded = 1000;
    gameInProgress = true;
}



// Create the world with Locations, Items, and NPCs
void Game::createWorld() {
    // Example:
    //Location kirkhoff_upstairs("kirkhoff upstairs", "The student union. There are restaurants, a store, and places to congregate.");
    //Item rusty_sword("rusty sword", "A rusty old sword.", 50, 5.0f);
    //NPC ball_of_light("ball of light", "A glowing orb of light.");
    //kirkhoff_upstairs.addItem(rusty_sword);
    //kirkhoff_upstairs.addNPC(ball_of_light);
    
    // Add more locations, items, NPCs, and set neighbors...
    
    // Add locations to the world
    // example:
    // locations.push_back(kirkhoff_upstairs);

    // Game creation here \/ :)
}


// TODO ---- add the setupCommands() function


// Randomly select a Location
Location Game::randomLocation() {
	int index = rand() % locations.size(); // Select a random index
	return locations[index];
}

// Helper method to split commands into tokens
std::vector<std::string> split(const std::string& str, char delimiter = ' ') {
	std::vector<std::string> tokens;
	std::istringstream stream(str);
	std::string token;
	while (std::getline(stream, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}



// Play method to run the game loop
void Game::play() {
	std::cout << "Welcome to the game!\n";
	showHelp({});

	while (gameInProgress) {
		std::string userResponse;
		std::cout << "What is your command? ";
		std::getline(std::cin, userResponse);

		std::vector<std::string> tokens = split(userResponse); // Split input into tokens
		std::string command = tokens[0];
		tokens.erase(tokens.begin()); // Remove the command from tokens
        
		if (commands.find(command) != commands.end()) {
			commands[command](tokens); // Call the function associated with the command
		} else {
			std::cout << "Invalid command! Type 'help' for a list of commands.\n";
		}

		// End game condition check
		if (caloriesNeeded <= 0) {
			std::cout << "Elf has saved the campus! You win!\n";
			gameInProgress = false;
		}
    	}
}


// Show help message and available commands
void Game::showHelp(std::vector<std::string> target) {
	std::cout << "Available commands:\n";
	for (const auto& pair : commands) {
		std::cout << "- " << pair.first << "\n";
	}
	
	// Print current time
	std::time_t current_time = std::time(nullptr);
	std::cout << "Current time: " << std::ctime(&current_time) << std::endl;
}


// Command to take an item
void Game::take(std::vector<std::string> target) {
	if (target.empty()) {
		std::cout << "Take what?\n";
		return;
	}

	std::string item_name = target[0];
	bool item_found = false;

	for (auto& item : currentLocation.getItems()) {
		if (item.getName() == item_name) {
			inventory.push_back(item);
			currentWeight += item.getWeight();
			std::cout << "You have taken the " << item_name << ".\n";
			item_found = true;
		break;
		}
	}

	if (!item_found) {
		std::cout << "Item not found in this location.\n";
	}
}

// Command to give an item to the NPC or location


//TODO ---- fix code
//its not perfect code we need to look at the docs and check if we are in the woods
//some compilation issue with the inventory erase func not sure why

void Game::give(std::vector<std::string> target) {
	if (target.empty()) {
		std::cout << "Give what?\n";
		return;
	}

	std::string item_name = target[0]; // Assume the target is the item name
	bool item_found = false;

	for (auto& item : inventory) {
		if (item.getName() == item_name) {
			currentLocation.addItem(item);
			currentWeight -= item.getWeight();
			// check if we are in the woods
			
			inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
			std::cout << "You have given the " << item_name << " to the location.\n";
			item_found = true;
			break;
		}
	}

	if (!item_found) {
		std::cout << "Item not found in your inventory.\n";
	}
}

// Command to move to a different location
void Game::go(std::vector<std::string> target) {
	if (target.empty()) {
		std::cout << "Go where?\n";
		return;
	}

	std::string direction = target[0];
	auto neighbors = currentLocation.getLocations();

	if (neighbors.find(direction) != neighbors.end()) {
		currentLocation = neighbors[direction]; // Move to new location
		std::cout << "You are now at " << currentLocation.getName() << ".\n";
	} else {
		std::cout << "There is no path in that direction.\n";
	}
}

// Command to look around in the current location
void Game::look(std::vector<std::string> target) {
	std::cout << currentLocation << "\n"; // Uses overloaded << operator for Location
}

// Command to talk to an NPC
void Game::talk(std::vector<std::string> target) {
	if (target.empty()) {
		std::cout << "Talk to who?\n";
		return;
	}

	std::string npc_name = target[0];
	for (auto& npc : currentLocation.getNPCs()) {
		if (npc.getName() == npc_name) {
			std::cout << npc.getMessage() << "\n";
			return;
		}
	}

	std::cout << "NPC not found in this location.\n";
}

// Command to show items in the player's inventory
void Game::showItems(std::vector<std::string> target) {
	std::cout << "You are carrying:\n";
	for (const auto& item : inventory) {
		std::cout << item << "\n";
	}
	std::cout << "Total weight: " << currentWeight << " lbs\n";
}

// Command to quit the game
void Game::quit(std::vector<std::string> target) {
	std::cout << "Thank you for playing. Goodbye!\n";
	gameInProgress = false;
}

