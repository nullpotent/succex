#pragma once

#include <vector>
#include "Matrix2D.h"

inline std::vector<Vector2D> WorldTransform(std::vector<Vector2D>& points,
                                            const Vector2D&        pos,
                                            const Vector2D&        forward,
                                            const Vector2D&        side,
                                            const Vector2D&        scale)
{
    std::vector<Vector2D> tranVector2DS = points;
    Matrix2D matTrans;

    if((scale.x_ != 1.0) || (scale.y_ != 1.0))
    {
        matTrans.Scale(scale.x_, scale.y_);
    }

    matTrans.Rotate(forward,side);
    matTrans.Translate(pos.x_,pos.y_);

    matTrans.TransformVectors(tranVector2DS);

    return tranVector2DS;
}

inline std::vector<Vector2D> WorldTransform(std::vector<Vector2D>& points,
                                            const Vector2D&        pos,
                                            const Vector2D&        forward,
                                            CONST Vector2D&        side)
{
    std::vector<Vector2D> tranVectors = points;
    Matrix2D matTrans;
    matTrans.Rotate(forward,side);
    matTrans.Translate(pos.x_,pos.y_);

    matTrans.TransformVectors(tranVectors);

    return tranVectors;
}

inline Vector2D PointToWorldSpace(const Vector2D& point,
                                  const Vector2D& forward,
                                  const Vector2D& side,
                                  const Vector2D& pos)
{
    Vector2D transPoint = point;
    Matrix2D matTrans;
    matTrans.Rotate(forward,side);
    matTrans.Translate(pos.x_,pos.y_);

    matTrans.TransformVector(transPoint);

    return transPoint;
}

inline Vector2D VectorToWorldSpace(const Vector2D& vec,
                                   const Vector2D& forward,
                                   const Vector2D& side)
{
    Vector2D transVec = vec;
    Matrix2D matTrans;
    matTrans.Rotate(forward,side);
    matTrans.TransformVector(transVec);

    return transVec;
}

inline Vector2D PointToLocalSpace(const Vector2D& point,
                                  const Vector2D&       forward,
                                  const Vector2D&       side,
                                  const Vector2D&       pos)
{
    Vector2D transPoint = point;
    Matrix2D matTrans;

    double tx = -pos.Dot(forward);
    double ty = -pos.Dot(side);

    matTrans._11(forward.x_); matTrans._12(side.x_);
    matTrans._21(forward.y_); matTrans._22(side.y_);
    matTrans._31(tx);         matTrans._32(ty);

    matTrans.TransformVector(transPoint);

    return transPoint;
}

inline Vector2D VectorToLocalSpace(const Vector2D& vec,
                                   const Vector2D& forward,
                                   const Vector2D& side)
{
    Vector2D transVec = vec;

    Matrix2D matTrans;

    matTrans._11(forward.x_); matTrans._12(side.x_);
    matTrans._21(forward.y_); matTrans._22(side.y_);

    matTrans.TransformVector(transVec);

    return transVec;
}

//rotates vector around the origin
inline void Vec2DRotateAroundO(Vector2D& v, double angle)
{
    Matrix2D mat;

    mat.Rotate(angle);

    mat.TransformVector(v);
}

inline std::vector<Vector2D> CreateSpikes(unsigned int numSpikes,
                                          double spikesLength,
                                          double fieldOfView,
                                          Vector2D facing,
                                          Vector2D origin
                                          )
{
    //koliko da ih odvoji
    double sectorSize = fieldOfView / (double) (numSpikes-1);

    std::vector<Vector2D> spikes;
    Vector2D temp;
    double angle = -fieldOfView * 0.5; //odakle krece

    for(unsigned int i=0; i < numSpikes; ++i)
    {
        temp = facing;
        Vec2DRotateAroundO(temp, angle);
        spikes.push_back(origin + spikesLength * temp);
        angle+=sectorSize;
    }
    return spikes;
}


