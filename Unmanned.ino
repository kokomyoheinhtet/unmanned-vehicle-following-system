// Motor 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 6; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 10;
int speedPinB = 5; // Needs to be a PWM pin to be able to control motor speed

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 8

void setup() {
// Setup runs once per reset
// initialize serial communication @ 9600 baud:
Serial.begin(9600);

//Define L298N Dual H-Bridge Motor Controller Pins
  pinMode(echoPin, INPUT);
pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(speedPinB,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);

}

char rx;

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance <= 10){ // This is where car move backward
    
  Rev();

  }
  else if( distance <= 40) {
  
  Stop();
  
  }
  else if( distance >=50) {
    Stop();
  Serial.println("Motors are Controlled by Master");
  Serial.println("   ");
  if(Serial.available()){
  rx = Serial.read();
  Serial.println(rx);
  while(Serial.read()<=0 ){

  delay(200); 
  Stop();
  }
    if( rx == 'f')
  {
   Forward();    
   delay(200);
   if(distance<=40)
   Stop();
   }
  }
  
  }
  else;
//  delay(500);

}

void Forward() {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  // Motor 1 Forward (Freespin)
  analogWrite(speedPinA, 140);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);

  // Motor 2 Forward (Freespin)
  analogWrite(speedPinB,140);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

void Rev() {
  Serial.println("Something is Covering in 10cm");
  Serial.println("Car is moving back");
  Serial.println();
  digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
  digitalWrite(led2,LOW);  
  
  //Motor 1 Reverse
  analogWrite(speedPinA, 140);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);

  // Motor 2 Reverse
  analogWrite(speedPinB, 140);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);

}

void Stop() {
    Serial.println("Destination reached");
    Serial.println("   ");
    digitalWrite(led,HIGH);
    digitalWrite(led2,HIGH);  
    analogWrite(dir1PinA, 0);
    analogWrite(dir2PinA, 0);
    analogWrite(dir1PinB, 0);
    analogWrite(dir2PinB, 0);
}



