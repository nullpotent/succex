#include "FontManager.h"

FontManager* FontManager::fontManagerI_ = NULL;

FontManager::FontManager()
{

}

FontManager::~FontManager()
{
    Destroy();
    std::cout<<"Font manager down"<<std::endl;
}

bool FontManager::Instantiate()
{
    fontManagerI_ = new FontManager();
    return fontManagerI_ != NULL;
}

FontManager* FontManager::Instance()
{
    Assert(fontManagerI_!=NULL);
    return fontManagerI_;
}

Font* FontManager::GetByName(std::string name)
{
    FontDescList::iterator it = fontList_.begin();
    FontDescList::iterator itEnd = fontList_.end();

    while(it!=itEnd)
    {
        if((*it)->name==name) //hmm ?
            return (*it)->font;
        it++;
    }

    if((*it)==NULL)
        throw std::runtime_error ( "Font "+name+" wasn't loaded " );
}

void FontManager::AddFontToList(FontDesc* font)
{
    FontDescList::iterator it = std::find(fontList_.begin(), fontList_.end(), font);

    if(it == fontList_.end())
    {
        fontList_.push_back(font);
    }
}

void FontManager::Destroy()
{
    while(fontList_.begin() != fontList_.end())
    {
        FontDesc* f = fontList_.front();
        fontList_.pop_front();
        delete f->font;
        delete f;
    }
    fontList_.clear();
}

