
int photoPin = A0;

int redPin = 2;
int greenPin = 4;
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

  analogWrite(bluePin, photo_input);


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2)*0.0344;
  int int_distance = min(distance, 255); 


  Serial.println(int_distance);

  for(int i = 0; i < 255; i ++){
    analogWrite(greenPin, i);
    //analogWrite(greenPin, 255 - i);
    delay(10);
  }

  //analogWrite(redPin, int_distance);
 // analogWrite(greenPin, 255 - int_distance);

  delay(1000);

}


