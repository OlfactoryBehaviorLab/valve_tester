// Dewan Lab Valve Tester
// Teensy 2.0 sketch to power the Dewan Lab solenoid valve tester
// Austin Pauley, Dewan Lab, Florida State University, 2024
// v2.0

// Configurables
const int VALVE_PULSE_ON_TIME_MS = 5000; // Time in ms that the valves will stay on in 'loop' mode
const int VALVE_PULSE_OFF_TIME_MS = 1000; // Inter valve interval

// Don't touch anything below
const int DEBOUNCE_TIME_MS = 15;
const int LED = 11;
const int SWITCH1 = 4;
const int buttons[4] = {3, 2, 1, 0};
const int valves[4] = {8, 7, 6, 5};


int switch_state = 0;
uint16_t prev_pin_states[4] = {0, 0 , 0, 0};
int button_states[4] = {0, 0, 0, 0};
int prev_button_states[4] = {0, 0, 0, 0};
int button_latched[4] = {0, 0, 0, 0};
uint16_t db_starts[4] = {0, 0, 0, 0};



void setup() {
  for(int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(valves[i], OUTPUT);
  }

  pinMode(SWITCH1, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  while(digitalRead(SWITCH1) == HIGH) {

      reset_all(); // If we enter into loop mode, reset all values and turn off valves

      digitalWrite(LED, HIGH); // Loop mode on
      for(int i = 0; i < 4; i++) {

        if(digitalRead(SWITCH1) == LOW) // If the user disables the loop, exit early
          break;
        
        pulse_valve(valves[i], VALVE_PULSE_ON_TIME_MS, VALVE_PULSE_OFF_TIME_MS);
        // Turn valves on and off based on defined times
      }     
    }

    digitalWrite(LED, LOW); // Loop mode off

    get_button_states(); // Get the 'actual' state of all the buttons
    set_outputs(); // Latch outputs based on states of buttons

}

void get_button_states(){
  // Teensy pin --> raw input data
  // Button state --> filtered state

  for(int i = 0; i < 4; i++){

    int button_pin = buttons[i]; // Get Teensy pin to read
    int current_pin_state = digitalRead(button_pin); // Read state of Teensy pin
    int prev_pin_state = prev_pin_states[i]; // Last state of the Teensy pin

    if (current_pin_state != prev_pin_state) { // Check whether the button has been pushed
      db_starts[i] = millis(); // Note debounce start timestamp
      prev_pin_states[i] = !prev_pin_state; // The last known state is now its inverse
    }
    if (millis() - db_starts[i] > DEBOUNCE_TIME_MS) // Debounce timer elapsed
      button_states[i] = prev_pin_states[i];  // The button state now matches the debounced pin state
  }
}

void set_outputs(){

  for(int i = 0; i < 4; i++){
    int button_state = button_states[i];  // Get the current, debounced button state; "filtered" state
    int prev_button_state = prev_button_states[i]; // Get the last state of the button to see if there was a change

    if (button_state != prev_button_state && button_state == HIGH){  // Make sure the button state changed, and it is still pressed
        int latch_state = button_latched[i];

        if(!latch_state){  // If it isn't latched, latch it
          button_latched[i] = 1;
          digitalWrite(valves[i], HIGH);
        }
        else{ // If it is latched, unlatch it
          button_latched[i] = 0;
          digitalWrite(valves[i], LOW);
        }
    }

    prev_button_states[i] = button_state; // Update previous state
  }

}

void pulse_valve(int valve, int on_time, int off_time) {
  digitalWrite(valve, HIGH); // Turn valve on
  delay(on_time); // Wait on_time
  digitalWrite(valve, LOW); // Turn valve off
  delay(off_time); // Wait off_time
}

void reset_all(){
  for (int i = 0; i < 4; i++){
    button_latched[i] = 0;
    prev_pin_states[i] = 0;
    button_states[i] = 0;
    prev_button_states[i] = 0;
    db_starts[i] = 0;
    digitalWrite(valves[i], LOW);
  }
}
