#include "image.h"
namespace BmpLib {

Image::Image(const unsigned int width, const unsigned int height, std::vector<vec3b> &pixels):
    width(width),
    height(height),
    pixels(pixels)
{

}

Image::Image(const unsigned int width, const unsigned int height):
    width(width),
    height(height),
    pixels(width*height)
{
    vec3b white = {{255}, {255}, {255}};
    for(uint w = 0; w < width; w++)
    {
        for(uint h = 0; h < height; h++)
        {
            setPixel(w, h,  white);
        }
    }
}

uint Image::getWidth() const
{
    return this->width;
}

uint Image::getHeight() const
{
    return this->height;
}

void Image::setPixel(const uint x, const uint y, const vec3b &color)
{
    uint arrayIndex = y*this->width+x;
    this->pixels[arrayIndex] = color;
}

const vec3b Image::getPixel(const uint x, const uint y) const
{
    uint arrayIndex = y*this->width+x;
    return this->pixels[arrayIndex];
}

std::vector<vec3b> Image::getRawPixels() const
{
    return pixels;
}

BmpLib::Image::Image(const BmpLib::Image &other):
    width(other.getWidth()),
    height(other.getHeight())
{
    pixels = other.getRawPixels();
}

Image &Image::operator=(const Image &other)
{
    if(&other == this)
        return *this;

    this->width = other.getWidth();
    this->height = other.getHeight();
    this->pixels = other.getRawPixels();
    return *this;
}

}
