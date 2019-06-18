int R1 = 2;
int R2 = 3;
int start = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  start = millis();
  Serial.begin(9600);
}

void loop() {
  MixDrink(start, 60000, 20000, R1, R2);
}

void MixDrink(long start, long mix, long booze, int mixPin, int boozePin) {
  if((millis() - start) > mix)  {
    digitalWrite(mixPin, HIGH);
  }
  if((millis() - start) > booze) {
    digitalWrite(boozePin, HIGH);
  }
}
