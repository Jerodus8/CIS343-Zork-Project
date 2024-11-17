/* add name here
 Joshua Johnson



*/


#include <iostream>
#include <stdexcept>
#include "item.hpp"    
#include "location.hpp"
#include "npc.hpp"     





int main(){
	bool gameRunning = true;
	while (gameRunning){
		// the is the main game file 


	}


	return 0;
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
