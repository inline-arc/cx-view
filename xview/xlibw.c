#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<cairo/cairo.h> //include cairo lib
#include<cairo/cairo-xlib.h>  //include the Xlib
#include <X11/Xutil.h>
#include <unistd.h>
#include<err.h>
#include<assert.h>
#include<png.h>
#include "arg.h"
#include <X11/extensions/Xfixes.h>
//#include<X11/Xpm.h>
/*#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "arg.h"

int path(imgpath) {
    int width, height, bpp;

    uint8_t* rgb_image = stbi_load("arc.png", &width, &height, &bpp, 3);

    stbi_image_free(rgb_image);

    return 0;
}*/
//#include<graphics.h>
//:#include"arc.h"
/*
XWMHint* win_hint; //pointer

Pixmap icon_pixmap = XCreateBitmapFromData( Display, win ,
    icon_bitmap_bits, icon_bitmap_width, icon_bitmap_height);

if(!icon_pixmap){
  print(stderr, "XCreateBitmapFromData - error creating pitmap\n");
  exit(1); // error message if things failed 
}

win_hint = XAllocWNHint();
if(!win_hint){
  print(stderr, "XAllocWNHint - out of memory\n");
  exit(1);
}
*/

int main(int argc,char *argv[]){
  Display *dpy; //Display is imp as its the canvas
  int screen;  //ya screen 
  Window win; //Window 
  XEvent event; //events the render 
  cairo_surface_t *cs, *img;
  cairo_t *c;
  int winw, winh;
  int imgw, imgh;
  char *imgpath;

  imgpath = "arc.png" ,argv[1];
  if(imgpath == NULL){
    printf("invalid");
    exit(1);
}

  //loading the image with diametion of the img with cairo
  img = cairo_image_surface_create_from_png(imgpath);
  if(cairo_surface_status(img) != CAIRO_STATUS_SUCCESS)
    errx(1, "load image");
  imgw = cairo_image_surface_get_width(img);
  imgh = cairo_image_surface_get_height(img);

  //adding screen  diametions
  dpy = XOpenDisplay(NULL);
  if(dpy == NULL)
    errx(1, "window failed");

 // screen = DefaultScreen(dpy, screen);
  winw = DisplayWidth(dpy,screen);
  winh = DisplayHeight(dpy, screen);
  
//resize window with image 
  //define minimum and and condition 
  #define MIN(x,y) ((x)<(y) ? (x):(y))
          winw = MIN(winw, imgw); //win = imh height 
          winh = MIN(winh, imgh);// win = img width 
 #undef MIN

  dpy = XOpenDisplay(NULL); // this is means you had some connection with the x-server
  if(dpy == NULL){
    printf("unable");
    exit(1);
  }

  screen = DefaultScreen(dpy);

  win = XCreateSimpleWindow(dpy, RootWindow(dpy,screen),//creating window 
        100, 100, 500, 300, //paramerters
        1, BlackPixel(dpy, screen), WhitePixel(dpy, screen)); //lame colours dispalyed

XSelectInput(dpy, win, ExposureMask | KeyPressMask); //close mask KeyPressMask 
XMapWindow(dpy, win); //mapping the window on screen 

//winodow name;
XStoreName(dpy , win , imgpath);

//main part image on xwindow layer
cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy,screen), winw ,winh);
c = cairo_create(cs);

//putting image in center od xwindow
cairo_set_source_surface(c , img,(winw - imgw)/2, (winh - imgh)/2);

while(1){
  XNextEvent(dpy , &event); //hence exit the event which was started and exit the code 
  // diconnecting to xserver
  switch(event.type){
    case Expose:
      if(event.xexpose.count < 1)
        cairo_paint(c);
      break;

  case KeyPress:
      if(XLookupKeysym(&(event.xkey), 0)== XStringToKeysym("q"))
        goto out;
      break;
  }
}

out: 

cairo_destroy(c);
cairo_surface_destroy(cs);
cairo_surface_destroy(img);
XCloseDisplay(dpy);
  return 0;
}
