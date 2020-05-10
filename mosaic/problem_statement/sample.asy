// Usage: asy ./sample.asy

import settings;
outformat="pdf";

defaultpen(1);

file finp = input("../data/sample/1.in");

int rows = finp;
int cols = finp;
int colours = finp;

pen[] choices = {
  heavyred,
  grey,
  orange,
  fuchsia,
  black,
  colorPen[0],
  colorPen[1],
  colorPen[17],
  colorPen[7],
  colorPen[5],
};

for (int i = rows - 1; i >= 0; --i) {
  if (true) {
    pen p = white;
    if (i == 1) {
      p = black;
    }
    filldraw(box((-0.5,i)*40+(5,5), (0,i+1)*40-(5,5)), fillpen=p, drawpen=black);
    filldraw(box((cols+0.5,i)*40-(5,-5), (cols,i+1)*40+(5,-5)), fillpen=p, drawpen=black);
  }
  for (int j = 0; j < cols; ++j) {
    int colour = finp;
    pen p = choices[colour - 1];
    pen s = white*0.4+p*0.6;
    pen t = white*0.5+p*0.5;
    filldraw(box((j, i    )*40+(3,3), (j+1, i+1)*40-(3,3)), fillpen=p, drawpen=p+black*0.2+linewidth(4));
    filldraw(box((j, i    )*40+(5,5), (j+1, i+1)*40-(5,5)), fillpen=p, drawpen=s+linewidth(4));
    fill(arc(    (j+1+0.5/sqrt(2), i+0.5)*40-(5,0), 20, 135, 225) -- cycle, s);
    fill(arc((j+0-0.5/sqrt(2), i+0.5)*40+(5,0), 20, 315, 405) -- cycle, s);

    filldraw(circle((j+0.7, i+0.3)*40, 7.5), fillpen=t, drawpen=s);
    label(minipage(format("%d", colour), 0), (j+0.7, i+0.3)*40-3);
  }
}

shipout();
