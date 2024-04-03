/*
아두이노 핀맵
14번(A5) : 오른쪽 조이스틱 y
15번(A4) : 오른쪽 조이스틱 x
16번(A3) : 왼쪽 조이스틱 x
17번(A2) : 왼쪽 조이스틱 y
조립 후 모터 90도 정렬기준
4,5,6,7번을 맨 위 모터부터 연결한다.
*/
#include<Servo.h>
//90도기준 맨위부터 첫번째
Servo motor[4];

//모터 작동한계
int limit[4][2] = {{90, 180}, //집개 최대로 벌리는 각도는 45도, 가장 조이는 각도는 93도로 약간 더 조이게 되어 있음
                   {0,180},
                   {0,180},
                   {0,180}};

//모터 작동 속도
int speed=5;

void setup() {
  //90도정렬
  motor[0].attach(2);
  motor[0].write(93);
  for(int i=4 ; i<=7 ; i++){
    motor[i].attach(i);
    motor[i].write(90);
  }
}

//값검증 작동한계 내의 값을 반환하는함수
int val(int m, int ang){
  if(ang < limit[m][0]){
    return limit[m][0];
  }
  else if(ang > limit[m][1]){
    return limit[m][1];
  }
  else{
    return ang;
  }
}

void loop() {

  //모터방향과 조이스틱방향이 맞도록 4개 제어
  if(analogRead(A0)<=0){
    //지금위치에서 1증가
    int start = motor[0].read();
    motor[0].write(val(0,start+1));
    delay(speed);
  }
  else if(analogRead(A0)>=1023){
    int start = motor[0].read();
    motor[0].write(val(0,start-1));
    delay(speed);
  }

  if(analogRead(A1)<=0){
    int start = motor[1].read();
    motor[1].write(val(1,start-1));
    delay(speed);
  } 
  else if(analogRead(A1)>=1023){
    int start = motor[1].read();
    motor[1].write(val(1,start+1));
    delay(speed);
  }

  if(analogRead(A4)<=0){
    int start = motor[2].read();
    motor[2].write(val(2,start+1));
    delay(speed);
  } 
  else if(analogRead(A4)>=1023){
    int start = motor[2].read();
    motor[2].write(val(2,start-1));
    delay(speed);
  }

  if(analogRead(A5)<=0){
    int start = motor[3].read();
    motor[3].write(val(3,start-1));
    delay(speed);
  } 
  else if(analogRead(A5)>=1023){
    int start = motor[3].read();
    motor[3].write(val(3,start+1));
    delay(speed);
  }

}
