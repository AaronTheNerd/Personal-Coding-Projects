class Triangle {
  float x1;
  float y1;
  float x2;
  float y2;
  float x3;
  float y3;
  
  Triangle(float x1_,float y1_,float x2_,float y2_,float x3_,float y3_) {
    x1 = x1_;
    y1 = y1_;
    x2 = x2_;
    y2 = y2_;
    x3 = x3_;
    y3 = y3_;
  }
  Triangle Top() {
    return new Triangle((x1 + x2) / 2, (y1 + y2) / 2,
                        x2, y2,
                        (x2 + x3) / 2, (y2 + y3) / 2);
  }
  Triangle Left() {
    return new Triangle(x1, y1,
                        (x1 + x2) / 2, (y1 + y2) / 2,
                        (x1 + x3) / 2, y3);
  }
  Triangle Right() {
    return new Triangle((x1 + x3) / 2, y1,
                        (x2 + x3) / 2, (y2 + y3) / 2,
                        x3, y3);
  }
  void DrawMiddle() {
    triangle((x2 + x1) / 2, (y1 + y2) / 2,
             (x3 + x2) / 2, (y1 + y2) / 2,
             (x3 + x1) / 2, y3);
  }
  void Draw() {
    triangle(x1, y1, x2, y2, x3, y3);
  }
}
