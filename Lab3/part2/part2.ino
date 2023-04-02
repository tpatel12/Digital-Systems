
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


  int photo_input = analogRead(photoPin);
  int scaled_input = photo_input / 4; //convert to 0-255
  float brightness_fraction = scaled_input / 40;


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //Send a pulse 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //read the pulse in and convert units
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2)*0.0344;
  distance = distance * 4;

  //Cast to int and limit max distance
  int int_distance =min(distance, 255); 


  //red and green gradient LED values, based on distance and photocell brightness
  int red_output = (int_distance) * brightness_fraction;
  int green_output = (255 - int_distance) * brightness_fraction;

  analogWrite(redPin, min(255, red_output));
  analogWrite(greenPin, min(255, green_output));

  delay(100);

}
