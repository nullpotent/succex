#pragma once

#include "Vector2D.h"
#include "../Graphics/GLCalls.h"

class IBBox2D
{
    private:

        Vector2D topLeft_;
        Vector2D botRight_;
        Vector2D center_;

    public:

        IBBox2D(Vector2D tl, Vector2D br) :
                                            topLeft_(tl),
                                            botRight_(br),
                                            center_((tl+br)/2.0)
        {

        }

        bool OverlappesWith(const IBBox2D& b)
        {
            return !((b.Top() > Bottom()) ||
                     (b.Bottom() < Top()) ||
                     (b.Left() > Right()) ||
                     (b.Right() < Left())
                     );
        }

        Vector2D TopLeft() const
        {
            return topLeft_;
        }

        Vector2D BottomRight() const
        {
            return botRight_;
        }

        double Top() const
        {
            return topLeft_.y_;
        }

        double Left() const
        {
            return topLeft_.x_;
        }

        double Bottom() const
        {
            return botRight_.y_;
        }

        double Right() const
        {
            return botRight_.x_;
        }

        Vector2D Center() const
        {
            return center_;
        }

        void Render() const
        {
            glColor3f(1.0,1.0,1.0);
            Graphics::DrawRectHollow(Left(),Top(),Left()+Right(),Top()+Bottom());
        }
};
