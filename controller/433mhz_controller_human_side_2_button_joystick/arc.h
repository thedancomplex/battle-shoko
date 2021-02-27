#define ARC_H 1

#define ARC_OK            0
#define ARC_ERROR         1
#define ARC_JOY_RIGHT     2 
#define ARC_JOY_LEFT      3
#define ARC_BUTTON_AND    4
#define ARC_BUTTON_START  5
#define ARC_BUTTON_SELECT 6


typedef struct arc_2dof {
  float x;     ///< dd: m_right
  float y;     ///< dd: m_left
}__attribute__((packed)) arc_2dof_t;

typedef struct arc_joy {
  arc_2dof_t left;
  arc_2dof_t right;
}__attribute__((packed)) arc_joy_t;


arc_joy_t arc;
arc_joy_t arc_robot;

int arc_setup()
{
  memset(&arc, 0, sizeof(arc));
  memset(&arc_robot, 0, sizeof(arc_robot));
  return 0;
}

int arc_2_robot()
{
  arc_robot.right.x = arc.right.y;
  arc_robot.left.x  = arc.left.y;
  arc_robot.right.y = arc.right.x;
  arc_robot.left.y  = arc.left.x;
  return 0;
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}





int arc_rx_decode(String s){
  int len = s.length();
  int n = len + 1;
  char packetBuffer[n]; //buffer to hold incoming packet,
  //memset(packetBuffer, 0, sizeof(packetBuffer));
  s.toCharArray(packetBuffer, n);
  String v0 = getValue(packetBuffer, ' ', 0);
  if(v0 == "joy"){
      String v1 = getValue(packetBuffer, ' ', 1);
      if(v1 == "right"){

        String d2 = getValue(packetBuffer, ' ', 2);
        arc.right.x = d2.toDouble();

        String d3 = getValue(packetBuffer, ' ', 3);
        arc.right.y = d3.toDouble();
        arc_2_robot();
        return ARC_JOY_RIGHT;
      }
      if(v1 == "left"){
        String d2 = getValue(packetBuffer, ' ', 2);
        arc.left.x = d2.toDouble();

        String d3 = getValue(packetBuffer, ' ', 3);
        arc.left.y = d3.toDouble();
        arc_2_robot();
        return ARC_JOY_LEFT;
      }
  }
  else if(v0 == "button"){
      String v1 = getValue(packetBuffer, ' ', 1);
      if(v1 == "&") return ARC_BUTTON_AND;
 
  }
  return ARC_ERROR;
}
