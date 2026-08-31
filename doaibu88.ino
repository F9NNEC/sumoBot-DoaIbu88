#define RPWM 25
#define LPWM 26
#define LEN  27
#define REN  33

void setup() {
  Serial.begin(115200);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(REN, OUTPUT);

  digitalWrite(LEN, HIGH);
  digitalWrite(REN, HIGH); 
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == 'w') {
      analogWrite(RPWM, 255);
      analogWrite(LPWM, 0);
    } 
    else if (cmd == 's') {
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 255);
    } 
    else if (cmd == ' ') {
      analogWrite(RPWM, 0);
      analogWrite(LPWM, 0);
    }
  }
}