# BMPLib
Deadly simple lib (and through not very potent) for reading and saving 24 bit BMP v4 images.

Features:
* Loading images;
* Saving images;
* Editing every pixel of the image;
* Creating blank images;
* loder and saver is separate classes.

Example:
```c++
using namespace BmpLib;
BmpLoader reader;
Image exampleImage = reader.load("example.bmp");
exampleImage.setPixel(0, 0, {0, 0, 0});
BmpWriter writer;
writer.write(exampleImage, "processedExample.bmp");
```
