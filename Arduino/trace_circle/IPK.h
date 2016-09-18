#include <math.h>

#define TO_DEG  (57.29577951308232f)
#define TO_RAD  (0.017453292519943295f)

class IPK {
  public:

    // パラメータに臨時の値を入れて初期化するコンストラクタ
    IPK() {
      _A = 120;
      _B = 200;
      _C = 430;
      _D = 130;
    }

    // パラメータを与えて初期化するコンストラクタ
    IPK(int A, int B, int C, int D) {
      _A = A;
      _B = B;
      _C = C;
      _D = D;
    }

    // 指定した座標に移動するための角度を計算する関数
    void solve(int pos[3], float angle[3]) {
      // pos(in):     目標の座標．int型配列，x,y,zの順番に代入されている
      // angle(out):  出力値の格納先．degreeなので注意
      float x = pos[0];
      float y = pos[1];
      float z = pos[2];

      for (int i = 0 ; i < 3 ; i++ ) {
        // sympyより計算された数式
        float phi = i * M_PI * 2.0 / 3.0;
        float cos_phi = cos(phi);
        float sin_phi = sin(phi);
        float P = -pow(_A, 2) + 2 * _A * _D + 2 * _A * x * cos_phi + 2 * _A * y * sin_phi
                  - pow(_B, 2) + pow(_C, 2) - pow(_D, 2) - 2 * _D * x * cos_phi - 2 * _D * y * sin_phi - pow(x, 2) - pow(y, 2) - pow(z, 2);
        float Q = -2 * _B * z;
        float R = -2 * _A * _B + 2 * _B * _D + 2 * _B * x * cos_phi + 2 * _B * y * sin_phi;
        float theta_0 = -2 * atan((Q - sqrt(-pow(P, 2) + pow(Q, 2) + pow(R, 2))) / (P - R));
        float theta_1 = -2 * atan((Q + sqrt(-pow(P, 2) + pow(Q, 2) + pow(R, 2))) / (P - R));

        // 絶対値の小さい方を選択し，角度を度数法に直す
        angle[i] = fabs(theta_0) > fabs(theta_1) ? theta_1 : theta_0;
        angle[i] *= 180 / M_PI;
      }
    }

  private:
    // パラメーター
    int _A, _B, _C, _D;
};

