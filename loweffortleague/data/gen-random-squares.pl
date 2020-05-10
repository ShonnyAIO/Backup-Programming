#!/usr/bin/env perl

use strict;
use warnings;

my $n = int(<STDIN>);
die unless 1 <= $n && $n <= 16;

my $teams = (1 << $n);
print "$n\n";

my %strengths = ();
while (keys %strengths < $teams) {
    $strengths{1 + int((rand 1000) ** 2)} = 1;
}
my @strengths = keys %strengths;
print "@strengths\n";
