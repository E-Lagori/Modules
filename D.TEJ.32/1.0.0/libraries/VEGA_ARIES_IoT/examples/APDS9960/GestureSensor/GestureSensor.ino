/*
 @file   GestureSensor.ino
 @brief  This is the test code for the APDS9960 Proximity sensor
 @detail This example reads gesture data from the on-board APDS-9960 sensor of the
          Nano 33 BLE Sense and prints any detected gestures to the Serial Monitor.

 * Reference aries IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference aries IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : Arduino_APDS9960 (Version 1.0.4)
 * 
 * Gesture directions are as follows:
 * - UP:    from USB connector towards antenna
 * - DOWN:  from antenna towards USB connector
 * - LEFT:  from analog pins side towards digital pins side
 * - RIGHT: from digital pins side towards analog pins side
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
*/

#include <Wire.h>
#include <Arduino_APDS9960.h>

TwoWire Wire(8);    

void setup() {
  delay(2000);
  Serial.begin(115200);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }

  // for setGestureSensitivity(..) a value between 1 and 100 is required.
  // Higher values make the gesture recognition more sensitive but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensitive (some gestures may be missed).
  // Default is 80
  //APDS.setGestureSensitivity(80);

  Serial.println("Detecting gestures ...");
}
void loop() {
 #if defined (VEGA_ARIES_IOT)
 
  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        break;

      default:
        // ignore
        break;
    }
  }

  #else
  Serial.println("Choose the correct board! " );
  #endif  
}
