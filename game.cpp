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
void Location::addLocation(std::string direction, Location &location) {
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

    // Set default values, Create the world and set the initial values for game variables
    std::vector<Item> inv;
    std::vector<Location> loc;
    this->inventory = inv;
    this->locations = loc;
    this->currentWeight = 0;
    this->caloriesNeeded = 1000;
    this->gameInProgress = true;

    this->createWorld();

    this->currentLocation = this->randomLocation();
    commands = setupCommands();
}



// Create the world with Locations, Items, and NPCs
void Game::createWorld() {
  	//create locations, link locations, create items/NPCs, place items/NPCs in locations, add locations to locations vector. 

    //create locations
	Location pac("Performing Art Center", "The music building. There are practice rooms, classrooms, and a performance hall.");
	Location kirkoff("Kirkhoff Center", "The student union. There are restaurants, a store, and places to congregate.");;
	Location library("Mary Idema Pew Library", "Books! Books! Get your books here! There are lots of places to study here.");
	Location zumberge("Zumberge Hall", "Business business business... numbers... is this working??");
	Location clockTower("The Clock Tower", "Ding Dong Ding Dong... Ding Dong Ding Dong... Time to get to class! ");
	Location transLink("Transformational Link Sculpture", "They say if you walk underneath, you'll fail your exams!");
	Location blueBridge("Blue Bridge", "Caution bridge may be icy.");
	Location mak("Mackinac Hall", "Why are all my classes in the same building? This place is a labrynth");


	//link locations
	pac.addLocation("east", kirkoff);
	pac.addLocation("south", zumberge);
	kirkoff.addLocation("west", pac);
	kirkoff.addLocation("east", library);
	kirkoff.addLocation("south", clockTower);
	library.addLocation("west", kirkoff);
	zumberge.addLocation("north", pac);
	zumberge.addLocation("east", clockTower);
	zumberge.addLocation("south", transLink);
	clockTower.addLocation("north", kirkoff);
	clockTower.addLocation("west", zumberge);
	transLink.addLocation("north", zumberge);
	transLink.addLocation("south", blueBridge);
	blueBridge.addLocation("north", transLink);
	blueBridge.addLocation("south", mak);
	mak.addLocation("north", blueBridge);


	//create items
	Item practiceSheetMusic("Practice Sheet Music", "A set of sheet music for a challenging piece. You can practice it to improve your musical skills.", 0, 0.2f);
	Item kirkhoffSnack("Snack from Java City", "A quick snack from the Java City cafe. It's a small boost to your energy.", 150, 0.1f);
	Item studyGuide("Study Guide", "A study guide filled with key points from your course. Perfect for last-minute cramming!", 0, 0.3f);
	Item businessTextbook("Business Textbook", "A heavy business textbook, full of charts, graphs, and numbers. It’s difficult to carry but full of useful information.", 0, 10.5f);
	Item clockTowerKey("Clock Tower Key", "A key to the Clock Tower. It’s said to open a mysterious room where time stands still.", 0, 0.05f);
	Item goodLuckCharm("Good Luck Charm", "A charm given to you by someone who walked under the sculpture. It is rumored to protect you from bad luck in exams.", 0, 0.1f);
	Item winterCoat("Winter Coat", "A warm winter coat perfect for the cold winds that sweep across the Blue Bridge. It’ll keep you warm and safe on icy days.", 0, 1.2f);
	Item labyrinthMap("Labyrinth Map", "A crumpled map of Mackinac Hall. With so many confusing corridors, this map will help you navigate through the labyrinth.", 0, 0.1f);
	Item chowMein("Stale Chow Mein", "Tasty and filling Stir-fried noodles from Panda Express, but it looks a little like cardboard.", 150, 0.3f);
	Item subSandwich("Boney Billy Sandwich", "A basic submarine sandwich loaded with turkey, lettuce, tomato, and mayo, all served on a soft french roll.", 600, 0.5f);
	Item hanburgur("Hanburgur", "Hanburgur. https://tinyurl.com/hanburgur", 700, 0.5f);

	//place items
	zumberge.addItem(businessTextbook);
	pac.addItem(practiceSheetMusic);
	kirkoff.addItem(kirkhoffSnack);
	library.addItem(studyGuide);
	mak.addItem(hanburgur);
	transLink.addItem(transLink);
	library.addItem(labyrinthMap);
	kirkoff.addItem(winterCoat);
	clockTower.addLocation(chowMein);
	pac.addItem(subSandwich);

	//create NPCs

	//Philomena Mantella (President Mantella)
	NPC mantella("Philomena Mantella", "Philomena Mantella, the glamorous yet secretively sinister president of the university. She rules with an iron fist, using her wealth and influence to manipulate everyone around her.");
    mantella.addMessage("You are merely a pawn in my grand design!");
    mantella.addMessage("Isn't it nice to have power and money? You wouldn't understand.");
    mantella.addMessage("You think the university cares about students? It's all about the profits!");
    mantella.addMessage("Oh, you want to change things? How cute. It's too late for that.");
    mantella.addMessage("Careful what you say around me, student. I have ways of making things disappear.");

    //Louie the Laker
	NPC louie("Louie the Laker", 
    "Louie the Laker, the school's proud mascot. He's a big, muscly laker man full of energy and spirit. "
    "Known for his towering presence, he's always ready to get the crowd fired up!");

	// Add dialogue options for Louie the Laker
	louie.addMessage("Let's go Lakers! We're number one!");
	louie.addMessage("You ready to show some school spirit? Get pumped!");
	louie.addMessage("You want to win this game? Just channel your inner Laker!");
	louie.addMessage("Don't forget, it's not just about academics—it's about heart, determination, and team spirit!");
	louie.addMessage("You need a cheer to get going? I've got plenty of those!");

	//Dr. Woodring
	NPC woodring("Dr. Woodring", 
	    "Dr. Woodring, the professor of Structure of Programming Languages. He's a scholar of the intricacies and theories behind "
	    "programming languages, from syntax and semantics to parsing and compilers. His passion for the subject is evident, but he’s "
	    "known for his demanding lectures and high expectations. A challenging but rewarding professor.");

	// Add dialogue options for Dr. Woodring
	woodring.addMessage("Well that's as different as a caterpillar from an ostrich.");
	woodring.addMessage("Ah yes, you do deserve extra credit for your C++ project.");
	woodring.addMessage("Hanburgur.");
	woodring.addMessage("Why don't you turn to your neighbor and see if they have any questions.")

	// Define NPC: Burger King Man
	NPC burgerKingMan("Burger King Man", 
	    "Burger King Man, the bizarre and unsettling figure who roams the campus dressed in a giant Burger King crown. "
	    "With an enigmatic, often cryptic smile, he's known for making strange appearances at unexpected times. No one quite knows why he's here, "
	    "but his oddball behavior always leaves an impression.");

	// Add dialogue options for Burger King Man
	burgerKingMan.addMessage("I drop my hanburgur :/ Help me find it.");
	burgerKingMan.addMessage("The king’s orders are simple: You must embrace the flame-grilled goodness.");
	burgerKingMan.addMessage("I rule the land of fast food, where every burger is fit for royalty.");
	burgerKingMan.addMessage("Did you know? The secret ingredient is always... mystery.");
	burgerKingMan.addMessage("Bow before the crown, for I am the Burger King Man, the true ruler of flavor.");
	burgerKingMan.addMessage("You don’t want to know what happens when the flame dies out... *shudder*");


	// Define NPC: Magic Elf (Quest version)
	NPC magicElf("Elandor the Magic Elf", 
	    "Elandor, a mischievous and wise magic elf, is the last hope to save the school from an ancient curse. "
	    "In order to restore balance and protect the school, you must feed him enough sustenance. His magic requires a certain amount of calories, "
	    "and only then will he reveal the secrets to stopping the curse. But he is a picky eater, and not all food is suitable for his powers.");

	// Add dialogue options for Magic Elf
	magicElf.addMessage("Ah, you’ve come to feed me, I see. But only the finest food will do for my magic!");
	magicElf.addMessage("To save the school, you must feed me well. Only when I am fully nourished will I grant you the power to break the curse.");
	magicElf.addMessage("Do you think a simple sandwich will suffice? Try harder, mortal.");
	magicElf.addMessage("Calories are not just numbers; they are the fuel that powers magic. Bring me more, and I will share my knowledge with you.");
	magicElf.addMessage("The more you feed me, the stronger I become... and the closer you come to saving your school.");
	magicElf.addMessage("Each bite I take, your hopes grow stronger. But beware, overfeeding could cause unexpected effects.");
	magicElf.addMessage("I sense you are struggling... Do not give up. The fate of the school rests on your hands... and your food.");

	//place NPCs
	mak.addNPC(woodring);
	transLink.addNPC(burgerKingMan);
	zumberge.addNPC(mantella);
	clockTower.addNPC(louie);



	//add locations to locations vector
	this->locations.push_back[pac];
	this->locations.push_back[kirkoff];
	this->locations.push_back[library];
	this->locations.push_back[zumberge];
	this->locations.push_back[clockTower];
	this->locations.push_back[transLink];
	this->locations.push_back[blueBridge];
	this->locations.push_back[mak];

	l = this->randomLocation();
	l.addNPC(magicElf);
	this->elfLocation = l;
}



using Command = std::function<void(std::vector<std::string>)>; // Function type alias
using CommandMap = std::map<std::string, Command>;

CommandMap Game::setupCommands(){
	/*
		Chat GPT gave us the alternative command vectors for this function.
	*/
	CommandMap commands; //create an empty map

	// Using lambdas to bind member functions
	commands["help"] = [this](std::vector<std::string> target)	{ showHelp(target); };
	commands["talk"] = [this](std::vector<std::string> target)	{ talk(target); };
	commands["meet"] = [this](std::vector<std::string> target)	{ meet(target); };
	commands["take"] = [this](std::vector<std::string> target)	{ take(target); };
	commands["give"] = [this](std::vector<std::string> target)	{ give(target); };
	commands["go"] = [this](std::vector<std::string> target)  	{ go(target); };
	commands["showItems"] = [this](std::vector<std::string> target){ showItems(target); };
	commands["look"] = [this](std::vector<std::string> target)	{ look(target); };
	commands["quit"] = [this](std::vector<std::string> target)	{ quit(target); };

	//create alternatives words for each command
	std::vector<std::string> help_commands = {"?", "h", "how", "commands", "showCommands", "Help", "HELP", "info", "instructions", "guide"};//all assigned to showHelp()
	for (const std::string& c : help_commands) { commands[c] = commands["help"]; }

	std::vector<std::string> talk_commands = {"talk", "speak", "chat", "converse", "discuss", "say", "ask", "dialogue"}; //all assigned to talk()
	for (const std::string& c : talk_commands) { commands[c] = commands["talk"]; }

	std::vector<std::string> meet_commands = {"meet", "greet", "encounter", "introduce", "sayHello", "connect", "meetUp", "join"};
	for (const std::string& c : meet_commands) { commands[c] = commands["meet"]; }

	std::vector<std::string> take_commands = {"take", "grab", "pick", "collect", "obtain", "get", "acquire"}; //all assigned to take()
	for (const std::string& c : take_commands) { commands[c] = commands["take"]; }

	std::vector<std::string> give_commands = {"give", "donate", "present", "offer", "hand", "pass", "transfer"}; //all assigned to give()
	for (const std::string& c : give_commands) { commands[c] = commands["give"]; }

	std::vector<std::string> go_commands = {"go", "move", "travel", "head", "leave", "walk", "advance", "proceed", "run"}; //all assigned to go()
	for (const std::string& c : go_commands) { commands[c] = commands["go"]; }

	std::vector<std::string> showItems_commands = {"showItems", "inventory", "items", "possessions", "things", "belongings", "checkItems"}; //all assigned to showItems()
	for (const std::string& c : showItems_commands) { commands[c] = commands["showItems"]; }

	std::vector<std::string> look_commands = {"look", "see", "view", "examine", "observe", "inspect", "search", "checkOut"}; //all assigned to look()
	for (const std::string& c : look_commands) { commands[c] = commands["look"]; }

	std::vector<std::string> quit_commands = {"quit", "exit", "leave", "end", "close", "stop", "terminate", "abandon"}; //all assigned to quit()
	for (const std::string& c : quit_commands) { commands[c] = commands["quit"]; }
	
	return commands;
}

// Randomly select a Location
Location Game::randomLocation() {
	int index = rand() % this->locations.size(); // Select a random index
	return this->locations[index];
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
	this->showHelp({});

	while (this->gameInProgress) {
		std::string userResponse;
		std::cout << "What is your command? ";
		std::getline(std::cin, userResponse);

		std::vector<std::string> tokens = split(userResponse); // Split input into tokens
		std::string command = tokens[0];
		tokens.erase(tokens.begin()); // Remove the command from tokens
        
		if (commands.find(command) != commands.end()) {
			this->commands[command](tokens); // Call the function associated with the command
		} else {
			std::cout << "Invalid command! Type 'help' for a list of commands.\n";
		}

		// End game condition check
		if (this->caloriesNeeded <= 0) {
			std::cout << "Elf has saved the campus! You win!\n";
			this->gameInProgress = false;
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
	throw std::logic_error("Function needs to remove items from the location. Implement Location.removeItem()")
	if (target.empty()) {
		std::cout << "Take what?\n";
		return;
	}

	std::string item_name = target[0];
	bool item_found = false;

	for (auto& item : this->currentLocation.getItems()) {
		if (item.getName() == item_name) {
			inventory.push_back(item);
			this->currentWeight += item.getWeight();
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

void Game::give(std::vector<std::string> target) {
	if (target.empty()) {
		std::cout << "Give what?\n";
		return;
	}

	std::string item_name = target[0]; // Assume the target is the item name
	bool item_found = false;

	for (auto& item : inventory) {
		if (item.getName() == item_name) {
			this->currentLocation.addItem(item);
			this->currentWeight -= item.getWeight();
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
	auto neighbors = this->currentLocation.getLocations();

	if (neighbors.find(direction) != neighbors.end()) {
		this->currentLocation = neighbors[direction]; // Move to new location
		std::cout << "You are now at " << this->currentLocation.getName() << ".\n";
	} else {
		std::cout << "There is no path in that direction.\n";
	}
}

// Command to look around in the current location
void Game::look(std::vector<std::string> target) {
	std::cout << this->currentLocation << "\n"; // Uses overloaded << operator for Location
}

// Command to talk to an NPC
void Game::talk(std::vector<std::string> target) {
	if (target.empty()) {
		std::cout << "Talk to who?\n";
		return;
	}

	std::string npc_name = target[0];
	for (auto& npc : this->currentLocation.getNPCs()) {
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
	std::cout << "Total weight: " << this->currentWeight << " lbs\n";
}

// Command to quit the game
void Game::quit(std::vector<std::string> target) {
	std::cout << "Thank you for playing. Goodbye!\n";
	this->gameInProgress = false;
}

