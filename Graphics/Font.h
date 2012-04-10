#pragma once

#include <GL/gl.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdarg>
#include <sstream>

class FTLibraryContainer
{
public:

    FTLibraryContainer();
    ~FTLibraryContainer();
    FT_Library& getLibrary();

private:

    static FT_Library library_;
};

class Font
{
public:
    Font();
    Font(const std::string& filename, unsigned int size);
    ~Font();

    void Open(const std::string& filename, unsigned int size);
    void Release();
    bool IsValid() const;

    const GLuint GetListBase() const;
    const GLuint GetTexture() const;


    const GLuint CalcStringWidth(const std::string& str) const;
    const GLuint GetHeight() const;

    static const unsigned int SPACE = 32;
    static const unsigned int NUM_CHARS = 96;

private:
    // leave copy constructor and operator= undefined to make noncopyable
    Font(const Font&);
    // font data
    unsigned int texID_;
    unsigned int listBase_;
    std::vector<unsigned char> widths_;
    unsigned char height_;

    static FTLibraryContainer library_;
};
