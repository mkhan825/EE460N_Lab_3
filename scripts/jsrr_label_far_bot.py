import os

file1 = open("./assembly/jsrr_label_far_bot.asm", "w")

file1.write(".ORIG x1000\n")
file1.write("BR START\n")
file1.write("B .FILL x3000\n")
file1.write("START LEA R6, B\n")
file1.write("LDW, R6, R6, #0\n")
file1.write("JSRR R6\n")
for i in range(4090):
  file1.write("ADD R1, R1, #1\n")
file1.write("HALT\n")
file1.write(".END")
file1.close()

os.system("../assembler.linux assembly/jsrr_label_far_bot.asm binary/jsrr_label_far_bot.obj")