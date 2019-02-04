Game dots_and_boxes;
void setup() {
  fullScreen();
  //size(1500, 1000);
  dots_and_boxes = new Game(10, 5);
  dots_and_boxes.show();
  Player player_1 = new Player("Aaron");
  player_1.SetColor(100, 0, 255);
  Player player_2 = new Player("Jess`");
  player_2.SetColor(255, 100, 0);
  dots_and_boxes.AddPlayer(player_1);
  dots_and_boxes.AddPlayer(player_2);
}

void draw() {
  dots_and_boxes.show();
}
void mouseClicked() {
  Line l = dots_and_boxes.FindClosestLine(mouseX, mouseY);
  boolean line_changed = l.setOwner(dots_and_boxes.current);
  if (!line_changed)
    return;
  boolean box_made = dots_and_boxes.checkForBoxes(l);
  if (!box_made)
    dots_and_boxes.switchPlayer();
}
