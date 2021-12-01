import os

def add_start(file):
  file.write(".ORIG x3000\n")
  file.write("AND R0, R0, #0\n")
  file.write("ADD R1, R1, #1\n")
  file.write("ADD R2, R2, #2\n")
  file.write("ADD R3, R3, #3\n")
  file.write("ADD R4, R4, #4\n")
  file.write("ADD R5, R5, #5\n")

def add_end(file):
  file.write("HALT\n")
  file.write(".END\n")

def add_no_halt_end(file):
  file.write(".END\n")

def add_br_end(file):
  file.write("A  HALT\n")
  file.write(".END\n")

def files_equal(test, input1, input2):
  content1 = input1.readlines()
  content2 = input2.readlines()

  count = 0
  for i in content2:
    count += 1
  try:
    for i in range(count):
      if (content1[i] == content2[i]):
        pass
      else:
        print(test + " has missmatches!")
        break
  except IndexError:
    print("Maybe something wrong with " + test)
    pass

def generate_asm():
  # First File

  test = "add1"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("ADD R5, R5, #-16\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  #

  test = "add2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("ADD R5, R5, #15\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Second file

  test = "and1"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("AND R5, R5, #-16\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  #

  test = "and2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("AND R5, R5, #15\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Third file

  test = "br"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("BR A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Fourth file

  test = "brp"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("BRP A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Fifth file

  test = "brz"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R0, R0, #0\n")
  file1.write("BRZ A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Sixth file

  test = "brzp"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("BRZP A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Seventh file

  test = "brn"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("ADD R0, R0, #-1\n")
  file1.write("BRN A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Eigth file

  test = "brnp"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("BRNP A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Ninth file

  test = "brnz"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R0, R0, #0\n")
  file1.write("BRNZ A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Tenth file

  test = "brnzp"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("BRNZP A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # Eleventh file

  test = "jmp"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("LEA R5, A\n")
  file1.write("JMP R5\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 12
  test = "ret"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("LEA R7, A\n")
  file1.write("RET\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 13 file

  test = "jsr"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("JSR A\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 14 file

  test = "jsrr"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("LEA R5, A\n")
  file1.write("JSRR R5\n")
  file1.write("ADD R5, R5, #-16\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 15 file

  test = "ldb1"
  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("LEA R5, A\n")
  file1.write("AND R1, R1 #0\n")
  for i in range(13):
    file1.write("ADD R1, R1, #1\n")
  file1.write("LDB R5, R5, #-32\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # #

  test = "ldb2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("A  LEA R5, A\n")
  file1.write("LDB R5, R5, #31\n")
  file1.write("AND R1, R1 #0\n")
  for i in range(12):
    file1.write("ADD R1, R1, #1\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 16 file

  test = "ldw1"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R1, R1, #0\n")
  file1.write("LEA R5, A\n")
  for i in range(31):
    file1.write("ADD R1, R1, #1\n")
  file1.write("A  LDW R5, R5, #-32\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # #

  test = "ldw2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R1, R1, #0\n")
  file1.write("LEA R5, A\n")
  file1.write("A  LDW R5, R5, #31\n")
  for i in range(30):
    file1.write("ADD R1, R1, #1\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 17 file

  test = "lea"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("LEA R5, A\n")
  add_br_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 18 file

  test = "not"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("NOT R5, R5\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 20 file
  test = "lshf"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("LSHF R5, R5, #15\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 20 file

  test = "rshfl"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("RSHFL R5, R5, #15\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 21 file

  test = "rshfa"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("RSHFA R5, R5, #15\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 21 file

  test = "stb1"
  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("LEA R5, A\n")
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("LSHF R5, R5, #4\n")
  file1.write("STB R5, R5, #1\n")

  file1.write("ADD R7, R7, #15\n")
  file1.write("ADD R7, R7, #15\n")
  file1.write("ADD R5, R7, #0\n")
  file1.write("STB R5, R5, #0\n")

  file1.write("LDW R5, R5, #0\n")
  file1.write("A  NOP\n")
  add_no_halt_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # #

  test = "stb2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R1, R1, #0\n")
  file1.write("LEA R4, A\n")
  file1.write("LEA R5, LOOP\n")
  file1.write("LOOP  AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("LSHF R5, R5, #4\n")
  file1.write("STB R5, R4, #-31\n")

  file1.write("ADD R7, R7, #15\n")
  file1.write("ADD R7, R7, #15\n")
  file1.write("ADD R5, R7, #0\n")
  for i in range(9):
    file1.write("ADD R1, R1, #1\n")
  file1.write("A  STB R5, R4, #-32\n")

  file1.write("LDW R5, R5, #0\n")
  file1.write("BR LOOP\n")
  add_no_halt_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 21 file

  test = "stw1"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("LSHF R5, R5, #12\n")
  file1.write("ADD R5, R5, #7\n")
  file1.write("ADD R5, R5, #15\n")
  file1.write("ADD R5, R5, #15\n")
  file1.write("LEA R4, A\n")
  file1.write("LOOP  AND R1, R1, #0\n")
  for i in range(32):
    file1.write("ADD R1, R1, #1\n")
  file1.write("A  STW R5, R4, #-32\n")
  file1.write("BR LOOP\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # #

  test = "stw2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("AND R1, R1, #0\n")
  file1.write("AND R5, R5, #0\n")
  file1.write("NOT R5, R5\n")
  file1.write("LSHF R5, R5, #12\n")
  file1.write("ADD R5, R5, #7\n")
  file1.write("ADD R5, R5, #15\n")
  file1.write("ADD R5, R5, #15\n")
  file1.write("LEA R7, A\n")
  file1.write("A  STW R5, R7, #31\n")
  for i in range(30):
    file1.write("ADD R1, R1, #1\n")
  file1.write("LSHF R5, R5, #0\n")
  add_no_halt_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 21 file

  test = "trap"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("TRAP x25\n")
  file1.write("NOT R5, R5\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # # 22 file

  test = "xor1"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("XOR R5, R5, #-16\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

  # #

  test = "xor2"

  file1 = open("assembly/"+test+"-py.asm", "w")
  add_start(file1)
  file1.write("XOR R5, R5, #15\n")
  add_end(file1)
  file1.close()

  os.system("../assembler.linux assembly/"+test+"-py.asm binary/"+test+"-py.obj")

def check_dump():
  print("")
  for file in os.listdir("./dump/"):
    dump = open("./dump/"+file, "r")
    asm = open("./assembly/"+file[:-5]+".asm", "r")
    print(asm.read())
    print(dump.read())
    print("Displaying " + file)
    input("Good?\n")
    dump.close()
    asm.close()

print("Generating assembly and binary files\n")
generate_asm()
os.system("gcc -std=c99 -o ../simulate ../lc3bsim3.c")
os.system("./run_sanity.sh")
check_dump()

# os.system("rm assembly/* binary/* dump/*")