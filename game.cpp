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
	this->weight = 0;
}
Item::Item(const std::string name, const std::string desc, int cal, float weight){
	this->name = name;
	this->desc = desc;
	this->cal = cal;
	this->weight = weight;
}

//Getters
std::string getName() const{return this->name}
std::string getDescription() const{return this->desc;}
int getCalories() const{return this->cal;}
float getWeight() const{return this->weight;}

//Setters
void setName(const std::string &newName){
	if (newName == "")
	{
		throw std::invalid_argument("Item name cannot be blank");  
	}
	this->name = newName;
}
void setDescription(const std::string &newDesc){
		if (newDesc == "")
	{
		throw std::invalid_argument("Item description cannot be blank");  
	}
	this->desc = newDesc;
}
void setWeight(float w){
	if (w < 0 || w > 500)
	{
		throw std::out_of_range("Item  weight must be between 0 and 500");
	}
	this->weight = w;
}
void setCalories(int c){
	if (c < 0 || c > 1000)
	{
		throw std::out_of_range("Item calorie variable cannot be less than 0 or more than 1000")
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
	this->message_num = 0;
}

NPC::NPC(const std::string &name, const std::string &desc){
	this->name = name;
	this->desc = desc;
	std::vector<std::string> m;
	this->messages = m;
	this->message_num = 0;
}


//getters
std::string getName() const{return this->name;}
std::string getDescription() const{return this->desc;}
std::string getMessage() const{
	m = this->messages[this->message_num++];
	if (message_num >= this.messages.size()) this->message_num = 0;
	return m;
}
//setters
void setName(const std::string newName){
	if (newName == "")
	{
		throw std::invalid_argument("NPC name cannot be blank");  
	}
	this->name = newName;
}
void setDescription(const std::string newDesc){
	if (newDesc == "")
	{
		throw std::invalid_argument("NPC description cannot be blank");  
	}
	this->desc = newDesc;
}
void addMessage(const std::string message){
	this->messages.push_back(message)
}
void updateMessage(int i, const std::string newMessage){
	this->messages[i] = newMessage;
}
