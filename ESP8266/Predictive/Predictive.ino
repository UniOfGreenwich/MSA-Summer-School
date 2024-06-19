/*
* AUTHOR: Dr T
* DESCRIPTION: Motor Control web server ESP8266 as Access Point (IP Address is: 192.168.4.1)
* CONTRIBUTOR: Seb Blair (CompEng0001)
* VERSION: 2.0.0
* MODIFICATIONS:
*    - Formatted file (CompEng0001)
*    - Added Doxygen comments for industrial compliance (CompEng0001)
*    - Converted const integers to variables (CompEng0001)
*    - Refactored Code (CompEng0001)
*    - Created {x,y,z}_axis variables to store mma events instead of calling more than once (CompEng0001)
*    - Created new handle for SBC POST request 'handleSBC()' & `server.on("/sbc",handleSBC)` visit ./predictiveMaintenance/predictiveMaintenance.py (CompEng0001)
*/

//Use version 2.5.2 ESP8266 Core

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include "index.h"

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
const char* ssid = "D1_Mini"; // You should up date this to something unique and clean for your SBC to connect to
const char* password = "12345678";

ESP8266WebServer server(80);  //Server on port 80

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
 * @brief Sends sensor data to a Single Board Computer (SBC).
 *
 * This function compiles various sensor readings into a comma-separated string
 * and sends it to a connected SBC. The data includes motor temperature, ambient
 * temperature, humidity, temperature, motor speed, motor state, and vibration
 * readings along the x, y, and z axes.
 *
 * @param none Uses global variables to compile data.
 * @return void
 */
void handleSBC(){
  String dataForSBC = String(m_Temp)+ ","+ String(a_Temp)+ ","+ String(h)+ ","+ String(t)+ ","+ String(motor_speed)+ ","+ String(Motor_state)+ ","+ String(x_axis)+ ","+ String(y_axis)+ ","+ String(z_axis)+ ","+ String(rms_vib);
  server.send(200, "/text/plain", dataForSBC);  // Send data to SBC
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

/**
 * @brief Initializes the system on startup.
 *
 * This function sets up the DHT sensor, initializes serial communication,
 * configures the Wi-Fi settings for the access point, and assigns the handling
 * functions for the web server's root, SBC, and form endpoints. It also
 * initializes the GPIO pins for various components like the motor, multiplexer,
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
  //IPAddress dns(192, 168, 0, 1);

  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
  WiFi.config(ip, gateway, subnet);


  //IPAddress myIP = WiFi . softAPIP (); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(ip);

  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/sbc",handleSBC);
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
