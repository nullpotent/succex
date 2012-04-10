#pragma once

#include "Game/BaseGameEntity.h"
#include "2D/Geometry.h"
#include "SuccorR/Vehicle.h"

/*
    Tests to see if an entity is overlapping any
    of a number of entities stored in a std container
*/
template<class T, class conT>
bool Overlapped(const T* ob, const conT& conOb, double minDistanceBetweenObstacles=40.0)
{
    typename conT::const_iterator it;

    for(it=conOb.begin();it!=conOb.end();++it)
    {
        if(TwoCirclesOverlapped(ob->GetPos(),ob->GetBRadius()+minDistanceBetweenObstacles,(*it)->GetPos(),(*it)->GetBRadius()))
        {
            return true;
        }
    }
    return false;
}

/*
    Tags any entities contained in a std container that
    are within the radius of the single entity parameter
*/
template<class T, class conT>
void TagNeighbours(T* entity, conT& others, const double radius)
{
    typename conT::iterator it;

    for(it=others.begin();it!=others.end();++it)
    {
        (*it)->UnTag();
        Vector2D to = (*it)->GetPos() - entity->GetPos();
        double range = radius + (*it)->GetBRadius();

        if(((*it) != entity) && (to.LengthSq() < range*range))
        {
            (*it)->Tag();
        }
    }
}

/*
    Given a pointer to an entity and a std container of pointer
    to nearby entites, this function checks to see if there is an overlap
    between entities. If there is, then the entities are moved away from each other
*/

template <class T, class conT>
void EnforceNonPenetrationConstraint(const T&    entity,
                                     const conT& ContainerOfEntities)
{
  //iterate through all entities checking for any overlap of bounding radii
  for (typename conT::const_iterator curEntity = ContainerOfEntities.begin();
       curEntity != ContainerOfEntities.end();
       ++curEntity)
  {
    //make sure we don't check against the individual
    if (*curEntity == entity) continue;

    //calculate the distance between the positions of the entities
    Vector2D ToEntity = entity->GetPos() - (*curEntity)->GetPos();

    double DistFromEachOther = ToEntity.Length();

    //if this distance is smaller than the sum of their radii then this
    //entity must be moved away in the direction parallel to the
    //ToEntity vector
    double AmountOfOverLap = (*curEntity)->GetBRadius() + entity->GetBRadius() -
                             DistFromEachOther;

    if (AmountOfOverLap >= 0.0)
    {
      //move the entity a distance away equivalent to the amount of overlap.
      entity->SetPos(entity->GetPos() + (ToEntity/DistFromEachOther) *
                     AmountOfOverLap);
    }
  }//next entity
}

template<class T, class conT>
std::list<T> GetEntityLineSegmentIntersections(const conT& entities,
                                               int         toIgnore,
                                               Vector2D    A,
                                               Vector2D    B,
                                               double range = MaxDouble)
{
    typename conT::const_iterator it;

    std::list<T> hits;

    for(it=entities.begin(); it != entities.end(); ++it)
    {
        if( ((*it)->GetID() == toIgnore) || (Vec2DDistanceSq((*it)->GetPos(),A) > range*range) )
        {
            continue;
        }

        if(DistToLineSegment(A,B,(*it)->GetPos()) < (*it)->GetBRadius())
        {
            hits.push_back(*it);
        }
    }

    return hits;
}

template<class T, class conT>

T*  GetClosestEntityLineSegmentIntersection(const conT&     entities,
                                            int             toIgnore,
                                            Vector2D        A,
                                            Vector2D        B,
                                            double          range = MaxDouble)
{
    typename conT::const_iterator it;

    T* closestE = NULL;

    double closestDist = MaxDouble;

    for(it=entities.begin(); it != entities.end(); ++it)
    {
        double distSq = Vec2DDistanceSq((*it)->GetPos(),A);

        if( ((*it)->GetID() == toIgnore) || (distSq > range*range) )
        {
            continue;
        }

        if(DistToLineSegment(A,B,(*it)->GetPos()) < (*it)->GetBRadius())
        {
            if(distSq < closestDist)
            {
                closestDist = distSq;
                closestE    = *it;
            }
        }
    }

    return closestE;

}

