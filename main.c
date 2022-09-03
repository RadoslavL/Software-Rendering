#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<assert.h>

void fillbottomtriangle(Display *dpy, Window w, GC gc, float v1[2], float v2[2], float v3[2]){
   float top[2];
   float left[2];
   float right[2];
   float currentxleft;
   float currentxright;
   float slopeleft;
   float sloperight;
   if(v1[1] < v2[1] && v1[1] < v3[1]){
      top[0] = v1[0];
      top[1] = v1[1];
      if(v2[0] < v3[0]){
         left[0] = v2[0];
	 left[1] = v2[1];
	 right[0] = v3[0];
	 right[1] = v3[1];
      }else{
         left[0] = v3[0];
	 left[1] = v3[1];
	 right[0] = v2[0];
	 right[1] = v2[1];
      }
   }
   if(v2[1] < v3[1] && v2[1] < v1[1]){
      top[0] = v2[0];
      top[1] = v2[1];
      if(v1[0] < v3[0]){
         left[0] = v1[0];
         left[1] = v1[1];
      }else{
         left[0] = v3[0];
         left[1] = v3[1];
      }
   }
   if(v3[1] < v1[1] && v3[1] < v2[1]){
      top[0] = v3[0];
      top[1] = v3[1];
      if(v1[0] < v2[0]){
         left[0] = v1[0];
         left[1] = v1[1];
      }else{
         left[0] = v2[0];
         left[1] = v2[1];
      }
   }
   currentxleft = top[0];
   currentxright = top[0];
   slopeleft  = (left[0]  - top[0]) / (left[1]  - top[1]);
   sloperight = (right[0] - top[0]) / (right[1] - top[1]);
   int i;
   for(i = top[1]; i <= left[1]; i++){
      XDrawLine(dpy, w, gc, (int)currentxleft, i, (int)currentxright, i);
      currentxleft += slopeleft;
      currentxright += sloperight;
   }
}

int main(){
   Display *dpy = XOpenDisplay(NULL);
   assert(dpy);
   int blackcolor = BlackPixel(dpy, DefaultScreen(dpy));
   int whitecolor = WhitePixel(dpy, DefaultScreen(dpy));
   Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 640, 480, 0, blackcolor, blackcolor);
   XSelectInput(dpy, w, StructureNotifyMask);
   XMapWindow(dpy, w);
   GC gc = XCreateGC(dpy, w, 0, NULL);
   XSetForeground(dpy, gc, whitecolor);
   XEvent e;
   for(;;){
      XNextEvent(dpy, &e);
      if(e.type == MapNotify)
         break;
   }
   float v1[2] = {50, 0};
   float v2[2] = {0, 50};
   float v3[2] = {100, 50};
   fillbottomtriangle(dpy, w, gc, v1, v2, v3);
   //XDrawLine(dpy, w, gc, 10, 60, 180, 20);
   XFlush(dpy);
   while(1){
      //printf("Loop!\n");
   }
   return 0;
}
