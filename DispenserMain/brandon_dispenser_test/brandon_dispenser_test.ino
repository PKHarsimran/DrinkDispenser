#include <Scheduler.h>

int R1 = 2;
int R2 = 3;

void setup() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  Serial.begin(9600);
  Scheduler.startLoop(loop1);
  //Scheduler.start(setupPin<R1>, startPump<R1, 10000>, 64);
}

void loop() {
  yield();
}

void loop1() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
}

void MixDrink(long start, long mix, long booze, int mixPin, int boozePin) {
  if((millis() - start) > mix)  {
    digitalWrite(mixPin, HIGH);
  }
  if((millis() - start) > booze) {
    digitalWrite(boozePin, HIGH);
  }
}
