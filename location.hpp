/* 11.22.2024
 *This code was worked on by:
 * Joshua Johnson
 * Austin Jackson
 * Jerod Muilenburg
 */



#ifndef __H__LOCATION__
#define __H__LOCATION__



#include <functional>
#include <string>
#include <map>
#include "item.hpp"
#include "npc.hpp"

class Location
{
private:
	std::string name;
	std::string desc;
	std::map<std::string, Location*> neighbors;
	std::vector<Item> items;
	std::vector<NPC> npcs;
	bool visited;


public:
	//constructor
	Location();
	Location(const std::string &name, const std::string &desc);

	//getters
	std::string getName() const;
	std::string getDescription() const;
	bool getVisited() const;
	std::map<std::string, Location*> getLocations() const;
	std::vector<Item> getItems();
	std::vector<NPC>& getNPCs();

	//setters
	void setName(const std::string &name);
	void setDescription(const std::string &desc);
	void setVisited(bool v);
	void addItem(Item item);
	void removeItem(Item item);
	void addNPC(NPC npc);
	void addLocation(const std::string& direction, Location& location);
	// Overloaded operator
	friend std::ostream& operator<<(std::ostream& stream, const Location& location){
	    // Start with the location name and description
	    stream << location.name << " - " << location.desc << "\n";

	    // Add the NPCs
	    stream << "You see the following NPCs:\n";
	    if (location.npcs.empty()) {
		stream << "- None\n";
	    } else {
		for (const auto& npc : location.npcs) {
		    stream << "- " << npc << "\n"; // Using NPC overloaded <<
		}
	    }

	    // Add the Items
	    stream << "You see the following Items:\n";
	    if (location.items.empty()) {
		stream << "- None\n";
	    } else {
		for (const auto& item : location.items) {
		    stream << "- " << item << "\n"; // Using the Item overloaded <<
		}
	    }

	    // Add the Directions and Neighbors
	    stream << "You can go in the following Directions:\n";
	    if (location.neighbors.empty()) {
		stream << "- None\n";
	    } else {
		for (auto [direction, n] : location.neighbors) {
		    const auto neighbor = *n;
		    stream << "- " << direction << " - " << neighbor.getName();
		    if (neighbor.getVisited()) {
			stream << " (Visited)";
		    } else {
			stream << " (Unknown)";
		    }
		    stream << "\n";
		}
	    }
	    return stream;
	}
};
#endif
