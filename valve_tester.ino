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

void pulse_valve(int valve, int time) {
  digitalWrite(valve, HIGH);
  delay(time);
  digitalWrite(valve, LOW);
  delay(time);
}

void debounce_button(int button_num) {


}