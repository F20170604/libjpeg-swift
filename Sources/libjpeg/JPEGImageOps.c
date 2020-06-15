#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <turbojpeg.h>
#include "include/JPEGImageOps.h"

#define THROW_TJ(action)  THROW(action, tjGetErrorStr2(tjInstance))
#define THROW_UNIX(action)  THROW(action, strerror(errno))
#define DEFAULT_SUBSAMP  TJSAMP_444
#define DEFAULT_QUALITY  95

tjscalingfactor *scalingFactors = NULL;
int numScalingFactors = 0;

DLLEXPORT unsigned char* tjJPEGLoadImage(const char *filename, int *width,
                                     int align, int *height, int *pixelFormat, int *inSubsamp,
                                     int flags) {

    tjscalingfactor scalingFactor = { 1, 1 };
    char *inFormat = "jpg", *outFormat = "jpg";
    FILE *jpegFile = NULL;
    unsigned char *imgBuf = NULL, *jpegBuf = NULL;
    int i;
    *pixelFormat = TJPF_UNKNOWN;
    tjhandle tjInstance = NULL;

    long size;
    int inColorspace;
    unsigned long jpegSize;

    /* Read the JPEG file into memory. */
    jpegFile = fopen(filename, "rb");
    fseek(jpegFile, 0, SEEK_END);
    size = ftell(jpegFile);
    fseek(jpegFile, 0, SEEK_SET);
    jpegSize = (unsigned long)size;
    jpegBuf = (unsigned char *)tjAlloc(jpegSize);
    fread(jpegBuf, jpegSize, 1, jpegFile);
    fclose(jpegFile);  jpegFile = NULL;

    tjInstance = tjInitDecompress();
    tjDecompressHeader3(tjInstance, jpegBuf, jpegSize, width, height, inSubsamp, &inColorspace);

    int jpegwidth = TJSCALED(*width, scalingFactor);
    int jpegheight = TJSCALED(*height, scalingFactor);
    width = &jpegwidth;
    height = &jpegheight;


    *pixelFormat = TJPF_BGRX;
    imgBuf = (unsigned char *)tjAlloc(*width * *height * tjPixelSize[*pixelFormat]);
    tjDecompress2(tjInstance, jpegBuf, jpegSize, imgBuf, *width, 0, *height, *pixelFormat, flags);
    tjFree(jpegBuf);  jpegBuf = NULL;
    tjDestroy(tjInstance);  tjInstance = NULL;

    return imgBuf;
}

DLLEXPORT unsigned char* tjJPEGLoadImageCompressed(const char *filename, int *width,
                                     int align, int *height, int *pixelFormat, int *inSubsamp,
                                     int flags) {

    tjscalingfactor scalingFactor = { 1, 1 };
    char *inFormat = "jpg", *outFormat = "jpg";
    FILE *jpegFile = NULL;
    unsigned char *imgBuf = NULL, *jpegBuf = NULL;
    int i;
    *pixelFormat = TJPF_UNKNOWN;
    tjhandle tjInstance = NULL;

    long size;
    int inColorspace;
    unsigned long jpegSize;

    /* Read the JPEG file into memory. */
    jpegFile = fopen(filename, "rb");
    fseek(jpegFile, 0, SEEK_END);
    size = ftell(jpegFile);
    fseek(jpegFile, 0, SEEK_SET);
    jpegSize = (unsigned long)size;
    jpegBuf = (unsigned char *)tjAlloc(jpegSize);
    fread(jpegBuf, jpegSize, 1, jpegFile);
    fclose(jpegFile);  jpegFile = NULL;

    tjInstance = tjInitDecompress();
    tjDecompressHeader(tjInstance, jpegBuf, jpegSize, width, height);
    imgBuf = (unsigned char *)tjAlloc(*width * *height * 3);
    tjDecompress2(tjInstance, jpegBuf, jpegSize, imgBuf, *width, 0, *height, TJPF_RGB, 0);
    tjFree(jpegBuf);  jpegBuf = NULL;
    tjDestroy(tjInstance);  tjInstance = NULL;

    return imgBuf;
}

DLLEXPORT unsigned char* tjJPEGSaveImage(unsigned char *buffer,
                          int width, int pitch, int height, int pixelFormat, int outSubsamp,
                          int flags) {
    
    FILE *jpegFile = NULL;
    unsigned char *imgBuf = NULL, *jpegBuf = NULL;
    int i;
    tjhandle tjInstance = NULL;

    long size;
    int inSubsamp, inColorspace;
    unsigned long jpegSize=61538;
    int retVal = -1;
    
    jpegBuf = NULL;  /* Dynamically allocate the JPEG buffer */
    
    int outQual = DEFAULT_QUALITY;
    
    tjInstance = tjInitCompress();
    tjCompress2(tjInstance, imgBuf, width, 0, height, pixelFormat,
                &jpegBuf, &jpegSize, outSubsamp, outQual, flags);
    tjDestroy(tjInstance);  tjInstance = NULL;
    tjDestroy(tjInstance);  tjInstance = NULL;
    fclose(jpegFile);  jpegFile = NULL;
    //printf("%lu", jpegSize);
    
    return jpegBuf;
    
    
}
