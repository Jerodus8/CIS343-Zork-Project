/* 11.22.2024
 *This code was worked on by:
 * Joshua Johnson
 * Austin Jackson
 * Jerod Muilenburg
 */


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
	mutable size_t message_num;
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
