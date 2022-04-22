touch generalTime.csv

echo "N,n_newtonDefault,o_newtonDefault,n_newtonGS,o_newtonGS" > generalTime.csv
for N in 10 32 50 64
do
  n_newtonDefault=$(cat ../saida.dat | grep -i -A 3 n_newtonDefault_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  n_newtonGS=$(cat ../saida.dat | grep -i -A 3 n_newtonGS_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_newtonDefault=$(cat ../saida.dat | grep -i -A 3 o_newtonDefault_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_newtonGS=$(cat ../saida.dat | grep -i -A 3 o_newtonGS_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  
  echo "$N,$n_newtonDefault,0,$n_newtonGS,0" >> generalTime.csv
done