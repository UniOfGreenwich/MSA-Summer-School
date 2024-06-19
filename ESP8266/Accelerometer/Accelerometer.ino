/*
* AUTHORS: YOUR NAMES
* VERSION: 1.0.O
* NOTES: 
*      - for testing the MMA8451Q accelerometer sensor
*      - Make sure common ground between sensor and microcontroller.
*      - Pin = 4 SDA Pin 5 = SCL on Lolin.
*/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void)
{
  Serial.begin(115200);
  pinMode(D0, OUTPUT); // PWM
  pinMode(D5, OUTPUT); // Direction

  // Motor in stop state
  digitalWrite(D5, LOW);
  analogWrite(D0, 0);

  if (!mma.begin())
  {
    Serial.println("Couldnt start");
    while (1)
      ;
  }
  // Set range to required G
  mma.setRange(MMA8451_RANGE_2_G); // divides each recieved x,y and z by 4096
  // mma.setRange(MMA8451_RANGE_4_G); // divides each recieved x,y and z by 2048
  // mma.setRange(MMA8451_RANGE_8_G); // divides each recieved x,y and z by 1024
}

void loop()
{
  sensors_event_t event;
  mma.getEvent(&event);

    digitalWrite(D5, LOW); // Motor Forward @500
    analogWrite(D0, 500);
    getData(200);   

    digitalWrite(D5, LOW); // Motor Stop
    digitalWrite(D0, LOW);
    getData(100);

    digitalWrite(D5, LOW); // Motor Forward @1000
    analogWrite(D0, 1000);
    getData(200);

    digitalWrite(D5, LOW); // Motor Stop
    digitalWrite(D0, LOW);
    getData(100);
}

void getData(int bound){
    for (int i = 0; i < bound; i++){
        sensors_event_t event;
        printEvent(event);
        delay(10);
    }
}

void printEvent(sensors_event_t event){

    mma.getEvent(&event);
    Serial.print("x: ");
    Serial.print(event.acceleration.x);
    Serial.print("\ty: ");
    Serial.print(event.acceleration.y);
    Serial.print("\tz: ");
    Serial.print(event.acceleration.z);
    Serial.println();

}