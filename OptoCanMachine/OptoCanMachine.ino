
/*
  ･
   *　★
      ･ ｡
        　･　ﾟ☆ ｡
  　　　 *　★ ﾟ･｡ *  ｡
          　　* ☆ ｡･ﾟ*.｡
      　　　ﾟ *.｡☆｡★　･                
                _____                    _____                    _____          
               /\    \                  /\    \                  /\    \         
              /::\    \                /::\    \                /::\____\        
             /::::\    \              /::::\    \              /::::|   |        
            /::::::\    \            /::::::\    \            /:::::|   |        
           /:::/\:::\    \          /:::/\:::\    \          /::::::|   |        
          /:::/  \:::\    \        /:::/__\:::\    \        /:::/|::|   |        
         /:::/    \:::\    \      /::::\   \:::\    \      /:::/ |::|   |        
        /:::/    / \:::\    \    /::::::\   \:::\    \    /:::/  |::|   | _____  
       /:::/    /   \:::\    \  /:::/\:::\   \:::\    \  /:::/   |::|   |/\    \ 
      /:::/____/     \:::\____\/:::/  \:::\   \:::\____\/:: /    |::|   /::\____\
      \:::\    \      \::/    /\::/    \:::\  /:::/    /\::/    /|::|  /:::/    /
       \:::\    \      \/____/  \/____/ \:::\/:::/    /  \/____/ |::| /:::/    / 
        \:::\    \                       \::::::/    /           |::|/:::/    /  
         \:::\    \                       \::::/    /            |::::::/    /   
          \:::\    \                      /:::/    /             |:::::/    /    
           \:::\    \                    /:::/    /              |::::/    /     
            \:::\    \                  /:::/    /               /:::/    /      
             \:::\____\                /:::/    /               /:::/    /       
              \::/    /                \::/    /                \::/    /        
               \/____/                  \/____/                  \/____/         
   *　
      ･ ｡
　　　　･　　ﾟ☆ ｡
  　　　 *　★ ﾟ･｡ *  ｡
          　　* ☆ ｡･ﾟ*.｡
      　　　ﾟ *.｡☆｡★　･
    *　　ﾟ｡·*･｡ ﾟ*
  　　　☆ﾟ･｡°*. ﾟ
　 ･ ﾟ*｡･ﾟ★｡
　　･ *ﾟ｡　　 *
　･ﾟ*｡★･
 ☆∴｡　*
･ ｡
*/

/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/

const int ledPin = 13;            // choose the pin for the LED
const int optoPin = 2;             // choose the input pin (for PIR sensor)
int relayPin1 = 7;               // choose the pin for the relay
int relayPin2 = 8;               // choose the pin for the relay

int optoStat = 0;                  // opto status
int optoState = LOW;               // we start, assuming no motion detected
int val = 0;                      // variable for reading the pin status

unsigned long previousMillis = 0; // will store last time LED was updated

// constants won't change:

const long intervalRelay1 = 7 * 60 * 1000UL; // 420000;  // interval at which to wait (milliseconds)
const long intervalOn1 = 3 * 60 * 1000UL;     // interval at which to wait (milliseconds)

const long intervalRelay2 = 0UL;  // interval at which to wait (milliseconds)
const long intervalOn2 =  17 * 60 * 1000UL;     // interval at which to wait (milliseconds)

/*
const long intervalRelay1 = 0 * 1000UL; // 420000;  // interval at which to wait (milliseconds)
const long intervalOn1 =  30 * 1000UL;     // interval at which to wait (milliseconds)

const long intervalRelay2 = 40 * 1000UL;  // interval at which to wait (milliseconds)
const long intervalOn2 = 30 * 1000UL;     // interval at which to wait (milliseconds)
*/
bool running = false;
bool relay1Done = false;
bool relay2Done = false;


/*==============================================================================
 * SETUP()
 *============================================================================*/
void setup() {
  pinMode(ledPin, OUTPUT);        // declare LED as output
  pinMode(optoPin, INPUT);         // declare sensor as input
  pinMode(relayPin1, OUTPUT);      // declare relay as output
  pinMode(relayPin2, OUTPUT);      // declare relay as output
  digitalWrite(relayPin1, LOW);  // turn relay OFF      
  digitalWrite(relayPin2, LOW);  // turn relay OFF
  Serial.begin(9600);
  Serial.println("Setup completed");
}

/*==============================================================================
 * LOOP()
 *============================================================================*/
void loop(){
  if (running) {
    // Countdown timer is running
    unsigned long currentMillis = millis();
    if (previousMillis == 0) {
      previousMillis = currentMillis;
    }
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (currentMillis - previousMillis >= intervalRelay1 && !relay1Done) { 
      Serial.println("turn relay 1 ON");
      digitalWrite(relayPin1, HIGH); // turn relay 1 ON1
    }
    if (currentMillis - previousMillis >= intervalRelay1 + intervalOn1 && !relay1Done) {
      Serial.println("turn relay 1 OFF");
      digitalWrite(relayPin1, LOW);  // turn relay OFF      
      relay1Done = true;
    }
    if (currentMillis - previousMillis >= intervalRelay2) { 
      Serial.println("turn relay 2 ON");
      digitalWrite(relayPin2, HIGH); // turn relay 1 ON
    }
    if (currentMillis - previousMillis >= intervalRelay2 + intervalOn2) {
      Serial.println("turn relay 2 OFF");
      digitalWrite(relayPin2, LOW);  // turn relay OFF      
      previousMillis = 0;     
      running = false;
      relay1Done = false;
      digitalWrite(ledPin, LOW); // turn LED OFF
      Serial.println("Back to motion sensor");
    }
  } else {
    // Motion sensor is running
    optoStat = digitalRead(optoPin); 
    if (optoStat == LOW) {         // if motion detected
      Serial.println("Hey I got you!!!");
      running = true;
    } else {
      //Log?
    }
  }
} 
