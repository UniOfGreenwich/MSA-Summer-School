/*
* AUTHORS: YOUR NAMES
* VERSION: 1.0.0
* NOTES: 
*      - Motor Speed is calculated using the Ktir0611s Photo Interrupter
*      - Motor will go forward, reverse and then stop in a loop and show speed in RPM
*/

// set variables 
const int noise_threshold = 20;
const float motor_speed_conversion_factor = 24.6;
float motor_speed;

void setup(){
  // initialise the serial
  Serial.begin(9600);
  
  //Motor speed reading
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}

void loop(){

  digitalWrite(D5, LOW);  // Motor Forward
  analogWrite(D0, 500);   // you change the speed here
  calculateSpeed();
  delay(100);

  digitalWrite(D0, LOW);  // Motor Stop
  analogWrite(D5, LOW);
  calculateSpeed();  
  delay(100);

  digitalWrite(D0, LOW);  // Motor Reverse
  analogWrite(D5, 500);   // you change the speed here
  calculateSpeed();
  delay(100);
}

void calculateSpeed(){
  // read 
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