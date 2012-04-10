#pragma once

#include "../Graphics/GLCalls.h"
#include "../Managers/FontManager.h"
#include <iostream>
#include "GameModule.types.h"
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class GameModule
{
protected:
    std::string name_;
    bool active_;
    bool pause_;

public:

    GameModule();
    GameModule(std::string name, bool active=false);

    virtual ~GameModule();
    virtual void Initialize();
    virtual void Destroy();
    virtual void HandleEvents();
    virtual void Render();
    virtual void SetupGL();
    virtual void Update(double elapsedTime_);

    const std::string& GetName() const
    {
        return name_;
    }

    void SetName(std::string name)
    {
        name_ = name;
    }

    void Pause()
    {
        pause_ = true;
    }

    void Resume()
    {
        pause_ = false;
    }

    void Activate()
    {
        active_ = true;
        std::cout<<name_<<" resumed"<<std::endl;
    }

    void Deactivate()
    {
        active_ = false;
        std::cout<<name_<<" paused"<<std::endl;
    }

    bool IsActive()
    {
        return active_;
    }
};
