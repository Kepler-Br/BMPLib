#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <cmath>

#include <iostream>

namespace BmpLib {
struct vec3b
{
    union {
        unsigned char x;
        unsigned char r;
        unsigned char h;
    };

    union {
        unsigned char y;
        unsigned char g;
        unsigned char s;
    };

    union {
        unsigned char z;
        unsigned char b;
        unsigned char v;
    };
};

class BmpLoader;

/*!
   \class Image
   \brief class for storing image data.
*/
class Image
{
private:
    unsigned int width;
    unsigned int height;
    std::vector<vec3b> pixels;

    Image(const unsigned int width, const unsigned int height, std::vector<vec3b> &pixels);
public:
    friend class BmpLoader;

    Image(const unsigned int width, const unsigned int height);
    Image(const Image &other);

    Image &operator=(const Image& img);

    uint getWidth() const;
    uint getHeight() const;

    void setPixel(const uint x, const uint y, const vec3b &color);

    const vec3b getPixel(const uint x, const uint y) const;

    std::vector<vec3b> getRawPixels() const;
};
}

#endif // IMAGE_H
