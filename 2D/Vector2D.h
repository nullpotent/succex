#pragma once

#include <math.h>
#include <windows.h>
#include <iosfwd>
#include <limits>
#include "Misc/Utils.h"
#include "Point.h"

using namespace util;

class Vector2D
{
public:
    double x_;
    double y_;

    Vector2D() : x_(0.0), y_(0.0)
    {

    }

    Vector2D(double a, double b) : x_(a), y_(b)
    {

    }

    //postavlja x i y komponente vektora na 0
    void Zero()
    {
        x_ = 0.0;
        y_ = 0.0;
    }

    //vraca true ako su i x i y jednaki nuli
    bool IsZero() const
    {
        return (x_*x_ + y_*y_) < constants::MinDouble;
    }

    //vraca pokazivac na x_, clanovi klase u memoriji su stackovani, pa samim tim dobijamo i y_ clan
    inline double* ToDoubleArray()
    {
        return &x_;
    }
    //vraca duzinu vektora
    inline double Length() const;

    //vraca kvadriranu duzinu vektora
    inline double LengthSq() const;

    inline void Normalize();

    inline double Dot(const Vector2D& v2) const;

    //vraca vrednost vecu od 0 ako je v2 od (this) vektora u clockwise pravcu
    //uz pretpostavku da je Y osa okrenuta ka dole (tj. 0px je na vrhu) i ako
    //je X osa okrenuta ka desno (0px na X-osi je skroz levo)
    inline int Sign(const Vector2D& v2) const;

    //vraca vektor normalan na (this) vektor
    inline Vector2D Perp() const;

    //Clampuje x i y
    inline void Truncate(double max);

    //vraca udaljenost izmedju (this) vektora i v2
    inline double Distance(const Vector2D& v2) const;

    //vraca kvadriranu udaljenost izmedju (this) vektora i v2
    inline double DistanceSq(const Vector2D& v2) const;

    inline void Reflect(const Vector2D& norm);

    //vraca vektor suprotan (this) vektoru
    inline Vector2D Reverse() const;

    inline operator double*()
    {
        return &x_;
    }

    const Vector2D& operator+=(const Vector2D& rhs)
    {
        x_ += rhs.x_;
        y_ += rhs.y_;
        return *this;
    }

    const Vector2D& operator-=(const Vector2D& rhs)
    {
        x_ -= rhs.x_;
        y_ -= rhs.y_;
        return *this;
    }

    const Vector2D& operator*=(const double& rhs)
    {
        x_ *= rhs;
        y_ *= rhs;
        return *this;
    }

    const Vector2D& operator/=(const double& rhs)
    {
        x_ /= rhs;
        y_ /= rhs;
        return *this;
    }

    bool operator==(const Vector2D& rhs) const
    {
        return (IsEqual(x_,rhs.x_) && IsEqual(y_,rhs.y_));
    }

    bool operator!=(const Vector2D& rhs) const
    {
        return (x_!=rhs.x_) || (y_ != rhs.y_);
    }
};


inline Vector2D operator*(const Vector2D& lhs, double rhs);
inline Vector2D operator*(double lhs, const Vector2D& rhs);
inline Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs);
inline Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);
inline Vector2D operator/(const Vector2D& lhs, double val);

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs);
std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs);

inline double Vector2D::Length() const
{
    return sqrt(x_ * x_ + y_ * y_);
}

//squared version of Vector2D::Length();
inline double Vector2D::LengthSq() const
{
    return (x_ * x_ + y_ * y_);
}

//calculates the dot product of (this) and v2 vector
inline double Vector2D::Dot(const Vector2D& v2) const
{
    return x_ * v2.x_ + y_ * v2.y_;
}

//return positive if v2 is clockwise of (this) vector
//minus otherwise (sdl oordinate)
inline int Vector2D::Sign(const Vector2D& v2) const
{
    if(y_*v2.x_ > x_*v2.y_)
    {
        return anticlockwise;
    }
    else
    {
        return clockwise;
    }
}

//vraca vektor perpedikularan na ovaj vektor
inline Vector2D Vector2D::Perp() const
{
    return Vector2D(-y_,x_);
}

//izracunava euklidsku udaljenost od drugog vektora
inline double Vector2D::Distance(const Vector2D& v) const
{
    double yDif = v.y_ - y_;
    double xDif = v.x_ - x_;

    return sqrt(yDif * yDif + xDif * xDif);
}

inline double Vector2D::DistanceSq(const Vector2D& v) const
{
    double xDif = v.x_ - x_;
    double yDif = v.y_ - y_;

    return xDif * xDif + yDif * yDif;
}

//odseca vektor tako da duzina ne prelazi max
inline void Vector2D::Truncate(double max)
{
    if(this->Length() > max)
    {
        this->Normalize();
        *this *= max;
    }
}

//Vektor mora biti normalizovan
//Vraca reflektovani vektor
inline void Vector2D::Reflect(const Vector2D& v)
{
    *this += 2.0 * this->Dot(v) * v.Reverse();
}

inline Vector2D Vector2D::Reverse() const
{
    return Vector2D(-this->x_,-this->y_);
}

inline void Vector2D::Normalize()
{
    double vecLength = this->Length();

    if(vecLength > std::numeric_limits<double>::epsilon())
    {
        this->x_ /= vecLength;
        this->y_ /= vecLength;
    }
}

//////////////////////////////////
///Non-member functions (friends)/
//////////////////////////////////

inline Vector2D Vec2DNormalize(const Vector2D& v)
{
    Vector2D vec = v;

    double vecLen = vec.Length();

    if(vecLen > std::numeric_limits<double>::epsilon())
    {
        vec.x_ /= vecLen;
        vec.y_ /= vecLen;
    }

    return vec;
}

inline double Vec2DDistance(const Vector2D& v1, const Vector2D& v2)
{
    double xDif = v2.x_ - v1.x_;
    double yDif = v2.y_ - v1.y_;

    return sqrt(xDif * xDif + yDif * yDif);

}

inline double Vec2DDistanceSq(const Vector2D& v1, const Vector2D& v2)
{
    double xDif = v2.x_ - v1.x_;
    double yDif = v2.y_ - v1.y_;

    return xDif * xDif + yDif * yDif;
}

inline double Vec2DLength(const Vector2D& v)
{
    return sqrt(v.x_ * v.x_ + v.y_ * v.y_);
}

inline double Vec2DLengthSq(const Vector2D& v)
{
    return v.x_ * v.x_ + v.y_ * v.y_;
}

template <typename T>
inline Vector2D PointToVector(const Point<T>& p)
{
    return Vector2D((double)p.x_,(double)p.y_);
}

template <typename T>
inline Point<T> VectorToPoint(const Vector2D& v)
{
    Point<T> p;
    p.x_ = v.x_;
    p.y_ = v.y_;

    return p;
}


//////////////////////////////////
///      Operator overloads    ///
//////////////////////////////////

inline Vector2D operator* (const Vector2D& lV, double rSc)
{
    Vector2D vec(lV);
    vec *= rSc;
    return vec;
}

inline Vector2D operator* (double lSc, const Vector2D& rV)
{
    Vector2D vec(rV);
    vec *= lSc;
    return vec;
}

inline Vector2D operator- (const Vector2D& lV, const Vector2D& rV)
{
    Vector2D vec(lV);
    vec.x_ -= rV.x_;
    vec.y_ -= rV.y_;
    return vec;
}

inline Vector2D operator+ (const Vector2D& lV, const Vector2D& rV)
{
    Vector2D vec(lV);
    vec.x_ += rV.x_;
    vec.y_ += rV.y_;

    return vec;
}

inline Vector2D operator/ (const Vector2D& lV, double val)
{
    Vector2D vec(lV);
    vec.x_ /= val;
    vec.y_ /= val;

    return vec;
}

//////////////////////////////////
///      Handy functions       ///
//////////////////////////////////

inline void WrapAround(Vector2D& pos, int minX, int minY, int maxX, int maxY)
{
    if(pos.x_ >= maxX)
    {
        pos.x_ = maxX;
    }

    if(pos.x_ <= minX)
    {
        pos.x_ = minX;
    }

    if(pos.y_ <= minY)
    {
        pos.y_ = minY;
    }

    if(pos.y_ >= maxY)
    {
        pos.y_ = maxY;
    }
}

//vraca true ako p nije unutar regiona definisanim topLeft i botRight
inline bool NotInsideRegion(Vector2D p, Vector2D topLeft, Vector2D botRight)
{
    return (p.x_ < topLeft.x_) || (p.x_ > botRight.x_) ||
           (p.y_ < topLeft.y_) || (p.y_ > botRight.y_);
}

inline bool InsideRegion(Vector2D p, Vector2D topLeft, Vector2D botRight)
{
    return !((p.x_ < topLeft.x_) || (p.x_ > botRight.x_) ||
             (p.y_ < topLeft.y_) || (p.y_ > botRight.y_)
            );
}

inline bool InsideRegion(Vector2D p, int left, int top, int right, int bottom)
{
    return !((p.x_ < left) || (p.y_ < top) || (p.x_ > right) || (p.y_ > bottom));
}

inline bool IsInFoV(Vector2D posFirst, Vector2D facingFirst, Vector2D posSecond, double fov)
{
    Vector2D toTarget = Vec2DNormalize(posSecond - posFirst);
    return facingFirst.Dot(toTarget) >= cos(fov/2.0); //zasto fov/2.0 ?
}

//Proverava da li su krajnje tacke vektora kolinearne
inline bool AreVectorsCollinear(Vector2D a, Vector2D b, Vector2D c)
{
    Vector2D A = b - a;
    Vector2D B = c - a;

    return abs(A.Dot(B))==A.Length()*B.Length();
}
