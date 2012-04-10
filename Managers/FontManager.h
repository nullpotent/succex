#pragma once

#include "Misc/Assert.h"
#include <iostream>
#include <deque>
#include "../Graphics/Font.h"
#include <algorithm>

struct FontDesc
{
    Font* font;
    std::string name;
};

typedef std::deque<FontDesc*> FontDescList;

class FontManager
{
    private:
        FontManager();
        FontManager(const FontManager& ref);
        FontDescList fontList_;
        static FontManager* fontManagerI_;

    public:
        virtual ~FontManager();
        static bool Instantiate();
        static FontManager* Instance();
        Font* GetByName(std::string name);
        void AddFontToList(FontDesc* font);
        void Destroy();
};
