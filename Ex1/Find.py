import mmap
import os, string, re

def mapfile(filename):
    file = open(filename, "r+")
    size = os.path.getsize(filename)
    return mmap.mmap(file.fileno(), size)

data = mapfile("OPT1.out")
m = re.search("== SCF", data)
data.seek(m.start())
print data.readline()

def repl(filename, this, withthis):
    input_file = open(filename, 'r')
    out_file   = open("Changed.out", 'w')
    clean      = input_file.read().replace(this, withthis)
    out_file.write(clean)
