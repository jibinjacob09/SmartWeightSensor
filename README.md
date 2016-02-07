Smart Weight Monitor

SmartWeight Monitor is targeted to help muscular strengthening in the physiotherapy industry, which has experience significance growth over the last decade. Currently physiotherapists predominantly use qualitative observation to identify if the exercising muscle is fatigued. Such assessment can vary the quality of the treatment a patient is receiving as it heavily dependent on the skill and the experience of the physiotherapist.

 The SmartWeight Monitor is a wireless, portable, easy-to-attach device that can be placed on any barbell/dumbbell. The numerous sensors within the system provide numerical data that reflect the exertion of the targeted muscle as the user is exercising.  The data collected by the device will help physiotherapist monitor the condition of the muscle in real time and provide a more tailored care.

System consists of:
  Arduino uno,
  Inertial Motion Unit (accelerometer, gyroscope)
  Xbee 2.0 (x2)
  Force Sensor (x3)

The device has only been tested with bicep curls. The 3D acceleration and rotational information provided by the IMU (placed on the bar) measures the force exertion by the bicepes on the bar.  The array of force sensors, placed under the handle measures the grip force excerted by the user. The Arduino is programmed to obtain readings from the sensors and use Xbee to wirelessly transmit data to the computer.

The Userinterface looks like:
![Alt text](./img.jpg?raw=true "Userinterface")
