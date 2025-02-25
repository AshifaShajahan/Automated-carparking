#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define IR_SENSOR1_PIN 2
#define IR_SENSOR2_PIN 3
#define SERVO_PIN 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gateServo;

int availableSlots = 4;
bool carEntering = false;
bool carExiting = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(2000);
  lcd.clear();
  lcd.print("Slots Available:");
  lcd.setCursor(0, 1);
  lcd.print(availableSlots);

  pinMode(IR_SENSOR1_PIN, INPUT);
  pinMode(IR_SENSOR2_PIN, INPUT);
  gateServo.attach(SERVO_PIN);
  closeGate();
}

void loop() {
  if (digitalRead(IR_SENSOR1_PIN) == HIGH && !carEntering) {
    carEntering = true;
    if (availableSlots > 0) {
      availableSlots--;
      updateLCD();
      openGate();
      delay(5000);
      closeGate();
    }
  } else if (digitalRead(IR_SENSOR2_PIN) == HIGH && !carExiting) {
    carExiting = true;
    if (availableSlots < 4) {
      availableSlots++;
      updateLCD();
    }
  }

  delay(1000);
  carEntering = false;
  carExiting = false;
}

void updateLCD() {
  lcd.setCursor(15, 1);
  lcd.print(availableSlots);
}

void openGate() {
  gateServo.write(90);
  delay(1000);
}

void closeGate() {
  gateServo.write(0);
  delay(1000);
}
