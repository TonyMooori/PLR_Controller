// arduinoのmap関数をfloatに拡張した関数
float fmap(float value, float minIn, float maxIn, float minOut, float maxOut) {
  float rangeIn = maxIn - minIn;
  float rangeOut = maxOut - minOut;
  float deltaIn = value - minIn;

  return rangeOut * (deltaIn / rangeIn)  + minOut;
}

// int型の値をchar arrayにする関数
void to_str(int val, char *buf) {
  sprintf (buf, "%d", val);
}

// 値が[low,high]内部ならtrueを返す関数
bool in_range(float val, float low, float high) {
  return low <= val && val <= high;
}

