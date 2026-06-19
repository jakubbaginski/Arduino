// LED pin number
// 13 pin - user LED of Z-Uno board
#define LED_PIN     13

// button pin number
// 18 pin - button(BTN) of Z-Uno board
#define BTN_PIN     18

// channel number
#define ZUNO_CHANNEL_NUMBER_ONE   1

// variable to store current button state
byte lastButtonState;

ZUNO_SETUP_CHANNELS(ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_GENERAL_PURPOSE, getter));

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED_PIN, OUTPUT); // set LED pin as output
  pinMode(BTN_PIN, INPUT_PULLUP); // set button pin as input
}
// the loop routine runs over and over again forever:
void loop() {
  // sample current button state
  byte currenButtonState = digitalRead(BTN_PIN);

  if (currenButtonState != lastButtonState) { // if state changes
    lastButtonState = currenButtonState; // save new state
    zunoSendReport(ZUNO_CHANNEL_NUMBER_ONE); // send report over the Z-Wave to the controller
    if (currenButtonState == LOW) { // if button is pressed
      digitalWrite(LED_PIN, HIGH);  // turn the LED on
    } else {                        // if button is released
      digitalWrite(LED_PIN, LOW);   // turn the LED off
    }
  }
}

byte getter() {
  if (lastButtonState == 0) { // if button is pressed
    return 0xff;              // return "Triggered" state to the controller
  } else {                    // if button is released
    return 0;                 // return "Idle" state to the controller
  }
}
