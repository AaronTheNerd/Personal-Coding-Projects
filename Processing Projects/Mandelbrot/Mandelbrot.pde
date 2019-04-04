float x, y;
float pixel_width = 1.25;
void setup() {  
  size(2700, 1800);
  background(255);
  fill(0);
  y = -height/2;
}
void draw() {
  translate(width/2, height/2);
  float map_y = map(y, -height/2, height/2, -1, 1);
  for (x = -width/2; x < width/2; x += pixel_width) { 
    float map_x = map(x, -width/2, width/2, -2, 1);
    if (iterate(new complex(map_x, map_y))) {
      point(x, y);
      point(x, -y);
    }
  }
  y += pixel_width;
  if(y > pixel_width) {
    saveFrame("Mandelbrot-###.png");
    noLoop();
    return;
  }
}

boolean iterate(complex C) {
  complex zn = new complex(0, 0);
  complex Z = new complex(0, 0);
  int i = 0;
  do {
    Z = f(zn, C);
    if (Z.gt(2) || Z.lt(-2))
      return false;
    zn = Z;
    i++;
  } while (i < 100);
  return true;
}

complex f(complex Z, complex C) {
  return Z.mult(Z).add(C);
}
