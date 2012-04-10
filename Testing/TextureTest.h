#pragma once
#include "AI/Vehicle.h"
#include "Modules/GameModule.h"
#include "Graphics/GLCalls.h"
#include "2D/Vector2D.h"
#include "2D/Wall2D.h"
#include "2D/Matrix2D.h"
#include "Engine/Engine.h"
#include "2D/Vector2D.h"

namespace TestingModuleNS
{
class TextureTest : public GameModule
{
public:
    TextureTest(const std::string& name);
    virtual ~TextureTest();
    virtual void Initialize();
    virtual void Destroy();
    virtual void ProcessEvent(SDL_Event* event);
    virtual void RenderModule();
    virtual void UpdateModule(double elapsedTime_);
protected:

private:
    Vehicle* v;
    Vector2D target;
    float angle;
};

};
