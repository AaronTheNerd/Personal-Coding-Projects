// Written by Aaron Barge
// Copyright 2019
Game dots_and_boxes;
// Welcome to the code for the game Dots and Boxes
// This is a two-player game with the goal of collecting the most boxes
// To do this you and another player will take turns claiming lines
// Whoever claims the last line of a box will win the box
// When there are no unclaimed boxes left the player with the most wins
// Press r to play again
void setup() {
  fullScreen();
  dots_and_boxes = new Game(10, 5); // You can change the size of the game here
  dots_and_boxes.show();
  setupPlayers("Aaron", "Jess"); // You can change the players' names
}



void setupPlayers(String player1, String player2) {
  Player player_1 = new Player(player1);
  player_1.SetColor(0, 50, 255); // Here you can set each player 1's color
  Player player_2 = new Player(player2);
  player_2.SetColor(255, 0, 0); // Here you can set each player 2's color
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



void mouseReleased() {
  Line l = dots_and_boxes.FindClosestLine(mouseX, mouseY);
  boolean line_changed = l.setOwner(dots_and_boxes.current);
  if (!line_changed)
    return;
  boolean box_made = dots_and_boxes.checkForBoxes(l);
  if (!box_made)
    dots_and_boxes.switchPlayer();
}



void keyPressed() {
  if (key == 'r') {
    dots_and_boxes.reset();
    key = ' ';
  }
}
