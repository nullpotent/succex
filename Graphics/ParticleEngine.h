#pragma once
#include "Particle.h"
#include <list>
#include "Misc/Utils.h"
#include <deque>
#include <algorithm>

#define TOTAL 20

typedef std::deque<Particle*> ParticlesList;

class ParticleEngine
{
    private:

        Vector2D            emitterPos_;
        ParticlesList       particles_;

    public:

        const Vector2D GetEmitterPos() const
        {
            return emitterPos_;
        }

        void SetEmitterPos(Vector2D pos)
        {
            emitterPos_ = pos;
        }

        ParticleEngine(Vector2D emPos) : emitterPos_(emPos)
        {
            particles_.clear();
        }

        ~ParticleEngine()
        {
            while(particles_.begin() != particles_.end())
            {
                Particle* part = particles_.front();
                particles_.pop_front();
                delete part;
            }
            particles_.clear();
        }

        void CreateParticles()
        {
            for(int i=0; i < TOTAL; ++i)
            {
                particles_.push_back(GenerateNewParticle());
            }
        }

        void CreateExplosionParticles()
        {
            for(int i=0; i < 160; ++i)
            {
                particles_.push_back(GenerateExplosionParticle());
            }
        }

        bool DoneRendering()
        {
            return particles_.size()==0;
        }

        void Update(double elapsedTime)
        {

            ParticlesList::iterator it = particles_.begin();

            while(it!=particles_.end())
            {
                (*it)->Update(elapsedTime);
                if((*it)->GetTTL()<=0)
                {
                    delete *it;
                    it = particles_.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }


    private:

        Particle*   GenerateNewParticle()
        {
            Vector2D pos = emitterPos_;

            Vector2D vel = Vector2D(1.0 * RandInRange(0.3,1.0) * 2 - 1,
                                    1.0 * RandInRange(0.3,1.0) * 2 - 1);
            double angle = 0.0;
            double angV = RandInRange(0.0,0.0);

            rgb_struct<float> color = rgb_struct<float>(RandInRange(0.0,0.2), RandInRange(0.0,0.2), RandInRange(0.0,0.2));

            double size = RandInRange(1.0,4.0);

            int ttl = 5 + RandInRange(2.0,5.0);

            return new Particle(pos,vel,angle,angV,color,size,ttl);
        }

        Particle*   GenerateExplosionParticle()
        {
            Vector2D pos = emitterPos_;

            Vector2D vel = Vector2D(1.0 * RandInRange(0.7,1.3) * 2 - 1,
                                    1.0 * RandInRange(0.7,1.3) * 2 - 1);
            double angle = 0.0;
            double angV = RandInRange(0.1,0.2);

            rgb_struct<float> color = rgb_struct<float>(RandInRange(0.7,1.0), RandInRange(0.0,0.4), RandInRange(0.0,0.4));

            double size = RandInRange(2.0,6.0);

            int ttl = RandInRange(20.0,45.0);

            return new Particle(pos,vel,angle,angV,color,size,ttl);
        }

    public:

        void Render()
        {
            ParticlesList::iterator it = particles_.begin();
            ParticlesList::iterator itEnd = particles_.end();

            while(it!=itEnd)
            {
                (*it)->Render();
                it++;
            }
        }
};
