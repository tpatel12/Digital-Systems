#include "concurrency.h"

void p1 (void)
{
  /* process 1 here */

  while(1){
    for(int i = 0; i < 100; i++){
      digitalWrite(2, 0);
      digitalWrite(4, 1);
      //delay(10);
    }
    
  }
 return;
}

void p2 (void)
{
/* process 2 here */
  while(1){

    
    
    for(int i = 0; i < 100; i++){
      digitalWrite(4, 0);
      digitalWrite(2, 1);
      //delay(10);
    }
    
    //digitalWrite(2, LOW);
    //digitalWrite(3, HIGH);
    
  }
 return;
}

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);

  //process_init(p1, 64);
  if (process_create (p2, 64) < 0) {
    Serial.println("failed");
    delay(500);
    return;
  }
  if (process_create (p1, 64) < 0) {
    Serial.println("failed");
    delay(500);
    return;
    //return;
  }

  
}

void loop()


{

  
  
  // Serial.println("why are we here");
  //delay(2000);
  process_start();
  
  /* if you get here, then all processes are either finished or
     there is deadlock */

  Serial.println("deadlock");
  
  while (1) ;
}


