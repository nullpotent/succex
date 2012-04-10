#pragma once

#pragma warning(disable:4786)

#include <vector>
#include <string>
#include <iosfwd>
#include "2D/Vector2D.h"
#include "2D/Geometry.h"
#include "Misc/Utils.h"

struct Telegram;

class BaseGameEntity
{
    public:

        enum {default_ent_type = -1};

    private:

        int id_;
        int entityType_;
        bool tag_;

    protected:

        Vector2D position_;
        Vector2D scale_;
        double boundingRadius_;
        BaseGameEntity(int entType);
        BaseGameEntity();
        BaseGameEntity(int entType, Vector2D pos, double r);
        BaseGameEntity(int entType, int forcedID);

    public:

        virtual ~BaseGameEntity(){}
        virtual void Update(){}
        virtual void Render()=0;

        virtual bool HandleMessage(const Telegram& msg)
        {
            return false;
        }

        virtual void Write(std::ostream& os) const {}
        virtual void Read(std::ifstream& is) {}

        static int GetNextValidID()
        {
            static int nextValidID_ = 0;
            return nextValidID_++;
        }

        Vector2D GetPos() const
        {
            return position_;
        }

        void SetPos(Vector2D newPos)
        {
            position_ = newPos;
        }

        double GetBRadius() const
        {
            return boundingRadius_;
        }

        void SetBRadius(double radius)
        {
            boundingRadius_ = radius;
        }

        int GetID()
        {
            return id_;
        }

        bool IsTagged() const
        {
            return tag_;
        }

        void Tag()
        {
            tag_ = true;
        }

        void UnTag()
        {
            tag_ = false;
        }

        Vector2D GetScale() const
        {
            return scale_;
        }

        void SetScale(Vector2D newScale)
        {
            boundingRadius_ *= MaxOf(newScale.x_, newScale.y_) / MaxOf(scale_.x_,scale_.y_);
            scale_ = newScale;
        }

        void SetScale(double val)
        {
            boundingRadius_ *= val / MaxOf(scale_.x_,scale_.y_);
            scale_ = Vector2D(val,val);
        }

        int GetEntityType() const
        {
            return entityType_;
        }

        void SetEntityType(int newType)
        {
            entityType_ = newType;
        }

};
