#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <SoftwareSerial.h>

/*   XBee Variables  */
SoftwareSerial XBee(2, 3); // RX, TX

/******* IMU variables  */
LSM9DS1 imu;
#define LSM9DS1_M 0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between 

#define DECLINATION -8.58 

/******* Flex variables  */
int Flex_Sensor[] = {0,1,2};
float Flex_val[3];
float average;
String Output_str;
int iteration;

void setup() {

  Serial.begin(115200);
  XBee.begin(9600);
  
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // The above lines will only take effect AFTER calling
  // imu.begin(), which verifies communication with the IMU
  // and turns it on.
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1)
      ;
  }



}

void loop() {
    /************  Flex Sensors ****************/
    delay (20);
   double Force =0;
   average = 0;

   iteration++;
   for (int i =0; i <3; i++){   //Reading input from 3 AnalogInputs
      Flex_val[i] = analogRead(Flex_Sensor[i]);
      if (Flex_val[i] <5)
          Flex_val[i] = 0;
      average = average + Flex_val[i];
   }
  average = average /3;
  
  if (average == 0)
    {Force = 0;}
  else 
    {Force = (12.174*average) + 26.893;}   //in grams

  Force = Force * 0.00220462;     //in pounds
  //Output_str = ",    Force = " + String (Force) + " pounds '\n'";
  
  Output_str = "," +String(iteration) + "," + String(Force)+ ",";

 
/*********************  IMU *************************************/
  printGyro();  // Print "G: gx, gy, gz"
  printAccel(); // Print "A: ax, ay, az"

  //Format:  Force,Gyro,Ax,Az
  Serial.println(Output_str );
  
  XBee.println(Output_str);
}

void printGyro()
{
  // To read from the gyroscope, you must first call the
  // readGyro() function. When this exits, it'll update the
  // gx, gy, and gz variables with the most current data.
  imu.readGyro();
  
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.

#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.

  
  Output_str = Output_str + String(imu.calcGyro(imu.gx), 2) + "," ;

 /* Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);*/

#elif defined PRINT_RAW
  Serial.print(imu.gx);
  Serial.print(" ");
  Serial.print(imu.gy);
  Serial.print(" ");
  Serial.println(imu.gz);
#endif
}

void printAccel()
{
  // To read from the accelerometer, you must first call the
  // readAccel() function. When this exits, it'll update the
  // ax, ay, and az variables with the most current data.
  imu.readAccel();
  
  // Now we can use the ax, ay, and az variables as we please.
  // Either print them as raw ADC values, or calculated in g's.

#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcAccel helper function to convert a raw ADC value to
  // g's. Give the function the value that you want to convert.
 
  
  Output_str = Output_str + String(imu.calcAccel(imu.ax), 2) + ",";
  //Serial.println(imu.calcAccel(imu.ax), 2);
  //Serial.print(imu.calcAccel(imu.ay), 2);
  //Serial.print(", ");
  Output_str = Output_str + String(imu.calcAccel(imu.az), 2);
 // Serial.println(", g");

#elif defined PRINT_RAW 
  Serial.print(imu.ax);
  Serial.print(" ");
  Serial.print(imu.ay);
  Serial.print(" ");
  Serial.println(imu.az);
#endif

}

void printMag()
{
  // To read from the magnetometer, you must first call the
  // readMag() function. When this exits, it'll update the
  // mx, my, and mz variables with the most current data.
  imu.readMag();
  
  // Now we can use the mx, my, and mz variables as we please.
  // Either print them as raw ADC values, or calculated in Gauss.
  Serial.print("M: ");
#ifdef PRINT_CALCULATED
  // If you want to print calculated values, you can use the
  // calcMag helper function to convert a raw ADC value to
  // Gauss. Give the function the value that you want to convert.
  Serial.print(imu.calcMag(imu.mx), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.my), 2);
  Serial.print(", ");
  Serial.print(imu.calcMag(imu.mz), 2);
  Serial.println(" gauss");
#elif defined PRINT_RAW
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
#endif
}

// Calculate pitch, roll, and heading.
// Pitch/roll calculations take from this app note:
// http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf?fpsp=1
// Heading calculations taken from this app note:
// http://www51.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/Magnetic__Literature_Application_notes-documents/AN203_Compass_Heading_Using_Magnetometers.pdf
void printAttitude(
float ax, float ay, float az, float mx, float my, float mz)
{
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  
  float heading;
  if (my == 0)
    heading = (mx < 0) ? 180.0 : 0;
  else
    heading = atan2(mx, my);
    
  heading -= DECLINATION * PI / 180;
  
  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);
  else if (heading < 0) heading += 2 * PI;
  
  // Convert everything from radians to degrees:
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
  
  Serial.print("Pitch, Roll: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Heading: "); Serial.println(heading, 2);
}
