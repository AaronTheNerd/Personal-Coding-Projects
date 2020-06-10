int points = 6;
int screen_length = 1500;
float snowflake_arm = (screen_length / 2.0) - 50;
Particle current;
void setup() {
  size(1500, 1500);
  translate(width/2, height/2);
  background(0);
  current = new Particle(snowflake_arm, 0);
}

void draw() {
  translate(width/2, height/2);
  rotate(PI/6);
  current.Move();
  current.Show(points);
  current.CheckBounds(points);
  if (current.resets > 2) {
    saveFrame("Snowflake####.jpg");
    clear();
    current.Reset();
  }
}
