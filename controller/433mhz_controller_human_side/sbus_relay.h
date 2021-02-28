#define SBUS_RELAY_H 1

#include <sbus.h>

/* SbusRx object on Serial1 */
SbusRx sbus_rx(&Serial1);
/* SbusTx object on Serial1 */
//SbusTx sbus_tx(&Serial1);

int sbus_relay_setup()
{
  /* Begin the SBUS communication */
  sbus_rx.Begin();
  //sbus_tx.Begin();
}

int sbus_read()
{
  Serial.println("**************************");
    if (sbus_rx.Read()) {
    /* Display the received data */
    for (int i = 0; i < sbus_rx.rx_channels().size(); i++) {
      Serial.print(sbus_rx.rx_channels()[i]);
      Serial.print("\t");
    }
    /* Display lost frames and failsafe data */
    Serial.print(sbus_rx.lost_frame());
    Serial.print("\t");
    Serial.println(sbus_rx.failsafe());
    /* Set the SBUS TX data to the received data */
//    sbus_tx.tx_channels(sbus_rx.rx_channels());
    /* Write the data to the servos */
//    sbus_tx.Write();
  }
}
