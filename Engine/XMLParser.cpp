#include "XMLParser.h"

#include "Game/BaseGameEntity.h"
#include "SuccorR/Enemy.h"
#include "SuccorR/Vehicle.h"
#include "SuccorR/Obstacle.h"

XMLParser* XMLParser::xmlParserI_ = NULL;

XMLParser::XMLParser()
{
    filename_ = "Setup.xml";
}

XMLParser::XMLParser(std::string file)
{
    filename_ = file;
}

XMLParser::~XMLParser()
{

}

XMLParser* XMLParser::Instance()
{
    Assert(xmlParserI_ != NULL);
    return xmlParserI_;
}

bool XMLParser::Instantiate(std::string file)
{
    xmlParserI_ = new XMLParser(file);
    return xmlParserI_ != NULL;
}

void XMLParser::ParseEngineParams()
{
    IrrXMLReader* xml = createIrrXMLReader(filename_.c_str());

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case EXN_ELEMENT:
            if(!strcmp("engine",xml->getNodeName()))
            {
                engineParams_.maindir = xml->getAttributeValue("resources");
                engineParams_.width = atoi(xml->getAttributeValue("width"));
                engineParams_.height = atoi(xml->getAttributeValue("height"));
                engineParams_.bpp = atoi(xml->getAttributeValue("bpp"));
                engineParams_.fullscreen = (!strcmp("true",xml->getAttributeValue("fullscreen"))?true:false);
                engineParams_.fps = atof(xml->getAttributeValue("fps"));
            }
        }
    }
    delete xml;
}

void XMLParser::ParseFonts()
{
    IrrXMLReader* xml = createIrrXMLReader(filename_.c_str());
    FontManager::Instance()->Destroy();
    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case EXN_ELEMENT:
            if(!strcmp("font",xml->getNodeName()))
            {
                FontDesc* temp = new FontDesc;
                std::string dir = xml->getAttributeValue("dir");
                std::string tempName = xml->getAttributeValue("name");
                std::string tempSize = xml->getAttributeValue("size");
                std::cout<<tempName<<"------------"<<tempSize<<std::endl;
                temp->font = new Font(dir+tempName+".ttf",atoi(tempSize.c_str()));
                temp->name = tempName + tempSize;
                FontManager::Instance()->AddFontToList(temp);
            }
        }
    }
    delete xml;
}

void XMLParser::ParseSteeringBehaviorParams()
{
    IrrXMLReader* xml = createIrrXMLReader(filename_.c_str());

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case EXN_ELEMENT:
        {
            if(!strcmp("steeringBehaviors",xml->getNodeName()))
            {
                steeringBehParams_.steeringForceTweaker = atof(xml->getAttributeValue("SteeringForceTweaker"));
                steeringBehParams_.steeringForce = atof(xml->getAttributeValue("SteeringForce"));
                steeringBehParams_.maxSpeed = atof(xml->getAttributeValue("MaxSpeed"));
                steeringBehParams_.agentMass = atof(xml->getAttributeValue("AgentMass"));
                steeringBehParams_.agentScale = atof(xml->getAttributeValue("AgentScale"));

                steeringBehParams_.separationWeight = atof(xml->getAttributeValue("SeparationWeight"));
                steeringBehParams_.alignmentWeight = atof(xml->getAttributeValue("AlignmentWeight"));
                steeringBehParams_.cohesionWeight = atof(xml->getAttributeValue("CohesionWeight"));
                steeringBehParams_.obstacleAvoidanceWeight = atof(xml->getAttributeValue("ObstacleAvoidanceWeight"));
                steeringBehParams_.wallAvoidanceWeight = atof(xml->getAttributeValue("WallAvoidanceWeight"));
                steeringBehParams_.wanderWeight = atof(xml->getAttributeValue("WanderWeight"));
                steeringBehParams_.seekWeight = atof(xml->getAttributeValue("SeekWeight"));
                steeringBehParams_.fleeWeight = atof(xml->getAttributeValue("FleeWeight"));
                steeringBehParams_.arriveWeight = atof(xml->getAttributeValue("ArriveWeight"));
                steeringBehParams_.pursuitWeight = atof(xml->getAttributeValue("PursuitWeight"));
                steeringBehParams_.offsetPursuitWeight = atof(xml->getAttributeValue("OffsetPursuitWeight"));
                steeringBehParams_.interposeWeight = atof(xml->getAttributeValue("InterposeWeight"));
                steeringBehParams_.hideWeight = atof(xml->getAttributeValue("HideWeight"));
                steeringBehParams_.evadeWeight = atof(xml->getAttributeValue("EvadeWeight"));
                steeringBehParams_.followPathWeight = atof(xml->getAttributeValue("FollowPathWeight"));

                steeringBehParams_.viewDistance = atof(xml->getAttributeValue("ViewDistance"));
                steeringBehParams_.obDetectionBox = atof(xml->getAttributeValue("ObDetectionBoxLength"));
                steeringBehParams_.wallDetectionFeelerLength = atof(xml->getAttributeValue("WallDetectionFeelerLengt"));

                steeringBehParams_.wallAvoidancePr = atof(xml->getAttributeValue("WallAvoidancePr"));
                steeringBehParams_.obstacleAvoidancePr = atof(xml->getAttributeValue("ObstacleAvoidancePr"));
                steeringBehParams_.separationPr = atof(xml->getAttributeValue("SeparationPr"));
                steeringBehParams_.alignmentPr = atof(xml->getAttributeValue("AlignmentPr"));
                steeringBehParams_.cohesionPr = atof(xml->getAttributeValue("CohesionPr"));
                steeringBehParams_.wanderPr = atof(xml->getAttributeValue("WanderPr"));
                steeringBehParams_.seekPr = atof(xml->getAttributeValue("SeekPr"));
                steeringBehParams_.fleePr = atof(xml->getAttributeValue("FleePr"));
                steeringBehParams_.evadePr = atof(xml->getAttributeValue("EvadePr"));
                steeringBehParams_.hidePr = atof(xml->getAttributeValue("HidePr"));
                steeringBehParams_.arrivePr = atof(xml->getAttributeValue("ArrivePr"));
            }
            break;
        }
        }
    }
    delete xml;
}

void XMLParser::ParseSuccorLevels(std::string file, GameWorld* world)
{

    IrrXMLReader* xml = createIrrXMLReader(file.c_str());

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case EXN_ELEMENT:
        {
            if(!strcmp("level", xml->getNodeName()))
            {
                std::string levelFile = xml->getAttributeValue("file");
                Assert(levelFile != "")
                ParseSuccorLevel(levelFile,world);
                std::cout<<"Loaded level: "<<levelFile<<std::endl;
            }
            break;
        }
        }
    }
    delete xml;
}

void XMLParser::ParseSuccorLevel(std::string file, GameWorld* world)
{
    IrrXMLReader* xml = createIrrXMLReader(file.c_str());
    //SuccorRLevel* lev = new SuccorRLevel;
    SuccorRLevel* lev = NULL;
    Enemy*        leader = NULL;
    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case EXN_ELEMENT:
        {
            if(!strcmp("world",xml->getNodeName()))
            {
                lev = new SuccorRLevel;
                lev->name = xml->getAttributeValue("name");
                lev->file = file;
                lev->obstacles.clear();
                lev->enemies.clear();
                if(lev!=NULL)
                world->LoadLevel(lev);
            }
            else if(!strcmp("player",xml->getNodeName()))
            {
                Vehicle* player = new Vehicle(world,
                                              Vector2D(atof(xml->getAttributeValue("PositionX")),atof(xml->getAttributeValue("PositionY"))),
                                              atof(xml->getAttributeValue("Rotation")),
                                              Vector2D(atof(xml->getAttributeValue("VelocityX")),atof(xml->getAttributeValue("VelocityY"))),
                                              Vector2D(atof(xml->getAttributeValue("ForceX")),atof(xml->getAttributeValue("ForceY"))),
                                              atof(xml->getAttributeValue("Mass")),
                                              atof(xml->getAttributeValue("MaxForce")),
                                              atof(xml->getAttributeValue("MaxSpeed")),
                                              atof(xml->getAttributeValue("MaxTurnRate")),
                                              atof(xml->getAttributeValue("Scale")),
                                              atoi(xml->getAttributeValue("Bullets"))
                                             );
                lev->player = player;
            }
            else if(!strcmp("obstacle",xml->getNodeName()))
            {

                Obstacle* ob = new Obstacle(atof(xml->getAttributeValue("X")),
                                            atof(xml->getAttributeValue("Y")),
                                            atof(xml->getAttributeValue("Radius"))
                                           );

                lev->obstacles.push_back(ob);

            }
            else if(!strcmp("enemy",xml->getNodeName()))
            {
                Enemy* enemy = new Enemy(world,
                                         Vector2D(atoi(xml->getAttributeValue("PositionX")),atof(xml->getAttributeValue("PositionY"))),
                                         atof(xml->getAttributeValue("Rotation")),
                                         Vector2D(atof(xml->getAttributeValue("VelocityX")),atof(xml->getAttributeValue("VelocityY"))),
                                         atof(xml->getAttributeValue("Mass")),
                                         atof(xml->getAttributeValue("MaxForce")),
                                         atof(xml->getAttributeValue("MaxSpeed")),
                                         atof(xml->getAttributeValue("MaxTurnRate")),
                                         atof(xml->getAttributeValue("Scale"))
                                        );

                std::string steering = xml->getAttributeValue("Steering");
                std::string type = xml->getAttributeValue("Type");

                enemy->Steering()->SetOffset(Vector2D(0.0,10.0));

                if(type.compare("Leader")==0)
                {
                    enemy->IsLeader();
                    leader = enemy;
                }

                if(steering.compare("Seek")==0)
                {
                    enemy->Steering()->SeekOn();
                }
                else if(steering.compare("Flee")==0)
                {
                    enemy->Steering()->FleeOn();
                }
                else if(steering.compare("Evade")==0)
                {
                    enemy->Steering()->EvadeOn();
                }
                else if(steering.compare("Hide")==0)
                {
                    enemy->Steering()->HideOn();
                }
                else if(steering.compare("Arrive")==0)
                {
                    enemy->Steering()->ArriveOn();
                }
                else if(steering.compare("Pursuit")==0)
                {
                    enemy->Steering()->PursuitOn();
                }
                else if(steering.compare("OffsetPursuit")==0 && leader != NULL)
                {
                    Assert(leader != NULL);
                    enemy->Steering()->SetTargetAgent1(leader);
                    enemy->Steering()->OffsetPursuitOn();
                }

                enemy->Steering()->ObstacleAvoidanceOn();
                enemy->Steering()->WallAvoidanceOn();
                //enemy->Steering()->SeparationOn();

                lev->enemies.push_back(enemy);
            }
            break;
        }
        }

        //world->LoadLevel(lev);
    }

    delete xml;
}

void XMLParser::PopulateLevel(SuccorRLevel& lev, GameWorld* world)
{
    IrrXMLReader* xml = createIrrXMLReader(lev.file.c_str());
    Enemy*        leader = NULL;

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case EXN_ELEMENT:
        {
            if(!strcmp("world",xml->getNodeName()))
            {
                lev.name = xml->getAttributeValue("name");
                lev.obstacles.clear();
                lev.enemies.clear();
            }
            else if(!strcmp("player",xml->getNodeName()))
            {
                Vehicle* player = new Vehicle(world,
                                              Vector2D(atof(xml->getAttributeValue("PositionX")),atof(xml->getAttributeValue("PositionY"))),
                                              atof(xml->getAttributeValue("Rotation")),
                                              Vector2D(atof(xml->getAttributeValue("VelocityX")),atof(xml->getAttributeValue("VelocityY"))),
                                              Vector2D(atof(xml->getAttributeValue("ForceX")),atof(xml->getAttributeValue("ForceY"))),
                                              atof(xml->getAttributeValue("Mass")),
                                              atof(xml->getAttributeValue("MaxForce")),
                                              atof(xml->getAttributeValue("MaxSpeed")),
                                              atof(xml->getAttributeValue("MaxTurnRate")),
                                              atof(xml->getAttributeValue("Scale")),
                                              atoi(xml->getAttributeValue("Bullets"))
                                             );
                lev.player = player;
            }
            else if(!strcmp("obstacle",xml->getNodeName()))
            {

                Obstacle* ob = new Obstacle(atof(xml->getAttributeValue("X")),
                                            atof(xml->getAttributeValue("Y")),
                                            atof(xml->getAttributeValue("Radius"))
                                           );

                lev.obstacles.push_back(ob);

            }
            else if(!strcmp("enemy",xml->getNodeName()))
            {
                Enemy* enemy = new Enemy(world,
                                         Vector2D(atoi(xml->getAttributeValue("PositionX")),atof(xml->getAttributeValue("PositionY"))),
                                         atof(xml->getAttributeValue("Rotation")),
                                         Vector2D(atof(xml->getAttributeValue("VelocityX")),atof(xml->getAttributeValue("VelocityY"))),
                                         atof(xml->getAttributeValue("Mass")),
                                         atof(xml->getAttributeValue("MaxForce")),
                                         atof(xml->getAttributeValue("MaxSpeed")),
                                         atof(xml->getAttributeValue("MaxTurnRate")),
                                         atof(xml->getAttributeValue("Scale"))
                                        );

                std::string steering = xml->getAttributeValue("Steering");

                std::string type = xml->getAttributeValue("Type");
                enemy->Steering()->SetOffset(Vector2D(0.0,10.0));

                if(type.compare("Leader")==0)
                {
                    enemy->IsLeader();
                    leader = enemy;
                }

                if(steering.compare("Seek")==0)
                {
                    enemy->Steering()->SeekOn();
                }
                else if(steering.compare("Flee")==0)
                {
                    enemy->Steering()->FleeOn();
                }
                else if(steering.compare("Evade")==0)
                {
                    enemy->Steering()->EvadeOn();
                }
                else if(steering.compare("Hide")==0)
                {
                    enemy->Steering()->HideOn();
                }
                else if(steering.compare("Arrive")==0)
                {
                    enemy->Steering()->ArriveOn();
                }
                else if(steering.compare("Pursuit")==0)
                {
                    enemy->Steering()->PursuitOn();
                }
                else if(steering.compare("OffsetPursuit")==0 && leader != NULL)
                {
                    Assert(leader != NULL);
                    enemy->Steering()->SetTargetAgent1(leader);
                    enemy->Steering()->OffsetPursuitOn();
                }

                enemy->Steering()->ObstacleAvoidanceOn();
                enemy->Steering()->WallAvoidanceOn();
                //enemy->Steering()->CohesionOn();

                lev.enemies.push_back(enemy);
            }
            break;
        }
        }

    }

    delete xml;
}
