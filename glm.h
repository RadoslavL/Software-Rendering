#include<math.h>

void mat2_mul(float a[4], float b[4], float *out){
   out[0] = a[0] * b[0] + a[1] * b[1];
   out[1] = a[0] * b[1] + a[1] * b[2];
   out[2] = a[2] * b[0] + a[3] * b[2];
   out[3] = a[2] * b[1] + a[3] * b[3];
}

void mat2_vec2_mul(float mat[4], float vec[2], float *out){
   out[0] = mat[0] * vec[0] + mat[1] * vec[1];
   out[1] = mat[2] * vec[0] + mat[3] * vec[1];
}

void mat4_mul(float l[16], float r[16], float *out){
   out[0]  = r[0] * l[0]  + r[4] * l[1]  + r[8]  * l[2]  + r[12] * l[3];
   out[1]  = r[1] * l[0]  + r[5] * l[1]  + r[9]  * l[2]  + r[13] * l[3];
   out[2]  = r[2] * l[0]  + r[6] * l[1]  + r[10] * l[2]  + r[14] * l[3];
   out[3]  = r[3] * l[0]  + r[7] * l[1]  + r[11] * l[2]  + r[15] * l[3];
   out[4]  = r[0] * l[4]  + r[4] * l[5]  + r[8]  * l[6]  + r[12] * l[7];
   out[5]  = r[1] * l[4]  + r[5] * l[5]  + r[9]  * l[6]  + r[13] * l[7];
   out[6]  = r[2] * l[4]  + r[6] * l[5]  + r[10] * l[6]  + r[14] * l[7];
   out[7]  = r[3] * l[4]  + r[7] * l[5]  + r[11] * l[6]  + r[15] * l[7];
   out[8]  = r[0] * l[8]  + r[4] * l[9]  + r[8]  * l[10] + r[12] * l[11];
   out[9]  = r[1] * l[8]  + r[5] * l[9]  + r[9]  * l[10] + r[13] * l[11];
   out[10] = r[2] * l[8]  + r[6] * l[9]  + r[10] * l[10] + r[14] * l[11];
   out[11] = r[3] * l[8]  + r[7] * l[9]  + r[11] * l[10] + r[15] * l[11];
   out[12] = r[0] * l[12] + r[4] * l[13] + r[8]  * l[14] + r[12] * l[15];
   out[13] = r[1] * l[12] + r[5] * l[13] + r[9]  * l[14] + r[13] * l[15];
   out[14] = r[2] * l[12] + r[6] * l[13] + r[10] * l[14] + r[14] * l[15];
   out[15] = r[3] * l[12] + r[7] * l[13] + r[11] * l[14] + r[15] * l[15];
}

void mat4_mul_rotate(float l[16], float r[16], float *out){
   out[0]  = r[0] * l[0]  + r[4] * l[1]  + r[8]  * l[2]  + r[12] * l[3];
   out[1]  = r[1] * l[0]  + r[5] * l[1]  + r[9]  * l[2]  + r[13] * l[3];
   out[2]  = r[2] * l[0]  + r[6] * l[1]  + r[10] * l[2]  + r[14] * l[3];
   out[3]  = r[3] * l[0]  + r[7] * l[1]  + r[11] * l[2]  + r[15] * l[3];
   out[4]  = r[0] * l[4]  + r[4] * l[5]  + r[8]  * l[6]  + r[12] * l[7];
   out[5]  = r[1] * l[4]  + r[5] * l[5]  + r[9]  * l[6]  + r[13] * l[7];
   out[6]  = r[2] * l[4]  + r[6] * l[5]  + r[10] * l[6]  + r[14] * l[7];
   out[7]  = r[3] * l[4]  + r[7] * l[5]  + r[11] * l[6]  + r[15] * l[7];
   out[8]  = r[0] * l[8]  + r[4] * l[9]  + r[8]  * l[10] + r[12] * l[11];
   out[9]  = r[1] * l[8]  + r[5] * l[9]  + r[9]  * l[10] + r[13] * l[11];
   out[10] = r[2] * l[8]  + r[6] * l[9]  + r[10] * l[10] + r[14] * l[11];
   out[11] = r[3] * l[8]  + r[7] * l[9]  + r[11] * l[10] + r[15] * l[11];
   out[12] = r[12];
   out[13] = r[13];
   out[14] = r[14];
   out[15] = r[15];
}

void mat4_vec4_mul(float mat[16], float vec[4], float *out){
   out[0] = vec[0] * mat[0]  + vec[1] * mat[1]  + vec[2] * mat[2]  + vec[3] * mat[3];
   out[1] = vec[0] * mat[4]  + vec[1] * mat[5]  + vec[2] * mat[6]  + vec[3] * mat[7];
   out[2] = vec[0] * mat[8]  + vec[1] * mat[9]  + vec[2] * mat[10] + vec[3] * mat[11];
   out[3] = vec[0] * mat[12] + vec[1] * mat[13] + vec[2] * mat[14] + vec[3] * mat[15];
}

void mat4_rotate(float degrees, unsigned int axis, float *out){
   float radians = degrees * (22.0f / 7.0f) / 180.0f;
   if(axis == 0){
      out[0]  =  1.0f;
      out[1]  =  0.0f;
      out[2]  =  0.0f;
      out[3]  =  0.0f;
      out[4]  =  0.0f;
      out[5]  =  cosf(radians);
      out[6]  = -sinf(radians);
      out[7]  =  0.0f;
      out[8]  =  0.0f;
      out[9]  =  sinf(radians);
      out[10] =  cosf(radians);
      out[11] =  0.0f;
      out[12] =  0.0f;
      out[13] =  0.0f;
      out[14] =  0.0f;
      out[15] =  1.0f;
   }else if(axis == 1){
      out[0]  =  cosf(radians);
      out[1]  =  0.0f;
      out[2]  =  sinf(radians);
      out[3]  =  0.0f;
      out[4]  =  0.0f;
      out[5]  =  1.0f;
      out[6]  =  0.0f;
      out[7]  =  0.0f;
      out[8]  = -sinf(radians);
      out[9]  =  0.0f;
      out[10] =  cosf(radians);
      out[11] =  0.0f;
      out[12] =  0.0f;
      out[13] =  0.0f;
      out[14] =  0.0f;
      out[15] =  1.0f;
   }else if(axis == 2){
      out[0]  =  cosf(radians);
      out[1]  = -sinf(radians);
      out[2]  =  0.0f;
      out[3]  =  0.0f;
      out[4]  =  sinf(radians);
      out[5]  =  cosf(radians);
      out[6]  =  0.0f;
      out[7]  =  0.0f;
      out[8]  =  0.0f;
      out[9]  =  0.0f;
      out[10] =  1.0f;
      out[11] =  0.0f;
      out[12] =  0.0f;
      out[13] =  0.0f;
      out[14] =  0.0f;
      out[15] =  1.0f;
   }
}
