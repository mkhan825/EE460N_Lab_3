import os

def compare_dump(test_name, dump1, dump2):
  file1 = open(dump1)
  file2 = open(dump2)

  lines_1 = file1.readlines()
  lines_2 = file2.readlines()

  try:
    if (len(lines_1) != len(lines_2)):
      print("Lens are not the same in " + test_name + "!")

    tests_good = True
    for i in range(len(lines_1)):
      if (lines_1[i] != lines_2[i]):
        tests_good = False
  except IndexError:
    print(test_name + " may be different!")

  file1.close()
  file2.close()
  
  return tests_good


def lab2_dump_parse(lab2_dump):
  line_num = 0
  lines = lab2_dump.readlines()
  registers = False

  while (not registers):
    line = lines[line_num]

    if ("PC                :" in line):
      line_num += 1

    elif ("Registers:" in line):
      # print("Found registers")
      registers = True

    elif ("CCs:" in line):
      line_num += 1

    elif ("-------------------------------------" in line):
      line_num += 1

    elif ("Current register/bus values :" in line):
      line_num += 1

    else:
      del lines[line_num]

  lab2_dump.close()

  lab2_dump_wb = open("../../EE460N_Lab_2/scripts/dump/" + dump_file, "w")
  for lin in lines:
    lab2_dump_wb.write(lin)
  lab2_dump_wb.close()

def lab3_dump_parse(lab3_dump):
  line_num = 0
  lines = lab3_dump.readlines()
  registers = False

  while (not registers):
    line = lines[line_num]

    if ("PC           :" in line):
      stripped_line = line.strip()
      new_line = stripped_line.replace("PC           :", "PC                :")
      lines[line_num] = new_line + "\n"
      line_num += 1

    elif ("Registers:" in line):
      # print("Found registers")
      registers = True

    elif ("CCs:" in line):
      line_num += 1
    
    elif ("PC                :" in line):
      line_num += 1

    elif ("-------------------------------------" in line):
      line_num += 1
      pass

    elif ("Current register/bus values :" in line):
      line_num += 1
      pass

    else:
      del lines[line_num]

  lab3_dump.close()

  lab3_dump_wb = open("./dump/" + dump_file, "w")
  for lin in lines:
    lab3_dump_wb.write(lin)
  lab3_dump_wb.close()


for dump_file in os.listdir("./dump"):
  lab3_dump = open("./dump/" + dump_file)
  lab2_dump = open("../../EE460N_Lab_2/scripts/dump/" + dump_file)

  lab3_dump_parse(lab3_dump)
  lab2_dump_parse(lab2_dump)

  if (not compare_dump(dump_file, "./dump/" + dump_file, "../../EE460N_Lab_2/scripts/dump/" + dump_file)):
    print("Test for " + dump_file + " failed!")
