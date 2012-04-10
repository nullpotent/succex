#pragma once

#include "../Modules/GameModule.h"
#include "../Graphics/GLCalls.h"
#include "../2D/Vector2D.h"
#include "../2D/Wall2D.h"
#include "../2D/Matrix2D.h"
#include "../Engine/Engine.h"
#include "Game/Region.h"
#include "2D/Transformations.h"

namespace TestingModuleNS
{
class TestModule : public GameModule
{
public:
    TestModule(const std::string& name);
    virtual ~TestModule();
    virtual void Initialize();
    virtual void Destroy();
    virtual void ProcessEvent(SDL_Event* event);
    virtual void RenderModule();
    virtual void UpdateModule(double elapsedTime_);
protected:

private:
    Wall2D wall;
    Vector2D tempV,tempC;
    double timeAcc_;
    double angle;
    Matrix2D mat;
    Region reg_;
};

};
