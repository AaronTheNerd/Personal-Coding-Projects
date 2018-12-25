class Particle {
  float sx, sy;
  float x, y;
  int d;
  int resets;
  Particle(float x_, float y_) {
    x = x_;
    y = y_;
    sx = x_;
    sy = y_;
    d = 4;
    resets = 0;
  }
  void Move() {
    x -= 1;
    y += random(-5, 5);
    
  }
  void Show() {
    Show(1);
  }
  void Show(int points) {
    stroke(255);
    fill(255);
    for (int i = 0; i < points; ++i) {
      float aX = (x * cos(i * PI/(points/2))) + (y * sin(i * PI/(points/2)));
      float aY = (y * cos(i * PI/(points/2))) - (x * sin(i * PI/(points/2)));
      ellipse(aX, aY, d, d);
      ellipse(aX, -aY, d, d);
    }
  }
  void CheckBounds(int points) {
    if (atan(y/x) > PI / (points)) {
      x = sx;
      y = sy;
      ++resets;
    }
  }
  void Reset() {
    resets = 0;
  }
}
