import os

file1 = open("assembly/brp_label_far_bot.asm", "w")

file1.write(".ORIG x1000\n")
file1.write("ADD R2, R2, #1\n")
file1.write("BRP A\n")
for i in range(2**8 - 1):
  file1.write("ADD R1, R1, #1\n")
file1.write("A  HALT\n")
file1.write(".END")
file1.close()

os.system("../assembler.linux assembly/brp_label_far_bot.asm binary/brp_label_far_bot.obj")