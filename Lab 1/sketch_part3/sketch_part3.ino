#include "testasm.h"

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  for(int i = 0; i < 20; i++){
      Serial.print("fib(");
      Serial.print(i);
      Serial.print(") = ");
      Serial.println(testasm(i));
    }
  pinMode (13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (13, HIGH);
  delay(400);
  digitalWrite (13, LOW);
  delay(400);
}
