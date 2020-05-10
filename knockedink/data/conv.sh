#!/bin/bash

for i in */*.svg ; do inkscape --export-png=`dirname $i`/`basename $i .svg`.png --export-dpi=96 --export-background-opacity=0 --without-gui $i ; done
