// Dewan Lab Valve Tester
// Teensy 2.0 sketch to power the Dewan Lab solenoid valve tester
// Austin Pauley, Dewan Lab, Florida State University, 2024
// v1.0

const int valve_pulse_time_ms = 1000;
const int debounce_time_ms = 15;
const int LED = 11;
const int switch1 = 4;
const int buttons[4] = {3, 2, 1, 0};
const int valves[4] = {8, 7, 6, 5};

int button_states[4] = {0, 0, 0, 0};
int prev_button_states[4] = {0, 0, 0, 0};
int button_latched[4] = {0, 0, 0 , 0};
int switch_state = 0;


void setup() {
  Serial.begin(11520); // For Debug

  for(int i = 0; i <= 4; i++) {
    pinMode(buttons[i], INPUT);
    pinMode(valves[i], OUTPUT);
  }

  pinMode(switch1, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {

  while(digitalRead(switch1) == HIGH) {
      digitalWrite(LED, HIGH);
      for(int i = 0; i < 4; i++) {
        if(digitalRead(SWITCH1) == LOW)
          break;
        
        pulse_valve(valves[i], valve_pulse_time_ms);
      }     
    }

      digitalWrite(LED, LOW);

      int b1_state = digitalRead(BUTTON1);
      int b2_state = digitalRead(BUTTON2); 
      int b3_state = digitalRead(BUTTON3);
      int b4_state = digitalRead(BUTTON4);


      for(int v = 0; v < 4, v++){
        digitalWrite(valve[v], button_latched[v])
      }
    

}

void pulse_valve(int valve, int time) {
  digitalWrite(valve, HIGH);
  delay(time);
  digitalWrite(valve, LOW);
  delay(time);
}

void debounce_button(int button_num) {


}