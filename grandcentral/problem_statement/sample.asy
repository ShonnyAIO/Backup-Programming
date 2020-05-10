// Usage: ./sample.asy

import settings;
outformat="pdf";

defaultpen(0.5);

void node(real x, real y, int id, pen fillpen) {
  filldraw(circle((x, y), 10), fillpen=fillpen, drawpen=black);
  if (fillpen==red+white*0.3) {
    filldraw(circle((x, y), 7), fillpen=white, drawpen=black);
    filldraw((x,y+10) -- (x+3,y+13) -- (x+2,y+13) -- (x+2,y+17)
          -- (x-2,y+17) -- (x-2,y+13) -- (x-3,y+13) -- cycle, fillpen=fillpen, drawpen=black);
  } else {
    filldraw(circle((x, y), 7), fillpen=fillpen+white*0.5, drawpen=black);
  }
  label(minipage(format("%d", id), 0), (x-2.75, y+0.5));
}

real ys = 0.75;
real xs = 20;

draw((0, 0*ys) -- (0+3*xs, 60*ys), black);
node(0+0*xs,  0*ys, 1, red+white*0.3);
node(0+1*xs, 20*ys, 2, yellow);
node(0+2*xs, 40*ys, 3, orange);
node(0+3*xs, 60*ys, 4, green);

draw((60-xs,-20*ys) -- (60+2*xs, 40*ys), black);
node(60-1*xs,-20*ys, 1, lightblue);
node(60+0*xs,  0*ys, 2, red+white*0.3);
node(60+1*xs, 20*ys, 3, purple);
node(60+2*xs, 40*ys, 4, blue);

draw((120-xs,-20*ys) -- (120+2*xs, 40*ys), black);
node(120-1*xs,-20*ys, 4, lightblue);
node(120+0*xs,  0*ys, 3, red+white*0.3);
node(120+1*xs, 20*ys, 2, purple);
node(120+2*xs, 40*ys, 1, blue);

draw((180, 0*ys) -- (180+3*xs, 60*ys), black);
node(180+0*xs,  0*ys, 4, red+white*0.3);
node(180+1*xs, 20*ys, 3, yellow);
node(180+2*xs, 40*ys, 2, orange);
node(180+3*xs, 60*ys, 1, green);

shipout();
