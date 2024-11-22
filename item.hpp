/* 11.22.2024
 *This code was worked on by:
 * Joshua Johnson
 * Austin Jackson
 * Jerod Muilenburg
 */


#ifndef __H__ITEM__
#define __H__ITEM__

#include <string>

class Item
{
	private:
		std::string name;
		std::string desc; //description
		int cal; //calories
		float weight;
	public:
		Item();
		//for the strings, we should use constant strings, pass by reference.
		Item(const std::string &name, const std::string &desc, int cal, float weight);

		//Getters
		std::string getName() const;
		std::string getDescription() const;
		int getCalories() const;
		float getWeight() const; 

		//Setters
		void setName(const std::string &newName);
		void setDescription(const std::string &newDesc);
		void setWeight(float w);
		void setCalories(int c);

		
		//overloaded stream operator
		friend std::ostream& operator<<(std::ostream& stream, const Item& other){
			stream << other.name << "(" << other.cal << " calories) - "; 
			stream << other.weight << "lb";
			if (other.weight != 1){
				stream << "s";
			}
			stream << " - " << other.desc;
			return stream;
		}

		bool operator==(const Item& other) const {
			return name == other.name; // Compare based on a unique attribute (e.g., name)
    		}	
};
#endif
