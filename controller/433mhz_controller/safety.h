#define SAFETY_H 1

#if !defined(PWM_H)
  #include "pwm.h"
#endif

#define SAFETY_MAX 1000

int safety_i = 0;

unsigned long safety_t0 = 0;

/* default safety dt is 1000 ms (i.e 1 sec) */
unsigned long safety_dt = 1000;

int safety_setup()
{
  safety_t0 = millis();
  return 0;
}


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

int set_safety_timer_ms(int ms)
{
  if( ms < 0 ) ms = 0;
  safety_dt = (unsigned long)ms;
  return 0;
}

int safety_timer_ms_reset()
{
  safety_t0 = millis();
  return 0;
}

int safety_timer_ms()
{
  unsigned long t1 = millis();
  if( (t1 - safety_t0) > safety_dt)
  {
    safety_do_stop();
    return 1;
  }
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
