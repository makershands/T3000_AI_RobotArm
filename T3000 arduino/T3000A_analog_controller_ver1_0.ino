/*

!!!! 컴퓨터에 로봇암을 연결한 채로 로봇암을 작동시키면 컴퓨터 메인 보드에 손상을 입을 수 있음.
절대로 로봇암 작동시에는 컴퓨터 USB를 빼고, 동봉된 아답타(5V 2A)를 연결해서 작동할 것!!!

아두이노 핀맵
(A0) : 오른쪽 조이스틱 y
(A1) : 오른쪽 조이스틱 x
(A4) : 왼쪽 조이스틱 x
(A5) : 왼쪽 조이스틱 y

조립 후 모터 90도 정렬기준
4,5,6,7번을 맨 위 글리퍼(집개) 모터부터 연결한다.

*/
#include<Servo.h>
//90도기준 맨위부터 첫번째
Servo motor[4];

//모터 작동한계
int limit[4][2] = {
  {92,182}, //집개 최대로 벌리는 각도는 92도, 가장 조이는 각도는 182도로 약간 더 조이게 되어 있음. 92도 이하로 유지되면 서보가 망가짐
  {0,180},
  {0,95},
  {0,180}
};

//모터 작동 속도 숫자가 작아지면 빨라짐. 초기 8, 익숙해진 경우 5가 적당함. 최고속도는 1
int speed=8;

void setup() {
  //90도정렬

motor[0].attach(4);
motor[0].write(90);
motor[1].attach(5);
motor[1].write(90);
motor[2].attach(6);
motor[2].write(90);
motor[3].attach(7);
motor[3].write(90);

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
  motor[motor_num].write(val(motor_num,start+mode));
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
    motor_move(2,-1);
    } 
  else if(analogRead(A4)>=1023){
    motor_move(2,1);
    }

  if(analogRead(A5)<=0){
    motor_move(3,-1);
    } 
  else if(analogRead(A5)>=1023){
    motor_move(3,1);
  }

}
