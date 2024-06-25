// Piezo Sensor connections
const int buzzerPin = 10;
const int sensorPin = A0;
const int vibrationThreshold = 300;
const int ledPin = A4;
int led = 0;

void setup() {
  // Set the all Piezo sensor pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  knock();
}

int knock(){
   int sensorValue = analogRead(sensorPin);
   if (sensorValue > vibrationThreshold) {
     Serial.println("Vibration detected!");
     Serial.print("knock = ");
     Serial.println(sensorValue);
     tone();
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
