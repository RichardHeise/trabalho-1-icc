# reqs: pandas and matplotlib

import pandas as pd
import matplotlib.pyplot as plt
import subprocess

def main():
  subprocess.call(['sh', './time.sh'])

  df = pd.read_csv("generalTime.csv")
  print(df)
  df.plot(x = 'N', y='n_newtonDefault', kind = 'line')
  plt.show()

if __name__ == "__main__":
  main()