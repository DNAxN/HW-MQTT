#include <Arduino.h>

// กำหนดขาของ push button และ LED
const int buttonPin = 35; // ขาที่ต่อ push button
const int ledPin = 27;   // ขาที่ต่อ LED

// สถานะปัจจุบันของ push button
int buttonState = 0;
// สถานะก่อนหน้าของ push button
int lastButtonState = 0;
// เก็บเวลาล่าสุดที่มีการกดปุ่ม
unsigned long lastDebounceTime = 0;
// ช่วงเวลาในการ debounce (เพื่อป้องกันการกระพริบของสัญญาณ)
unsigned long debounceDelay = 50;

// สถานะปัจจุบันของ LED
bool ledState = false;

void setup() {
  // กำหนดขาของ push button เป็นขาที่อ่านค่า digital
  pinMode(buttonPin, INPUT);
  // กำหนดขาของ LED เป็นขาที่ส่งสัญญาณ digital
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // อ่านสถานะปัจจุบันของ push button
  int reading = digitalRead(buttonPin);

  // ตรวจสอบว่ามีการกดปุ่มหรือไม่โดยใช้การ debounce
  if (reading != lastButtonState) {
    // ระบุเวลาปัจจุบัน
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // ถ้าผ่านเวลา debounce แล้ว
    
    if (reading != buttonState) {
      // อัพเดทสถานะปัจจุบันของ push button
      buttonState = reading;

      // ถ้ามีการกด push button
      if (buttonState == HIGH) {
        // สลับสถานะ LED
        ledState = !ledState;
        // เปิดหรือปิด LED ตามสถานะปัจจุบัน
        digitalWrite(ledPin, ledState);
      }
    }
  }

  // อัพเดทสถานะของ push button สำหรับการ debounce ในการวน loop ต่อไป
  lastButtonState = reading;
}
