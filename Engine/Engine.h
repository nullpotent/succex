#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Timer/PrecisionTimer.h"
#include "Managers/ModuleManager.h"
#include "Graphics/GLCalls.h"
#include "FrameCounter.h"
#include "Timer/Smoother.h"
#include "Managers/FontManager.h"
#include "XMLParser.h"

class Engine
{
public:

    Engine();

    virtual ~Engine();
    virtual bool Initialize();
    virtual bool InitializeGLContext();
    virtual bool SetupGL();
    virtual void SetupGLAttributes();
    virtual void Resize(unsigned int width, unsigned int height);
    virtual void Update(double elapsedTime);

    void Destroy();
    void Render();
    void Run();
    void Info();
    void ToggleFullscreen();

    void Shutdown()
    {
        endProcess_ = true;
    }

    unsigned int GetHeight()
    {
        return height_;
    }

    unsigned int GetWidth()
    {
        return width_;
    }

    void SetMainDir(std::string name)
    {
        mainDir_ = name;
    }

    std::string GetMainDir()
    {
        return mainDir_;
    }

    static Engine* Instance();
    static bool Instantiate();

    bool Create(std::string title,
                short int width,
                short int height,
                char bits,
                Uint32 sdlFlags,
                Uint32 videoFlags,
                double fps = 60.0,
                bool fullscreen=false,
                std::string maindir="Data/");

    const double GetFps() const;

protected:

private:

    double perspectiveRatio_;
    double fps_;
    int lastFPS_;

    bool endProcess_;
    bool active_;
    bool showFPS_;
    bool fullscreen_;

    Uint32 videoFlags_;
    Uint32 sdlFlags_;

    unsigned int posX_;
    unsigned int posY_;
    unsigned int width_;
    unsigned int height_;

    char bits_;

    std::string name_;
    std::string mainDir_;
    Font* tahomaFont_;

    PrecisionTimer* timer_;

    SDL_Surface* screen_;

    SDL_Event event_;

    static Engine* engine_;
};
