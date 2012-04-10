#include "BaseModuleManager.h"
#include "../Modules/GameModule.h"
#include <typeinfo>

BaseModuleManager::BaseModuleManager()
{
    Clean();
    destroyList_.clear();
    current_ = NULL;
}

BaseModuleManager::~BaseModuleManager()
{
    Destroy();
}

void BaseModuleManager::AddModule(GameModule* module)
{
    GameModulesList::iterator it = std::find(moduleList_.begin(), moduleList_.end(), module);

    if(it == moduleList_.end())
    {
        moduleList_.push_back(module);
    }

    current_ = module;
}

void BaseModuleManager::ActivateNext()
{
    if(current_!=NULL)
    {
        current_->Deactivate();
        current_ = (*(++(std::find(moduleList_.begin(),moduleList_.end(),current_))));
        if(current_==NULL)
        {
            current_ = (*(moduleList_.begin()));
        }
        current_->Activate();
    }
}

void BaseModuleManager::RemoveModule(GameModule* module)
{
    GameModulesList::iterator it = std::find ( moduleList_.begin(), moduleList_.end(), module );

    if ( it != moduleList_.end() )
    {
        moduleList_.erase ( it );
    }
}

GameModule* BaseModuleManager::GetNextModule(GameModule* module, bool loop)
{
    GameModule* returnModule = NULL;

    if(moduleList_.size())
    {
        GameModulesList::iterator it = std::find(moduleList_.begin(), moduleList_.end(), module);
        if(it != moduleList_.end())
        {
            it++;
            if(it == moduleList_.end())
            {
                if(loop)
                {
                    returnModule = (*moduleList_.begin());
                }
                else
                {
                    returnModule = (*it);
                }
            }
        }
    }
    return returnModule;
}

GameModule* BaseModuleManager::GetNextOfSameType(GameModule* module, bool loop)
{
    GameModule* returnModule = NULL;
    bool found = false;
    bool end = false;

    returnModule = GetNextModule(module, loop);

    while(returnModule && (!found) && (!end ))
    {
        if (returnModule == module)
        {
            returnModule = NULL;
            end = true;
        }
        else
        {
            if(typeid(*returnModule) == typeid(*module))
            {
                found = true;
            }
            else
            {
                returnModule = GetNextModule(returnModule, loop);
            }
        }
    }
    return returnModule;
}

GameModule* BaseModuleManager::GetModule(const std::string& name)
{
    GameModule* returnModule = NULL;

    GameModulesList::iterator it = moduleList_.begin();
    GameModulesList::iterator itEnd = moduleList_.end();

    bool found = false;
    while((it != itEnd) && (!found))
    {
        if((*it)->GetName().compare(name)==0)
        {
            found = true;
            returnModule = (*it);
        }
        else
        {
            it++;
        }
    }
    return returnModule;
}

void BaseModuleManager::Clean()
{
    moduleList_.clear();
}

void BaseModuleManager::Destroy()
{
    while(moduleList_.begin() != moduleList_.end())
    {
        GameModule* module = moduleList_.front();
        moduleList_.pop_front();
        delete module;
    }
    moduleList_.clear();
    DestroyModules();
}

const GameModulesList& BaseModuleManager::GetModuleList() const
{
    return moduleList_;
}

void BaseModuleManager::AddToDestroyList(GameModule* module)
{
    GameModulesList::iterator it = std::find(destroyList_.begin(), destroyList_.end(), module);
    if(it != destroyList_.end())
    {
        destroyList_.push_back(module);
    }
}

void BaseModuleManager::RemoveFromDestroyList(GameModule* module)
{
    GameModulesList::iterator it = std::find(destroyList_.begin(), destroyList_.end(), module);
    if(it != destroyList_.end())
    {
        destroyList_.erase (it);
    }
}

const GameModulesList& BaseModuleManager::GetDestroyList() const
{
    return destroyList_;
}

void BaseModuleManager::DestroyModules()
{
    while(destroyList_.begin() != destroyList_.end())
    {
        GameModule* module = destroyList_.front();
        destroyList_.pop_front();
        delete module;
    }
    destroyList_.clear();
}

