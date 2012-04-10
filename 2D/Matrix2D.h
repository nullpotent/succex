#pragma once

#include <math.h>
#include <vector>
#include "Misc/Utils.h"
#include "Vector2D.h"

class Matrix2D
{
private:
    struct Matrix
    {
        double _11,_12,_13;
        double _21,_22,_23;
        double _31,_32,_33;
        Matrix()
        {
            _11=0.0;
            _12=0.0;
            _13=0.0;
            _21=0.0;
            _22=0.0;
            _23=0.0;
            _31=0.0;
            _32=0.0;
            _33=0.0;
        }
    };

    Matrix matrix_;
    inline void Multiply(Matrix &m);

public:

    Matrix2D(double __11,double __12,double __13,
             double __21,double __22,double __23,
             double __31,double __32,double __33)
    {
        matrix_._11 = __11;
        matrix_._12 = __12;
        matrix_._13 = __13;
        matrix_._21 = __21;
        matrix_._22 = __22;
        matrix_._23 = __23;
        matrix_._31 = __31;
        matrix_._32 = __32;
        matrix_._33 = __33;
    }

    Matrix2D()
    {
        //inicijalizovanje matrice na identitetnu
        Identity();
    }

    //Pravi identitetnu matricu
    inline void Identity();

    //Centralna simetrija u odnosu na vektor v (njegov kraj)
    inline void CentralSymetry(Vector2D& v);

    //Pravi matricu za translaciju
    inline void Translate(double x, double y);

    //Pravi matricu za skaliranje
    inline void Scale(double xScale, double yScale);

    //Pravi matricu za rotiranje
    inline void Rotate(double angle);

    //Pravi matricu za rotiranje od fwd i side vektora
    inline void Rotate(const Vector2D& fwd, const Vector2D& side);

    //Afino preslikavanje na std::vector vektora
    inline void TransformVectors(std::vector<Vector2D>& vectors);

    //Kompozicija dve afine transformacije
    inline void Compose(const Matrix2D& m);

    //vraca determinantu matrice
    inline double Det();

    //Afino preslikavanje na tacku
    inline void TransformVector(Vector2D& vec);

    void _11(double val)
    {
        matrix_._11 = val;
    }
    void _12(double val)
    {
        matrix_._12 = val;
    }
    void _13(double val)
    {
        matrix_._13 = val;
    }
    void _21(double val)
    {
        matrix_._21 = val;
    }
    void _22(double val)
    {
        matrix_._22 = val;
    }
    void _23(double val)
    {
        matrix_._23 = val;
    }
    void _31(double val)
    {
        matrix_._31 = val;
    }
    void _32(double val)
    {
        matrix_._32 = val;
    }
    void _33(double val)
    {
        matrix_._33 = val;
    }
};

//////////////////////////////////
///      Member functions        /
//////////////////////////////////

inline void Matrix2D::Multiply(Matrix& m)
{
    Matrix2D::Matrix temp;

    //prvi red
    temp._11 = (matrix_._11 * m._11) + (matrix_._12 * m._21) + (matrix_._13 * m._31);
    temp._12 = (matrix_._11 * m._12) + (matrix_._12 * m._22) + (matrix_._13 * m._32);
    temp._13 = (matrix_._11 * m._13) + (matrix_._12 * m._23) + (matrix_._13 * m._33);

    //drugi red
    temp._21 = (matrix_._21 * m._11) + (matrix_._22 * m._21) + (matrix_._23 * m._31);
    temp._22 = (matrix_._21 * m._12) + (matrix_._22 * m._22) + (matrix_._23 * m._32);
    temp._23 = (matrix_._21 * m._13) + (matrix_._22 * m._23) + (matrix_._23 * m._33);

    //treci red
    temp._31 = (matrix_._31 * m._11) + (matrix_._32 * m._21) + (matrix_._33 * m._31);
    temp._32 = (matrix_._31 * m._12) + (matrix_._32 * m._22) + (matrix_._33 * m._32);
    temp._33 = (matrix_._31 * m._13) + (matrix_._32 * m._23) + (matrix_._33 * m._33);

    matrix_ = temp;
}

inline void Matrix2D::TransformVectors(std::vector<Vector2D>& vectors)
{
    for(unsigned int i=0; i<vectors.size(); ++i)
    {
        double tempX = (matrix_._11 * vectors[i].x_) + (matrix_._21 * vectors[i].y_) + matrix_._31;
        double tempY = (matrix_._12 * vectors[i].x_) + (matrix_._22 * vectors[i].y_) + matrix_._32;

        vectors[i].x_ = tempX;
        vectors[i].y_ = tempY;
    }
}

inline void Matrix2D::Compose(const Matrix2D& m)
{
    matrix_._11 = (matrix_._11 * m.matrix_._11) + (m.matrix_._21 * matrix_._12);
    matrix_._12 = (matrix_._11 * m.matrix_._12) + (m.matrix_._22 * matrix_._12);
    matrix_._21 = (matrix_._21 * m.matrix_._11) + (m.matrix_._21 * matrix_._22);
    matrix_._22 = (matrix_._21 * m.matrix_._12) + (m.matrix_._22 * matrix_._22);
    matrix_._31 = (matrix_._11 * m.matrix_._31) + (m.matrix_._12 * matrix_._32) + matrix_._31;
    matrix_._32 = (matrix_._21 * m.matrix_._31) + (m.matrix_._22 * matrix_._32) + matrix_._32;
}

inline double Matrix2D::Det()
{
    return (matrix_._11 * matrix_._22) - (matrix_._12 * matrix_._21);
}

inline void Matrix2D::TransformVector(Vector2D& vec)
{
    double tempX = (matrix_._11 * vec.x_) + (matrix_._21 * vec.y_) + matrix_._31;
    double tempY = (matrix_._12 * vec.x_) + (matrix_._22 * vec.y_) + matrix_._32;

    vec.x_ = tempX;
    vec.y_ = tempY;
}

inline void Matrix2D::Identity()
{
    matrix_._11 = 1;
    matrix_._12 = 0;
    matrix_._13 = 0;
    matrix_._21 = 0;
    matrix_._22 = 1;
    matrix_._23 = 0;
    matrix_._31 = 0;
    matrix_._32 = 0;
    matrix_._33 = 1;
}

inline void Matrix2D::Translate(double x, double y)
{
    Matrix mat;

    mat._11 = 1;
    mat._12 = 0;
    mat._13 = 0;
    mat._21 = 0;
    mat._22 = 1;
    mat._23 = 0;
    mat._31 = x;
    mat._32 = y;
    mat._33 = 1;

    Multiply(mat);
}

inline void Matrix2D::Scale(double xScale, double yScale)
{
    Matrix mat;

    mat._11 = xScale;
    mat._12 = 0;
    mat._13 = 0;
    mat._21 = 0;
    mat._22 = yScale;
    mat._23 = 0;
    mat._31 = 0;
    mat._32 = 0;
    mat._33 = 1;

    Multiply(mat);
}

inline void Matrix2D::CentralSymetry(Vector2D& v)
{
    Matrix mat;

    mat._11 = -1;
    mat._12 = 0;
    mat._13 = 0;
    mat._21 = 0;
    mat._22 = -1;
    mat._23 = 0;
    mat._31 = 2*v.x_;
    mat._32 = 2*v.y_;
    mat._33 = -1;

    Multiply(mat);
}

inline void Matrix2D::Rotate(double angle)
{
    Matrix mat;
    double cos_ = cos(angle);
    double sin_ = sin(angle);

    mat._11 = cos_;
    mat._12 = sin_;
    mat._13 = 0;
    mat._21 = -sin_;
    mat._22 = cos_;
    mat._23 = 0;
    mat._31 = 0;
    mat._32 = 0;
    mat._33 = 1;

    Multiply(mat);
}

inline void Matrix2D::Rotate(const Vector2D& fwd, const Vector2D& side)
{
    Matrix mat;

    mat._11 = fwd.x_;
    mat._12 = fwd.y_;
    mat._13 = 0;
    mat._21 = side.x_;
    mat._22 = side.y_;
    mat._23 = 0;
    mat._31 = 0;
    mat._32 = 0;
    mat._33 = 1;

    Multiply(mat);
}
