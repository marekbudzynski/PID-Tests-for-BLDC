double channel[1];
void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  channel[0] = pulseIn(2, HIGH);
  Serial.print(channel[0]);
  Serial.println(" - ");

}
