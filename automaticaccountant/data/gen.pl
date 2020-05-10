#!/usr/bin/env perl

use strict;
use warnings;

my $slots = 100000;
print "$slots\n";

for my $i (1 .. $slots-1) {
  my $a = 1 + int rand 10000;
  my $b = 50000 + int rand 50000;
  if ($i % 1000 == 0) {
      $a = 1 + int rand 100000;
      $b = 1 + int rand 100000;
  }
  print "$a $b\n";
}
print "100000 1\n";

my $coins = 50000;
print "$coins\n";

for my $i (1 .. $coins) {
  my $a = 1 + int rand 100000;
  my $b = 1 + int rand 100000;
  print "$a $b\n";
}
