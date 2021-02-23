#define TEST_H 1

String arc_test_string_cw  = "joy right 0.3 0.0";
String arc_test_string_ccw  = "joy right -0.3 -0.0";
String arc_test_string_stop = "joy right 0.0 0.0";


int test2()
{
  Serial.println("CCW");
  arc_rx_decode(arc_test_string_ccw);
  send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  delay(5000);
  Serial.println("CW");
  arc_rx_decode(arc_test_string_cw);
  send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  delay(5000);
  Serial.println("Stop");
  arc_rx_decode(arc_test_string_stop);
  send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  delay(5000);
  return 0;
}

int test1()
{
  Serial.println("CCW");
  send_message(0.3, -0.3);
  delay(5000);
  Serial.println("CW");
  send_message(-0.3, 0.3);
  delay(5000);
  Serial.println("Stop");
  send_message(0.0, 0.0);
  delay(5000);
  return 0;
}
