int ledPin = 12;                // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int relayPin1 = 7;               // choose the pin for the relay
int relayPin2 = 8;               // choose the pin for the relay
int val = 0;                    // variable for reading the pin status

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(relayPin1, OUTPUT);    // declare relay as output
  pinMode(relayPin2, OUTPUT);    // declare relay as output
  Serial.begin(9600);
}

void loop() {
  digitalWrite(relayPin1, HIGH); // turn relay ON
  Serial.println("relay 1 ON"); // print on output change
  delay(1000);
  digitalWrite(relayPin2, HIGH); // turn relay ON
  Serial.println("relay 2 ON"); // print on output change
  delay(1000);
  digitalWrite(relayPin1, LOW);  // turn relay OFF
  Serial.println("relay 1 OFF"); // print on output change
  delay(1000);
  digitalWrite(relayPin2, LOW);  // turn relay OFF
  Serial.println("relay 2 OFF"); // print on output change
  delay(1000);
}
