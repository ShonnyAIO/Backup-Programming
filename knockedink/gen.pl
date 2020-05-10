#!/usr/bin/env perl

use strict;
use warnings;

my $n = 100;
my $a = 31415.92;
print "$n $a\n";

for my $i (1 ... $n) {
  my $x = 50 * cos(($i / $n) * 2 * 3.141592);
  my $y = 50 * sin(($i / $n) * 2 * 3.141592);
  printf "%.3f %.3f %.2f\n", $x, $y, 5;
}
