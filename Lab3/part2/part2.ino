
int photoPin = A0;

int redPin = 10;
int greenPin = 9;
int bluePin = 3;

int trigPin = 5;
int echoPin = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (13, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  
}



void loop() {
  // put your main code here, to run repeatedly:


  int photo_input = analogRead(photoPin);
  int scaled_input = photo_input / 4; //convert to 0-255

  //Serial.println(scaled_input);

//  analogWrite(bluePin, photo_input);


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);



  

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2)*0.0344;
  distance = distance * 4;
  int int_distance =min(distance, 255); 


  Serial.println(int_distance);

  // for(int i = 100; i < 150; i ++){
  //   analogWrite(redPin, i);
    
  //   analogWrite(bluePin, 255 - i);

  //   Serial.println(i);
  //   delay(100);
  // }

   analogWrite(redPin, int_distance);
   analogWrite(greenPin, 255 - int_distance);

  delay(1000);

}

// void loop(){
//   analogWrite(greenPin, 200);
//   analogWrite(redPin, 255);
//   analogWrite(bluePin, 120);
// }


