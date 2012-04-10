#include "GameModule.h"
#include <iostream>


GameModule::GameModule() : active_(false)
{
    name_ = "";
    Initialize();
}

GameModule::~GameModule()
{
    Destroy();
}

GameModule::GameModule(std::string name, bool active) : active_(active), name_(name)
{
    Initialize();
    std::cout << "GameModule " << name_ << " initialized" << std::endl;
}

void GameModule::Destroy()
{
    std::cout << "GameModule " << name_ << " down" << std::endl;
}

void GameModule::Initialize()
{
    //REDEFINE
}

void GameModule::HandleEvents()
{

}

void GameModule::Render()
{

}

void GameModule::Update(double elapsedTime)
{

}

void GameModule::SetupGL()
{

}


