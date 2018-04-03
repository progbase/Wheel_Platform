

#include <Servo.h>

const int in3 = 2;
const int in4 = 3;
const int en2 = 5;

const int servoPin = 7;
byte incomingByte;
Servo servo;
int i = 0;


void setup() {
    Serial.begin(9600);
  servo.attach(servoPin);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(en2, OUTPUT);

    analogWrite(en2, 255);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == 'w'){
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if(incomingByte == 'q'){
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    else if(incomingByte == 's'){
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    else if(incomingByte == 'a'){
      
      while(i < 90){
          i += 10;
        servo.write(i);
        delay(50);
      }
    }
    else if(incomingByte == 'd'){
      while(i > -90){
          i -= 10;
        servo.write(i);
        delay(50);
      }
    }
  }
}
