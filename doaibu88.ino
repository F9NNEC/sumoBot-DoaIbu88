#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
  PS4.begin("68:fe:71:0c:af:6c"); // MAC Address
  Serial.println("Menunggu koneksi dari stik PS4...");
}

void loop() {
  if (PS4.isConnected()) {
    
    // TOMBOL ARAH (D-PAD)
    if (PS4.Up()) Serial.println("D-Pad Atas");
    if (PS4.Right()) Serial.println("D-Pad Kanan");
    if (PS4.Down()) Serial.println("D-Pad Bawah");
    if (PS4.Left()) Serial.println("D-Pad Kiri");

    // TOMBOL AKSI
    if (PS4.Triangle()) Serial.println("Segitiga");
    if (PS4.Circle()) Serial.println("Lingkaran (O)");
    if (PS4.Cross()) Serial.println("Silang (X)");
    if (PS4.Square()) Serial.println("Kotak");

    // L1 & L2
    if (PS4.L1()) Serial.println("L1");
    if (PS4.R1()) Serial.println("R1");
  
    // L2 & R2 (0 sampai 255)
    if (PS4.L2Value() > 10) {
      Serial.printf("L2 Ditekan pelan/keras: %d\n", PS4.L2Value());
    }
    if (PS4.R2Value() > 10) {
      Serial.printf("R2 Ditekan pelan/keras: %d\n", PS4.R2Value());
    }

    // TOMBOL MENU & SPESIAL
    if (PS4.Share()) Serial.println("Share");
    if (PS4.Options()) Serial.println("Options");
    if (PS4.PSButton()) Serial.println("PS Button");
    if (PS4.Touchpad()) Serial.println("Touchpad ditekan");

    // JOYSTICK
    if (PS4.L3()) Serial.println("L3 (Analog Kiri Ditekan)");
    if (PS4.R3()) Serial.println("R3 (Analog Kanan Ditekan)");

    // abs() untuk mengabaikan nilai getaran kecil (deadzone di bawah 20)
    if (abs(PS4.LStickX()) > 20 || abs(PS4.LStickY()) > 20) {
      Serial.printf("Analog Kiri  -> X: %d, Y: %d\n", PS4.LStickX(), PS4.LStickY());
    }
    if (abs(PS4.RStickX()) > 20 || abs(PS4.RStickY()) > 20) {
      Serial.printf("Analog Kanan -> X: %d, Y: %d\n", PS4.RStickX(), PS4.RStickY());
    }

    // baterai stik
    Serial.printf("Baterai: %d%%\n", PS4.Battery());

    delay(100);
  }
}