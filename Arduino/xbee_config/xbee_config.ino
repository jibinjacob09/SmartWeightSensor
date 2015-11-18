/* This Code is arduino with COORDINATEOR Xbee.  This Code allows the arduino to RECIEVE the
 *  XBee's transmission
 */


#include <SoftwareSerial.h>
SoftwareSerial XBee(2, 3); // RX, TX
String output;

void setup()
{

  //XBee.begin(115200);
  Serial.begin(115200);
  XBee.begin(9600);
 // Serial.begin(9600);
}

void loop()
{ 
  output = "";
  if (Serial.available())
  {
  //  XBee.write("Testing from serial");
  }
  if (XBee.available())
  { 
  
    int ir = XBee.read();
    //Serial.write(XBee.read());
    //Serial.print(ir);

    if (((ir>32) && (ir < 127)) || (ir == 10))
     { char c= ir;
       Serial.print(c);
     }
    
  } 
  //delay(1000);
}

