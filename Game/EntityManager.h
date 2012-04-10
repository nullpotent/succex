#pragma once
#pragma warning(disable:4786)

#include <map>
#include "Misc/Assert.h"
#include "BaseGameEntity.h"

class EntityManager
{
    private:

        typedef std::map<int, BaseGameEntity*> EntityMap;

    private:

        EntityMap entityMap_;
        EntityManager(){}
        EntityManager(const EntityManager&);
        EntityManager& operator=(const EntityManager&);

    public:

        static EntityManager* Instance();
        void RegisterEntity(BaseGameEntity* newEnt);
        BaseGameEntity* GetEntityFromID(int id) const;
        void RemoveEntity(BaseGameEntity* ent);

        void Reset()
        {
            entityMap_.clear();
        }
};
