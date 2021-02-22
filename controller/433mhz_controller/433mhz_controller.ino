#if !defined(COMS_H)
  #include "coms.h"
#endif

#if !defined(MESSAGE_H)
  #include "message.h"
#endif

#if !defined(PWM_H)
  #include "pwm.h"
#endif

#if !defined(SAFETY_H)
  #include "safety.h"
#endif

#if !defined(JOYSTICK_H)
  #include "joystick.h"
#endif

void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer
  coms_setup();
  pwm_setup();
  safety_setup();
  //soft_start();
}

int soft_start()
{
  Serial.println("Do Diff Drive");
  int ret = 0;
  ret += set_mot(PWM_CHAN_MOT_LEFT,  0.0);
  Serial.println(1);
  ret += set_mot(PWM_CHAN_MOT_RIGHT, 0.0);
  Serial.println(2);
  if (ret >=1) ret = 1;
  delay(5000);
  return ret;
}


int do_diff_drive()
{
  Serial.println("Do Diff Drive");
  int ret = 0;
  ret += set_mot(PWM_CHAN_MOT_LEFT,  get_mot_val(MOT_LEFT));
  Serial.println(1);
  ret += set_mot(PWM_CHAN_MOT_RIGHT, get_mot_val(MOT_RIGHT));
  Serial.println(2);
  if (ret >=1) ret = 1;
  return ret;
}

int do_joystick()
{
  float x = get_mot_val(JOY_X);
  float y = get_mot_val(JOY_Y);
  if( xy_to_joy(x,y) ) return 1;
  int ret = 0;
  ret += set_mot(MOT_LEFT,  get_mot_val_joy(MOT_LEFT));
  ret += set_mot(MOT_RIGHT, get_mot_val_joy(MOT_RIGHT));
  if(ret >= 1) ret = 1;
  return ret;
}

int ic = 0;
void loop() {
  if( get_message() == 0)
  {
    /* Received Mesage */
    safety_timer_ms_reset();
    if(get_mode() == MODE_DIFFERENTIAL_DRIVE) do_diff_drive();
    if(get_mode() == MODE_JOYSTICK          ) do_joystick();
  }

  /* Safety Timer */
  safety_timer_ms();
}
