#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<assert.h>
#include<cglm/cglm.h>
#include"glm.h"

const unsigned int width = 1054;
const unsigned int height = 1057;

void vertexshader(float position[3], float model[16], float view[16], float proj[16], float out[2]){
   float int1[16];
   float int2[16];
   float int3[4];
   float int4[4];
   float int5[2];
   float int6[2];
   /*
   glm_mat4_mul(view, model, int1);
   glm_mat4_mul(proj, int1, int2);
   glm_mat4_mulv(int2, (vec4){position[1], position[2], position[3], 1.0f}, int3);
   */
   int3[0] = position[0];
   int3[1] = position[1];
   int3[2] = position[2];
   int3[3] = 1.0f;
   mat4_mul(view, model, int1);
   mat4_mul(proj, int1, int2);
   mat4_vec4_mul(int2, int3, int4);
   int5[0] = int4[0] / int4[3];
   int5[1] = int4[1] / int4[3];
   int6[0] = int5[0] * 0.5f + 0.5f;
   int6[1] = int5[1] * 0.5f + 0.5f;
   out[0] = int6[0] * width;
   out[1] = (1.0f - int6[1]) * height;
   printf("%f, %f\n", out[0], out[1]);
   //glm_vec2_ucopy(int3, out);
}

void fragmentshader(float color[3], float out[4]){
   out[0] = /*rand() % 255;*/ color[0];
   out[1] = /*rand() % 255;*/ color[1];
   out[2] = /*rand() % 255;*/ color[2];
   out[3] = 1.0f;
}

void clearscreen(int *framebuffer){
   int i;
   for(i = 0; i < width * height; i++){
      framebuffer[i] = 0xFF000000;
   }
}

void fillbottomtriangle(float v1[2], float v2[2], float v3[2], int *framebuffer){
   //printf("v1: %f, %f; v2: %f, %f; v3: %f, %f\n", v1[0], v1[1], v2[0], v2[1], v3[0], v3[1]);
   //fflush(stdout);
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
   //printf("top: %f, %f; left: %f, %f; right: %f, %f\n", top[0], top[1], left[0], left[1], right[0], right[1]);
   //fflush(stdout);
   currentxleft = top[0];
   currentxright = top[0];
   slopeleft  = (left[0]  - top[0]) / (left[1]  - top[1]);
   sloperight = (right[0] - top[0]) / (right[1] - top[1]);
   float incolor[3] = {1.0f, 1.0f, 1.0f};
   float outcolor[4];
   int i, j;
   for(i = top[1]; i <= left[1]; i++){
      for(j = currentxleft; j <= currentxright; j++){
         fragmentshader(incolor, outcolor);
	 framebuffer[i * width + j] = (255 << 24 | ((int)outcolor[0] * 255 & 0xFF) << 16 | ((int)outcolor[1] * 255 & 0xFF) << 8 | (int)outcolor[2] * 255 & 0xFF);
      }
      currentxleft += slopeleft;
      currentxright += sloperight;
   }
}

void filltoptriangle(float v1[2], float v2[2], float v3[2], int *framebuffer){
   //printf("v1: %f, %f; v2: %f, %f; v3: %f, %f\n", v1[0], v1[1], v2[0], v2[1], v3[0], v3[1]);
   //fflush(stdout);
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
   //printf("bottom: %f, %f; left: %f, %f; right: %f, %f\n", bottom[0], bottom[1], left[0], left[1], right[0], right[1]);
   //fflush(stdout);
   currentxleft = bottom[0];
   currentxright = bottom[0];
   slopeleft  = (bottom[0] - left[0])  / (bottom[1] - left[1]);
   sloperight = (bottom[0] - right[0]) / (bottom[1] - right[1]);
   float incolor[3] = {1.0f, 1.0f, 1.0f};
   float outcolor[4];
   int i, j;
   for(i = bottom[1]; i > left[1]; i--){
      for(j = currentxleft; j <= currentxright; j++){
         fragmentshader(incolor, outcolor);
	 framebuffer[i * width + j] = (255 << 24 | ((int)outcolor[0] * 255 & 0xFF) << 16 | ((int)outcolor[1] * 255 & 0xFF) << 8 | (int)outcolor[2] * 255 & 0xFF);
      }
      currentxleft -= slopeleft;
      currentxright -= sloperight;
   }
}

void drawtriangle(float pos1[3], float pos2[3], float pos3[3], float model[16], float view[16], float proj[16], int *framebuffer){
   float v1[2];
   float v2[2];
   float v3[2];
   //glm_lookat((vec3){0, 0, 5}, (vec3){0, 0, 0}, (vec3){0, 1, 0}, view);
   //glm_perspective(glm_rad(45.0f), (float)width/(float)height, 0.1f, 100.0f, proj);
   vertexshader(pos1, model, view, proj, v1);
   vertexshader(pos2, model, view, proj, v2);
   vertexshader(pos3, model, view, proj, v3);
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
      //printf("v1: max, v2: mid, v3: min\n");
   }else if(v1[1] < v3[1] && v3[1] < v2[1]){
      max[0] = v1[0];
      max[1] = v1[1];
      mid[0] = v3[0];
      mid[1] = v3[1];
      min[0] = v2[0];
      min[1] = v2[1];
      //printf("v1: max, v3: mid, v2: min\n");
   }else if(v2[1] < v1[1] && v1[1] < v3[1]){
      max[0] = v2[0];
      max[1] = v2[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v3[0];
      min[1] = v3[1];
      //printf("v2: max, v1: mid, v3: min\n");
   }else if(v2[1] < v3[1] && v3[1] < v1[1]){
      max[0] = v2[0];
      max[1] = v2[1];
      mid[0] = v3[0];
      mid[1] = v3[1];
      min[0] = v1[0];
      min[1] = v1[1];
      //printf("v2: max, v3: mid, v1: min\n");
   }else if(v3[1] < v1[1] && v1[1] < v2[1]){
      max[0] = v3[0];
      max[1] = v3[1];
      mid[0] = v1[0];
      mid[1] = v1[1];
      min[0] = v2[0];
      min[1] = v2[1];
      //printf("v3: max, v1: mid, v2: min\n");
   }else if(v3[1] < v2[1] && v2[1] < v1[1]){
      max[0] = v3[0];
      max[1] = v3[1];
      mid[0] = v2[0];
      mid[1] = v2[1];
      min[0] = v1[0];
      min[1] = v1[1];
      //printf("v3: max, v2: mid, v1: min\n");
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
   //printf("max: %f, %f; mid: %f, %f; min: %f, %f\n", max[0], max[1], mid[0], mid[1], min[0], min[1]);
   //fflush(stdout);
   if(flatbottom == 1){
      fillbottomtriangle(max, mid, min, framebuffer);
   }else if(flattop == 1){
      filltoptriangle(max, mid, min, framebuffer);
   }else{
      mid2[0] = max[0] + ((mid[1] - max[1]) / (min[1] - max[1])) * (min[0] - max[0]);
      mid2[1] = mid[1];
      //printf("mid2: %f, %f\n", mid2[0], mid2[1]);
      fillbottomtriangle(max, mid2, mid, framebuffer);
      filltoptriangle(mid, mid2, min, framebuffer);
   }
}

int main(){
   Display *dpy = XOpenDisplay(NULL);
   assert(dpy);
   int blackcolor = BlackPixel(dpy, DefaultScreen(dpy));
   int whitecolor = WhitePixel(dpy, DefaultScreen(dpy));
   Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, width, height, 0, blackcolor, blackcolor);
   XSelectInput(dpy, w, StructureNotifyMask);
   XMapWindow(dpy, w);
   XStoreName(dpy, w, "Software rendering");
   //XSelectInput(dpy, w, ExposureMask);
   GC gc = XCreateGC(dpy, w, 0, NULL);
   GC background = XCreateGC(dpy, w, 0, NULL);
   //XSetErrorHandler(errorhandle);
   XImage *ximage;
   XSetForeground(dpy, gc, whitecolor);
   XSetForeground(dpy, background, blackcolor);
   XEvent e;
   for(;;){
      XNextEvent(dpy, &e);
      if(e.type == MapNotify)
         break;
   }
   float model[16] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1};
   float view[16] = {1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 2,
                     0, 0, 0, 1};
   float proj[16] = {1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 0, 1,
                     0, 0, 1, 0};
   /*
   float v1[3] = {-0.5f, -0.5f,  0.0f};
   float v2[3] = {-0.5f,  0.5f,  0.0f};
   float v3[3] = { 0.5f,  0.5f,  0.0f};
   float v4[3] = { 0.5f, -0.5f,  0.0f};
   */
   float v1[3] = {-0.5f, -0.5f,  0.0f};
   float v2[3] = { 0.0f,  0.5f,  0.0f};
   float v3[3] = { 0.5f, -0.5f,  0.0f};
   int *framebuffer = malloc(width * height * sizeof(int));
   //drawtriangle(dpy, w, gc, colormap, v1, v2, v3, model, view, proj);
   //drawtriangle(dpy, w, gc, colormap, v1, v3, v4, model, view, proj);
   float angle = 0.0f;
   //filltoptriangle(dpy, w, gc, v1, v2, v3);
   //fillbottomtriangle(dpy, w, gc, max, mid2, mid);
   //filltoptriangle(dpy, w, gc, mid, mid2, min);
   //XDrawLine(dpy, w, gc, 10, 60, 180, 20);
   XFlush(dpy);
   while(1){
      //printf("Loop!\n");
      //XClearArea(dpy, w, 400, 400, 600, 600, 0);
      //XFillRectangle(dpy, w, background, 0, 0, width, height);
      clearscreen(framebuffer);
      drawtriangle(v1, v2, v3, model, view, proj, framebuffer);
      //ximage = XCreateImage(dpy, vinfo.visual, 24, ZPixmap, 0, (char*)framebuffer, width, height, 8, width * 4);
      //XPutImage(dpy, w, gc, ximage, 0, 0, 0, 0, width, height);
      //drawtriangle(v1, v3, v4, model, view, proj, framebuffer);
      ximage = XCreateImage(dpy, DefaultVisual(dpy, DefaultScreen(dpy)), DefaultDepth(dpy, DefaultScreen(dpy)), ZPixmap, 0, (char*)framebuffer, width, height, 8, 0);
      //image = XCreateBitmapFromData(dpy, w, (char*)framebuffer, width, height);
      //XCopyArea(dpy, image, w, gc, 0, 0, width, height, 0, 0);
      XPutImage(dpy, w, gc, ximage, 0, 0, 0, 0, width, height);
      angle += 1.0f;
      mat4_rotate(angle, 1, model);
   }
   XCloseDisplay(dpy);
   free(framebuffer);
   return 0;
}
