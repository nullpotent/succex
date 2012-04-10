#include "SimpleTests.h"


using namespace TestingModuleNS;

TestModule::TestModule(const std::string& name) :
    timeAcc_ ( 0.0f )
{
    name_ = name;
    std::cout << "GameModule " << name_ << " initialized" << std::endl;
    Initialize();
}

TestModule::~TestModule()
{
    Destroy();
}

void TestModule::Initialize()
{
    wall = Wall2D(Vector2D(30,100),Vector2D(150,100));
    tempV = wall.From();
    angle = 0.0;
    reg_ = Region(0,150,200,300,22);
}

void TestModule::Destroy()
{
    std::cout << "GameModule " << name_ << " down" << std::endl;
}

void TestModule::UpdateModule(double elapsedTime_)
{

        wall.SetFrom(tempV);
        wall.SetTo(tempC);


}

void TestModule::RenderModule()
{

    wall.Render(true);


    reg_.Render(true);
    Graphics::SetColor(COLOR_GREEN);
    Graphics::DrawText(FontManager::Instance()->GetByName("arial9"),0,Engine::Instance()->GetHeight()-16,name_);
}

void TestModule::ProcessEvent(SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            if(event->button.button == 4)
            {

            }
            else if(event->button.button == 5)
            {

            }
            break;
        }
        case SDL_KEYDOWN:
        {
            if(event->key.keysym.sym == SDLK_UP)
            {
                tempC = wall.To();
                tempV = wall.From();
                Vec2DRotateAroundO(tempV,angle);
                Vec2DRotateAroundO(tempC,angle);
                angle = angle + 0.01;
            }
            else if(event->key.keysym.sym == SDLK_DOWN)
            {
                std::cout<<"e lol";
                tempV.x_ = ++wall.From().x_;
                tempV.y_ = ++wall.From().y_;
            }
            break;
        }
    }
}



