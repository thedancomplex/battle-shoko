#define COMS_SERIAL_H 1

int coms_serial_read()
{
  if(Serial.available() > 0)
  {
    String tmp = Serial.readString();
    arc_rx_decode(tmp);
    return 0;
  }
  return 1;
}
