//
//  loadJPEGImage.h
//  
//
//  Created by Ayush Agrawal on 13/06/20.
//

#ifndef loadJPEGImage_h
#define loadJPEGImage_h

#include <stdio.h>

#endif /* loadJPEGImage_h */

DLLEXPORT unsigned char *tjJPEGLoadImage(const char *filename, int *width,
                                         int align, int *height, int *pixelFormat,
                                         int flags);
