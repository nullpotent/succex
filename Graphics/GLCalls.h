#pragma once
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include "Font.h"
#include "Misc/Assert.h"
#include "GraphicsUtils.h"
#include <vector>
#include "2D/Vector2D.h"

namespace Graphics
{
const void DrawLine(Vector2D a, Vector2D b);
const void DrawLine(int x1, int y1, int x2, int y2);
const void DrawRectFilled(int left, int top, int right, int bottom);
const void DrawRectHollow(int left, int top, int right, int bottom);
const void DrawText(const Font* fnt, int x, int y, const char *str, ...);
const void DrawText(const Font* fnt, int x, int y, const std::string& str);
const void SetColor(int r, int g, int b, int a);
const void SetColor(int r, int g, int b);
const void RenderVectorOfVertices(const std::vector<Vector2D> poly);
const void DrawCircleFilled(Vector2D pos, double r);
const void DrawCircleHollow(Vector2D pos, double r);
const void DrawCircleFilled(Vector2D pos, double r, int segments);
const void DrawCircleHollow(Vector2D pos, double r, int segments);
}
