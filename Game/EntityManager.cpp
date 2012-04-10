#include "EntityManager.h"

EntityManager* EntityManager::Instance()
{
    static EntityManager instance;
    return &instance;
}

BaseGameEntity* EntityManager::GetEntityFromID(int id) const
{
    EntityMap::const_iterator ent = entityMap_.find(id);
    Assert((ent != entityMap_.end()));
    return ent->second;
}

void EntityManager::RemoveEntity(BaseGameEntity* ent)
{
    entityMap_.erase(entityMap_.find(ent->GetID()));
}

void EntityManager::RegisterEntity(BaseGameEntity* newEnt)
{
    entityMap_.insert(std::make_pair(newEnt->GetID(),newEnt));
}
