#include "part1.h"




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  init_switch();
  pinMode (13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int output = loop_switch();
  if(output != -1){
    if (output == 1){
    Serial.print("pressed ");
    Serial.println(output);
    }
    else{
      Serial.print("not pressed ");
      Serial.println(output);
    }
  }


}


