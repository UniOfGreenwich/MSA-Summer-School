# Testing the Accelerometer

In order to understand the this component it is important to review the supporting technical documentation: 

- [MMA8451Q Accelerometer Datasheet](../../Data_Sheets/MMA8451Q.pdf)

We can see from table 12 on page 20 that the x,y and z values are stored in to MSB and LSB values in the respectiuve registers 0x1,0x2,..., 0x6

Normally we would have to write the code to obtain the information from the chip ourselves luckily, libaries are written for us: 

- [Wire.h](https://github.com/esp8266/Arduino/blob/master/libraries/Wire/Wire.h)

- [Adafruit_MMA8451.h](https://github.com/adafruit/Adafruit_MMA8451_Library/blob/master/Adafruit_MMA8451.h)

- [Adafruit_Sensor.h](https://github.com/adafruit/Adafruit_Sensor/blob/master/Adafruit_Sensor.h)

Luckily you can click these links below to download the zips that needed to be addedd to the Arduino Libraries: 

- [Wire]()
- [Adafruit_MMA8451](https://github.com/adafruit/Adafruit_MMA8451_Library/archive/refs/heads/master.zip)
- [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor/archive/refs/heads/master.zip)

Once downloaded, you can use the import function within the Arduino software to unzip the folders into `/path/to/Arduino/Libraries/`:

![Image for importing...]()


## Full code below

<details>
<summary>Click here:</summary>

```cpp
// Make sure common ground between sensor and microcontroller.
// Pin = 4 SDA Pin 5 = SCL on Lolin.

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
  mma.setRange(MMA8451_RANGE_2_G);
  // mma.setRange(MMA8451_RANGE_4_G);
  // mma.setRange(MMA8451_RANGE_8_G);
}

void loop()
{
  int i;
  sensors_event_t event;
  mma.getEvent(&event);

  digitalWrite(D5, LOW); // Motor Forward @500
  analogWrite(D0, 500);
  for (i = 0; i < 200; i++)
  {
    sensors_event_t event;
    printEvent();
    delay(10);
  }

  digitalWrite(D5, LOW); // Motor Stop
  digitalWrite(D0, LOW);
  for (i = 0; i < 100; i++)
  {
    sensors_event_t event;
    printEvent();
    delay(10);
  }

  digitalWrite(D5, LOW); // Motor Forward @1000
  analogWrite(D0, 1000);
  for (i = 0; i < 200; i++)
  {
    sensors_event_t event;
    printEvent();
    delay(10);
  }

  digitalWrite(D5, LOW); // Motor Stop
  digitalWrite(D0, LOW);
  for (i = 0; i < 100; i++)
  {
    sensors_event_t event;
    printEvent();
    delay(10);
  }
}

void printEvent(){
    mma.getEvent(&event);
    Serial.print("x: ");
    Serial.print(event.acceleration.x);
    Serial.print("\ty: ");
    Serial.print(event.acceleration.y);
    Serial.print("\tz: ");
    Serial.print(event.acceleration.z);
    Serial.println();

}
```


</details>