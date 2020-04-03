#ifndef FRAMEBUFFERCAIRO_TOOLS
#define FRAMEBUFFERCAIRO_TOOLS

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cairo.h>

#define FBC_DIRECT 0
#define FBC_DOUBLEBUFFER 1

struct fbcairo_context;

int fb_getInfo(int fbfd, int* xres, int* yres, int* bits_per_pixel=NULL, char* pixelformatRGB=NULL, char* pixelformatRGBX=NULL);
int fb_setBitsPerPixel(int fbfd, int bits_per_pixel);

fbcairo_context* fbcairo_bind(int fbfd, int mode=FBC_DIRECT, bool rotated=false);
fbcairo_context* fbcairo_bind(const char* device, int mode=FBC_DIRECT, bool rotated=false);
void fbcairo_unbind(fbcairo_context* context);
void fbcairo_copyDoubleBuffer(fbcairo_context* context);
int fbcairo_getInfo(fbcairo_context* context, int* xres, int* yres, int* bits_per_pixel=NULL, char* pixelformatRGB=NULL, char* pixelformatRGBX=NULL);
int fbcairo_getWidth(const fbcairo_context *context);
int fbcairo_getHeight(const fbcairo_context* context);
cairo_t* fbcairo_create(fbcairo_context* context);
void fbcairo_destroy(fbcairo_context* context, cairo_t* c);
cairo_surface_t* fbcairo_getSurface(fbcairo_context* context);
  
#endif // FRAMEBUFFERCAIRO_TOOLS
