#include "coms.h"
#include "pwm.h"

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
    int v = s_msg.mode % 3;
    if ( v == 1)
    {
      Serial.println("Set PWM - CW"); set_mot(MOT_LEFT, 0.35); set_mot(MOT_RIGHT, -0.35);
    }
    else if (v == 2)
    {
      Serial.println("Set PWM - CCW"); set_mot(MOT_LEFT, -0.35); set_mot(MOT_RIGHT, 0.35);
    }
    else
    {
      Serial.println("Set PWM - Stop"); set_mot(MOT_LEFT, 0.0); set_mot(MOT_RIGHT, 0.0);
    }
  }
}
