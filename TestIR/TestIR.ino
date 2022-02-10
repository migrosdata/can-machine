int ledPin = 13;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int relayPin = 7;               // choose the pin for the relay
int val = 0;                    // variable for reading the pin status

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(relayPin, OUTPUT);    // declare relay as output
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(inputPin);  // read input value

  if (val == HIGH)  // check if the input is HIGH
  {
    digitalWrite(ledPin, HIGH);  // turn LED ON
    digitalWrite(relayPin, HIGH); // turn relay ON
    delay(1000);
    if (pirState == LOW)
    {
      Serial.println("Motion detected!"); // print on output change
      pirState = HIGH;
    }
  }
  else
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    digitalWrite(relayPin, LOW);  // turn relay OFF
    delay(1000);
    if (pirState == HIGH)
    {
      Serial.println("Motion ended!");  // print on output change
      pirState = LOW;
    }
  }
}
