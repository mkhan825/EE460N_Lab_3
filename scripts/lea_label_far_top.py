import os

file1 = open("./assembly/lea_label_far_top.asm", "w")

file1.write(".ORIG x1000\n")
file1.write("A ADD R1, R1, R1\n")
for i in range(2**8 - 1):
  file1.write("ADD R1, R1, R1\n")
file1.write("BRNZ A\n")
file1.write(".END")
file1.close()

os.system("../assemble.linux ./assembly/lea_label_far_top.asm ./binary/lea_label_far_top.obj")
os.system("")