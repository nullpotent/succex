#pragma once
#include "EventManager.h"
#include "BaseModuleManager.h"
#include "Misc/Assert.h"

#define NUMKEYS 300

#define ModuleMgr  (*ModuleManager::Instance())
#define MouseButtonHandler ModuleManager::Instance()->Button()
#define MouseMotionHandler ModuleManager::Instance()->Motion()
#define EventType ModuleManager::Instance()->GetEventType()

class ModuleManager : public BaseModuleManager
{
public:

    virtual ~ModuleManager();

    virtual void Destroy();

    void InitializeGL();
    void UpdateModules(double elapsedTime);
    void RenderModules();
    void HandleEvents(SDL_Event* event);
    void Initialize();
    void KeyDown(int code);
    void KeyUp(int code);
    void SetType(Uint8 type);

    int GetMouseButton();
    int GetMouseX();
    int GetMouseY();


    Uint8 GetEventType();

    Vector2D GetMousePos();

    SDL_MouseMotionEvent* Motion();
    SDL_MouseButtonEvent* Button();

    void MouseButtonDown(SDL_Event& event);
    void MouseMotion(SDL_Event& event);

    static ModuleManager* Instance();
    static bool Instantiate();

    bool operator[](int i) { return keys_[i]; }

private:

    ModuleManager();
    ModuleManager(const ModuleManager& ref); //Not implemented

    static ModuleManager*  mManager_;
    bool                   keys_[NUMKEYS];

    Uint8                  type_;

    SDL_MouseButtonEvent*  mouseButtonEv_;

    SDL_MouseMotionEvent*  mouseMotionEv_;

};
