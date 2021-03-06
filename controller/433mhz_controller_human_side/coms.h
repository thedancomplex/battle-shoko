// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging client
// with the RH_RF69 class. RH_RF69 class does not provide for addressing or
// reliability, so you should only use RH_RF69  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf69_server.
// Demonstrates the use of AES encryption, setting the frequency and modem 
// configuration


#define COMS_H 1

int set_message_mode(int m);

int set_message(float d0, float d1);
int set_message(int m, float d0, float d1);

int set_message_motor(int m, float v);

int send_message();
int send_message(float d0, float d1);
int send_message(int m, float d0, float d1);


void Blink(byte PIN, byte DELAY_MS, byte loops);

#if !defined(MESSAGE_H)
  #include "message.h"
#endif


#include <SPI.h>
#include <RH_RF69.h>
#include <RHReliableDatagram.h>
/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 433.0

// Where to send packets to!
#define DEST_ADDRESS   1
// change addresses for each client board, any number :)
#define MY_ADDRESS     2


#if defined (__AVR_ATmega32U4__) // Feather 32u4 w/Radio
  #define RFM69_CS      8
  #define RFM69_INT     7
  #define RFM69_RST     4
  #define LED           13
#endif

#if defined(ADAFRUIT_FEATHER_M0) // Feather M0 w/Radio
  #define RFM69_CS      8
  #define RFM69_INT     3
  #define RFM69_RST     4
  #define LED           13
#endif

#if defined (__AVR_ATmega328P__)  // Feather 328P w/wing
  #define RFM69_INT     3  // 
  #define RFM69_CS      4  //
  #define RFM69_RST     2  // "A"
  #define LED           13
#endif

#if defined(ESP8266)    // ESP8266 feather w/wing
  #define RFM69_CS      2    // "E"
  #define RFM69_IRQ     15   // "B"
  #define RFM69_RST     16   // "D"
  #define LED           0
#endif

#if defined(ESP32)    // ESP32 feather w/wing
  #define RFM69_RST     13   // same as LED
  #define RFM69_CS      33   // "B"
  #define RFM69_INT     27   // "A"
  #define LED           13
#endif

/* Teensy 3.x w/wing
#define RFM69_RST     9   // "A"
#define RFM69_CS      10   // "B"
#define RFM69_IRQ     4    // "C"
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ )
*/
 
/* WICED Feather w/wing 
#define RFM69_RST     PA4     // "A"
#define RFM69_CS      PB4     // "B"
#define RFM69_IRQ     PA15    // "C"
#define RFM69_IRQN    RFM69_IRQ
*/

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram rf69_manager(rf69, MY_ADDRESS);


int16_t packetnum = 0;  // packet counter, we increment per xmission

s_message_t s_msg;

void coms_setup() 
{
  memset( &s_msg,   0, sizeof(s_msg));
  
  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Battle Shoko Controller");

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  if (!rf69_manager.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);
  
  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}


// Dont put this on the stack:
uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
uint8_t data[] = "  OK";



int set_message_mode(int m)
{
  if(m == MODE_DIFFERENTIAL_DRIVE){ s_msg.mode = m; return 0; }
  if(m == MODE_JOYSTICK)          { s_msg.mode = m; return 0; }
  return 1;
}


int set_message(float d0, float d1)
{
  /* 
   * d0 = MOT_RIGHT or JOY_X
   * d1 = MOT_LEFT  or JOY_X
   */
  if(set_message_motor(MOT_RIGHT, d0)) return 1;
  if(set_message_motor(MOT_LEFT , d1)) return 1;
  return 0;
}


int set_message(int m, float d0, float d1)
{
  /* m  = mode
   * d0 = MOT_RIGHT or JOY_X
   * d1 = MOT_LEFT  or JOY_X
   */
  if(set_message_mode(m))               return 1;
  if(set_message_motor(MOT_RIGHT, d0)) return 1;
  if(set_message_motor(MOT_LEFT , d1)) return 1;
  return 0;
}


int set_message_motor(int m, float v)
{
  
  if (m == MOT_LEFT)  {s_msg.d0 = v; return 0;}
  if (m == MOT_RIGHT) {s_msg.d1 = v; return 0;}

  return 1;
}


int send_message(float d0, float d1)
{
   /* d0 = MOT_RIGHT or JOY_X
   * d1 = MOT_LEFT  or JOY_X
   */
  if(set_message_motor( MOT_RIGHT,  d0)) return 1;
  if(set_message_motor( MOT_LEFT,   d1)) return 1;
  return send_message();
}



int send_message(int m, float d0, float d1)
{
    /* m  = mode
   * d0 = MOT_RIGHT or JOY_X
   * d1 = MOT_LEFT  or JOY_X
   */
  if(set_message( m, d0, d1)) return 1;
  return send_message();
}

int coms_led_blink()
{
  digitalWrite(LED, !digitalRead(LED));
  return 0;
}

int send_message() {
  
  char radiopacket[20] = "Hello World #";
  char s_buff[sizeof(s_msg)];

  memcpy(&s_buff, &s_msg, sizeof(s_msg));
  
  // Send a message to the DESTINATION!
  if (rf69_manager.sendtoWait((uint8_t *)s_buff, sizeof(s_buff), DEST_ADDRESS)) {
    // Now wait for a reply from the server
    uint8_t len = sizeof(buf);
    uint8_t from;   
    /* Send and try to receive from with a 10ms timeout */
    if (rf69_manager.recvfromAckTimeout(buf, &len, 10, &from)) {
      buf[len] = 0; // zero out remaining string
      coms_led_blink();
      
      if(buf[0] == MSG_OK)
      {
        Serial.println("MSG_OK");
        return 0;
      }
      else
      {
        Serial.println("MSG_ERR");
        return 1;
      }
      /*
      Serial.print("Got reply from #"); Serial.print(from);
      Serial.print(" [RSSI :");
      Serial.print(rf69.lastRssi());
      Serial.print("] : ");
      Serial.println((char*)buf);   
      Serial.print("max message len = ");
      Serial.println(RH_RF69_MAX_MESSAGE_LEN);  
      */
      
      // Blink(LED, 1, 3); //blink LED 3 times, 1ms between blinks

      
      return 0;
      
    } 
    else 
    {
      Serial.println("MSG_NO_REPLY");
      return 1;
    }
  } 
  else 
  {
    Serial.println("MSG_NO_ACK");
    return 1;
  }
  return 1;
}

void Blink(byte PIN, byte DELAY_MS, byte loops) {
  for (byte i=0; i<loops; i++)  {
    digitalWrite(PIN,HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN,LOW);
    delay(DELAY_MS);
  }
}
