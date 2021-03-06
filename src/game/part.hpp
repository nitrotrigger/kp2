#ifndef SERVER_PART_HPP
#define SERVER_PART_HPP

#include <string>
#include <memory>

#include "object.hpp"

namespace Game
{

class Part : public Object
{
	public:
		virtual const std::string& getName() const;
		virtual int getPrice() const;

		float getMass() const;
		
		Part(const Json::Value& value);
		virtual void save(Json::Value& value) const;
		
	private:
		std::string name;
		int price;
		float mass;
};

};

#endif
