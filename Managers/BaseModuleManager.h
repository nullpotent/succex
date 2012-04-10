#pragma once
#include "../Modules/GameModule.types.h"

class BaseModuleManager
{
public:
    BaseModuleManager();
    virtual ~BaseModuleManager();

    void AddModule(GameModule* module);
    void RemoveModule(GameModule *module);

    GameModule* GetNextModule(GameModule* module, bool loop=false);
    GameModule* GetNextOfSameType(GameModule* module, bool loop=false);
    GameModule* GetModule(const std::string& name);

    void ActivateNext();
    void Clean();
    virtual void Destroy();

    const GameModulesList& GetModuleList() const;

    void AddToDestroyList(GameModule* module);
    void RemoveFromDestroyList(GameModule* module);
    const GameModulesList& GetDestroyList() const;
    void DestroyModules();

protected:
    GameModulesList moduleList_;
    GameModulesList destroyList_;

private:
    GameModule* current_;

};
