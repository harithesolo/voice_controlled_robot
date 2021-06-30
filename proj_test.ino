#include <SoftwareSerial.h>
#include <AFMotor.h>
#include<Servo.h>

Servo myservo;
const int TRIGGER_PIN = 13;
const int ECHO_PIN = 2;


AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

SoftwareSerial bluetooth(14,15);
String t;
char sp = 180;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode (TRIGGER_PIN, OUTPUT);
  pinMode (ECHO_PIN, INPUT);
  pinMode(A2,INPUT);  
  myservo.attach(9);
  servo_forward();



  // set the data rate for the SoftwareSerial port
  bluetooth.begin(9600);

}
void servo_forward(){
   myservo.write(90);
  Serial.println("Straight");
  delay(5000);
  }

void servo_left(){
  
  myservo.write(180);
  Serial.println("left");
  delay(5000);
  }
void servo_right(){
   myservo.write(0);
  Serial.println("Right");
  delay(5000);
  }

float calc_dist()
{
  unsigned long duration;
  float distance;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn (ECHO_PIN, HIGH);
  distance = (duration / 2.0) / 29.0;
  /*Serial.print("Data:");
  Serial.print (duration);
  Serial.print(", d = ");*/
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
  ; 
  }


void loop() { // run over and over
  if (bluetooth.available()) {
    t = bluetooth.readString();
    Serial.println(t);
  }
  float obstacle = calc_dist();
  
  if (t == "forward")  {          //move forward(all motors rotate in forward direction)
    servo_forward();
    float obstacle=calc_dist();
    if(obstacle > 10){
    Serial.println("Forward");
    motor1.setSpeed(sp);
    motor1.run(FORWARD);
    motor2.setSpeed(sp);
    motor2.run(FORWARD);
    motor3.setSpeed(sp);
    motor3.run(FORWARD);
    motor4.setSpeed(sp);
    motor4.run(FORWARD);
    }
    else
    {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      t="";
      Serial.println("Obstacle Found");
      }
  }

  else if (t == "backward") {    //move reverse (all motors rotate in reverse direction)
    Serial.println("Reverse");
    if(digitalRead(A2)!=0)
    {
    motor1.setSpeed(sp);
    motor1.run(BACKWARD);
    motor2.setSpeed(sp);
    motor2.run(BACKWARD);
    motor3.setSpeed(sp);
    motor3.run(BACKWARD);
    motor4.setSpeed(sp);
    motor4.run(BACKWARD);
  }
    else
    {
       motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      t="";
      Serial.println("Obstacle on back");
      }
    }
  else if (t == "left") {    //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
    servo_left();
    float obstacle=calc_dist();
    servo_forward();
    if(obstacle > 20){
    Serial.println("Left");
    motor1.run(BACKWARD);
    motor1.setSpeed(sp);
    motor2.run(BACKWARD);
    motor2.setSpeed(sp);
    motor3.run(FORWARD);
    motor3.setSpeed(sp);
    motor4.run(FORWARD);
    motor4.setSpeed(sp);
    delay(2000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    t="";
    }
    else
    {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      t="";
      Serial.println("Obstacle on left");
      }
  }

  else if (t == "right") {    //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    servo_right();
    float obstacle=calc_dist();
    servo_forward();
    if(obstacle > 20){
    Serial.println("Right");
    motor1.run(FORWARD);
    motor1.setSpeed(sp);
    motor2.run(FORWARD);
    motor2.setSpeed(sp);
    motor3.run(BACKWARD);
    motor3.setSpeed(sp);
    motor4.run(BACKWARD);
    motor4.setSpeed(sp);
    delay(2000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    t="";
    }
    else
    {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
      motor3.run(RELEASE);
      motor4.run(RELEASE);
      t="";
      Serial.println("Obstacle on right");
      }
  }


  else if (t == "stop") {    //STOP (all motors stop)
    Serial.println("Stop");
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
}

\
