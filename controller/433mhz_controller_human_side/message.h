#define MESSAGE_H 1

#define MSG_OK 0
#define MSG_ERR 1

#define MOT_RIGHT 0
#define MOT_LEFT 1

#define JOY_X MOT_RIGHT
#define JOY_Y MOT_LEFT


#define MODE_DIFFERENTIAL_DRIVE 0
#define MODE_JOYSTICK 1

typedef struct s_message {
  float d0;     ///< dd: m_right
  float d1;     ///< dd: m_left
  int16_t mode; ///<  mode
}__attribute__((packed)) s_message_t;
