import os

file1 = open("assembly/brnz_label_far_top.asm", "w")

file1.write(".ORIG x1000\n")
file1.write("A ADD R1, R1, #1\n")
file1.write("LEA R6, A\n")
file1.write("AND R5, R5, #0\n")
file1.write("NOT R5, R5\n")
file1.write("LSHF R5, R5, #12\n")
file1.write("ADD R5, R5, #15\n")
file1.write("ADD R5, R5, #15\n")
file1.write("ADD R5, R5, #7\n")
file1.write("STW R5, R6, #0\n")
for i in range(2**8 - 10):
  file1.write("ADD R1, R1, #1\n")
file1.write("BRNZ A\n")
file1.write(".END")
file1.close()

os.system("../assembler.linux assembly/brnz_label_far_top.asm binary/brnz_label_far_top.obj")