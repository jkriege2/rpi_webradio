#include "framebuffer_cairo_tools.h"

#include <errno.h>

struct fbcairo_context {
	int fbfd;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize;
	unsigned char* fbp ;
    unsigned char* buffer ;
	cairo_surface_t * surface;
	int privateFileID;
    int mode=0;
};


int fb_getInfo(int fbfd, int* xres, int* yres, int* bits_per_pixel, char* pixelformatRGB, char* pixelformatRGBX) {
	struct fb_var_screeninfo var_info;
	//struct fb_fix_screeninfo finfo;
	if (fbfd != -1) {
		int err;
		if ((err=ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info))==0) {
				if (xres) *xres=var_info.xres;
				if (yres) *yres=var_info.yres;
				if (bits_per_pixel) *bits_per_pixel=var_info.bits_per_pixel;
				if (pixelformatRGB) sprintf(pixelformatRGB, "RGB%d%d%d",var_info.red.length,
                                                 var_info.green.length,
                                                 var_info.blue.length);
				if (pixelformatRGBX) sprintf(pixelformatRGBX, "RGBX%d%d%d%d",var_info.red.length,
                                                 var_info.green.length,
                                                 var_info.blue.length,
                                                 var_info.transp.length);
		} else {
			fprintf(stderr, "fb_getInfo(): ioctl (FBIOGET_VSCREENINFO) didn't succeed!\n    ERROR: %d\n\n", err);
			return -1;
		}
		
		// Get fixed screen information
		//if ((err=ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))!=0) {
		//	fprintf(stderr, "fb_getInfo(): ioctl (FBIOGET_FSCREENINFO) didn't succeed!\n    ERROR: %d\n\n", err);
		//	return -1;
		//}
	} else {
		fprintf(stderr, "fb_getInfo(): framebuffer device not opened!\n");
		return -1;
	}
	return 0;
}

int fb_setBitsPerPixel(int fbfd, int bits_per_pixel) {
	struct fb_var_screeninfo var_info;
	if (fbfd != -1) {
		int err;
		if ((err=ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info))!=0) {
			fprintf(stderr, "fb_setBitsPerPixel(): ioctl (FBIOGET_VSCREENINFO) didn't succeed!\n    ERROR: %d\n\n", err);
			return -1;
		}
		
		var_info.bits_per_pixel = bits_per_pixel;
		if ((err=ioctl(fbfd, FBIOPUT_VSCREENINFO, &var_info))!=0) {
			fprintf(stderr, "fb_setBitsPerPixel(): ioctl (FBIOPUT_VSCREENINFO) didn't succeed!\n    ERROR: %d\n\n", err);
			return -1;
		}

	} else {
		fprintf(stderr, "fb_getInfo(): framebuffer device not opened!\n");
		return -1;
	}
	return 0;
}


fbcairo_context* fbcairo_bind(int fbfd, int mode) {
	fbcairo_context* res=NULL;
	int err;
	if (fbfd != -1) {
		// get memory for context
		res=(fbcairo_context*)malloc(sizeof(fbcairo_context));
		
		// init context
		res->fbfd=fbfd;
		res->privateFileID=0;
		res->fbp=NULL;
	    res->surface=NULL;
        res->buffer=NULL;
        res->mode=mode;
		
		// try to set 32-bit mode RGB32
		fb_setBitsPerPixel(res->fbfd, 32);
		
		// get device config
		if ((err=ioctl(res->fbfd, FBIOGET_FSCREENINFO, &(res->finfo)))!=0) {
			fprintf(stderr, "fbcairo_bind(): ioctl (FBIOGET_FSCREENINFO) didn't succeed!\n    ERROR: %d\n\n", err);
			free(res);
			return NULL;
		}

		if ((err=ioctl(res->fbfd, FBIOGET_VSCREENINFO, &(res->vinfo)))!=0) {
			fprintf(stderr, "fbcairo_bind(): ioctl (FBIOGET_VSCREENINFO) didn't succeed!\n    ERROR: %d\n\n", err);
			free(res);
			return NULL;
		}

		
		// calculate screen size
		res->screensize = res->vinfo.xres * res->vinfo.yres * res->vinfo.bits_per_pixel / 8;
		
		// map the device to memory 
		res->fbp = (unsigned char*) mmap (0, res->screensize, PROT_READ | PROT_WRITE, MAP_SHARED, res->fbfd, 0);

		if ((void*)(res->fbp) == MAP_FAILED) {
			fprintf(stderr, "fbcairo_bind(): mmap() failed!    ERROR %d: %s\n", errno, strerror(errno));
			
			return NULL;
		}

        unsigned char* buf=res->fbp;
        if (mode==FBC_DOUBLEBUFFER) {
            res->buffer=(unsigned char*)malloc(res->screensize);
            buf=res->buffer;
        }
		
		if (res->vinfo.bits_per_pixel==16) {
			if (res->vinfo.red.length==5 && res->vinfo.green.length==6 && res->vinfo.blue.length==5) { // RGB565
                res->surface = cairo_image_surface_create_for_data(buf, CAIRO_FORMAT_RGB16_565, res->vinfo.xres, res->vinfo.yres, res->finfo.line_length);
			}
		} else if (res->vinfo.bits_per_pixel==32) {
            res->surface = cairo_image_surface_create_for_data(buf, CAIRO_FORMAT_ARGB32, res->vinfo.xres, res->vinfo.yres, res->finfo.line_length);
		}
		
		if (res->surface==NULL){
			fprintf(stderr, "fbcairo_bind(): cannot create cairo surface for device with %d bpp and RGB%d%d%d\n", res->vinfo.bits_per_pixel, res->vinfo.red.length, res->vinfo.green.length, res->vinfo.blue.length);
			fbcairo_unbind(res);
			return NULL;
		}
	}
	return res;
}

fbcairo_context* fbcairo_bind(const char* device, int mode) {
	int fbfd = 0; // framebuffer filedescriptor
	
	fbfd = open(device, O_RDWR);
	if (fbfd == -1) {
		fprintf(stderr, "fbcairo_bind(): cannot open framebuffer device '%s'\n", device);
		return  NULL;
	}
    fbcairo_context* c=fbcairo_bind(fbfd, mode);
	if (c) {
		c->privateFileID=1;
	}
	return c;
}

void fbcairo_unbind(fbcairo_context* context) {
	if (context) {
		if (context->surface) cairo_surface_destroy(context->surface);
		munmap(context->fbp, context->screensize);
		if (context->privateFileID!=0) {
			close(context->fbfd);
		}
        if (context->buffer) free(context->buffer);
		free(context);
	}
}

int fbcairo_getInfo(fbcairo_context* context, int* xres, int* yres, int* bits_per_pixel, char* pixelformatRGB, char* pixelformatRGBX) {
	if (context) {
		return fb_getInfo(context->fbfd, xres, yres, bits_per_pixel, pixelformatRGB, pixelformatRGBX);
	} else {
		fprintf(stderr, "fbcairo_getInfo(): no valid context\n");
		return 0;
	}
}

cairo_t* fbcairo_create(fbcairo_context* context) {
    if (context && context->surface) {
		return cairo_create (context->surface);
	} else {
		fprintf(stderr, "fbcairo_create(): no valid context\n");
		return  NULL;
	}
}
cairo_surface_t* fbcairo_getSurface(fbcairo_context* context) {
	if (context) {
		return context->surface;
	} else {
		fprintf(stderr, "fbcairo_getSurface(): no valid context\n");
		return  NULL;
	}
}






void fbcairo_copyDoubleBuffer(fbcairo_context *context)
{
    if (context) {
        if (context->mode!=FBC_DOUBLEBUFFER) return;
        if (context->buffer) {
            memcpy(context->fbp, context->buffer, context->screensize);
        } else {
            fprintf(stderr, "fbcairo_copyDoubleBuffer(): no valid double-bufer\n");
            return  ;
        }
    } else {
        fprintf(stderr, "fbcairo_copyDoubleBuffer(): no valid context\n");
        return  ;
    }
}


int fbcairo_getWidth(const fbcairo_context *context)
{
    if (context) {
        return context->vinfo.xres;
    }
    return 0;
}


int fbcairo_getHeight(const fbcairo_context *context)
{
    if (context) {
        return context->vinfo.yres;
    }
    return 0;
}
