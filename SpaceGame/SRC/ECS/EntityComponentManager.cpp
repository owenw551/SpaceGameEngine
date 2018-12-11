#include "EntityComponentManager.h"

void Entity::addToGroup(GroupID id)
{
	groupsBitSet[id] = true;
	manager.addToGroup(this, id);
}
