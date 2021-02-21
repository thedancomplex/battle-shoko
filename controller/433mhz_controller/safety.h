#define SAFETY_H 1

#if !defined(PWM_H)
  #include "pwm.h"
#endif

#define SAFETY_MAX 1000

int safety_i = 0;

int safety_message_received()
{
  safety_i = SAFETY_MAX;
  return 0;
}

int safety_do_stop()
{
  int ret = 0;
  ret += set_mot(MOT_LEFT,  0.0);
  ret += set_mot(MOT_RIGHT, 0.0);
  if(ret > 0) return 1;
  return 0;
}

int safety_timer()
{
  safety_i -= 1;
  if(safety_i < 0){
    safety_i = 0;
    safety_do_stop();
    return 1;
  }
  else return 0;

}
