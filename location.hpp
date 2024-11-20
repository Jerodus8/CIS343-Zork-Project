/* add name
 * Joshua Johnson
 *
 */



#ifndef __H__LOCATION__
#define __H__LOCATION__

#include <string>
#include <map>
#include "item.hpp"
#include "npc.hpp"

class Location
{
private:
        std::string name;
	std::string desc;
        //map<direction, Location>, very similar to dict
        std::map<std::string, Location> neighbors;
        std::vector<Item> items;
        std::vector<NPC> npcs;
        bool visited;


public:
        //constructor
        Location();
        Location(const std::string &name, const std::string &desc, bool visited = false);

        //getters
        std::string getName() const;
        std::string getDescription() const;
        bool getVisited() const;
        std::map<std::string, Location> getLocations();
        std::vector<Item> getItems();
        std::vector<NPC> getNPCs();

        //setters
        void setName(const std::string &name);
        void setDescription(const std::string &desc);
        void setVisited(bool v);
        void addItem(Item item);
        void addNPC(NPC npc);
	void addLocation(std::string direction, Location& location);

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
		for (const auto& neighbor : location.neighbors) {
		    const auto& direction = neighbor.first;
		    const auto& neighborLocation = neighbor.second;
		    stream << "- " << direction << " - " << neighborLocation.getName();
		    if (neighborLocation.getVisited()) {
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
