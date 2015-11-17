/* This Code is for arduino with Endpoint Xbee.  This code allows the arduino to SEND 
 *  the anlaogread value from port 0
 */


#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX
int sensor_val;


void setup()
{
  
  XBee.begin(9600);
  Serial.begin(115200);
  XBee.write("Arduino Powered up and ready to go");

}

void loop()
{ 
  String _send;
  sensor_val = analogRead(0);

  _send = "," + String(sensor_val)+",volts";
  Serial.println(_send);
  XBee.println(_send);

  delay(1000);

}

