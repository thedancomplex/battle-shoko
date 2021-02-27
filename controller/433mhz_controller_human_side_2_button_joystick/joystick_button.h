#define JOYSTICK_BUTTON_H 1

#define JOYSTICK_BUTTON_PIN_RIGHT 12
#define JOYSTICK_BUTTON_PIN_LEFT 11

#define JOYSTICK_BUTTON_SPEED 0.15


int joystick_button_setup()
{
  pinMode(JOYSTICK_BUTTON_PIN_RIGHT, INPUT);
  pinMode(JOYSTICK_BUTTON_PIN_LEFT,  INPUT);
  return 0;
}



int joystick_button_is_pressed(int p)
{
  int v = digitalRead(p);
  if(v == 0) return 1;
  else return 0;
}

int joystick_button_run()
{
  double s = JOYSTICK_BUTTON_SPEED;
  int mot_r = joystick_button_is_pressed(JOYSTICK_BUTTON_PIN_RIGHT);
  int mot_l = joystick_button_is_pressed(JOYSTICK_BUTTON_PIN_LEFT);
  Serial.print(mot_l);
  Serial.print(" ");
  Serial.print(mot_r);
  Serial.println();
  if     ( (mot_r == 1) &  (mot_l == 1) ){ send_message(MODE_DIFFERENTIAL_DRIVE,  s,    s);   Serial.println("FWD");}
  else if( (mot_r == 1) &  (mot_l == 0) ){ send_message(MODE_DIFFERENTIAL_DRIVE, -s,    s);   Serial.println("CCW");}
  else if( (mot_r == 0) &  (mot_l == 1) ){ send_message(MODE_DIFFERENTIAL_DRIVE,  s,   -s);   Serial.println("CW");}
  else                                   { send_message(MODE_DIFFERENTIAL_DRIVE,  0.0,  0.0); Serial.println("STOP");}
  
  return 0;
}
