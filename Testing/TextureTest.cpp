#include "TextureTest.h"

using namespace TestingModuleNS;

TextureTest::TextureTest(const std::string& name) : GameModule(name)
{

}

void TextureTest::Initialize()
{


    v = new Vehicle(Vector2D(320,240),
                1.0,
                Vector2D(0.0,7.0),
                Vector2D(0.0,0.0),
                2.0,
                400.0,
                350.0,
                HalfPi,
                1.0);
    angle = 1.0;

    target = Vector2D(610,20);
}


void TextureTest::Destroy()
{
    delete v;
}

void TextureTest::UpdateModule(double elapsedTime_)
{
    v->Update(elapsedTime_);
//    if((int)v->GetVelocity().Length()!=0)
//        v->SetVelocity(v->GetVelocity()-Vector2D(0,1));
   //else
        //v->SetVelocity(Vector2D(0,0));
}

void TextureTest::RenderModule()
{

    v->Render();

    Graphics::SetColor(COLOR_GREEN);
    Graphics::DrawText(FontManager::Instance()->GetByName("arial11"),0,Engine::Instance()->GetHeight()-16,name_);
}

void TextureTest::ProcessEvent(SDL_Event* event)
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
                Vector2D oldSteer = v->GetVelocity();
                Vector2D temp = v->GetVelocity();
                temp.Normalize();
                v->SetVelocity(oldSteer+temp*16);
                //v->SetHeading(v->GetVelocity());
            }
            if(event->key.keysym.sym == SDLK_DOWN)
            {
                Vector2D oldSteer = v->GetVelocity();
                Vector2D temp = v->GetVelocity();
                temp.Normalize();
                v->SetVelocity(oldSteer-temp*163);
            }
            if(event->key.keysym.sym == SDLK_LEFT)
            {
                Matrix2D mat;
                //Vector2D vec = v->GetVelocity();
                Vector2D vecH = v->GetVelocity();
                //Vec2DRotateAroundO(vecH,angle);
                mat.Rotate(angle);
//
               //mat.Rotate(angle);
                mat.TransformVector(vecH);
//              / mat.TransformVector(vecH);
//                //v->SetVelocity(vec);
//                v->RotateHeadingToFacePosition(vecH);
                //v->SetSteeringForce(vecH);
                v->SetVelocity(vecH);
                angle=0.07;

            }
            break;
        }
        //case SDL_KEYUP
    }
}



