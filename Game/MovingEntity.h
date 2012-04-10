#pragma once

#include "Misc/Assert.h"
#include "Game/BaseGameEntity.h"

class MovingEntity : public BaseGameEntity
{
    protected:

        Vector2D velocity_;

        //normalizovani vektor koji je usmeren u pravcu kretanja vozila
        Vector2D heading_;

        //vektor perpendikularan na heading_ vektor
        Vector2D side_;

        double mass_;
        double maxSpeed_;
        double maxForce_;
        double maxTurnRate_;

    public:

        MovingEntity(Vector2D position,
                     double radius,
                     Vector2D velocity,
                     double maxSpeed,
                     Vector2D heading,
                     double mass,
                     Vector2D scale,
                     double turnRate,
                     double maxForce) : BaseGameEntity(0, position, radius),
                                                       heading_(heading),
                                                       velocity_(velocity),
                                                       mass_(mass),
                                                       side_(heading.Perp()),
                                                       maxSpeed_(maxSpeed),
                                                       maxTurnRate_(turnRate),
                                                       maxForce_(maxForce)
        {
            scale_ = scale;
        }

        virtual ~MovingEntity() {}

        //ACCESSORS
        Vector2D GetVelocity() const { return velocity_; }
        void     SetVelocity(const Vector2D& vel) { velocity_ = vel; }

        double   GetMass() const { return mass_; }

        Vector2D GetSide() const { return side_; }

        double   GetMaxSpeed() const { return maxSpeed_; }
        void     SetMaxSpeed(double newSpeed) { maxSpeed_ = newSpeed; }

        double   GetMaxForce() const { return maxForce_; }
        void     SetMaxForce(double newForce) { maxForce_ = newForce; }

        bool     IsSpeedMaxedOut() const { return maxSpeed_*maxSpeed_ >= velocity_.LengthSq(); }

        double   GetSpeed() const { return velocity_.Length(); }
        double   GetSpeedSq() const { return velocity_.LengthSq(); }

        Vector2D GetHeading() const { return heading_; }
        void     SetHeading(Vector2D newHeading);
        bool     RotateHeadingToFacePosition(Vector2D target);

        double   GetMaxTurnRate() const { return maxTurnRate_; }
        void     SetMaxTurnRate(double val) { maxTurnRate_ = val; }

};
/*
    Given a target position, this function rotates the entity's heading
    and side vectors by an amount not greater than maxTurnRate_ until it
    directly faces the target.

    Returns true when the heading is facing in the desired direction
*/
inline bool MovingEntity::RotateHeadingToFacePosition(Vector2D target)
{
    Vector2D toTarget = Vec2DNormalize(target - position_);

    double dot = heading_.Dot(toTarget);

    Clamp(dot,-1,1);

    double angle = acos(dot);

    if(angle < 0.00001) return true;

    if(angle > maxTurnRate_) angle = maxTurnRate_;

    Matrix2D rotationMat;
    rotationMat.Rotate(angle * heading_.Sign(toTarget));
    rotationMat.TransformVector(heading_);
    rotationMat.TransformVector(velocity_);

    side_ = heading_.Perp();

    return false;
}

inline void MovingEntity::SetHeading(Vector2D newHeading)
{
    Assert((newHeading.LengthSq()-1.0) < 0.00001);
    heading_ = newHeading;
    side_ = heading_.Perp();
}
