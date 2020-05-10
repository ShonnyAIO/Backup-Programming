#!/usr/bin/env python

"""
run to create the figure on the problem statement.
the input used is the first line of ../data/sample/1.in
"""

from math import sin,cos,pi,hypot

colours = [
  'LimeGreen', 'blue',
  'red', 'ProcessBlue',
  'brown', 'black']

def get_xy(i, cycle_len, radius=10):
  return (
    4 + radius * sin(i*pi*2.0/cycle_len),
    4 + radius * cos(i*pi*2.0/cycle_len))

def distance(a, b, cycle_len):
  a = get_xy(a, cycle_len)
  b = get_xy(b, cycle_len)
  return hypot(a[0]-b[0], a[1]-b[1])

def solve(path, cycle):
  xy = [get_xy(i, len(cycle)) for i in range(len(cycle))]
  dp = [[(0.0 if cycle[i] == path[0] else 1e60, i) for i in range(len(cycle))]]
  for i in range(1, len(path)):
    dp += [[]]
    for j in range(len(cycle)):
      dp[i] += [(1e60, i)]
      if cycle[j] == path[i]:
        for k in range(len(cycle)):
          dp[i][j] = min(dp[i][j], (dp[i-1][k][0] + distance(j, k, len(cycle)), k))

  best = min([(b,a) for a,b in enumerate(dp[-1])])[1]
  res = []
  for i in range(len(path) - 1, -1, -1):
      assert cycle[best] == path[i]
      res += [get_xy(best, len(cycle), 10-4 - float(len(cycle) - i) / len(cycle))]
      best = dp[i][best][1]

  return [(4, 4)] + res[::-1]

if __name__ == '__main__':
  f = open('../data/sample/1.in', 'r')
  ff = map(lambda s: s.strip(), f.readlines())
  path = map(int, ff[1].split())
  cycle = map(int, ff[3].split())
  s = [
    '\\documentclass[class=article,border=0pt]{standalone}\n',
    '\\usepackage[usenames,dvipsnames]{xcolor}\n',
    '\\usepackage{tikz}\n',
    '\\begin{document}\n',
    '\\pagestyle{empty}\n',
    '\\thispagestyle{empty}\n',
    '\\begin{tikzpicture}[scale=0.25]\n']
  y0 = 0
  k = 0

  # Centre node.
  s.append('\\draw[fill=black,draw=white] ({0}, {1}) ellipse (0.5 and 0.5);\n'.format(4, 4))

  # s.append('\\node[anchor=east] at (-6, ' + str(y0) + ') {\small step ' + str(k) + '};\n')
  for i,colour_id in enumerate(cycle):
    x, y = get_xy(i, len(cycle))

    '''
    # Draw the coloured receptacles.
    s.append('\\draw[fill={2}] ({0}, {1}) ellipse (4 and 4);\n'.format(
        x, y, colours[colour_id-1]))

    # Draw the centre.
    s.append('\\draw[fill=white,draw=white] ({0}, {1}) ellipse (2 and 2);\n'.format(
        x, y))

    # Draw the label.
    s.append('\\node[anchor=center] at ({0}, {1}) {3}\\Large {2}{4};\n'.format(
        x, y, colour_id, '{', '}'))
    '''

    # Draw the access points for receptacles.
    s.append('\\draw[fill={0},draw=white] ({1}, {2}) ellipse (0.5 and 0.5);\n'.format(
        colours[colour_id-1], *get_xy(i, len(cycle), 10.0 - 4.0)))

  route = solve(path, cycle)
  for a,b in zip(route[:-1], route[1:]):
      # s.append('\\draw [->,>=latex] ({0},{1}) to ({2},{3});\n'.format(
      s.append('\\path [draw=black,->,>=latex] ({0},{1}) to [bend left=10] ({2},{3});\n'.format(
        a[0], a[1], b[0], b[1]))

  s.append('\\end{tikzpicture}\n')
  s.append('\\end{document}\n')
  f = open('fig.tex', 'w')
  for x in s:
    f.write(x)
  f.close()
