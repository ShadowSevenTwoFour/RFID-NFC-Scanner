#include <Wire.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <Servo.h>

#define PN532_IRQ   (2)
#define PN532_RESET (3)

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 8, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

Servo lock;
int pos = 0;
int buzzer = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // Initialize serial communications with the PC
  while (!Serial) delay(10);                  // Do nothing if no serial port is opened
  SPI.begin();         // Initialise SPI bus
  
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  lcd.begin(16, 2);
  lcd.print("Tap Key to Scan");
  lock.attach(3);
  lock.write(pos);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  
  uint8_t uidLength;

  if (!nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength)) {
    return;
  }
  // if (!mfrc522.PICC_ReadCardSerial()) {
  //   return;
  // }
  String userid;
  for (byte i = 0; i < strlen(uid); i++) {
    userid += String(uid[i], HEX);
  }
  userid.toUpperCase();
  Serial.println(userid);
  if (userid == "331748C5") {
    lcd.clear();
    lcd.print("Authorized");
    lcd.setCursor(0, 1);
    lcd.print("Access");
    for (pos = 0; pos <= 90; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      lock.write(pos);  // tell servo to go to position in variable 'pos'
    }
    delay(5000);
    for (pos = 90; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      lock.write(pos);                    // tell servo to go to position in variable 'pos'
    }
    lcd.clear();
    lcd.print("Tap Key to Scan");
  }

  else {
    lcd.clear();
    lcd.print("Access");
    lcd.setCursor(0, 1);
    lcd.print("Denied");
    delay(3000);
    lcd.clear();
    lcd.print("Tap Key to Scan");
  }
}
