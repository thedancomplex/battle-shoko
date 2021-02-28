#define RC_READ_H 1

#define RC_READ_JOY_RIGHT_Y 0
#define RC_READ_JOY_RIGHT_X 1

#define RC_READ_PWM_CENTER 1500
#define RC_READ_PWM_DT     500
#define RC_READ_PWM_MIN    (RC_READ_PWM_CENTER - RC_READ_PWM_DT)
#define RC_READ_PWM_MAX    (RC_READ_PWM_CENTER + RC_READ_PWM_DT)
#define RC_READ_PWM_ERROR  500

#define RC_READ_JOY_RIGHT_Y_DIR -1.0
#define RC_READ_JOY_RIGHT_X_DIR  1.0


float rc_read_pwm_to_one(unsigned long vl)
{
  float dt = (float)(RC_READ_PWM_DT);
  float e  = (float)((float)vl - (float)RC_READ_PWM_CENTER);
  float v  = e / dt;
  if(v > 1.0)  v =  1.0;
  if(v < -1.0) v = -1.0;
  return v;
}

typedef struct rc_read_2dof {
  float x;     ///< dd: m_right
  float y;     ///< dd: m_left
}__attribute__((packed)) rc_read_2dof_t;

typedef struct rc_read_joy {
  rc_read_2dof_t left;
  rc_read_2dof_t right;
}__attribute__((packed)) rc_read_joy_t;

typedef struct rc_read_pwm_2dof {
  unsigned long x;     ///< dd: m_right
  unsigned long y;     ///< dd: m_left
}__attribute__((packed)) rc_read_pwm_2dof_t;

typedef struct rc_read_pwm_joy {
  rc_read_2dof_t left;
  rc_read_2dof_t right;
}__attribute__((packed)) rc_read_pwm_joy_t;

rc_read_joy_t rc_joy;
rc_read_pwm_joy_t rc_joy_pwm;


int rc_read_pwm_to_message()
{
  if     (rc_joy_pwm.right.x > RC_READ_PWM_MAX)   rc_joy_pwm.right.x = RC_READ_PWM_MAX;
  else if(rc_joy_pwm.right.x < RC_READ_PWM_ERROR) rc_joy_pwm.right.x = RC_READ_PWM_CENTER;
  else if(rc_joy_pwm.right.x < RC_READ_PWM_MIN)   rc_joy_pwm.right.x = RC_READ_PWM_MIN;

  if     (rc_joy_pwm.right.y > RC_READ_PWM_MAX)   rc_joy_pwm.right.y = RC_READ_PWM_MAX;
  else if(rc_joy_pwm.right.y < RC_READ_PWM_ERROR) rc_joy_pwm.right.y = RC_READ_PWM_CENTER;
  else if(rc_joy_pwm.right.y < RC_READ_PWM_MIN)   rc_joy_pwm.right.y = RC_READ_PWM_MIN;

  float vrx = rc_read_pwm_to_one(rc_joy_pwm.right.x) * RC_READ_JOY_RIGHT_X_DIR;
  float vry = rc_read_pwm_to_one(rc_joy_pwm.right.y) * RC_READ_JOY_RIGHT_Y_DIR;

  rc_joy.right.x = vrx;
  rc_joy.right.y = vry;
  return 0;
}





int rc_read_setup()
{
  memset(&rc_joy, 0, sizeof(rc_joy));
  pinMode(RC_READ_JOY_RIGHT_X, INPUT);
  pinMode(RC_READ_JOY_RIGHT_Y, INPUT);
  return 0;
}

int rc_read_update()
{
  rc_joy_pwm.right.x = pulseIn(RC_READ_JOY_RIGHT_X, HIGH);
  rc_joy_pwm.right.y = pulseIn(RC_READ_JOY_RIGHT_Y, HIGH);
  rc_read_pwm_to_message();
  return 0;
}
