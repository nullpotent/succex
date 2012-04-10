#pragma once
#include "Engine/Engine.h"
#include <stdlib.h>
#include "Managers/FontManager.h"
#include "xml/irrXML.h"
#include "Graphics/Font.h"
#include "Misc/Assert.h"
#include "2D/Wall2D.h"

#define ResPrm (*XMLParser::Instance())
#define EnginePrm (*XMLParser::Instance()).engineParams_

using namespace irr;
using namespace io;

class Vehicle;
class Enemy;
class GameWorld;
class BaseGameEntity;

struct SuccorRSetup
{
    int numSamplesForSmoothing;
};

//mozda bih je trebao particionisati (hot and cold optimizacija) zbog mogucih cache missed hitova
struct SteeringBehaviorsParams
{
    double steeringForceTweaker;
    double steeringForce;
    double agentMass;
    double maxSpeed;
    double agentScale;

    //this is used to tweak the amount that each steering
    //force contributes to the total steering force

    double separationWeight;
    double alignmentWeight;
    double cohesionWeight;
    double obstacleAvoidanceWeight;
    double wallAvoidanceWeight;
    double wanderWeight;
    double seekWeight;
    double fleeWeight;
    double arriveWeight;
    double pursuitWeight;
    double offsetPursuitWeight;
    double interposeWeight;
    double hideWeight;
    double evadeWeight;
    double followPathWeight;

    double viewDistance;

    //used in obstacle avoidance
    double obDetectionBox;

    //used in wall avoidance
    double wallDetectionFeelerLength;

    //these are the probabilities that a steering behavior
    //will be used when the Prioritized Dither calculate method
    //is used to sum combine behaviors

    double wallAvoidancePr;
    double obstacleAvoidancePr;
    double separationPr;
    double alignmentPr;
    double cohesionPr;
    double wanderPr;
    double seekPr;
    double fleePr;
    double evadePr;
    double hidePr;
    double arrivePr;

};

struct SuccorRLevel
{
    std::vector<Enemy*>           enemies;
    std::vector<Wall2D>           walls;
    std::vector<BaseGameEntity*>  obstacles;
    Vehicle*                      player;
    std::string                   name;
    std::string                   file;
    ~SuccorRLevel()
    {
        for(unsigned int i=0;i < enemies.size(); ++i)
        {
            delete enemies[i];
        }

        for(unsigned int i=0;i < obstacles.size(); ++i)
        {
            delete obstacles[i];
        }

        walls.clear();

        delete player;
    }
    /**
        std::vector<Path*> paths;
        std::vector<Region*> region;
    */
};

struct EngineParams
{
    int width;
    int height;
    char bpp;
    bool fullscreen;
    double fps;
    std::string maindir;
};

class XMLParser
{
    public:

        XMLParser();
        XMLParser(std::string file);
        virtual ~XMLParser();

        static bool Instantiate(std::string file = "Setup.xml");
        static XMLParser* Instance();

        void ParseEngineParams();
        void ParseFonts();
        void ParseSteeringBehaviorParams();
        /**
            Recursion
        */
        void ParseSuccorLevels(std::string file, GameWorld* world);
        void ParseSuccorLevel(std::string file, GameWorld* world);
        void PopulateLevel(SuccorRLevel& lev, GameWorld* world);
        EngineParams engineParams_;
        SteeringBehaviorsParams steeringBehParams_;

    private:

        std::string filename_;
        static XMLParser* xmlParserI_;
};
