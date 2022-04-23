# reqs: pandas and matplotlib

import pandas as pd
import matplotlib.pyplot as plt
import subprocess

def main():
  subprocess.call(['sh', './time.sh'])

  df = pd.read_csv("generalTime.csv")
  print(df)
  df.plot(
    x = 'N', 
    y=[
      'n_hessian',
      'o_hessian',
      'n_gradient',
      'o_gradient', 
      'n_newtonDefault', 
      'o_newtonDefault',
      'n_newtonDefault_solver',
      'o_newtonDefault_solver',
      'n_newtonGS', 
      'o_newtonGS',
      'n_newtonGS_solver',
      'o_newtonGS_solver'
    ], 
    kind = 'line',
    title= 'Time (sec)',
  )
  plt.show()

if __name__ == "__main__":
  main()