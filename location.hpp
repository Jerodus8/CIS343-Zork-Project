#ifndef __H__LOCATION__
#define __H__LOCATION__

#include <string>
#include <"item.h">
#include <"npc.h">

class Location
{
private:
	std:string name;
	std:string desc;
	//map<direction, Location>, very similar to dict
	std::map<std::string, Location> neighbors;
	std::vector<Item> items;
	std::vector<NPC> npcs;
	bool visited;


public:
	//constructor
	location();
	location(const std::string &name, const std::string &desc, bool visited = false);

	//getters
	std::string getName() const;
	std::string getDescription() const;
	bool getVisited();
	std::map<std::string, Location> getLoactions();
	std::vector<Item> getItems();
	std::vector<NPC> getNPCs();

	//setters
	void setName(const std::string &name);
	void setDescription(const std::string &desc);
	void setVisited(bool v);
	void addItem(Item item);
	void addNPC(NPC npc); 



};
#endif
