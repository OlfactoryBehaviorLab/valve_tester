// Dewan Lab Valve Tester
// Teensy 2.0 sketch to power the Dewan Lab solenoid valve tester
// Austin Pauley, Dewan Lab, Florida State University, 2024
// v2.0

const int VALVE_PULSE_TIME_MS = 1000;
const int DEBOUNCE_TIME_MS = 15;
const int LED = 11;
const int SWITCH1 = 4;
const int buttons[4] = {3, 2, 1, 0};
const int valves[4] = {8, 7, 6, 5};


int switch_state = 0;
uint16_t pin_states[4] = {0, 0 , 0, 0};
int button_states[4] = {0, 0, 0, 0};
int prev_button_states[4] = {0, 0, 0, 0};
int button_latched[4] = {0, 0, 0, 0};
uint16_t db_starts[4] = {0, 0, 0, 0};



void setup() {
  Serial.begin(11520); // For Debug

  for(int i = 0; i < 4; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(valves[i], OUTPUT);
  }

  pinMode(SWITCH1, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  while(digitalRead(SWITCH1) == HIGH) {
      digitalWrite(LED, HIGH); // Loop mode on
      for(int i = 0; i < 4; i++) {
        if(digitalRead(SWITCH1) == LOW)
          break;
        
        pulse_valve(valves[i], VALVE_PULSE_TIME_MS);
      }     
    }

      digitalWrite(LED, LOW); // Loop mode off

      for(int v = 0; v < 4; v++){
        digitalWrite(valves[v], button_latched[v]);
      }

    get_button_states();
    poll_buttons();
    

}

void get_button_states(){
  for(int i = 0; i < 4; i++){

    int button_pin = buttons[i];
    int current_pin_state = digitalRead(button_pin);
    int prev_pin_state = pin_states[i];

    if (current_pin_state != prev_pin_state) { // Check whether the button has been pushed
      db_starts[i] = millis(); // Note debounce start time
      pin_states[i] = !prev_pin_state; // The last known state is now its inverse
    }
    if (millis() - db_starts[i] > DEBOUNCE_TIME_MS) // Debounce timer elapsed
      button_states[i] = pin_states[i];
  }
}

void poll_buttons(){

  for(int i = 0; i < 4; i++){
    int button_state = button_states[i];
    int prev_button_state = prev_button_states[i];

    if (button_state != prev_button_state && button_state == HIGH){
        int latch_state = button_latched[i];

        if(!latch_state){
          button_latched[i] = 1;
          digitalWrite(valves[i], HIGH);
        }
        else{
          button_latched[i] = 0;
          digitalWrite(valves[i], LOW);
        }


    }

    prev_button_states[i] = button_state;
  }

}

void pulse_valve(int valve, int time) {
  digitalWrite(valve, HIGH);
  delay(time);
  digitalWrite(valve, LOW);
  delay(time);
}
