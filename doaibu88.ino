#include <Ps3Controller.h>

#define ML_RPWM 26
#define ML_LPWM 27 
#define MR_RPWM 25
#define MR_LPWM 33 

void setup() {
  Serial.begin(115200);

  pinMode(ML_RPWM, OUTPUT);
  pinMode(ML_LPWM, OUTPUT); 
  pinMode(MR_RPWM, OUTPUT);
  pinMode(MR_LPWM, OUTPUT); 

  Ps3.begin("58:2a:bd:76:9d:ac");
  Serial.println("Menunggu koneksi dari stik PS3...");
}

void loop() {
  if (Ps3.isConnected()) {
    int yValue = Ps3.data.analog.stick.ly;
    int maxSpeed = Ps3.data.button.r2 ? 128 : 255; // Setengah kecepatan jika R2 ditekan

    if (yValue > 20) {
      analogWrite(ML_RPWM, 0);
      analogWrite(ML_LPWM, maxSpeed);
      analogWrite(MR_RPWM, 0);
      analogWrite(MR_LPWM, maxSpeed);
    } 
    else if (yValue < -20) {
      analogWrite(ML_RPWM, maxSpeed);
      analogWrite(ML_LPWM, 0);
      analogWrite(MR_RPWM, maxSpeed);
      analogWrite(MR_LPWM, 0);
    } 
    else {
      analogWrite(ML_RPWM, 0);
      analogWrite(ML_LPWM, 0);
      analogWrite(MR_RPWM, 0);
      analogWrite(MR_LPWM, 0);
    }

    // TOMBOL ARAH (D-PAD)
    if (Ps3.data.button.up) Serial.println("D-Pad Atas");
    if (Ps3.data.button.right) Serial.println("D-Pad Kanan");
    if (Ps3.data.button.down) Serial.println("D-Pad Bawah");
    if (Ps3.data.button.left) Serial.println("D-Pad Kiri");

    // TOMBOL AKSI
    if (Ps3.data.button.triangle) Serial.println("Segitiga");
    if (Ps3.data.button.circle) Serial.println("Lingkaran (O)");
    if (Ps3.data.button.cross) Serial.println("Silang (X)");
    if (Ps3.data.button.square) Serial.println("Kotak");

    // L1 & R1
    if (Ps3.data.button.l1) Serial.println("L1");
    if (Ps3.data.button.r1) Serial.println("R1");
  
    // L2 & R2
    if (Ps3.data.analog.button.l2 > 10) Serial.printf("L2 Value: %d\n", Ps3.data.analog.button.l2);
    if (Ps3.data.analog.button.r2 > 10) Serial.printf("R2 Value: %d\n", Ps3.data.analog.button.r2);

    // TOMBOL MENU
    if (Ps3.data.button.select) Serial.println("Select"); // PS3 menggunakan Select menggantikan Share
    if (Ps3.data.button.start) Serial.println("Start");   // PS3 menggunakan Start menggantikan Options
    if (Ps3.data.button.ps) Serial.println("PS Button");

    // JOYSTICK BUTTONS & AXIS
    if (Ps3.data.button.l3) Serial.println("L3 (Analog Kiri Ditekan)");
    if (Ps3.data.button.r3) Serial.println("R3 (Analog Kanan Ditekan)");

    int lx = Ps3.data.analog.stick.lx;
    int ly = Ps3.data.analog.stick.ly;
    int rx = Ps3.data.analog.stick.rx;
    int ry = Ps3.data.analog.stick.ry;

    if (abs(lx) > 20 || abs(ly) > 20) {
      Serial.printf("Analog Kiri  -> X: %d, Y: %d\n", lx, ly);
    }
    if (abs(rx) > 20 || abs(ry) > 20) {
      Serial.printf("Analog Kanan -> X: %d, Y: %d\n", rx, ry);
    }

    delay(10);
  }
}
