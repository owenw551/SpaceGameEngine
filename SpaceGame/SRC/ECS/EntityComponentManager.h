#pragma once

#include <array>
#include <vector>
#include <bitset>
#include <array>
#include <memory>
#include <iostream>
#include "Groups.h"

class Component;
class Entity;
class Manager;

using componentID = std::size_t;
using GroupID = std::size_t;

constexpr int maxComponents = 32;
constexpr int maxGroups = 32;

/*
*These two functions manage the IDs for components.
*The first time a template version of getComponent Type
*ID is called, it assigns a new ID for that type, and
*returns that ID every other time it is called.
*/
inline componentID assignIDToComponentType() 
{
	static int numberOfIDsAssigned = 0;
	return numberOfIDsAssigned++;
}


template<typename T>
inline componentID getComponentTypeID()
{
	static int typeID = assignIDToComponentType();
	return typeID;
}

//Plug in functionality for entities
class Component
{
protected:
	Entity *owner;
public:
	virtual void update() {}
	virtual void draw() {} //render to screen
	virtual void init() {} // use to set references to other components
	virtual ~Component() {};

	//Getters + setters
	void setOwner(Entity *newowner)
	{
		owner = newowner;
	}

	Entity* getOwner()
	{
		return owner;
	}
};

//Entity is a vector of components a bool flag indicating whether it can be removed from the game
class Entity
{
private:

	bool active;
	Manager& manager;

	std::bitset<maxComponents> componentBitSet;
	std::array<Component* , maxComponents> componentArray;
	std::vector<std::unique_ptr<Component>> components;
	std::bitset<maxGroups> groupsBitSet;


public:

	Entity(Manager& managerRef): manager(managerRef)
	{
		active = true;
	}

	void update()
	{
		for (auto& c : components) c->update();
	}

	void draw() 
	{
		for (auto& c : components) c->draw();
	}

	bool isActive() { return active; }

	void destroy()  {active = false;}

	template<typename T>
	bool hasComponent()
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	/*
	* Guidelines when adding components:
	* Anything that can be done without references to other components - do in constructor
	* Anything that cannot be done without references to components - do in init function
	*/

	//Add Component with generic type
	template <typename T, typename... Args>
	T& addComponent(Args&&... mArgs)
	{
		//create component + pointer to component
		T* c(new T(std::forward<Args>(mArgs)...));
		//set Owner
		c->setOwner(this);
		//initialise - set pointers to other comps
		c->init();
		std::unique_ptr<Component> newCmpnt{ c };
		components.emplace_back(std::move(newCmpnt));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		return *c;
	}

	//Add Child of Component
	template <typename T, typename cT, typename... Args>
	T& addComponent(Args&&... mArgs) 
	{
		//Create component + pointer to component
		T* c(new cT(std::forward<Args>(mArgs)...));
		//set Owner
		c->setOwner(this);
		//initialise - set pointers to other comps
		c->init();
		std::unique_ptr<Component> newCmpnt{c};
		components.emplace_back(std::move(newCmpnt));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		return *c;
	}

	

	template<typename T>
	T& getComponent() const
	{
		return *static_cast<T*>((componentArray[getComponentTypeID<T>()]));
	}

	//return whether entity belongs to a group
	bool inGroup(GroupID id)
	{
		return groupsBitSet[id];
	}
	//defined in cpp as requires use of address
	void addToGroup(GroupID id);

	void removeFromGroup(GroupID id)
	{
		groupsBitSet[id] = false;
	}

};

//vector of entities which also holds all members to groups
class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entityList;
	std::vector<std::unique_ptr<Entity>>::iterator it;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
	std::vector<Entity*>::iterator groupIt;

public:
	void update()
	{
		for (auto& e : entityList) e->update();
	}


	
	void refresh()
	{
		//Remove entities from groups
		for (int k = 0; k < maxGroups; k++)
		{
			groupIt = groupedEntities[k].begin();
			int j = 0;
			while (groupIt != groupedEntities[k].end())
			{
				if ((*groupIt)->isActive() == false || (*groupIt)->inGroup(k) == false)
				{
					groupedEntities[k].erase(groupIt);
					groupIt = groupedEntities[k].begin() + j;
					continue;
				}
				j++;
				groupIt++;
			}
		}

		//Remove destroyed entities from vector
		it = entityList.begin();
		int i = 0;
		while (it != entityList.end())
		{
			if ((*it)->isActive() == false)
			{
				entityList.erase(it);
				it = entityList.begin() + i;
				continue;
			}
			i++;
			it++;
		}

	}

	//Entities manage their own groups, this is called by Entity
	void addToGroup(Entity *entity, GroupID id)
	{
		groupedEntities[id].emplace_back(entity);
	}


	std::vector<Entity*>& getGroup(GroupID id)
	{
		return groupedEntities[id];
	}

	//place entity in vector
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entityList.emplace_back(std::move(uPtr));
		return *e;
	}

};



