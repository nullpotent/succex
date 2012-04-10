#include "GLCalls.h"

namespace Graphics
{

const void DrawLine(int x1, int y1, int x2, int y2)
{
    glPushMatrix();
    glTranslated ( x1, y1, 0 );

    glBegin(GL_LINES);
    {
        glVertex2i( 0, 0);
        glVertex2i( x2 - x1, y2 - y1);
    }

    glEnd();
    glFlush();
    glPopMatrix();
}

const void DrawLine(Vector2D a, Vector2D b)
{
    DrawLine(a.x_,a.y_,b.x_,b.y_);
}

const void DrawRectFilled(int left, int top, int right, int bottom)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    {
        glVertex2i(left, top);
        glVertex2i(left, bottom);
        glVertex2i(right, bottom);
        glVertex2i(right, top);
    }
    glEnd();
    glFlush();
    glPopMatrix();
}

const void DrawRectHollow(int left, int top, int right, int bottom)
{
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    {
        glVertex2i(left, top);
        glVertex2i(left, bottom);
        glVertex2i(right, bottom);
        glVertex2i(right, top);
    }
    glEnd();
    glFlush();
    glPopMatrix();
}

const void DrawText(const Font* fnt, int x, int y, const char *str, ...)
{

    Assert ( fnt->IsValid() );

    glEnable ( GL_TEXTURE_2D );
    std::va_list args;
    static char buf[1024];

    va_start ( args, str );
    vsnprintf ( buf, 1024, str, args ); // avoid buffer overflow
    va_end ( args );

    glBindTexture ( GL_TEXTURE_2D, fnt->GetTexture() );
    glPushMatrix();
    glTranslated ( x, y, 0 );

    for ( int i = 0; i < strlen ( buf ); ++i )
    {
        unsigned char ch ( buf[i] - Font::SPACE );    // ch-SPACE = DisplayList offset
        // replace characters outside the valid range with undrawable
        if ( ch > Font::NUM_CHARS )
        {
            ch = Font::NUM_CHARS - 1; // last character is 'undrawable'
        }
        glCallList ( fnt->GetListBase() + ch ); // calculate list to call
    }
    glPopMatrix();
    glDisable ( GL_TEXTURE_2D );
}

const void DrawText(const Font* fnt, int x, int y, const std::string& str)
{

    Assert ( fnt->IsValid() );

    glEnable ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, fnt->GetTexture() );
    glPushMatrix();
    glTranslated ( x, y, 0 );

    for ( std::string::const_iterator i = str.begin(); i != str.end(); ++i )
    {
        unsigned char ch ( *i - Font::SPACE );   // ch-SPACE = DisplayList offset
        // replace characters outside the valid range with undrawable
        if ( ch > Font::NUM_CHARS )
        {
            ch = Font::NUM_CHARS - 1;            // last character is 'undrawable'
        }
        glCallList ( fnt->GetListBase() + ch );   // calculate list to call
    }

    glPopMatrix();
    glDisable ( GL_TEXTURE_2D );
}


const void SetColor(int r, int g, int b, int a)
{

    Assert ( r <= 255 && r >= 0 );
    Assert ( g <= 255 && g >= 0 );
    Assert ( b <= 255 && b >= 0 );
    Assert ( a <= 255 && a >= 0 );

    glColor4f ( ( ( float ) r / 255 ), ( ( float ) g / 255 ), ( ( float ) b / 255 ), ( ( float ) a / 255 ) );
}

const void SetColor(int r, int g, int b)
{

    Assert ( r <= 255 && r >= 0 );
    Assert ( g <= 255 && g >= 0 );
    Assert ( b <= 255 && b >= 0 );

    glColor3f ( ( ( float ) r / 255 ), ( ( float ) g / 255 ), ( ( float ) b / 255 ) );
}

const void RenderVectorOfVertices(const std::vector<Vector2D> poly)
{
    std::vector<Vector2D>::const_iterator it = poly.begin();
    glPushMatrix();
    glBegin(GL_POLYGON);
    {
        for(it;it!=poly.end();++it)
        {
            glVertex2f((int)(*it).x_,(int)(*it).y_);
        }
    }
    glEnd();
    glFlush();
    glPopMatrix();
}

const void DrawCircleFilled(Vector2D pos, double r)
{
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex2f(pos.x_,pos.y_);

        for(double angle=0.0;angle<TwoPi;angle+=0.1)
        {
            glVertex2f(pos.x_ + sin(angle) * r, pos.y_ + cos(angle) * r);
        }
    }
    glEnd();
    glFlush();
    glPopMatrix();
}

const void DrawCircleHollow(Vector2D pos, double r)
{
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    {
        glVertex2f(pos.x_,pos.y_);

        for(double angle=0.0;angle<TwoPi;angle+=0.1)
        {
            glVertex2f(pos.x_ + sin(angle) * r, pos.y_ + cos(angle) * r);
        }
    }
    glEnd();
    glFlush();
    glPopMatrix();
}

const void DrawCircleHollow(Vector2D pos, double r, int segments)
{
	float theta = 2 * 3.1415926 / float(segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

    float cx = pos.x_;
    float cy = pos.y_;

	float x = r;//we start at angle = 0

	float y = 0;

	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -y;
		float ty = x;

		//add the tangential vector

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

const void DrawCircleFilled(Vector2D pos, double r, int segments)
{
	float theta = 2 * 3.1415926 / float(segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = r;//we start at angle = 0

	float y = 0;

	float cx = pos.x_;
	float cy = pos.y_;

	glBegin(GL_TRIANGLE_FAN);
	for(int ii = 0; ii < segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -y;
		float ty = x;

		//add the tangential vector

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

};
