/*
* AUTHORS: YOUR NAMES
* VERSION: 1.0.O
* NOTES: 
*      - for testing the 2x TMP36 Temperature sensors 
*      - and DHT11  Humidity and Temperature sensor
*/

#include <DHTesp.h>

const float voltage_conversion_factor = 0.004;
const float temperature_conversion_factor = 17.5;
const float temperature_offset = 20;

float m_Temp, m_Temp_v, a_Temp, a_Temp_v;
float h ,t;

DHTesp dht;

void setup(void) {
  dht.setup(D6, DHTesp::DHT22);

  Serial.begin(9600);
  Serial.println("");
  
  //Set up ports
  //D1 and D2 SCL and SCA
  pinMode(D3, OUTPUT);  //Mux A
  pinMode(D4, OUTPUT);  //Mux B
  pinMode(D6, INPUT);   //Humidity
  pinMode(A0, INPUT);   //Analogue input
}


void loop(void) {
  getTemp();
  delay(1000);
}

void getTemp() {

  //Motor Temp sensor reading
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW);
  m_Temp = analogRead(A0);  //Read Analog Voltage of ADC Pin
  m_Temp_v = m_Temp * voltage_conversion_factor;
  m_Temp = ((temperature_conversion_factor * m_Temp_v) - temperature_offset);
  Serial.print("Motor Temp: ");
  Serial.println(m_Temp);
  delay(200);

  //Amb Temp sensor reading
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  a_Temp = analogRead(A0);  //Read Analog Voltage of ADC Pin
  a_Temp_v = a_Temp * voltage_conversion_factor;
  a_Temp = (temperature_conversion_factor * a_Temp_v) - temperature_offset;
  Serial.print("Ambient Temp: ");
  Serial.println(a_Temp);
  delay(200);

  //Humidity sensor reading
  h = dht.getHumidity();
  t = dht.getTemperature();
  Serial.print("DHT11 Hum: ");
  Serial.print(h);
  Serial.print(" Temp: ");
  Serial.println(t);
  delay(200);

}