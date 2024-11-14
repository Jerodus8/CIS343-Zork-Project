#ifndef __H__ITEM__
#define __H__ITEM__

#include <string.h>

class Item
{
public:
	Item();
	~Item(std::string name, std::string desc, int calories, float weight);
private:
	std::string name;
	std::string desc;
	int calories;
	float weight;
	
};





#endif
