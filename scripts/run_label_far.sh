#!/bin/bash

gcc -std=c99 -o ../simulate ../lc3bsim3.c

python3 br_label_far_top.py
printf "\nRunning br_label_far_top test!\n"
../simulate ../ucode3 binary/br_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/br_label_far_top.dump

python3 br_label_far_bot.py
printf "\nRunning br_label_far_bot test!\n"
../simulate ../ucode3 binary/br_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/br_label_far_bot.dump