#!/bin/bash
# -*- ENCODING: UTF-8 -*-

make entrena
./entrena $1

make bot
mv bot invSim64/resources/bots
rm src/export.csv
rm src/dim.csv

