#!/usr/bin/env perl

use strict;
use warnings;

my ($lx, $mx, $ly, $my) = (0, 0, 0, 0);

my $tnow = 50 * <> // die;

sub min {return $_[0] < $_[1] ? $_[0] : $_[1];}
sub max {return $_[0] < $_[1] ? $_[1] : $_[0];}

my ($n, $warea) = map {int} split / /, <> // die;
my @cx = ();
my @cy = ();
my @cr = ();
for my $i (1 ... $n) {
  my ($x, $y, $t) = map {50 * int $_} split / /, <>;
  my $r = $tnow - $t;
  if ($r > 0) {
    push @cx, $x;
    push @cy, $y;
    push @cr, $r;
    $lx = min $lx, $x - $r;
    $mx = max $mx, $x + $r;
    $ly = min $ly, $y - $r;
    $my = max $my, $y + $r;
  }
}
for my $i (0 ... $#cx) {
  $cx[$i] -= $lx;
  $cy[$i] -= $ly;
}
$mx -= $lx;
$my -= $ly;

while ($mx > 512) {
  for my $i (0 ... $#cx) {
    $cx[$i] /= 2;
    $cy[$i] /= 2;
    $cr[$i] /= 2;
  }
  $mx /= 2;
  $my /= 2;
}

print <<SVG;
<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg"
     lang="en-gb"
     version="1.1"
     width="$mx"
     height="$my" >
<title>Case</title>
<rect width="100%" height="100%" fill="white"/>
SVG

for my $i (0 ... $#cx) {
  my ($x, $y, $r) = ($cx[$i], $cy[$i], $cr[$i]);
  print <<SVG;
  <circle cx='$x' cy='$y' r='$r' fill='none' stroke='black' />
SVG
}

print <<SVG;
</svg>
SVG
