import mmap
import os, string, re

def mapfile(filename):
    file = open(filename, "r+")
    size = os.path.getsize(filename)
    return mmap.mmap(file.fileno(), size)

##Finding in data file
#data = mapfile("OPT1.out")
#m = re.search("== SCF", data)
#data.seek(m.start())
#print data.readline()

def repl(filename1,filename2, this, withthis):
    input_file = open(filename1, 'r')
    out_file   = open(filename2, 'w')
    clean      = input_file.replace(this, withthis)
    out_file.write(clean)

input_1 = raw_input("Input file")
input_2 = raw_input("Output file")
input_3 = raw_input("replace what")
input_4 = raw_input("with what")
repl(input_1,input_2,input_3,input_4)
