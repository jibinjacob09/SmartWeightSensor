#include <string.h>
String s;
void setup() {
  Serial.begin(9600);
 


}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() >0) {
    int ir = Serial.read();
     Serial.print(ir);
     Serial.print("  ");

    if ((ir > 32) && (ir < 127))
      {Serial.write(ir);
      char c = ir;
      s = s + c;
      Serial.println();}
    else
      Serial.println();
  
   Serial.print("The final is  -->");
   Serial.println(s);
  }
}

