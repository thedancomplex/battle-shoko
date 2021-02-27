// rf69 demo tx rx.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RH_RF69 class. RH_RF69 class does not provide for addressing or
// reliability, so you should only use RH_RF69  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf69_server.
// Demonstrates the use of AES encryption, setting the frequency and modem 
// configuration

#if !defined(COMS_H)
  #include "coms.h"
#endif

#if !defined(ARC_H)
  #include "arc.h"
#endif

#if !defined(COMS_SERIAL_H)
  #include "coms_serial.h"
#endif

#if !defined(JOYSTICK_BUTTON_H)
  #include "joystick_button.h"
#endif

#if !defined(TEST_H)
  #include "test.h"
#endif




void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer
  joystick_button_setup();
  coms_setup();
  arc_setup();
}







void loop() 
{
  test6();
}
