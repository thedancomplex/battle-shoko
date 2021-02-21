#define JOYSTICK_H 1

#if !defined(MESSAGE_H)
  #include "message.h"
#endif

#define JOY_MOT_LEFT MOT_LEFT
#define JOY_MOT_RIGHT MOT_RIGHT

float joy_mot_left  = 0.0;
float joy_mot_right = 0.0;

float get_mot_val_joy(int m)
{
  if(m == JOY_MOT_LEFT)  return joy_mot_left;
  if(m == JOY_MOT_RIGHT) return joy_mot_right;
  return 0.0;
}

int  xy_to_joy(float x, float y){
  if(x >  1.0) x =  1.0;
  if(x < -1.0) x = -1.0;
  if(y >  1.0) y =  1.0;
  if(y < -1.0) y = -1.0;
  
  x = -x;
  float v = (1.0-abs(x))*(y) + y;
  float w = (1.0-abs(y))*(x) + x;
  float r = (v+w)/2.0;
  float l = (v-w)/2.0;

  if(r >  1.0) r =  1.0;
  if(r < -1.0) r = -1.0;
  if(l >  1.0) l =  1.0;
  if(l < -1.0) l = -1.0;
  
  joy_mot_right = r;
  joy_mot_left  = l;
  return 0;
}
