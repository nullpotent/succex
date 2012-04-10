#pragma once

/**
    Description:

    Class to divide a 2D space into a grid of cells each of which
    may contain a number of entities. Once created and initialized
    with entities, fast proximity querys can be made by calling the
    CalculateNeighbors method with a position and proximity radius.

    If an entity is capable of moving, and therefore capable of moving
    between cells, the Update method should be called each update-cycle
    to sychronize the entity and the cell space it occupies

*/

#pragma warning(disable:4786)

#include <vector>
#include <list>
#include "Misc/Assert.h"

#include "2D/Vector2D.h"
#include "2D/IBBox2D.h"
#include "Misc/Utils.h"
#include "Graphics/GLCalls.h"

template <class entity>

struct Cell
{
    //clanovi celije
    std::list<entity> members_;
    IBBox2D bBox_;
    Cell(Vector2D topLeft, Vector2D botRight) : bBox_(IBBox2D(topLeft,botRight)) {}
};

template <class entity>
class CellSpacePartition
{
    private:

        std::vector<Cell<entity> >   cells_;
        std::vector<entity>         neighbours_;

        //iterator za prolazenje kroz listu komsija
        typename std::vector<entity>::iterator curNeighbour_;

        double spaceWidth_;
        double spaceHeight_;

        double cellSizeX_;
        double cellSizeY_;

        int numCellsX_;
        int numCellsY_;

        inline int PositionToIndex(const Vector2D& pos) const;

    public:

        CellSpacePartition(double width,
                           double height,
                           int cellsX,
                           int cellsY,
                           int maxEntities);

        inline void AddEntity(const entity& ent);
        inline void UpdateEntity(const entity& ent, Vector2D& oldPos);
        inline void CalculateNeighbours(Vector2D targetPos, double searchRadius);

        inline entity& Begin()
        {
            curNeighbour_ = neighbours_.begin();
            return curNeighbour_;
        }

        inline entity& Next()
        {
            ++curNeighbour_;
            return curNeighbour_;
        }

        inline bool End()
        {
            return ((curNeighbour_==neighbours_.end()) || (*curNeighbour_==0));
        }

        void EmptyCells();

        inline void RenderCells() const;
};

template<class entity>
CellSpacePartition<entity>::CellSpacePartition(double width,
                                               double height,
                                               int cellsX,
                                               int cellsY,
                                               int maxEntities) :

                                               spaceWidth_(width),
                                               spaceHeight_(height),
                                               numCellsX_(cellsX),
                                               numCellsY_(cellsY),
                                               neighbours_(maxEntities,entity())
{
    cellSizeX_  = width  / cellsX;
    cellSizeY_  = height / cellsY;

    for(int i=0;i<numCellsY_;++i)
    {
        for(int j=0;j<numCellsX_;++j)
        {
            double left  = i * cellSizeX_;
            double right = left + cellSizeX_;
            double top   = j * cellSizeY_;
            double bot   = top + cellSizeY_;

            cells_.push_back(Cell<entity>(Vector2D(left,top),Vector2D(right,bot)));
        }
    }
}

template<class entity>
void CellSpacePartition<entity>::CalculateNeighbours(Vector2D targetPos, double searchRadius)
{
    typename std::vector<entity>::iterator curNBor = neighbours_.begin();
    IBBox2D searchBox(targetPos - Vector2D(searchRadius,searchRadius),
                      targetPos + Vector2D(searchRadius,searchRadius));

    typename std::vector<Cell<entity> >::iterator curCell;

    for(curCell=cells_.begin(); curCell!=cells_.end(); ++curCell)
    {
        if(curCell->bBox_.OverlappesWith(searchBox) &&
          !curCell->members_.empty())
        {
            typename std::list<entity>::iterator it  = curCell->members_.begin();
            for(it; it != curCell->members_.end(); ++it)
            {
                if(Vec2DDistanceSq((*it)->GetPos(),targetPos) < searchRadius*searchRadius)
                {
                    *curNBor++ = *it;
                }
            }
        }
    }
    *curNBor = 0;
}

template<class entity>
void CellSpacePartition<entity>::EmptyCells()
{
    typename std::vector<Cell<entity> >::iterator it = cells_.begin();
    for(it;it!=cells_.end();++it)
    {
        it->members_.clear();
    }
}

template<class entity>
inline int CellSpacePartition<entity>::PositionToIndex(const Vector2D& pos) const
{
    int idx = (int)(numCellsX_ * pos.x_ / spaceWidth_) + ((int)(numCellsY_ * pos.y_ / spaceHeight_) * numCellsX_);

    if(idx > cells_.size()-1)
    {
        idx = cells_.size() - 1;
    }

    return idx;
}

template<class entity>
inline void CellSpacePartition<entity>::AddEntity(const entity& ent)
{
    Assert(ent != NULL);
    int s = cells_.size();
    int idx = PositionToIndex(ent->GetPos());
    cells_[idx].members_.push_back(ent);
}

template<class entity>
inline void CellSpacePartition<entity>::UpdateEntity(const entity& ent, Vector2D& oldPos)
{
    int oldIdX = PositionToIndex(oldPos);
    int newIdX = PositionToIndex(ent->GetPos());
    if(newIdX == oldIdX)
    {
        return;
    }
    cells_[oldIdX].members_.remove(ent);
    cells_[newIdX].members_.push_back(ent);
}

template<class entity>
inline void CellSpacePartition<entity>::RenderCells() const
{
    typename std::vector<Cell<entity> >::const_iterator curCel;
    for(curCel=cells_.begin();curCel!=cells_.end();++curCel)
    {
        curCel->bBox_.Render(false);
    }
}

