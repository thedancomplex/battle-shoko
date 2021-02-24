#define TEST_H 1

String arc_test_string_cw  = "joy right 0.3 0.0";
String arc_test_string_ccw  = "joy right -0.3 -0.0";
String arc_test_string_stop = "joy right 0.0 0.0";

String arc_test_string_fwd  = "joy right 0.0 0.3";
String arc_test_string_bkw  = "joy right -0.0 -0.3";

int test6()
{
  joystick_button_run();
  delay(50);
  return 0;
}

int test4()
{
  if(coms_serial_read()== 0)
  {
    send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  }
  return 0;
}


int test3()
{
  Serial.println("FWD");
  arc_rx_decode(arc_test_string_fwd);
  send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  delay(5000);
  Serial.println("BKW");
  arc_rx_decode(arc_test_string_bkw);
  send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  delay(5000);
  Serial.println("Stop");
  arc_rx_decode(arc_test_string_stop);
  send_message(MODE_JOYSTICK, arc_robot.right.x, arc_robot.right.y);
  delay(5000);
  return 0;
}

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
