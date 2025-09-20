#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN D2       // SDA
#define RST_PIN D1      // RST

#define SERVO1_PIN D3   // GPIO0
#define SERVO2_PIN D4   // GPIO2
#define SERVO3_PIN D8   // GPIO15

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo1;
Servo servo2;
Servo servo3;

// Card 1: 136B5413 → D3 & D4
byte uid1[4] = {0x13, 0x6B, 0x54, 0x13};
// Card 2: C382040E → D8
byte uid2[4] = {0xC3, 0x82, 0x04, 0x0E};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("RFID ready. Scan your card...");

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  // Initial positions
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (isCard(rfid.uid.uidByte, uid1)) {
    Serial.println("Card 1 detected: Unlocking servos 1 & 2");
    actuateServos(servo1, servo2);
  } else if (isCard(rfid.uid.uidByte, uid2)) {
    Serial.println("Card 2 detected: Unlocking servo 3");
    actuateServo(servo3);
  } else {
    Serial.println("Unknown card");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

bool isCard(byte *readUID, byte *targetUID) {
  for (byte i = 0; i < 4; i++) {
    if (readUID[i] != targetUID[i]) return false;
  }
  return true;
}

void actuateServos(Servo &s1, Servo &s2) {
  s1.write(90);
  s2.write(90);
  delay(2000);
  s1.write(0);
  s2.write(0);
}

void actuateServo(Servo &s) {
  s.write(90);
  delay(2000);
  s.write(0);
}