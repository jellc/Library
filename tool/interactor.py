import numpy
import os
import random
import subprocess


class interactor:
    def __init__(self, exec):
        self.proc = subprocess.Popen([exec], stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    def __del__(self):
        self.proc.terminate()

    def write(self, x):
        self.proc.stdin.write((str(x) + '\n').encode('utf-8'))
        self.proc.stdin.flush()

    def read(self):
        return self.proc.stdout.readline().decode('utf-8').strip()

    def poll(self):
        return self.proc.poll()

    def wait(self):
        return self.proc.wait()
