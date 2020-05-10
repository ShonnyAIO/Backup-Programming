// Usage: asy -nosafe ./sample.asy

import settings;
outformat="pdf";

defaultpen(1);

file finp = input("../data/sample/2.in");
file fans = input("../data/sample/2.ans");

int card_count = finp;
int hand_size = finp;
int[][] hands = {};

while (!eof(fans)) {
  int[] hand = new int[];
  for (int i = 0; i < hand_size && !eof(fans); ++i) {
    hand.push(fans);
  }
  if (hand.length == hand_size) {
    hands.push(hand);
  }
}

real table_radius = card_count * 10;
path table(real width, real radius) {
  return
    arc((-width, 0.0),  radius, 90, 270) --
    arc((+width, 0.0),  radius, 270, 450) --
    cycle;
}

real table_width = 140;
filldraw(table(table_width, 100), fillpen=black, drawpen=invisible);
filldraw(table(table_width,  90), fillpen=palegreen, drawpen=black);
filldraw(table(table_width,  50), fillpen=lightgreen, drawpen=grey);

real[] xs = new real[]{-table_width/2, +table_width/2, -table_width/2, +table_width/2};
real[] ys = new real[]{-70, +70, +70, -70};

for (int i = 0; i < hands.length; ++i) {
  for (int j = 0; j < hands[i].length; ++j) {
    real x = xs[i] + (j - hands[i].length / 2.0) * 24;
    real y = ys[i] + sin(i * 1.8 + j * 4.3) * 3;
    real w = 6.4 * 4;
    real h = 8.9 * 4;
    real r = 3;
    path card =
        (x-w,y-h+r) --
        (x-w,y+h-r){up}..{right}(x-w+r,y+h) --
        (x+w-r,y+h){right}..{down}(x+w,y+h-r) --
        (x+w,y-h+r){down}..{left}(x+w-r,y-h) --
        (x-w+r,y-h){left}..{up}cycle;
    filldraw(shift(1, -2) * card, fillpen=black+opacity(0.5), drawpen=invisible);
    filldraw(               card, fillpen=white, drawpen=black);
    label(scale(2.0) * minipage(format("%d", hands[i][j]), 0), (x - w*2/3, y + h/2));
    if (j == hands[i].length - 1) {
      label(scale(2.0) * rotate(-180) * minipage(format("%d", hands[i][j]), 0), (x + w*2/3, y - h/2), gray(0.75));
    }
  }
}

shipout();
