#!/bin/env bash

cmake -B build
make -C build
./bin/tinyraytracer
pnmtopng out.ppm > out.png
xdg-open out.png