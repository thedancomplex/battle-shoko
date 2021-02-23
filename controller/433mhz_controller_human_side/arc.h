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

int arc_setup()
{
  memset(&arc, 0, sizeof(arc));
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





int doStringDecode(String s){
  int len = s.length();
  int n = len + 1;
  char packetBuffer[n]; //buffer to hold incoming packet,
  packetBuffer[n-1] = 0;
  String v0 = getValue(packetBuffer, ' ', 0);
  if(v0 == "joy"){
      String v1 = getValue(packetBuffer, ' ', 1);
      if(v1 == "right"){

        String d2 = getValue(packetBuffer, ' ', 2);
        arc.right.x = d2.toDouble();

        String d3 = getValue(packetBuffer, ' ', 3);
        arc.right.y = d3.toDouble();
        return ARC_JOY_RIGHT;
      }
      if(v1 == "left"){
        String d2 = getValue(packetBuffer, ' ', 2);
        arc.left.x = d2.toDouble();

        String d3 = getValue(packetBuffer, ' ', 3);
        arc.left.y = d3.toDouble();
        return ARC_JOY_LEFT;
      }
  }
  else if(v0 == "button"){
      String v1 = getValue(packetBuffer, ' ', 1);
      if(v1 == "&") return ARC_BUTTON_AND;
 
  }
  return ARC_ERROR;
}
