#include "EventManager.h"
#include "../Modules/GameModule.h"
#include <iostream>

EventManager* EventManager::manager_ = NULL;

EventManager::EventManager(GameModulesList* list) : moduleList_(list)
{
    for(int i=0;i<255;++i)
    {
        keys_[i] = false;
    }
}

EventManager::EventManager()
{
    for(int i=0;i<255;++i)
    {
        keys_[i] = false;
    }
}

EventManager::~EventManager()
{
    std::cout << "EventManager down" << std::endl;
}

EventManager* EventManager::Instance()
{
    if (manager_ == NULL)
    {
        manager_ = new EventManager();
    }
    return manager_;
}

bool EventManager::Instantiate(GameModulesList* list)
{
    manager_ = new EventManager (list);
    return manager_ != NULL;
}

void EventManager::SendEvent(SDL_Event* event)
{
    if(event->key.keysym.sym<NUMKEYS)
        keys_[event->key.keysym.sym] = !keys_[event->key.keysym.sym];
}
