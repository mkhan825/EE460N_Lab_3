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

python3 brp_label_far_top.py
printf "\nRunning brp_label_far_top test!\n"
../simulate ../ucode3 binary/brp_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brp_label_far_top.dump

python3 brp_label_far_bot.py
printf "\nRunning brp_label_far_bot test!\n"
../simulate ../ucode3 binary/brp_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brp_label_far_bot.dump

python3 brz_label_far_top.py
printf "\nRunning brz_label_far_top test!\n"
../simulate ../ucode3 binary/brz_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brz_label_far_top.dump

python3 brz_label_far_bot.py
printf "\nRunning brz_label_far_bot test!\n"
../simulate ../ucode3 binary/brz_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brz_label_far_bot.dump

python3 brzp_label_far_top.py
printf "\nRunning brzp_label_far_top test!\n"
../simulate ../ucode3 binary/brzp_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brzp_label_far_top.dump

python3 brzp_label_far_bot.py
printf "\nRunning brzp_label_far_bot test!\n"
../simulate ../ucode3 binary/brzp_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brzp_label_far_bot.dump

python3 brn_label_far_top.py
printf "\nRunning brn_label_far_top test!\n"
../simulate ../ucode3 binary/brn_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brn_label_far_top.dump

python3 brn_label_far_bot.py
printf "\nRunning brn_label_far_bot test!\n"
../simulate ../ucode3 binary/brn_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brn_label_far_bot.dump

python3 brnp_label_far_top.py
printf "\nRunning brnp_label_far_top test!\n"
../simulate ../ucode3 binary/brnp_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnp_label_far_top.dump

python3 brnp_label_far_bot.py
printf "\nRunning brnp_label_far_bot test!\n"
../simulate ../ucode3 binary/brnp_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnp_label_far_bot.dump

python3 brnz_label_far_top.py
printf "\nRunning brnz_label_far_top test!\n"
../simulate ../ucode3 binary/brnz_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnz_label_far_top.dump

python3 brnz_label_far_bot.py
printf "\nRunning brnz_label_far_bot test!\n"
../simulate ../ucode3 binary/brnz_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnz_label_far_bot.dump

python3 brnzp_label_far_top.py
printf "\nRunning brnzp_label_far_top test!\n"
../simulate ../ucode3 binary/brnzp_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnzp_label_far_top.dump

python3 brnzp_label_far_bot.py
printf "\nRunning brnzp_label_far_bot test!\n"
../simulate ../ucode3 binary/brnzp_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/brnzp_label_far_bot.dump

python3 jsr_label_far_top.py
printf "\nRunning jsr_label_far_top test!\n"
../simulate ../ucode3 binary/jsr_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jsr_label_far_top.dump

python3 jsr_label_far_bot.py
printf "\nRunning jsr_label_far_bot test!\n"
../simulate ../ucode3 binary/jsr_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jsr_label_far_bot.dump

python3 jsr_label_far_top.py
printf "\nRunning jsr_label_far_top test!\n"
../simulate ../ucode3 binary/jsr_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jsr_label_far_top.dump

python3 jsr_label_far_bot.py
printf "\nRunning jsr_label_far_bot test!\n"
../simulate ../ucode3 binary/jsr_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/jsr_label_far_bot.dump

python3 lea_label_far_top.py
printf "\nRunning lea_label_far_top test!\n"
../simulate ../ucode3 binary/lea_label_far_top.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/lea_label_far_top.dump

python3 lea_label_far_bot.py
printf "\nRunning lea_label_far_bot test!\n"
../simulate ../ucode3 binary/lea_label_far_bot.obj<<EOF
go
rdump
quit
EOF
cp dumpsim dump/lea_label_far_bot.dump