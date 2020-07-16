//
//  JPEGImageOps.h
//  
//
//  Created by Ayush Agrawal on 13/06/20.
//

#ifndef JPEGImageOps_h
#define JPEGImageOps_h

#include <stdio.h>

#endif /* JPEGImageOps_h */

DLLEXPORT int tjJPEGSaveImage(const char *filename, unsigned char *buffer,
                          int width, int pitch, int height, int pixelFormat, int outSubsamp,
                          int flags);

DLLEXPORT unsigned char* tjJPEGLoadCompressedImage(const char *filename, int *width,
                                                   int align, int *height, int *pixelFormat, int *inSubsamp,
                                                   int flags);
