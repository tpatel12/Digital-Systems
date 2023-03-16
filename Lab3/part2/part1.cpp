#include "part1.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void light(){
  


  

}



int BIT = 2;

int get_state(){
  return (~PIND & (1 << BIT)) >> BIT;
}

int prev_state;




void init_switch(){

  //Set direction
  DDRD = 0;
  
  prev_state = get_state();
}


int loop_switch(){


  //internal pull-up
  PORTD |= (1 << BIT) ;
  
  int current = get_state();

  //Check if state is changed
  if(current != prev_state){

    //wait and poll again for de-bouncing
    _delay_ms(50);
    int check = get_state();
    if(current == check){


      prev_state = current;
      return current;

    }
  }

  return -1;

}