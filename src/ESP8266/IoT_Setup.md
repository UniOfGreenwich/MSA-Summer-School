# IoT Setup

In this section we are going to put all the functionality together from the previous sections, we will also include the web page provision after this here:

-  [Building the Web Page](./Build_WebPage.md) 

We need to include various libraries into this programme, if you have been following along from the previous sections you will should have all the but the following libraries, so make sure you download and install the following libraries to be included in the programme: 

   - All of the following are part of the [ESP8266 GitHub Repo](https://github.com/esp8266/Arduino/tree/master?tab=readme-ov-file) that you downloaded as part of the [ESP8266 setup](Set_Up.md):

     - [ESP8266WiFi](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFi.h)

     - [WiFiClient](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/WiFiServer.h)

     - [ESP8266WebServer](https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/src/ESP8266WebServer.h)

> **Note:** You can use the import function within the Arduino software to unzip the folders into `/path/to/Arduino/Libraries/`, `Sketch` -> `Include Library` -> `Add` .`Zip Library...`, then navigate to the `/path/to/zipped_library` to include it.

## Developing the script

1. Create a new a script call it something meaningful like, `predictive.ino`

2. Start by adding the standard header information about the script

    ```cpp
    /*
    * AUTHORS: YOUR NAMES
    * VERSION: 1.0.0
    * DESCRIPTION: Motor Control web server ESP8266 as Access Point (IP Address is: 192.168.4.1)
    */
    ```

3.  Using the `#include` directive reference the wire, Adafruit_MMA845, Adafruit_Sensor libraries:

    > **Note:** 
    > - If you see `...` that means that other code is hidden for brevity 

    ```cpp
    ...

    #include <ESP8266WiFi.h>
    #include <WiFiClient.h>
    #include <ESP8266WebServer.h>
    #include <DHTesp.h>
    #include <Wire.h>
    #include <Adafruit_MMA8451.h>
    #include <Adafruit_Sensor.h>
    #include "index.h"
    ```

    >**Note:** 
    >> - If you are using the Arduino IDE you should be able to hover over the library and it will show the following paths for each library, respectivley to the above:
    >>    - `path\to\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\libraries\ESP8266WiFi\src\ESP8266WiFi.h`
    >>
    >>    - `path\to\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\libraries\ESP8266WiFi\src\WiFiClient.h`
    >>
    >>    - `path\to\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\libraries\ESP8266WebServer\src\ESP8266WebServer.h`
    >>
    >>    - `path\to\Documents\Arduino\libraries\DHT_sensor_library_for_ESPx\DHTesp.h`
    >>
    >>    - `path\to\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\libraries\Wire\Wire.h`
    >>
    >>    - `path\to\Documents\Arduino\libraries\Adafruit_MMA8451_Library\Adafruit_MMA8451.h`
    >>
    >>    - `path\to\Documents\Arduino\libraries\Adafruit_Unified_Sensor\Adafruit_Sensor.h`
    >>
    >>    - `path\to\Temp\arduino-language-server1776684319\build\sketch\index.h`


4. Now we need to set the following global variables and define objects that we can use from Classes: 

    ```cpp
    ...

    const float voltage_conversion_factor = 0.004;
    const float temperature_conversion_factor = 17.5;
    const float temperature_offset = 20;
    const float motor_speed_conversion_factor = 24.6;
    const int noise_threshold = 20;

    float m_Temp, m_Temp_v, a_Temp, a_Temp_v;
    float h ,t;
    float motor_speed;
    float average_vib, rms_vib, x_axis, y_axis, z_axis;
    String Motor_state = "Stop";

    DHTesp dht;
    Adafruit_MMA8451 mma = Adafruit_MMA8451();

    //SSID and Password to your ESP Access Point
    const char* ssid = "NAME_OF_YOUR_SSID"; // You should up date this to something unique and clean for your SBC to connect to
    const char* password = "12345678";

    ESP8266WebServer server(80);  //Server on port 80
    ```
    
    > **Note:** There are three new variables/objects created that have not come from the other section you have worked through:
    > - Firstly, the `ssid` and `password` the name and password of our hotspot once it is setup further on in the programme. 
    > - Secondly, the `ESP8266WebServer server(80);` creates an websever set on port 80.

5. We should now modify the `setup()` function, there are 56 lines of codes and comments (that are very important to the understanding of the code base). Explainations will be provided after the fact that you can look at:

    ```cpp
    ...

    /**
    * @brief Initialises the system on startup.
    *
    * This function sets up the DHT sensor, initialises serial communication,
    * configures the Wi-Fi settings for the access point, and assigns the handling
    * functions for the web server's root, SBC, and form endpoints. It also
    * initialises the GPIO pins for various components like the motor, multiplexer,
    * and the MMA8451 accelerometer sensor.
    *
    * @param none This function does not take parameters.
    * @return void
    */
    void setup(void) {
        dht.setup(D6, DHTesp::DHT22);

        Serial.begin(9600);
        Serial.println("");
        
        WiFi.mode(WIFI_AP);           //Only Access point
        WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security

        IPAddress myIP = WiFi.softAPIP (); //Get IP address
        Serial.print("HotSpt IP:");
        Serial.println(myIP); 

        server.on("/", handleRoot);      //Which routine to handle at root location
        server.on("/form", handleForm);  //These request sent when we click on button
        server.begin();                  //Start server

        Serial.println("HTTP server started");

        //Set up ports
        //D1 and D2 SCL and SCA
        pinMode(D0, OUTPUT);  //PWM
        pinMode(D3, OUTPUT);  //Mux A
        pinMode(D4, OUTPUT);  //Mux B
        pinMode(D5, OUTPUT);  //Direction
        pinMode(D6, INPUT);   //Humidity
        pinMode(A0, INPUT);   //Analogue input

        //Set Mux INH to low and unused mux port to low
        //Motor in stop state
        digitalWrite(D5, LOW);
        analogWrite(D0, 0);

        //begin MMA vibration sensor
        mma.begin();
        //Set MMA range
        mma.setRange(MMA8451_RANGE_2_G);
    }
    ```
    > **Note:**
    >> - The body of comments at the top of the function is presented in a standard called Doxygen that is commonly used to produce documentation for code base, you can see an example here -> []()
    >> - The lines that show `WiFi.mode(WIFI_AP);`, `WiFi.softAP(ssid, password);` set up the WiFi Access Point
    >> - This line enables us to get the default IP address in the ESP8266 core `IPAddress myIP = WiFi.softAPIP ();` 192.168.4.1


6. Next we will place one line of code inside the the `loop()`:

    ```cpp
    void loop(void) {
      server.handleClient();  //Handle client requests
    }
    ```
  - the `server`, that is serving on port 80, has a function that "handles" the clients various http requests. Uou can see the implementation here -> [handleClient implementation](https://github.com/esp8266/Arduino/blob/c2f136515a396be1101b261fe7b71e137aef0dce/libraries/ESP8266WebServer/src/ESP8266WebServer-impl.h#L357)


7. The next function you are to create places all of the various testing sections code together with two new bits of code for the IoT part, it will be explained after: 

    ```cpp
    /**
    * @brief Serves the main page and updates it with sensor readings.
    *
    * This function is called when the root URL of the server is accessed. It reads
    * various sensor data including motor speed, motor temperature, ambient temperature,
    * humidity, and vibration. The readings are then used to update placeholders in the
    * HTML page before sending it to the client's web browser.
    *
    * @param none Uses global variables and server object to read sensors and send data.
    * @return void
    */
    void handleRoot() {
      String s = MAIN_page;

      //Motor speed reading
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      motor_speed = analogRead(A0);
      delay(200);

      //Motor Temp sensor reading
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);
      m_Temp = analogRead(A0);  //Read Analog Voltage of ADC Pin
      m_Temp_v = m_Temp * voltage_conversion_factor;
      m_Temp = ((temperature_conversion_factor * m_Temp_v) - temperature_offset);
      Serial.println(m_Temp);
      delay(200);

      //Amb Temp sensor reading
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);
      a_Temp = analogRead(A0);  //Read Analog Voltage of ADC Pin
      a_Temp_v = a_Temp * voltage_conversion_factor;
      a_Temp = (temperature_conversion_factor * a_Temp_v) - temperature_offset;
      Serial.println(a_Temp);
      delay(200);
      
      //Eliminate analogue input noise
      if (motor_speed < noise_threshold) {
        motor_speed = 0;
      }

      //Calibrate motor speed
      motor_speed = motor_speed * motor_speed_conversion_factor;
      Serial.println(motor_speed);

      //Humidity sensor reading
      h = dht.getHumidity();
      t = dht.getTemperature();
      Serial.println(h);
      Serial.println(t);
      delay(200);

      //Accelerometer
      sensors_event_t event;
      mma.getEvent(&event);
      x_axis = event.acceleration.x;
      y_axis = event.acceleration.y;
      z_axis = event.acceleration.z;
      average_vib = ((sq(x_axis)) + (sq(y_axis)) + (sq(z_axis))) / 3;
      rms_vib = sqrt(average_vib);
      Serial.println(rms_vib);
      delay(200);

      //Convert variables to String then Replace @@temp@@ in HTML with temperaure value
      s.replace("@@m_temp@@", String(m_Temp));
      s.replace("@@a_temp@@", String(a_Temp));
      s.replace("@@humidity@@", String(h));
      s.replace("@@motor_temp@@", String(t));
      s.replace("@@motor_speed@@", String(motor_speed));
      s.replace("@@status@@", Motor_state);
      s.replace("@@vibration@@", String(rms_vib));
      server.send(200, "text/html", s);  //Send webpage to browser

    }
    ``` 
    > **Note:**
    >> - You should see that the fist variable is showing an error in reference due to the fact that `MAIN_page` does not exist in its current context. This will be remedied after this section. 
    >> - You should also see that we are using regex `s.replace(@@m_temp@@", String(m_temp))` as part of the `String` class to replace the default values in the `MAIN_page` string object `s` becauase `MAIN_page` is the text for the html page. In the example provided here, the value of the motor temperature will replace `@@m_temp@@`.

8. So now the webpage would display data, but it is non-iteractive. We will add some functionality to handle POST information that will control the motor, such as, direction of the motor, "Forward", "Reverse", and "Stop", the new function is below:


    ```cpp
    /**
    * @brief Handles the form submission from the web interface.
    *
    * This function is called when the user submits a form on the web interface.
    * It reads the state of the button from the form data and controls the motor
    * accordingly. After setting the motor state, it redirects the web browser
    * back to the root location.
    *
    * @param none Uses global server object to access form data.
    * @return void
    */
    void handleForm() {
      String m_state = server.arg("button");  //Get button state

      if (m_state == "Forward") {
        digitalWrite(D5, LOW);  //Motor Forward
        analogWrite(D0, 500);
        Motor_state = "Forward";
      }
      if (m_state == "Stop") {
        digitalWrite(D0, LOW);  //Motor Stop
        analogWrite(D5, LOW);
        Motor_state = "Stop";
      }
      if (m_state == "Reverse") {
        digitalWrite(D0, LOW);  //Motor Reverse
        analogWrite(D5, 500);
        Motor_state = "Reverse";
      }

      server.sendHeader("Location", "/");  //Send web browser to root location
      server.send(302, "text/html", "");   //Send browser 302 redirect go back to root location
      delay(500);                          //Delay to let motor get up to speed
    }
    ```

9. The script will not compile yet, due to the fact that still `MAIN_page` does not have a reference.  We can do this now, by following the steps in this section: [Build WebPage](Build_WebPage.md).

---------------------------- 

## Full Code here

<details>
<summary>Click here...</summary>

```cpp
/*
* AUTHORS: YOUR NAMES
* VERSION: 1.0.0
* DESCRIPTION: Motor Control web server ESP8266 as Access Point (IP Address is: 192.168.4.1)
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

const float voltage_conversion_factor = 0.004;
const float temperature_conversion_factor = 17.5;
const float temperature_offset = 20;
const float motor_speed_conversion_factor = 24.6;
const int noise_threshold = 20;

float m_Temp, m_Temp_v, a_Temp, a_Temp_v;
float h ,t;
float motor_speed;
float average_vib, rms_vib, x_axis, y_axis, z_axis;
String Motor_state = "Stop";

DHTesp dht;
Adafruit_MMA8451 mma = Adafruit_MMA8451();

//SSID and Password to your ESP Access Point
const char* ssid = "NAME_OF_YOUR_SSID"; // You should up date this to something unique and clean for your SBC to connect to
const char* password = "12345678";

ESP8266WebServer server(80);  //Server on port 80

/**
 * @brief initialises the system on startup.
 *
 * This function sets up the DHT sensor, initialises serial communication,
 * configures the Wi-Fi settings for the access point, and assigns the handling
 * functions for the web server's root, SBC, and form endpoints. It also
 * initialises the GPIO pins for various components like the motor, multiplexer,
 * and the MMA8451 accelerometer sensor.
 *
 * @param none This function does not take parameters.
 * @return void
 */
void setup(void) {
  dht.setup(D6, DHTesp::DHT22);

  Serial.begin(9600);
  Serial.println("");
  
  //Change IP address to avoid conflicts with other devices.
  IPAddress ip(192, 168, 0, 12);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);
  
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
  WiFi.config(ip, gateway, subnet);

  //IPAddress myIP = WiFi . softAPIP (); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(ip);

  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/form", handleForm);  //These request sent when we click on button
  server.begin();                  //Start server

  Serial.println("HTTP server started");

  //Set up ports
  //D1 and D2 SCL and SCA
  pinMode(D0, OUTPUT);  //PWM
  pinMode(D3, OUTPUT);  //Mux A
  pinMode(D4, OUTPUT);  //Mux B
  pinMode(D5, OUTPUT);  //Direction
  pinMode(D6, INPUT);   //Humidity
  pinMode(A0, INPUT);   //Analogue input

  //Set Mux INH to low and unused mux port to low
  //Motor in stop state
  digitalWrite(D5, LOW);
  analogWrite(D0, 0);

  //begin MMA vibration sensor
  mma.begin();
  //Set MMA range
  mma.setRange(MMA8451_RANGE_2_G);
}

void loop(void) {
  server.handleClient();  //Handle client requests
}

/**
 * @brief Serves the main page and updates it with sensor readings.
 *
 * This function is called when the root URL of the server is accessed. It reads
 * various sensor data including motor speed, motor temperature, ambient temperature,
 * humidity, and vibration. The readings are then used to update placeholders in the
 * HTML page before sending it to the client's web browser.
 *
 * @param none Uses global variables and server object to read sensors and send data.
 * @return void
 */
void handleRoot() {
  String s = MAIN_page;

  //Motor speed reading
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  motor_speed = analogRead(A0);
  delay(200);

  //Motor Temp sensor reading
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  m_Temp = analogRead(A0);  //Read Analog Voltage of ADC Pin
  m_Temp_v = m_Temp * voltage_conversion_factor;
  m_Temp = ((temperature_conversion_factor * m_Temp_v) - temperature_offset);
  Serial.println(m_Temp);
  delay(200);

  //Amb Temp sensor reading
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  a_Temp = analogRead(A0);  //Read Analog Voltage of ADC Pin
  a_Temp_v = a_Temp * voltage_conversion_factor;
  a_Temp = (temperature_conversion_factor * a_Temp_v) - temperature_offset;
  Serial.println(a_Temp);
  delay(200);

  //Eliminate analogue input noise
  if (motor_speed < noise_threshold) {
    motor_speed = 0;
  }

  //Calibrate motor speed
  motor_speed = motor_speed * motor_speed_conversion_factor;
  Serial.println(motor_speed);

  //Humidity sensor reading
  h = dht.getHumidity();
  t = dht.getTemperature();
  Serial.println(h);
  Serial.println(t);
  delay(200);

  //Accelerometer
  sensors_event_t event;
  mma.getEvent(&event);
  x_axis = event.acceleration.x;
  y_axis = event.acceleration.y;
  z_axis = event.acceleration.z;
  average_vib = ((sq(x_axis)) + (sq(y_axis)) + (sq(z_axis))) / 3;
  rms_vib = sqrt(average_vib);
  Serial.println(rms_vib);
  delay(200);

  //Convert variables to String then Replace @@temp@@ in HTML with temperaure value
  s.replace("@@m_temp@@", String(m_Temp));
  s.replace("@@a_temp@@", String(a_Temp));
  s.replace("@@humidity@@", String(h));
  s.replace("@@motor_temp@@", String(t));
  s.replace("@@motor_speed@@", String(motor_speed));
  s.replace("@@status@@", Motor_state);
  s.replace("@@vibration@@", String(rms_vib));
  server.send(200, "text/html", s);  //Send webpage to browser

}

/**
 * @brief Handles the form submission from the web interface.
 *
 * This function is called when the user submits a form on the web interface.
 * It reads the state of the button from the form data and controls the motor
 * accordingly. After setting the motor state, it redirects the web browser
 * back to the root location.
 *
 * @param none Uses global server object to access form data.
 * @return void
 */
void handleForm() {
  String m_state = server.arg("button");  //Get button state

  if (m_state == "Forward") {
    digitalWrite(D5, LOW);  //Motor Forward
    analogWrite(D0, 500);
    Motor_state = "Forward";
  }
  if (m_state == "Stop") {
    digitalWrite(D0, LOW);  //Motor Stop
    analogWrite(D5, LOW);
    Motor_state = "Stop";
  }
  if (m_state == "Reverse") {
    digitalWrite(D0, LOW);  //Motor Reverse
    analogWrite(D5, 500);
    Motor_state = "Reverse";
  }

  server.sendHeader("Location", "/");  //Send web browser to root location
  server.send(302, "text/html", "");   //Send browser 302 redirect go back to root location
  delay(500);                          //Delay to let motor get up to speed
}
```

</detials>