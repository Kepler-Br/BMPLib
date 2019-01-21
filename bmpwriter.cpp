#include "bmpwriter.h"

namespace BmpLib{

void BmpWriter::write32BitNumber(uint32_t number)
{
    imageFile.write(reinterpret_cast<char*>(&number), 4);
}

void BmpWriter::write16BitNumber(uint16_t number)
{
    imageFile.write(reinterpret_cast<char*>(&number), 2);
}

void BmpWriter::writeUnusedSpace(unsigned int count)
{
    char zero = 0x0;
    for(unsigned int i = 0; i < count; i++)
    {
        imageFile.write(&zero, 1);
    }
}

uint BmpWriter::calcPadding(uint width)
{
    uint pad = 0;
    if ((width * 3) % 4 != 0)
        pad = 4 - ((width * 3) % 4);
    return pad;
}

void BmpWriter::writeSignature()
{
    char header[2] = {0x42, 0x4D};
    imageFile.write(header, 2);
}

void BmpWriter::writeFileSize(unsigned int pixelTotal)
{
    //In bytes
    uint32_t bitMapHeaderSize = 14;
    uint32_t dibSize = 108;
    uint32_t colorsPerPixel = 3;
    uint32_t size = bitMapHeaderSize+dibSize+pixelTotal*colorsPerPixel;
    write32BitNumber(size);
}

void BmpWriter::writeRawDataOffset()
{
    uint32_t bitMapHeaderSize = 14;
    uint32_t dibSize = 108;
    uint32_t offset = bitMapHeaderSize+dibSize;
    write32BitNumber(offset);
}

void BmpWriter::writeDibHeaderSize()
{
    uint32_t dibHeaderSize = 108;
    write32BitNumber(dibHeaderSize);
}

void BmpWriter::writeRawDataSize(const Image &img)
{
    uint32_t colorsPerPixel = 3;
    uint32_t pixelTotal = img.getWidth()*img.getHeight();
    uint32_t size = colorsPerPixel*pixelTotal;
    write32BitNumber(size);
}

void BmpWriter::writePrintResolution()
{
    // Some magic numbers.
    uint32_t dpi = 2835;
    // Horizontal
    write32BitNumber(dpi);
    // Vertical
    write32BitNumber(dpi);
}

void BmpWriter::writeColorSpace()
{
    // BGRs
    char colorSpace[] = {0x42, 0x47, 0x52, 0x73};
    imageFile.write(colorSpace, 4);
}

void BmpWriter::writePixels(Image &img)
{
    uint width = img.getWidth();
    uint height = img.getHeight();

    for(uint h = 0; h < height; h++)
    {
        for(uint w = 0; w < width; w++)
        {
            vec3b color = img.getPixel(w, h);
            imageFile.write(reinterpret_cast<char*>(&color.b), 1);
            imageFile.write(reinterpret_cast<char*>(&color.g), 1);
            imageFile.write(reinterpret_cast<char*>(&color.r), 1);
        }
        uint pad = calcPadding(width);
        writeUnusedSpace(pad);
    }
}

BmpWriter::BmpWriter()
{

}


void BmpWriter::write(Image &img, const std::string &fileName)
{
    imageFile = std::ofstream(fileName);

    // Bitmap file header.
    writeSignature();
    unsigned int pixelTotal = img.getWidth()*img.getHeight();
    writeFileSize(pixelTotal);
    writeUnusedSpace(4);
    writeRawDataOffset();

    // DIB header.
    writeDibHeaderSize();
    write32BitNumber(img.getWidth());
    write32BitNumber(img.getHeight());
    // Color plane.
    write16BitNumber(0x1);
    // Bits per pixel.
    write16BitNumber(24);
    // No compression used.
    write32BitNumber(0);
    writeRawDataSize(img);
    writePrintResolution();

    write32BitNumber(0);
    write32BitNumber(0);
    writeColorSpace();

    writeUnusedSpace(24+40);
    writePixels(img);

}

}
