#include<stdio.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<assert.h>

void fillbottomtriangle(Display *dpy, Window w, GC gc, float v1[2], float v2[2], float v3[2]){
   printf("v1: %f, %f; v2: %f, %f; v3: %f, %f\n", v1[0], v1[1], v2[0], v2[1], v3[0], v3[1]);
   fflush(stdout);
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
	 right[0] = v3[0];
         right[1] = v3[1];
      }else{
         left[0] = v3[0];
         left[1] = v3[1];
	 right[0] = v1[0];
         right[1] = v1[1];
      }
   }
   if(v3[1] < v1[1] && v3[1] < v2[1]){
      top[0] = v3[0];
      top[1] = v3[1];
      if(v1[0] < v2[0]){
         left[0] = v1[0];
         left[1] = v1[1];
	 right[0] = v2[0];
         right[1] = v2[1];
      }else{
         left[0] = v2[0];
         left[1] = v2[1];
	 right[0] = v1[0];
         right[1] = v1[1];
      }
   }
   printf("top: %f, %f; left: %f, %f; right: %f, %f\n", top[0], top[1], left[0], left[1], right[0], right[1]);
   fflush(stdout);
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

void filltoptriangle(Display *dpy, Window w, GC gc, float v1[2], float v2[2], float v3[2]){
   printf("v1: %f, %f; v2: %f, %f; v3: %f, %f\n", v1[0], v1[1], v2[0], v2[1], v3[0], v3[1]);
   fflush(stdout);
   float bottom[2];
   float left[2];
   float right[2];
   float currentxleft;
   float currentxright;
   float slopeleft;
   float sloperight;
   if(v1[1] > v2[1] && v1[1] > v3[1]){
      bottom[0] = v1[0];
      bottom[1] = v1[1];
      printf("First\n");
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
   if(v2[1] > v3[1] && v2[1] > v1[1]){
      bottom[0] = v2[0];
      bottom[1] = v2[1];
      printf("Second\n");
      if(v1[0] < v3[0]){
         left[0] = v1[0];
         left[1] = v1[1];
	 right[0] = v3[0];
         right[1] = v3[1];
      }else{
         left[0] = v3[0];
         left[1] = v3[1];
	 right[0] = v1[0];
         right[1] = v1[1];
      }
   }
   if(v3[1] > v1[1] && v3[1] > v2[1]){
      bottom[0] = v3[0];
      bottom[1] = v3[1];
      printf("Third\n");
      if(v1[0] < v2[0]){
         left[0] = v1[0];
         left[1] = v1[1];
	 right[0] = v2[0];
         right[1] = v2[1];
      }else{
         left[0] = v2[0];
         left[1] = v2[1];
	 right[0] = v1[0];
         right[1] = v1[1];
      }
   }
   printf("bottom: %f, %f; left: %f, %f; right: %f, %f\n", bottom[0], bottom[1], left[0], left[1], right[0], right[1]);
   fflush(stdout);
   currentxleft = bottom[0];
   currentxright = bottom[0];
   slopeleft  = (bottom[0] - left[0])  / (bottom[1] - left[1]);
   sloperight = (bottom[0] - right[0]) / (bottom[1] - right[1]);
   int i;
   for(i = bottom[1]; i > left[1]; i--){
      XDrawLine(dpy, w, gc, (int)currentxleft, i, (int)currentxright, i);
      currentxleft -= slopeleft;
      currentxright -= sloperight;
   }
}

void drawtriangle(Display *dpy, Window w, GC gc, float v1[2], float v2[2], float v3[2]){
   float max[2];
   float mid[2];
   float min[2];
   float mid2[2];
   float flattop = 0;
   float flatbottom = 0;
   if(v1[1] < v2[1] && v2[1] < v3[1]){
      max[0] = v1[0];
      max[1] = v1[1];
      mid[0] = v2[0];
      mid[1] = v2[1];
      min[0] = v3[0];
      min[1] = v3[1];
      printf("v1: max, v2: mid, v3: min\n");
   }else if(v1[1] < v3[1] && v3[1] < v2[1]){
      max[0] = v1[0];
      max[1] = v1[1];
      mid[0] = v3[0];
      mid[1] = v3[1];
      min[0] = v2[0];
      min[1] = v2[1];
      printf("v1: max, v3: mid, v2: min\n");
   }else if(v2[1] < v1[1] && v1[1] < v3[1]){
      max[0] = v2[0];
      max[1] = v2[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v3[0];
      min[1] = v3[1];
      printf("v2: max, v1: mid, v3: min\n");
   }else if(v2[1] < v3[1] && v3[1] < v1[1]){
      max[0] = v2[0];
      max[1] = v2[1];
      mid[0] = v3[0];
      mid[1] = v3[1];
      min[0] = v1[0];
      min[1] = v1[1];
      printf("v2: max, v3: mid, v1: min\n");
   }else if(v3[1] < v1[1] && v1[1] < v2[1]){
      max[0] = v3[0];
      max[1] = v3[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v2[0];
      min[1] = v2[1];
      printf("v3: max, v1: mid, v2: min\n");
   }else if(v3[1] < v2[1] && v2[1] < v1[1]){
      max[0] = v3[0];
      max[1] = v3[1];
      mid[0] = v2[0];
      mid[1] = v2[1];
      min[0] = v1[0];
      min[1] = v1[1];
      printf("v3: max, v2: mid, v1: min\n");
   }else if(v1[1] < v2[1] && v2[1] == v3[1]){
      max[0] = v1[0];
      max[1] = v1[1];
      mid[0] = v2[0];
      mid[1] = v2[1];
      min[0] = v3[0];
      min[1] = v3[1];
      flatbottom = 1;
   }else if(v2[1] < v1[1] && v1[1] == v3[1]){
      max[0] = v2[0];
      max[1] = v2[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v3[0];
      min[1] = v3[1];
      flatbottom = 1;
   }else if(v3[1] < v1[1] && v1[1] == v2[1]){
      max[0] = v3[0];
      max[1] = v3[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v2[0];
      min[1] = v2[1];
      flatbottom = 1;
   }else if(v1[1] > v2[1] && v2[1] == v3[1]){
      max[0] = v2[0];
      max[1] = v2[1];
      mid[0] = v3[0];
      mid[1] = v3[1];
      min[0] = v1[0];
      min[1] = v1[1];
      flattop = 1;
   }else if(v2[1] > v1[1] & v1[1] == v3[1]){
      max[0] = v1[0];
      max[1] = v1[1];
      mid[0] = v3[0];
      mid[1] = v3[1];
      min[0] = v2[0];
      min[1] = v2[1];
      flattop = 1;
   }else if(v3[1] > v1[1] && v1[1] == v2[1]){
      max[0] = v3[0];
      max[1] = v3[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v2[0];
      min[1] = v2[1];
      flattop = 1;
   }
   printf("max: %f, %f; mid: %f, %f; min: %f, %f\n", max[0], max[1], mid[0], mid[1], min[0], min[1]);
   fflush(stdout);
   if(flatbottom == 1){
      fillbottomtriangle(dpy, w, gc, max, mid, min);
   }else if(flattop == 1){
      filltoptriangle(dpy, w, gc, max, mid, min);
   }else{
      mid2[0] = max[0] + ((mid[1] - max[1]) / (min[1] - max[1])) * (min[0] - max[0]);
      mid2[1] = mid[1];
      printf("mid2: %f, %f\n", mid2[0], mid2[1]);
      fillbottomtriangle(dpy, w, gc, max, mid2, mid);
      filltoptriangle(dpy, w, gc, mid, mid2, min);
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
   float v1[2] = {0, 0};
   float v2[2] = {100, 10};
   float v3[2] = {50, 100};
   //filltoptriangle(dpy, w, gc, v1, v2, v3);
   drawtriangle(dpy, w, gc, v1, v2, v3);
   //fillbottomtriangle(dpy, w, gc, max, mid2, mid);
   //filltoptriangle(dpy, w, gc, mid, mid2, min);
   //XDrawLine(dpy, w, gc, 10, 60, 180, 20);
   XFlush(dpy);
   while(1){
      //printf("Loop!\n");
   }
   return 0;
}
