/* This Code is arduino with COORDINATEOR Xbee.  This Code allows the arduino to RECIEVE the
 *  XBee's transmission
 */


#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX

void setup()
{

  //XBee.begin(115200);
  Serial.begin(115200);
  XBee.begin(9600);
 // Serial.begin(9600);
}

void loop()
{ 
  if (Serial.available())
  {
  //  XBee.write("Testing from serial");
  }
  if (XBee.available())
  { 

    Serial.write(XBee.read());

   
  }
  //delay(1000);
}

