#include <Ps3Controller.h>

#define ML_RPWM 26
#define ML_LPWM 27 
#define MR_RPWM 25
#define MR_LPWM 33 

void setMotor(int pinRPWM, int pinLPWM, int speed) {
  if (speed > 0) {
    analogWrite(pinRPWM, 0);
    analogWrite(pinLPWM, speed); // Maju
  } else if (speed < 0) {
    analogWrite(pinRPWM, -speed); // Mundur
    analogWrite(pinLPWM, 0);
  } else {
    analogWrite(pinRPWM, 0);
    analogWrite(pinLPWM, 0);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ML_RPWM, OUTPUT);
  pinMode(ML_LPWM, OUTPUT); 
  pinMode(MR_RPWM, OUTPUT);
  pinMode(MR_LPWM, OUTPUT); 

  Ps3.begin("58:2a:bd:77:2c:f4");
  Serial.println("Menunggu koneksi stik PS3...");
}

void loop() {
  if (Ps3.isConnected()) {
    // Rem
    int maxSpeed = Ps3.data.button.r2 ? 128 : 255;

    int leftSpeed = 0;
    int rightSpeed = 0;

    if (Ps3.data.button.triangle) {
      // Segitiga
      leftSpeed = maxSpeed;
      rightSpeed = maxSpeed;
    } 
    else if (Ps3.data.button.cross) {
      // Silang 
      leftSpeed = -maxSpeed;
      rightSpeed = -maxSpeed;
    } 
    else if (Ps3.data.button.circle) {
      // Lingkaran
      leftSpeed = -maxSpeed;
      rightSpeed = maxSpeed;
    } 
    else if (Ps3.data.button.square) {
      // Kotak
      leftSpeed = maxSpeed;
      rightSpeed = -maxSpeed;
    } 
    // ANALOG KIRI
    else {
      int lx = Ps3.data.analog.stick.lx;
      int ly = Ps3.data.analog.stick.ly;

      if (abs(lx) > 20 || abs(ly) > 20) {
        int move = map(-ly, -128, 127, -maxSpeed, maxSpeed);
        int turn = map(lx, -128, 127, -maxSpeed, maxSpeed);

        leftSpeed = move - turn;
        rightSpeed = move + turn;

        leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
        rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);
      }
    }

    setMotor(ML_RPWM, ML_LPWM, leftSpeed);
    setMotor(MR_RPWM, MR_LPWM, rightSpeed);

    delay(10);
  }
}
