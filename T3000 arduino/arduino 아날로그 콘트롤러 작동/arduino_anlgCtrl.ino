/*
아두이노 핀맵
(A9) : 오른쪽 조이스틱 y
(A1) : 오른쪽 조이스틱 x
(A4) : 왼쪽 조이스틱 x
(A5) : 왼쪽 조이스틱 y
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

//mode에 따라 증가또는 감소
void motor_move(int motor_num, int mode){
  int start = motor[motor_num].read();
  motor[motor_num].write(val(motor_num),start+mode);
  delay(speed);
}

void loop() {

  //모터방향과 조이스틱방향이 맞도록 4개 제어
  if(analogRead(A0)<=0){
    motor_move(0,1);
    }
  else if(analogRead(A0)>=1023){
    motor_move(0,-1);
  }

  if(analogRead(A1)<=0){
    motor_move(1,1);
  } 
  else if(analogRead(A1)>=1023){
    motor_move(1,-1);
  }

  if(analogRead(A4)<=0){
    motor_move(2,1);
    } 
  else if(analogRead(A4)>=1023){
    motor_move(2,-1);
    }

  if(analogRead(A5)<=0){
    motor_move(3,-1);
    } 
  else if(analogRead(A5)>=1023){
    motor_move(3,1);
  }

}
