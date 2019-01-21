#ifndef BMPWRITER_H
#define BMPWRITER_H

#include <string>
#include <fstream>
#include <cstring>

#include "image.h"

//BITMAPV4HEADER
namespace BmpLib {
/*!
   \class BmpWriter
   \brief class for writing 24 bit BMPv4 images.
*/
class BmpWriter
{
    std::ofstream imageFile;

    void write32BitNumber(uint32_t number);
    void write16BitNumber(uint16_t number);
    void writeUnusedSpace(unsigned int count);
    uint calcPadding(uint width);

    // BMP Header
    void writeSignature();
    void writeFileSize(unsigned int pixelTotal);
    void writeRawDataOffset();

    // DIB header
    void writeDibHeaderSize();
    void writeRawDataSize(const Image &img);
    void writePrintResolution();
    void writeColorSpace();

    // Write pixels

    void writePixels(Image &img);

public:
    BmpWriter();

    void write(Image &img, const std::string &fileName);
};
}

#endif // BMPWRITER_H
