#include <Servo.h>
#include "IPK.h"

#define MIN_PULSE 500         // サーボモーターのパルス幅の下限
#define MAX_PULSE 2400        // サーボモーターのパルス幅の上限
#define MIN_ANGLE -30         // サーボの角度の下限
#define MAX_ANGLE 75          // サーボの角度の上限
#define WAIT_TIME 10         // 1ループの待ち時間
#define TIME_CYCLE  (2.0f)    // 回転周期[sec]
#define CIRCLE_R  (150.0f)    // 円の半径

Servo servo[3];
IPK ipk;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Start");

  // 変数初期化
  ipk = IPK();
  for (int i = 0 ; i < 3 ; i++ )
    servo[i].attach(i + 2, MIN_PULSE, MAX_PULSE);

  delay(2000);
}

void loop() {
  draw_circle();
  delay(WAIT_TIME);
}

// 円を描かせる関数
void draw_circle() {
  float theta_rad = (2.0 * PI) * millis() / (1000.0f * TIME_CYCLE);
  int pos_val[3];

  // 目標座標を決定
  pos_val[0] = (int)(CIRCLE_R * cos( theta_rad ));
  pos_val[1] = (int)(CIRCLE_R * sin( theta_rad ));
  pos_val[2] = -400;

  // サーボに出力
  servo_output(pos_val);
}

// サーボの出力値を計算・出力する関数
void servo_output(int pos_val[3]) {
  float angle[3];
  int temp;

  ipk.solve(pos_val, angle);
  for (int i = 0; i < 3 ; i++ ) {
    // サーボモータの角度の範囲外である場合，
    if ( in_range(angle[i], MIN_ANGLE, MAX_ANGLE) == false )
      return;

    // ipk.solveで動作範囲外の場合はnanとなるので
    if ( isnan(angle[i]) )
      return;
  }

  for (int i = 0 ; i < 3 ; i++ ) {
    // より細かい値にするため，パルス幅を計算して出力
    temp = (int)fmap(angle[i], -90, 90, MIN_PULSE, MAX_PULSE);
    servo[i].writeMicroseconds(temp);
    Serial.print(angle[i]);
    Serial.print("\t");
  }
  Serial.print("\n");
}


