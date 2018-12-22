ArrayList<Triangle> triangles;
void setup() {
  triangles = new ArrayList<Triangle>();
  size(1200, 1100);
  Triangle start = new Triangle(0, height, width / 2, 0, width, height);
  triangles.add(start);
  start.Draw();
  fill(0);
}
void draw() {
  ArrayList<Triangle> nextTriangles = new ArrayList<Triangle>();
  for (Triangle next : triangles) {
    if ((next.x3 - next.x1) >= 10) {
      next.DrawMiddle();
      nextTriangles.add(next.Top());
      nextTriangles.add(next.Left());
      nextTriangles.add(next.Right());
    }
  }
  triangles = nextTriangles;
}
