#ifndef __H__NPC__
#define __H__NPC__

#include <string>
#include <vector>
#include <iostream>
class NPC
{
private:
	std::string name;
	std::string desc;
	std::vector<std::string> messages;
	int message_num;
public: 
	NPC();
	NPC(const std::string &name, const std::string &desc);

	//getters
	std::string getName() const;
	std::string getDescription() const;
	std::string getMessage();

	//setters
	void setName(const std::string &newName);
	void setDescription(const std::string &newDesc);
	void addMessage(const std::string &message);
	void updateMessage(int i, const std::string &newMessage)

	//overloaded stream operator
	friend std::ostream& operator<<(std::ostream& stream, const NPC& other){
		stream << other.name;
	}
};
#endif
