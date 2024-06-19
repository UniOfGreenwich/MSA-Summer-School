/*
* AUTHORS: YOUR NAMES
* VERSION: 1.0.O
* NOTES: 
*      - for testing the 2x TMP36 Temperature sensors 
*      - and DHT11  Humidity and Temperature sensor
*/

const float motor_speed_conversion_factor = 24.6;
float motor_speed;

void setup(){
    Serial.begin(9600);
}

void loop(){

     //Motor speed reading
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  motor_speed = analogRead(A0);
  delay(200);

    //Eliminate analogue input noise
  if (motor_speed < noise_threshold) {
    motor_speed = 0;
  }

  //Calibrate motor speed
  motor_speed = motor_speed * motor_speed_conversion_factor;
  Serial.print(motor_speed);
  Serial.println(" RPM");
}