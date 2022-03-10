#! /usr/bin/env python3
import subprocess
import sys
import glob
import os

path_from_curr_dir = sys.argv[0][:-len("testsuite.py")]

# equivalent to an enum type for colors
class bcolors(object):
      GREEN = '\033[92m'
      WARNING = '\033[93m'
      FAIL = '\033[91m'
      ENDC = '\033[0m'
      BLUE = '\033[34m'
      UNDER = '\033[4m'

# executes the sanity test on the file 'path'
def check_sanity(path, expected):
  # run all the tests trough valgrind
  my = subprocess.run(["valgrind", "--error-exitcode=5", sys.argv[1], path],
                      stdout = subprocess.PIPE ,
                      stderr = subprocess.PIPE )
  name = path.split("/")[-1]
  if my.returncode == 5:
    print (bcolors.FAIL + "KO" + bcolors.ENDC + "File: " + name)
    return 0
  else:
    print (bcolors.GREEN + "OK" + bcolors.ENDC + "File: " + name) 
    return 1

# executes a test on the file 'path' gives simple oneline output
def basic_test(path, expected):
  ret = 1;
  my = subprocess.run([os.path.abspath(sys.argv[1]), path],
                      stdout = subprocess.PIPE,
                      stderr = subprocess.PIPE)
  name = path.split("/")[-1]
  if (my.returncode == expected):
    print (bcolors.GREEN + "OK " + bcolors.ENDC + "File: " + name)
  else:
    ret = 0
    print (bcolors.FAIL + "KO " + bcolors.ENDC + "File: " + name)
  return ret;

# tests a directory with the corresponding display
def test_dir(directory, function = basic_test):
  d = open(directory + "/info")
  d.readline()
  line = d.readline()
  d.close()
  expected = int(line[-2])
  files = glob.glob(directory + "/*.tig")
  ret = 0
  for name in files:
    ret += function(name, expected)
  if len(files) == 0:
    return [0 , 0]
  return [ret, len(files)]

def display_results(ret):
  if ret[1]:
    color = bcolors.GREEN
    if (ret[0] != ret[1]):
      color = bcolors.FAIL
    print("\nResult: " + color + "{:.2f}".format((ret[0] / ret[1]) * 100) + 
bcolors.ENDC + " % of tests are good. Total:",ret[1], "tests.")
    print(color + """\n
   _
  ( \                ..-----..__
   \.'.        _.--'`  [   '  ' ```'-._
    `. `'-..-'' `    '  ' '   .  ;   ; `-'''-.,__/|/_
      `'-.;..-''`|'  `.  '.    ;     '  `    '   `'  `,
                 \ '   .    ' .     '   ;   .`   . ' 7 \\
                  '.' . '- . \    .`   .`  .   .\     `Y
                    '-.' .   ].  '   ,    '    /'`""';:'
                      /Y   '.] '-._ /    ' _.-'
                      \\'\_   ; (`'.'.'  ."/
                       ' )` /  `.'   .-'.'
                        '\  \).'  .-'--"
                          `. `,_'`
                            `.__) 
""" + bcolors.ENDC)
  else:
    print("No tests were found")

def display_info(path, detail = 0):
  # checking if the fie exists
  if (os.path.isfile(path + "/info")):
    # and opening it
    with open(path + "/info") as f:
      name = path[len(path_from_curr_dir):]
      print("\n" + "-" * (30 - len(name) // 2) + bcolors.UNDER + name.upper() +
            bcolors.ENDC + (30 - (len(name) + 1) // 2) *"-" + "\n")
      if (detail):
        print(f.readline(), end = "")
    return 1
  else:
    return 0

def execute(args):
  # pickup all the directories existing arround the testsuite
  
  dirs = [i for i in glob.glob(path_from_curr_dir + "*") if os.path.isdir(path_from_curr_dir + i)]

  # if you forgot the binary
  if (len(args) == 1):
    print ("usage: './testsuite.py [BIN] [OPTION]' use option -h for a list of options.")
    return 1

  elif ("-h" in args or "--help" in args or (("-c" in args or "--category" in args) and len(args) == 2)):
    print ("usage: './testsuite.py [BIN] [OPTION]'\
\nOptions:\
\n\t-l or --list : displays a list of all test categories with a brief description.\
\n\t-s or --sanity : runs the tests with checking memory leaks or invalid reads\
\n\t-c [category] or --category [category] : launches a specific category")
    return 0

  elif ("-l" in args or "--list" in args):
    for i in dirs:
      display_info(i, 1)
    print("")
    return 0

  elif (len(args) == 2):
    results = [0, 0]
    for i in dirs:
      if (display_info(i)):
        tmp = test_dir(i)
        results[0], results[1] = results[0] + tmp[0], results[1] + tmp[1]
    display_results(results)
    return 0

  elif (len(args) == 3 and ("-s" in args or "--sanity" in args)):
    results = [0, 0]
    # run a check over all of the directories
    for i in dirs:
      if (display_info(i)):
        tmp = test_dir(i, check_sanity)
        results[0], results[1] = results[0] + tmp[0], results[1] + tmp[1]
    display_results(results) 
    return 0

  elif (len(args) == 3 and ("-c" in args or "--category" in args)):
    print("you must give a category to check use ./test.py -l to display the list of categories")
    return 1;

  elif (len(args) >= 4 and ("-c" in args or "--category" in args)):
    k = 0
    # scrapping off the / out of the name
    if args[3][-1] == '/':
      args[3] = args[3][:-1]
    # running trough all the directories
    for i in dirs:
      tmp = i[len(path_from_curr_dir):]
      # if we have a match for the name of the directory launch the tests
      if tmp == args[3]:
        display_info(i)
        if ("-s" in args or "--sanity" in args):
          display_results(test_dir(i, check_sanity))
        else:
          display_results(test_dir(i))
        k = 1

    # if no match error message
    if k == 0:
      print("No such category.\nUse ./test.py -l for a list of categories.")
      return 1
    return 0

  print("Unknown option use -h for a list of options")
  return 1

value = execute(sys.argv)

exit(value)
