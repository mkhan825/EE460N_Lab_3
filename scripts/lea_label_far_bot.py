import os

file1 = open("../tests/lea_label_far_bot.asm", "w")

file1.write(".ORIG x1000\n")
file1.write("LEA A\n")
for i in range(2**8):
  file1.write("ADD R1, R1, R1\n")
file1.write("A ADD R1, R1, R1\n")
file1.write(".END")
file1.close()

os.system("gcc -std=c99 -o ../assemble ../assembler.c")
os.system("../assemble ../tests/lea_label_far_bot.asm ./output/lea_label_far_bot.obj")