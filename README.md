# BMP library

Simple library for loading 24 bit color BMP files with v4 header.

To create makefile type in the project directory:  
`qmake ./BmpLib.pro`

Lib provides 3 classes for dealing with BMP files:
- BmpLoader
- BmpWriter
- Image  

BmpLoader provides simple interface for loading image. You should instance this class to work with.  
```
BmpLoader loader;
Image img = loader.load("image.bmp");
```  
BmpWriter provides simple interface for loading image. You should instance this class to work with. 
```
BmpLoader writer; 
Image img = loader.write(img, "image.bmp");
```
Image provides simple interface for manipulating image's pixel color.  
**Expect bugs!**
Should compile under GNU/Linux but Windows compatibility is not guaranteed.  
