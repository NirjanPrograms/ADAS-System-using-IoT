// Motor A connections
int enA = 11;
int in1 = 12;
int in2 = 13;
// Motor B connections
int enB = 9;
int in3 = 8;
int in4 = 7;
int speed = 0;

// Ultrasonic Sensor connections
int trig = 5;
int echo = 6;
int timet =0;
int dist = 0;

// Piezo Sensor connections
const int buzzerPin = 10;
const int sensorPin = A0; 
const int vibrationThreshold = 300;
const int ledPin = A4;
int led = 0;

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Turn on motors - Initial state
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  
  // set the all ultrasonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Set the all Piezo sensor pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  dist = distance();
  Serial.print("Distance = ");
  Serial.println(dist);
  if(dist>100){
    speed = start();
  }
  else if(dist>50){
    speed = slow();
  }
  else{
    speed = stop();
    tone();
    if(led == 1){
      analogWrite(ledPin, 0);
      led = 0;
    }
    else{
      analogWrite(ledPin, 255);
      led = 1;
    }
    Serial.println("Close");
  }
  Serial.print("Speed = ");
  Serial.println(speed);
  knock();
}

int knock(){
   int sensorValue = analogRead(sensorPin);
   if (sensorValue > vibrationThreshold) {
     Serial.println("Vibration detected!");
     Serial.print("knock = ");
     Serial.println(sensorValue);
     analogWrite(ledPin, 200);
     digitalWrite(buzzerPin, HIGH); 
     delay(1000); 
     digitalWrite(buzzerPin, LOW); 
     stop();
  }
  else{
    analogWrite(ledPin, 0);
  }
  return 1;
}

void tone(){
  tone(10, 700, 300);
  noTone(7);
  analogWrite(ledPin, 255);
  analogWrite(ledPin, 0);
}

int distance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  timet = pulseIn(echo, HIGH);
  dist = (timet*0.034)/2;
  return dist;
}

int start(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  return 255;
}

int slow(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 50);
  analogWrite(enB, 50);
  return 50;
}

int stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  return 0;
}
