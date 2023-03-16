#include "part2.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define DATA_PIN  3 
#define CLOCK_PIN 2 
#define LATCH_PIN 1 

//send a bit that is 1 or 0
void sendBit(int bit) {
  

  PORTB &= ~(1 << CLOCK_PIN);

  
  if (bit) {
    PORTB |= (1 << DATA_PIN); 
  } else {
    PORTB &= ~(1 << DATA_PIN); 
  }

  
  PORTB |= (1 << CLOCK_PIN); 
  
  
}

void sendByte(int data) {

  

  for (int i = 7; i >= 0; i--) { // Iterate through each bit in the byte, starting from the MSB
    sendBit((data >> i) & 1); // Send the current bit to the shift register
  }

  PORTB |= (1 << LATCH_PIN); // Set the latch pin to high to update the output
  PORTB &= ~(1 << LATCH_PIN); // Set the latch pin to low

  
}


setRegisterBit(int value, int bit, uint8_t* reg){
  if(!value){
    (*reg) |= (1 << bit);
  }
  else{
    (*reg) &= ~(1 << bit);

  }
}
//sets the columns and rows to high/low voltage based on values of col and row
void setPattern(int columns[], int rows[]){
  setRegisterBit(columns[0], 4, &PORTD);
  setRegisterBit(columns[1], 5, &PORTD);
  setRegisterBit(columns[2], 6, &PORTD);
  setRegisterBit(columns[3], 7, &PORTD);
  setRegisterBit(columns[4], 0, &PORTB);

  uint8_t columnByte = 0;
  setRegisterBit(rows[0], 0, &columnByte);
  setRegisterBit(rows[1], 2, &columnByte);
  setRegisterBit(rows[2], 3, &columnByte);
  setRegisterBit(rows[3], 4, &columnByte);
  setRegisterBit(rows[4], 5, &columnByte);
  setRegisterBit(rows[5], 6, &columnByte);
  setRegisterBit(rows[6], 7, &columnByte);

  
  sendByte(columnByte);
  

}

void lights(){

  DDRD = ~(0); //all pins output
  DDRB = ~(0); //all pins output
  PORTD = 0b00000000;
  PORTB = 0;
  
  //Array of all values for columns and rows to be high or low voltage
  //Some digits have multiple patterns that alternate to give illusion of being all lit at once
  int pattern_length[10];


  int col0a[] = {1,1,1,1,1};
  int row0a[] = {0,1,1,1,1,1,0};

  int col0b[] = {1,0,0,0,1};
  int row0b[] = {0,0,0,0,0,0,0};

  int* col0[] = {col0a, col0b};
  int* row0[] = {row0a, row0b};
  pattern_length[0] = 2;


  int col1a[] = {0,0,0,0,1};
  int row1a[] = {0,0,0,0,0,0,0};
  int *col1[] = {col1a};
  int *row1[] = {row1a};

   pattern_length[1] = 1;

  int col2a[] = {1,1,1,1,1};
  int row2a[] = {0,1,1,0,1,1,0};

  int col2b[] = {1,0,0,0,0};
  int row2b[] = {1,1,1,1,0,0,0};

  int col2c[] = {0,0,0,0,1};
  int row2c[] = {0,0,0,1,1,1,1};

  int* col2[] = {col2a, col2b, col2c};
  int* row2[] = {row2a, row2b, row2c};
  pattern_length[2] = 3;

  int col3a[] = {1,1,1,1,1};
  int row3a[] = {0,1,1,0,1,1,0};

  int col3b[] = {0,0,0,0,1};
  int row3b[] = {0,0,0,0,0,0,0};

  int* col3[] = {col3a, col3b};
  int* row3[] = {row3a, row3b};
  pattern_length[3] = 2;


  int col4a[] = {1,1,1,1,1};
  int row4a[] = {1,1,1,0,1,1,1};

  int col4b[] = {1,0,0,0,1};
  int row4b[] = {0,0,0,0,1,1,1};

  int col4c[] = {0,0,0,0,1};
  int row4c[] = {0,0,0,0,0,0,0};

  int* col4[] = {col4a, col4b, col4c};
  int* row4[] = {row4a, row4b, row4c};
  pattern_length[4] = 3;

  int col5a[] = {1,1,1,1,1};
  int row5a[] = {0,1,1,0,1,1,0};

  int col5b[] = {0,0,0,0,1};
  int row5b[] = {1,1,1,1,0,0,0};

  int col5c[] = {1,0,0,0,0};
  int row5c[] = {0,0,0,1,1,1,1};

  int* col5[] = {col5a, col5b, col5c};
  int* row5[] = {row5a, row5b, row5c};
  pattern_length[5] = 3;

  int col6a[] = {1,1,1,1,1};
  int row6a[] = {0,1,1,0,1,1,0};

  int col6b[] = {1,0,0,0,0};
  int row6b[] = {0,0,0,0,0,0,0};

  int col6c[] = {0,0,0,0,1};
  int row6c[] = {1,1,1,1,0,0,0};

  int* col6[] = {col6a, col6b, col6c};
  int* row6[] = {row6a, row6b, row6c};
  pattern_length[6] = 3;

  int col7a[] = {1,1,1,1,1};
  int row7a[] = {0,1,1,1,1,1,1};

  int col7b[] = {0,0,0,0,1};
  int row7b[] = {0,0,0,0,0,0,0};

  int* col7[] = {col7a, col7b};
  int* row7[] = {row7a, row7b};
  pattern_length[7] = 2;

  int col8a[] = {1,1,1,1,1};
  int row8a[] = {0,1,1,0,1,1,0};

  int col8b[] = {1,0,0,0,1};
  int row8b[] = {0,0,0,0,0,0,0};

  int* col8[] = {col8a, col8b};
  int* row8[] = {row8a, row8b};
  pattern_length[8] = 2;

  int col9a[] = {1,1,1,1,1};
  int row9a[] = {0,1,1,0,1,1,1};

  int col9b[] = {0,0,0,0,1};
  int row9b[] = {0,0,0,0,0,0,0};

  int col9c[] = {1,0,0,0,0};
  int row9c[] = {0,0,0,1,1,1,1};

  int* col9[] = {col9a, col9b, col9c};
  int* row9[] = {row9a, row9b, row9c};
  pattern_length[9] = 3;


  int** cols[10] = {col0, col1, col2, col3, col4, col5, col6, col7, col8, col9};
  int** rows[10] = {row0, row1, row2, row3, row4, row5, row6, row7, row8, row9};

  int num = 0;
  while(1){
    
    for(int k = 0; k < 200/pattern_length[num]; k++){
      //make each number pulse for 200 * 5 = 1000 milliseconds

      for(int i = 0; i < pattern_length[num]; i++){
        

        setPattern(cols[num][i], rows[num][i]);
        _delay_ms(5); 
      
      }

    }
    
    num ++;
    if(num > 9){
      num = 0;
    }

  }
  


}




