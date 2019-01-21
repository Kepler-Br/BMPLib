#include "bmploader.h"

namespace BmpLib {

bool BmpLoader::checkFileType()
{
    imageFile.seekg(0);
    char fileType[3];
    fileType[2] = '\0';
    imageFile.read(fileType, 2);
    if(std::strcmp(fileType, "BM") == 0)
        return true;
    else
        return false;
}

unsigned int BmpLoader::getBmpSize()
{
    imageFile.seekg(2);
    unsigned int fileSize = 0;
    imageFile.read(reinterpret_cast<char*>(&fileSize), 4);
    return fileSize;
}

unsigned int BmpLoader::getImageDataOffset()
{
    imageFile.seekg(10);
    unsigned int imageDataOffset = 0;
    imageFile.read(reinterpret_cast<char*>(&imageDataOffset), 4);
    return imageDataOffset;
}

unsigned int BmpLoader::getImageWidth()
{
    imageFile.seekg(18);
    unsigned int width = 0;
    imageFile.read(reinterpret_cast<char*>(&width), 4);
    return width;
}

unsigned int BmpLoader::getImageHeight()
{
    imageFile.seekg(22);
    unsigned int height = 0;
    imageFile.read(reinterpret_cast<char*>(&height), 4);
    return height;
}

std::vector<vec3b> BmpLoader::getPixels(const unsigned int width, const unsigned int heigth)
{
    unsigned int dataOffset = getImageDataOffset();
    unsigned int pixelCount= width*heigth;
    std::vector<vec3b> pixels;
    pixels.reserve(pixelCount+1);
    imageFile.seekg(dataOffset);
    for(unsigned int h = 0; h < heigth; h++)
    {
        for(unsigned int w = 0; w < width; w++)
        {
            vec3b color;
            imageFile.read(reinterpret_cast<char*>(&color.b), 1);
            imageFile.read(reinterpret_cast<char*>(&color.g), 1);
            imageFile.read(reinterpret_cast<char*>(&color.r), 1);

//            unsigned int index = h*width+w;
            pixels.push_back(color);
//            pixels[index];
        }
        uint pad = calcPadding(width);
        imageFile.ignore(pad);
    }
    return pixels;
}

uint BmpLoader::calcPadding(uint width)
{
    uint pad = 0;
    if ((width * 3) % 4 != 0)
        pad = 4 - ((width * 3) % 4);
    return pad;
}

BmpLoader::BmpLoader()
{

}

Image BmpLoader::load(const std::string &fileName)
{
    imageFile = std::ifstream(fileName);
    if(!checkFileType())
        throw std::logic_error("NOT IMPLEMENTED");

    unsigned int width = getImageWidth();
    unsigned int height = getImageHeight();
    std::vector<vec3b> pixels = getPixels(width, height);
    Image img(width, height, pixels);

    return img;
}

}
