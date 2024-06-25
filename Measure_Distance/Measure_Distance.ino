// Ultrasonic Sensor connections
int trig = 5;
int echo = 6;
int timet =0;
int dist = 0;

void setup() {
  // set the all ultrasonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop() {
  dist = distance();
  Serial.print("Distance = ");
  Serial.println(dist);
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
