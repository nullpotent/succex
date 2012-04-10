#pragma once

#include "Managers/FontManager.h"
#include <math.h>
#include "Misc/Utils.h"
#include "Graphics/GLCalls.h"
#include "Misc/StreamUtilFunctions.h"

class Region
{
public:

    enum region_modifier {halfsize, normal};

protected:

    double      top_;
    double      left_;
    double      right_;
    double      bottom_;
    bool        showText_;
    double      width_;
    double      height_;
    bool        highlighted_;
    Vector2D    center_;

    std::string text_;

    int         id_;

public:

    Region() : top_(0), bottom_(0), right_(0), left_(0) {}

    Region(double       left,
           double       top,
           double       right,
           double       bottom,
           std::string  text,
           bool         showText,
           int          id = -1)  :
                                    top_(top),
                                    left_(left),
                                    right_(right),
                                    bottom_(bottom),
                                    id_(id),
                                    highlighted_(false),
                                    showText_(showText),
                                    text_(std::string(text))
    {
        center_ = Vector2D((left+right)*0.5, (top+bottom)*0.5);
        width_  = fabs(right_ - left_);
        height_ = fabs(bottom_ - top_);
    }

    virtual ~Region() {}
    virtual inline void Render(bool showId) const;

    inline bool Inside(Vector2D pos, region_modifier r) const;
    inline Vector2D GetRandomPosition() const;

    void HighlightRegion()
    {
        highlighted_ = true;
    }
    void DeHighlightRegion()
    {
        highlighted_ = false;
    }

    double GetTop() const
    {
        return top_;
    }
    double GetBottom() const
    {
        return bottom_;
    }
    double GetLeft() const
    {
        return left_;
    }
    double GetRight() const
    {
        return right_;
    }
    double GetHeight() const
    {
        return fabs(top_ - bottom_);
    }
    double GetWidth() const
    {
        return fabs(right_ - left_);
    }
    double GetLength() const
    {
        return Maximum(GetWidth(), GetHeight());
    }
    double Breadth() const
    {
        return Minimum(GetWidth(), GetHeight());
    }

    Vector2D Center() const
    {
        return center_;
    }
    int GetID() const
    {
        return id_;
    }
};

inline Vector2D Region::GetRandomPosition() const
{
    return Vector2D(RandInRange(left_,right_), RandInRange(top_,bottom_));
}

inline bool Region::Inside(const Vector2D pos, region_modifier r = normal) const
{
    if(r == normal)
    {
        return ( (pos.x_ > GetLeft() ) && (pos.x_ < GetRight() ) && (pos.y_ > GetTop() ) && (pos.y_ < GetBottom() ) );
    }
    else
    {
        const double marginX = width_ * 0.25;
        const double marginY = height_ * 0.25;

        return ((pos.x_ > (left_+marginX)) && (pos.x_ < (right_-marginX)) &&
                (pos.y_ > (top_+marginY)) && (pos.y_ < (bottom_-marginY)));
    }
}

inline void Region::Render(bool showId = false) const
{
    if(highlighted_)
    {
        glColor3f(0.87f,0.79f,0.89f);
        Graphics::DrawRectFilled((int)left_,(int)top_,(int)right_,(int)bottom_);
    }
    else
    {
        glColor3f(1.0,1.0,1.0);
        Graphics::DrawRectHollow((int)left_,(int)top_,(int)right_,(int)bottom_);
    }

    if(showText_)
    {
        glColor3f(0.73f,0.3f,0.45f);
        Graphics::DrawText(FontManager::Instance()->GetByName("lsansdi16"), left_ + 8, top_ + 8, text_);
    }
    if(showId)
    {
        Graphics::SetColor(COLOR_WHITE);
        Graphics::DrawText(FontManager::Instance()->GetByName("arial9"),Center().x_,Center().y_,"%i",id_);
    }
}
