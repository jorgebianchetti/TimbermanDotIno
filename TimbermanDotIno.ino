#include "GameActions.h"

#define button  3   /* Push button input pin */
#define ldr     A5  /* LDR input pin */
#define led     13  /* LED output pin */
#define e1      12  /* Left electrode output pin */
#define e2      8   /* Right electrode output pin */

GameActions ga(ldr, e1, e2, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(button, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if(!digitalRead(button)){
    ga.initGame(2000);

    digitalWrite(led, HIGH);

    ga.setLevel();

    while(digitalRead(button)) ga.processGame(220);

    digitalWrite(led, LOW);
    
    ga.endGame(1000);
  }

  ga.deactElec(e1);
  ga.deactElec(e2);
}
