#ifndef BMPFILE_H
#define BMPFILE_H

#include <string>
#include <fstream>
#include <cstring>

#include "image.h"

namespace BmpLib {
/*!
   \class BmpLoaded
   \brief class for loading 24 bit BMPv4 images.
*/
class BmpLoader
{
    std::ifstream imageFile;

    /*!
       \brief check if file has BMP sign.
    */
    bool checkFileType();
    /*!
       \brief get total BMP size in bytes.
    */
    unsigned int getBmpSize();
    /*!
       \brief get where image data begins.
    */
    unsigned int getImageDataOffset();
    unsigned int getImageWidth();
    unsigned int getImageHeight();
    std::vector<vec3b> getPixels(const unsigned int width, const unsigned int heigth);
    uint calcPadding(uint width);

public:
    BmpLoader();

    Image load(const std::string &fileName);
};
}
#endif // BMPFILE_H
