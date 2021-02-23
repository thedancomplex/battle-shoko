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

void setup() 
{
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, remove if not tethered to computer

  coms_setup();
}

void loop() {
  Serial.println("CCW");
  send_message(0.3, -0.3);
  delay(3000);
  Serial.println("CW");
  send_message(-0.3, 0.3);
  delay(3000);
  Serial.println("Stop");
  send_message(0.0, 0.0);
  delay(3000);
}
