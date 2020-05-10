import settings;
outformat="pdf";

import graph;
size(1200,600,IgnoreAspect);

real solve(real x) {
  if (x < 10) {
    return round(x);
  } else {
    return 10 * solve(x / 10);
  }
}

real f(real x) {return x;}
real g(real x) {return log10(solve(x));}

int n = 350;

scale(Linear,Log);
pen thin=black; // palegrey+linewidth(0.5*linewidth());
draw(graph(f,1,n,operator ..),blue+linewidth(5*linewidth()));
xaxis("$x$",Bottom,LeftTicks(begin=false,end=false,extend=true,ptick=thin,pTick=thin));
yaxis("$y$",Left,RightTicks(begin=false,end=false,extend=true,ptick=thin,pTick=thin));

real prev = 0.0;
for (real i = 0.5; i < n; i += 0.5) {
  real value = g(i);
  draw((i,prev) -- (i, value) -- (i+0.5,value), black+linewidth(2*linewidth()));
  prev = value;
}

shipout();
