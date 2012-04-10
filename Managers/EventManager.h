#pragma once
#include "../Modules/GameModule.types.h"
#include <SDL/SDL.h>

#define MEventManager EventManager->Instance()
#define NUMKEYS 300

class EventManager
{
public:

    EventManager(GameModulesList* list);
    EventManager();
    virtual ~EventManager();
    void SendEvent(SDL_Event *event);
    static bool Instantiate(GameModulesList* list);
    static EventManager* Instance();

    bool operator[](int i) { return keys_[i]; }

protected:

private:
    GameModulesList*        moduleList_;
    bool                    keys_[NUMKEYS];
    static EventManager*    manager_;
};
