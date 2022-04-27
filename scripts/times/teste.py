# reqs: pandas and matplotlib

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import subprocess

def makeGraph(kind, title, x, log, alg, search, input):
  subprocess.call(['sh', './time.sh', alg, title, search, input])

  y = ['n_' + alg, 'o_' + alg]
  df = pd.read_csv(title + '.csv').fillna(0)
  df.plot(
    x = x, 
    y=y, 
    kind = kind,
    title= title,
    logy = log,
    grid = True,
  )
  figure = plt.gcf()
  figure.set_size_inches(18, 9)
  plt.savefig(fname=title + '.png')
  

def main():
  makeGraph('line', 'Time Default (sec)', 'N', True, 'newtonDefault', 'rdtsc', 'saida.dat')
  makeGraph('line', 'Time Hessian Default (sec)', 'N', True, 'newtonDefault_hessian', 'rdtsc', 'saida.dat')
  makeGraph('line', 'Time gradient Default (sec)', 'N', True, 'newtonDefault_gradient', 'rdtsc', 'saida.dat')
  makeGraph('line', 'Time solver Default (sec)', 'N', True, 'newtonDefault_solver', 'rdtsc', 'saida.dat')
  
  makeGraph('line', 'Time GS (sec)', 'N', True, 'newtonGS', 'rdtsc', 'saida.dat')
  makeGraph('line', 'Time Hessian GS (sec)', 'N', True, 'newtonGS_hessian', 'rdtsc', 'saida.dat')
  makeGraph('line', 'Time gradient GS (sec)', 'N', True, 'newtonGS_gradient', 'rdtsc', 'saida.dat')
  makeGraph('line', 'Time solver GS (sec)', 'N', True, 'newtonGS_solver', 'rdtsc', 'saida.dat')
  
  
  makeGraph('line', 'L2 Miss Ratio Default (sec)', 'N', False, 'newtonDefault', 'L2 miss ratio', 'saida.dat')
  makeGraph('line', 'L2 Miss Ratio Hessian Default (sec)', 'N', False, 'newtonDefault_hessian', 'L2 miss ratio', 'saida.dat')
  makeGraph('line', 'L2 Miss Ratio gradient Default (sec)', 'N', False, 'newtonDefault_gradient', 'L2 miss ratio', 'saida.dat')
  makeGraph('line', 'L2 Miss Ratio solver Default (sec)', 'N', False, 'newtonDefault_solver', 'L2 miss ratio', 'saida.dat')
  
  makeGraph('line', 'L2 Miss Ratio GS (sec)', 'N', False, 'newtonGS', 'L2 miss ratio', 'saida.dat')
  makeGraph('line', 'L2 Miss Ratio Hessian GS (sec)', 'N', False, 'newtonGS_hessian', 'L2 miss ratio', 'saida.dat')
  makeGraph('line', 'L2 Miss Ratio gradient GS (sec)', 'N', False, 'newtonGS_gradient', 'L2 miss ratio', 'saida.dat')
  makeGraph('line', 'L2 Miss Ratio solver GS (sec)', 'N', False, 'newtonGS_solver', 'L2 miss ratio', 'saida.dat')


if __name__ == "__main__":
  main()