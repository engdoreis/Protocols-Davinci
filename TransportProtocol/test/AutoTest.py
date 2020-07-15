
from time import sleep
import re
from time import localtime, strftime
import csv
import subprocess
import filecmp
import os.path
import os
import sys

class AutoTest:
    def __init__(self, binName):
        self.binName = binName

    def Execute(self, test):
        print("Starting test ", test.name)                
        
        #subprocess.call (["rm", test.output], stdout=subprocess.DEVNULL)        
        subprocess.call ([self.binName, test.input , test.output], stdout=subprocess.DEVNULL)

        if os.path.exists(test.output):
            if filecmp.cmp(test.expected, test.output, shallow=False):
                print ("Passed!!")
            else:
                print ("Comparisson between {} and {} failed".format(test.output, test.expected))
        else:
            print("Failed to run ", self.binName, test.input + ' ' + test.output)


        print ("------------------------------------------\n")


class UnitTest:
    def __init__(self, name, input, output, expected):
        self.name = name
        self.input = input
        self.output = output
        self.expected = expected
 

print (sys.argv[1], sys.argv[2])
print ("\n------------------------------------------")
print ("             Starting Server..              ")
print ("--------------------------------------------\n")
subprocess.Popen([str(sys.argv[1])], stdout=subprocess.DEVNULL)

print ("------------------------------------------")
print ("             AUTO TEST STARTING              ")
print ("--------------------------------------------\n")
at = AutoTest(str(sys.argv[2]))

testList = []

testList.append(UnitTest("Test case 1 ", "test/mock/Test1.txt", "~build/x86/debug/Test1.txt", "test/mock/Test1.txt"))
testList.append(UnitTest("Test case 2 ", "test/mock/Test2.txt", "~build/x86/debug/Test2.txt", "test/mock/Test2.txt"))
testList.append(UnitTest("Test case 3 ", "test/mock/Test3.txt", "~build/x86/debug/Test3.txt", "test/mock/Test3.txt"))
testList.append(UnitTest("Test case 4 ", "test/mock/Test4.txt", "~build/x86/debug/Test4.txt", "test/mock/Test4.txt"))

for test in testList:
    at.Execute(test)
        
    
