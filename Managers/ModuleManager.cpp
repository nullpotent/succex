#include "ModuleManager.h"
#include "../Modules/GameModule.h"

ModuleManager* ModuleManager::mManager_ = NULL;

ModuleManager::ModuleManager()
{
    Initialize();
}

ModuleManager::~ModuleManager()
{
    std::cout << "ModuleManager down" << std::endl;
}

ModuleManager* ModuleManager::Instance()
{
    Assert ( mManager_ != NULL );
    return mManager_;
}

void ModuleManager::Destroy()
{
    delete mouseButtonEv_;
    delete mouseMotionEv_;
}

void ModuleManager::RenderModules()
{
    DestroyModules();
    GameModulesList::iterator it = moduleList_.begin();
    GameModulesList::iterator itEnd = moduleList_.end();
    while (it != itEnd)
    {
        if((*it)->IsActive())
            (*it)->Render();
        it++;
    }
}

void ModuleManager::KeyDown(int code)
{
    if(code < NUMKEYS && code > 0)
        keys_[code] = true;
}

void ModuleManager::KeyUp(int code)
{
    if(code < NUMKEYS && code > 0)
        keys_[code] = false;
}

void ModuleManager::UpdateModules(double elapsedTime_)
{
    DestroyModules();
    GameModulesList::iterator it = moduleList_.begin();
    GameModulesList::iterator itEnd = moduleList_.end();
    while (it != itEnd)
    {
        if((*it)->IsActive())
        {
            (*it)->HandleEvents();
            (*it)->Update(elapsedTime_);
        }
        it++;
    }
}
bool ModuleManager::Instantiate()
{
    mManager_ = new ModuleManager();
    return mManager_ != NULL;
}

void ModuleManager::Initialize()
{
    for(int i=0;i<NUMKEYS;++i)
    {
        keys_[i] = false;
    }
}

SDL_MouseButtonEvent* ModuleManager::Button()
{
    return mouseButtonEv_;
}

SDL_MouseMotionEvent* ModuleManager::Motion()
{
    return mouseMotionEv_;
}

void ModuleManager::InitializeGL()
{
    GameModulesList::iterator it = moduleList_.begin();
    GameModulesList::iterator itEnd = moduleList_.end();
    while (it != itEnd)
    {
        if((*it)->IsActive())
        {
            (*it)->SetupGL();
        }
        it++;
    }
}

void ModuleManager::MouseButtonDown(SDL_Event& event)
{
    mouseButtonEv_ = &event.button;
}

void ModuleManager::MouseMotion(SDL_Event& event)
{
    mouseMotionEv_ = &event.motion;
}

Uint8 ModuleManager::GetEventType()
{
    return type_;
}

int ModuleManager::GetMouseX()
{
    return mouseMotionEv_->x;
}

int ModuleManager::GetMouseY()
{
    return mouseMotionEv_->y;
}

Vector2D ModuleManager::GetMousePos()
{
    return Vector2D(GetMouseX(),GetMouseY());
}

void ModuleManager::SetType(Uint8 type)
{
    type_ = type;
}


