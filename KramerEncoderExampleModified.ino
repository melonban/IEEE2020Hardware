/*
 * Encoder example sketch
 * by Andrew Kramer
 * Modified for the IEEE 2020 Hardware Team
 * 1/1/2016
 *
 * Records encoder ticks for the motor
 * and calculates the rpm
 *
 */

// variables to store encoder pulses
volatile unsigned long Count = 0; //Interrupt variables must be volatile
volatile unsigned long RPM = 0;

//variable to store timing information
long previousMillis = 0; //Avoids using delay
long interval = 1000; //The encoder sends 12 CPR, so this
// determines resolution for raw RPM

void setup() {
  // initialize hardware interrupts
  attachInterrupt(digitalPinToInterrupt(3), EncoderEvent, CHANGE);
  //CHANGE triggers on rising and falling edges
  //This gives best resolution from all 6CPR per channel
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval) { //Acts as delay
    previousMillis = currentMillis;   

  Serial.print("Actual RPM: ");  
  Serial.println(RPM/8);
  RPM = 0; //Resets RPM for next count
  
  Serial.println(); 
  Serial.print("Rotations since startup: ");
  Serial.println(Count);
  Serial.println();
    }
}

// encoder event for the interrupt call
void EncoderEvent() {
      Count++;
      RPM++;
}
