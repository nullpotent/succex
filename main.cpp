#include "Engine/Engine.h"
#include "SuccorR/GameWorld.h"
#include "Engine/XMLParser.h"
#include "2D/Transformations.h"
#include "Misc/CellSpacePartition.h"
#include "SuccorR/MainMenu.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if(XMLParser::Instantiate("Setup.xml"))
    {
        std::cout<<"XMLParser initialized"<<std::endl;
    }
    else
    {
        std::cout<<"XMLParser initialization failed"<<std::endl;
    }

    XMLParser::Instance()->ParseEngineParams();

    if(Engine::Instantiate() && Engine::Instance()->Create("2D Engine - Succor", EnginePrm.width, EnginePrm.height, EnginePrm.bpp, SDL_INIT_VIDEO, SDL_OPENGL | SDL_RESIZABLE, EnginePrm.fps, EnginePrm.fullscreen, EnginePrm.maindir))
    {
        std::cout << "Engine operational " << std::endl;
    }
    else
    {
        std::cout << "Something terrible happened " << "SDL ERROR: " << SDL_GetError() << std::endl << "OPENGL ERROR: " << glGetError() << std::endl;
        throw std::runtime_error ( "Game window could not be created " );
    }

    //ModuleManager::Instance()->AddModule(new TestingModuleNS::TestModule("Simple TEST1"));
    //ModuleManager::Instance()->AddModule(new TestingModuleNS::TextureTest("Texture TEST1"));
    //ModuleManager::Instance()->AddModule(new TestingModuleNS::TextureTest("Texture TEST2"));

    ModuleManager::Instance()->AddModule(new MainMenu("SuccorR Main Menu",true));

    Engine::Instance()->Run();

    delete Engine::Instance();
    delete XMLParser::Instance();

    return 0;

}
