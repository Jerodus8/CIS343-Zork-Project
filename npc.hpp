#ifndef __H__NPC__
#define __H__NPC__

#include <iostream>
#include <string>
#include <vector>
class NPC
{
private:
	std::string name;
	std::string desc;
	std::vector<std::string> messages;
public: 
	NPC();
	NPC(const std::string &name, const std::string &desc);

	//getters
	std::string getName() const;
	std::string getDescription() const;
	std::string getMessage() const;

	//setters
	void setName(const std::string &newName);
	void setDescription(const std::string &newDesc);
	void addMessage(const std::string &message);
	void updateMessage(int i, const std::string &newMessage);

	//overloaded stream operator
	friend std::ostream& operator<<(std::ostream& stream, const NPC& other){
		stream << other.name;
		return stream;
	}
};
#endif
