#!/bin/bash

for i in */*.in ; do x=`dirname $i`/`basename $i .in`; echo $x; cat $x.{ans,in} | ./draw.pl > $x.svg ; done
