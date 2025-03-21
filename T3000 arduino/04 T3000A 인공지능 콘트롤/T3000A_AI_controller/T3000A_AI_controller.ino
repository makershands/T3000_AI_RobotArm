/*
핀맵
hc-06의 Rx -> 아두이노의 1번
hc-06의 Tx -> 아두이노의 0번

조립 후 모터 90도 정렬기준
4,5,6,7번을 맨 위 모터부터 연결한다.

모터 관련 배열도 맨 위부터 첫 번째 값이다

문자 들어오는 형식

조이스틱 모드 : (번호)(부호)(상태)
예시
0번 모터가 증가일 때 -> 0+1
3번 모터가 감소일 때 -> 3-1
1번 모터가 멈춤일 때 -> 1+0

인공지능 모드 : (라벨)

각도 설정 : (라벨):(1번각도),(2번각도),(3번각도)

속도 설정 : ;(속도)

모든 수신문자는 구분자 #가 끝에 붙어 들어옴
*/

#include <Servo.h>

// 받은 문자
String received;

// 모터 객체 배열
Servo motor[4];

// 모터 각도 배열
int motor_angle[4] = {93, 90, 90, 90};

// 모터 상태 배열
int motor_state[4] = {0, 0, 0, 0};

// 모터 작동 한계
int limit[4][2] = {
  {90, 180},
  {0, 180},
  {0, 180},
  {0, 180}
};

// 모터 작동 속도
int speed = 9;

// 색 인식 시 위치 값
int ini_pos[3] = {90, 90, 90};
int ball_pos[3] = {115, 0, 90};
int whi_pos[3] = {140, 60, 10};
int org_pos[3] = {140, 60, 180};

// 모터 각도와 색 인식 위치 배열이 일치하는가
bool isarrsame(int arr[]) {
  for (int i = 0; i < 3; i++) {
    if (motor_angle[i + 1] != arr[i]) {
      return false;
    }
  }
  return true;
}

// 모터 각도 값을 실행
void motor_write() {
  for (int i = 0; i < 4; i++) {
    motor[i].write(motor_angle[i]);
  }
}

// 좌표로 이동
void pos_move(int end_pos[]) {
  while (!isarrsame(end_pos)) {
    for (int i = 0; i < 3; i++) {
      if (motor_angle[i + 1] < end_pos[i]) {
        motor_angle[i + 1] += 1;
      } else if (motor_angle[i + 1] > end_pos[i]) {
        motor_angle[i + 1] -= 1;
      }
    }
    motor_write();
    delay(speed);
  }
}

// 집게발 조작 함수 -1 : 벌리기, 1 : 집기
void crab(int n) {
  while (motor[0].read() != (n == 1 ? limit[0][1] : limit[0][0])) {
    motor_angle[0] += n;
    motor[0].write(motor_angle[0]);
    delay((int)(speed * 1.3));
  }
}

// 색깔 이동
void color_move(String color) {
  if (color == "None") {
    return;
  }
  crab(-1);
  pos_move(ini_pos);
  pos_move(ball_pos);
  crab(1);
  delay(300);
  pos_move(ini_pos);
  delay(100);
  int* arr = color == "White" ? whi_pos : org_pos;
  pos_move(arr);
  crab(-1);
  delay(300);
  pos_move(ini_pos);
  crab(1);
}

// 조이스틱 모드
void joystick(String str) {
  if (str != "") {
    motor_state[str.substring(0, 1).toInt()] = str.substring(1).toInt();
  }
  for (int i = 0; i < 4; i++) {
    motor_angle[i] = val(i, motor_angle[i] + motor_state[i]);
  }
  motor_write();
  delay(speed);
}

// 작동 한계 내의 값을 반환하는 함수
int val(int m, int ang) {
  if (ang < limit[m][0]) {
    return limit[m][0];
  } else if (ang > limit[m][1]) {
    return limit[m][1];
  } else {
    return ang;
  }
}

void send_angle() {
  String temp = "";
  for (int i = 0; i < 4; i++) {
    temp += (String(motor_angle[i]) + ",");
  }
  temp = temp.substring(0, temp.length() - 1);
  Serial.print(temp);
}

void set_speed(String received) {
  String temp = received.substring(1);
  speed = temp.toInt();
  Serial.print("speed saved");
}

void angle_set(String received) {
  String name = received.substring(0, received.indexOf(":"));
  int comma1 = received.indexOf(",");
  int comma2 = received.indexOf(",", comma1 + 1);
  String temp_m2 = received.substring(received.indexOf(":") + 1, comma1);
  String temp_m3 = received.substring(comma1 + 1, comma2);
  String temp_m4 = received.substring(comma2 + 1);

  int* temp_p = NULL;
  if (name == "Ball") {
    temp_p = ball_pos;
  } else if (name == "White") {
    temp_p = whi_pos;
  } else if (name == "Orange") {
    temp_p = org_pos;
  }

  temp_p[0] = temp_m2.toInt();
  temp_p[1] = temp_m3.toInt();
  temp_p[2] = temp_m4.toInt();

  Serial.print(name + "angle saved");
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    motor[i].attach(i + 4);
    motor[i].write(motor_angle[i]);
  }
}

void receive() {
  if (Serial.available() > 0) {
    String result;
    char temp;
    do {
      temp = Serial.read();
      delay(10);
      result += String(temp);
    } while (temp != '#');
    result = result.substring(0, result.length() - 1);
    received = result;
  }
}

void loop() {
  receive();
  if (received == "Detection") {
    send_angle();
  } else if (received.indexOf(";") != -1) {
    set_speed(received);
  } else if (received.indexOf(":") != -1) {
    angle_set(received);
  } else if (received.indexOf("e") != -1) {
    color_move(received);
  } else {
    joystick(received);
  }
  received = "";
}
