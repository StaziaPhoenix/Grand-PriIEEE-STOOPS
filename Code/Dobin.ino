#include <Wire.h>
#include <Servo.h>
 
#define SLAVE_ADDRESS 0x04 // Discover real

Servo servo;
byte values[2] = {0,0};
byte servoPin = 9;
byte motorPin = 11;
int motorlevel = 1;


//MOTOR code
#define pwmA 3
byte spd = 0;
 long elapsed = 0;
 
void setup() {
  
 Serial.begin(9600);
 servo.attach(servoPin);
 servo.write(90);
 pinMode(motorPin, OUTPUT);
 
 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 
 // define callbacks for i2c communication
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);
 analogWrite(pwmA,spd = 0);
 delay(3000);
 analogWrite(pwmA, spd = 255);

}

void loop() {
  elapsed = millis();
//  Serial.pri
  Serial.println(spd);
    if (elapsed > 5000) {
      spd = 0;
      analogWrite(pwmA, spd = 0);
    }
}

// callback for received data
void receiveData(int byteCount){
  
  if (Wire.available() ) {
    values[0] = Wire.read();
    values[1] = 191;
    Serial.println(values[0]);
    Serial.println(values[1]);

    servo.write(values[0]);
    analogWrite(motorPin, values[1]);
  }
}
 
// callback for sending data
void sendData(){
  // Kill switch interrupt stuff
  // if interrupt: Wire.write(1);
  // else: Wire.write(0);
}
