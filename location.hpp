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
	void addLocation(std::string direction, Location location);


};
#endif
