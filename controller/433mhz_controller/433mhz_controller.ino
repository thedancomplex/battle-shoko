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


void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer
  coms_setup();
  pwm_setup();
}




void loop() {
  if( get_message() == 0)
  {
    /* Received Mesage */
    safety_message_received();
    set_mot(MOT_LEFT,  get_mot_val(MOT_LEFT));
    set_mot(MOT_RIGHT, get_mot_val(MOT_RIGHT));
  }

  /* Safety Timer */
  safety_timer();
}
