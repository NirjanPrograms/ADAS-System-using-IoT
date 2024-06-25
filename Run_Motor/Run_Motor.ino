// Motor A connections
int enA = 11;
int in1 = 12;
int in2 = 13;

// Motor B connections
int enB = 9;
int in3 = 8;
int in4 = 7;
int speed = 0;

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

  Serial.begin(9600);
}

void loop() {
  speed = start();
  Serial.print("Speed = ");
  Serial.println(speed);
  delay(2000);
  
  speed = slow();
  Serial.print("Speed = ");
  Serial.println(speed);
  delay(2000);
  
  speed = stop();
  Serial.print("Speed = ");
  Serial.println(speed);
  delay(2000);
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
