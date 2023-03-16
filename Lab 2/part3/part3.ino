#include "part3.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //C function to make all active output ports have direction set to output
  setup_lights();
  
  //Setup button interrupt 
  int button_pin = 2;
  pinMode(button_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_pin), handler, RISING);


}

void loop()
{
  //Update all lights
  lights();
}


//Track time since previous handler call for debouncing
int last_press = 0;
void handler(){

  if(millis() - last_press > 200){
    last_press = millis();
    handle_button(); //C function to handle the button press
    Serial.println("button pressed");
  }

  
}


