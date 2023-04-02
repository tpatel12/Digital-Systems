#include <Adafruit_SSD1306.h>

/* 
   #define statements for OLED_CS, OLED_DC, OLED_RST, OLED_SI, OLED_CLK 
   go here.
*/

int OLED_CS = 6;
int OLED_RST = 4;
int OLED_CLK = 2;
int OLED_SI = 3;
int OLED_DC = 5;

int ENCODER_A = 9;
int ENCODER_B = 10;

Adafruit_SSD1306 disp(128,64,OLED_SI,OLED_CLK,OLED_DC,OLED_RST,OLED_CS);

void setup() {
  disp.begin(SSD1306_SWITCHCAPVCC);
  disp.clearDisplay();
  
  Serial.begin(9600);

  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);

}



int a_last = 0;
int b_last = 0;

int input = 128;
int x_v = 1;
int y_v = 1;

int x_coord = 10;
int y_coord = 10;

void loop() {
  

  int a_state = digitalRead(ENCODER_A);
  int b_state = digitalRead(ENCODER_B);

  // Serial.print(a_state);
  // Serial.print(", ");
  // Serial.print(b_state);
  // Serial.print("\n");
  if(a_state == 1 && a_last == 0 && b_state == b_last){

    if(a_state == b_state){

      Serial.println("Counter clockwise");
      input -= 10;
      input = max(0, input);
    }

  }

  else if(b_state == 1 && b_last == 0 && a_state == a_last){

    if(a_state == b_state){

      Serial.println("clockwise");
      input += 10;
      input = min(255, input);
    }

  }


  float MAX_V = 20;
  float multiplier = (float)(input - 128) * MAX_V/128; 
  x_coord += multiplier * x_v;
  y_coord += multiplier * y_v;


  if(x_coord < 0 || x_coord > 128){
    x_v *= -1;
  }
  if(y_coord < 0 || y_coord > 64){
    y_v *= -1;
  }

  disp.clearDisplay();
  disp.drawCircle(x_coord, y_coord, 4, WHITE);

  disp.display();
  
  



  a_last = a_state;
  b_last = b_state;
  


}
