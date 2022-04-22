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
    y=['n_newtonDefault', 'o_newtonDefault', 'n_newtonGS', 'o_newtonGS'], 
    kind = 'line',
    title= 'Tempo Geral (segundos)',
  )
  plt.show()

if __name__ == "__main__":
  main()