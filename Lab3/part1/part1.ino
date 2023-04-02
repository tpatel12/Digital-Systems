

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (13, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  int analogPin = A0;
  int val = analogRead(analogPin);
  int output_val = val / 4; //convert to 0-255

  Serial.println(output_val);

  //Output blue light intensity based on input
  int outputPin = 3;
  analogWrite(outputPin, val);

  delay(100);

}


