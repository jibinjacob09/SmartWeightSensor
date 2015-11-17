
int Flex_Sensor[] = {0,1,2};
float Flex_val[3];
float average;


void setup() {
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  
}

void loop() {
   String temp_str;
   double Force =0;
   average = 0;

   for (int i =0; i <3; i++){   //Reading input from 3 AnalogInputs
    Flex_val[i] = analogRead(Flex_Sensor[i]);
    if (Flex_val[i] <5)
      Flex_val[i] = 0;
      
    average = average + Flex_val[i];
   }
  average = average /3;

//Printing the values
  temp_str = "Flex1 = " + String(Flex_val[0]) +  " Flex2 = " + String(Flex_val[1]) + " Flex3 = " + String(Flex_val[2]) + "=> Average =" + String(average);
  Serial.println(temp_str);
  if (average == 0)
    {Force = 0;}
  else 
    {Force = (12.174*average) + 26.893;}   //in grams

  Force = Force * 0.00220462;     //in pounds
  temp_str = "    Force = " + String (Force) + " pounds";
  Serial.println(temp_str );
 
  delay(1000);
}

