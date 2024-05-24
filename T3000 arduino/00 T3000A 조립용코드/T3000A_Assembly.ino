#include <Servo.h>

//모터 객체 배열
Servo motor[4];

//모터 각도 배열
int motor_angle[4] = { 93,90,90,90 };

void setup() {
  //시리얼 시작
  Serial.begin(9600);
  //초기화 90도정렬, 핀은 4567번
  for (int i = 0; i < 4; i++) {
    motor[i].attach(i + 4);
    motor[i].write(motor_angle[i]);
  }
}

void loop() {
  Serial.println("Assembly");
  for (int i = 0; i < 4; i++) {
    motor[i].write(motor_angle[i]);
  }
}