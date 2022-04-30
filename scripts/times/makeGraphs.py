# reqs: pandas and matplotlib

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import subprocess

def makeGraph(kind, title, x, log, alg, search, input, size):
  subprocess.call(['sh', './getTables.sh', alg, title, search, input, size])

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
  plt.close('all')

def makeGraphDP(kind, title, x, log, alg, input, size):
  subprocess.call(['sh', './getTableFlops.sh', alg, title, input, size])

  y = ['n_' + alg + '_DP', 'o_' + alg + '_DP', 'n_' + alg + '_AVX', 'o_' + alg + '_AVX']
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
  plt.close('all')
  

def main():
  makeGraph('line', 'Time Default (sec)', 'N', True, 'newtonDefault', 'rdtsc', 'saidaL2', '9')
  makeGraph('line', 'Time Hessian Default (sec)', 'N', True, 'newtonDefault_hessian', 'rdtsc', 'saidaL2', '9')
  makeGraph('line', 'Time gradient Default (sec)', 'N', True, 'newtonDefault_gradient', 'rdtsc', 'saidaL2', '9')
  makeGraph('line', 'Time solver Default (sec)', 'N', True, 'newtonDefault_solver', 'rdtsc', 'saidaL2', '9')
  
  makeGraph('line', 'Time GS (sec)', 'N', True, 'newtonGS', 'rdtsc', 'saidaL2', '9')
  makeGraph('line', 'Time Hessian GS (sec)', 'N', True, 'newtonGS_hessian', 'rdtsc', 'saidaL2', '9')
  makeGraph('line', 'Time gradient GS (sec)', 'N', True, 'newtonGS_gradient', 'rdtsc', 'saidaL2', '9')
  makeGraph('line', 'Time solver GS (sec)', 'N', True, 'newtonGS_solver', 'rdtsc', 'saidaL2', '9')
  
  
  makeGraph('line', 'L2 Miss Ratio Default', 'N', False, 'newtonDefault', 'L2 miss ratio', 'saidaL2', '9')
  makeGraph('line', 'L2 Miss Ratio Hessian Default', 'N', False, 'newtonDefault_hessian', 'L2 miss ratio', 'saidaL2', '9')
  makeGraph('line', 'L2 Miss Ratio gradient Default', 'N', False, 'newtonDefault_gradient', 'L2 miss ratio', 'saidaL2', '9')
  makeGraph('line', 'L2 Miss Ratio solver Default', 'N', False, 'newtonDefault_solver', 'L2 miss ratio', 'saidaL2', '9')
  
  makeGraph('line', 'L2 Miss Ratio GS', 'N', False, 'newtonGS', 'L2 miss ratio', 'saidaL2', '9')
  makeGraph('line', 'L2 Miss Ratio Hessian GS', 'N', False, 'newtonGS_hessian', 'L2 miss ratio', 'saidaL2', '9')
  makeGraph('line', 'L2 Miss Ratio gradient GS', 'N', False, 'newtonGS_gradient', 'L2 miss ratio', 'saidaL2', '9')
  makeGraph('line', 'L2 Miss Ratio solver GS', 'N', False, 'newtonGS_solver', 'L2 miss ratio', 'saidaL2', '9')


  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] Default', 'N', False, 'newtonDefault', 'L3 bandwidth', 'saidaL3', '10')
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] Hessian Default', 'N', False, 'newtonDefault_hessian', 'L3 bandwidth', 'saidaL3', '10')
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] gradient Default', 'N', False, 'newtonDefault_gradient', 'L3 bandwidth', 'saidaL3', '10')
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] solver Default', 'N', False, 'newtonDefault_solver', 'L3 bandwidth', 'saidaL3', '10')
  
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] GS', 'N', False, 'newtonGS', 'L3 bandwidth', 'saidaL3', '10')
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] Hessian GS', 'N', False, 'newtonGS_hessian', 'L3 bandwidth', 'saidaL3', '10')
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] gradient GS', 'N', False, 'newtonGS_gradient', 'L3 bandwidth', 'saidaL3', '10')
  makeGraph('line', 'L3 Memory Bandwidth [MBytes por seg] solver GS', 'N', False, 'newtonGS_solver', 'L3 bandwidth', 'saidaL3', '10')


  makeGraphDP('line', 'FLOPS [MFLOPS por seg] Default', 'N', False, 'newtonDefault', 'saidaFDP', '10')
  makeGraphDP('line', 'FLOPS [MFLOPS por seg] Hessian Default', 'N', False, 'newtonDefault_hessian', 'saidaFDP', '10')
  makeGraphDP('line', 'FLOPS [MFLOPS por seg] gradient Default', 'N', False, 'newtonDefault_gradient', 'saidaFDP', '10')
  makeGraphDP('line', 'FLOPS [MFLOPS por seg] solver Default', 'N', False, 'newtonDefault_solver', 'saidaFDP', '10')

  makeGraphDP('line', 'FLOPS [MFLOPS por seg] GS', 'N', False, 'newtonGS', 'saidaFDP', '10')
  makeGraphDP('line', 'FLOPS [MFLOPS por seg] Hessian GS', 'N', False, 'newtonGS_hessian', 'saidaFDP', '10')
  makeGraphDP('line', 'FLOPS [MFLOPS por seg] gradient GS', 'N', False, 'newtonGS_gradient', 'saidaFDP', '10')
  makeGraphDP('line', 'FLOPS [MFLOPS por seg] solver GS', 'N', False, 'newtonGS_solver', 'saidaFDP', '10')
  


if __name__ == "__main__":
  main()
