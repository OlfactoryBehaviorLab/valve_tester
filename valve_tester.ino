// Dewan Lab Valve Tester
// Teensy 2.0 sketch to power the Dewan Lab solenoid valve tester
// Austin Pauley, Dewan Lab, Florida State University, 2024
// v1.0

#define SWITCH1 4
#define BUTTON1 3
#define BUTTON2 2
#define BUTTON3 1
#define BUTTON4 0

#define VALVE1 8
#define VALVE2 7
#define VALVE3 6
#define VALVE4 5

int valves[4] = {8, 7, 6, 5};

#define LED 11

void setup()
{
  Serial.begin(11520);
  pinMode(SWITCH1, INPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);

  pinMode(VALVE1, OUTPUT);
  pinMode(VALVE2, OUTPUT);
  pinMode(VALVE3, OUTPUT);
  pinMode(VALVE4, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{

  while(digitalRead(SWITCH1) == HIGH)
    {
      digitalWrite(LED, HIGH);
      for(int i = 0; i < 4; i++)
      {
        if(digitalRead(SWITCH1) == LOW)
          break;
        
        pulse_valve(valves[i], 1000);
      }     
    }

      digitalWrite(LED, LOW);

      int b1_state = digitalRead(BUTTON1);
      int b2_state = digitalRead(BUTTON2); 
      int b3_state = digitalRead(BUTTON3);
      int b4_state = digitalRead(BUTTON4);


      digitalWrite(VALVE1, b1_state);
      digitalWrite(VALVE2, b2_state);
      digitalWrite(VALVE3, b3_state);
      digitalWrite(VALVE4, b4_state);
    

}

void pulse_valve(int valve, int time)
{
  digitalWrite(valve, HIGH);
  delay(time);
  digitalWrite(valve, LOW);
  delay(time);
}