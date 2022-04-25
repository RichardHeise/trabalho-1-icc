touch generalTime.csv

# hessian and gradient are the same for both newtonDefault and newtonGS
# we use the same function

echo "N,n_newtonDefault,o_newtonDefault,n_newtonDefault_solver,o_newtonDefault_solver,\
n_hessian,o_hessian,n_gradient,o_gradient,n_newtonGS,o_newtonGS,n_newtonGS_solver,o_newtonGS_solver" > generalTime.csv
for N in 10 32 50 64
do
  n_newtonDefault=$(cat ../saida.dat | grep -i -A 9 n_newtonDefault_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_newtonDefault=$(cat ../saida.dat | grep -i -A 9 o_newtonDefault_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  n_gradient=$(cat ../saida.dat | grep -i -A 9 n_newtonDefault_gradient_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_gradient=$(cat ../saida.dat | grep -i -A 9 o_newtonDefault_gradient_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  n_hessian=$(cat ../saida.dat | grep -i -A 9 n_newtonDefault_hessian_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_hessian=$(cat ../saida.dat | grep -i -A 9 o_newtonDefault_hessian_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  n_newtonDefault_solver=$(cat ../saida.dat | grep -i -A 9 n_newtonDefault_solver_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_newtonDefault_solver=$(cat ../saida.dat | grep -i -A 9 o_newtonDefault_solver_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  
  n_newtonGS=$(cat ../saida.dat | grep -i -A 9 n_newtonGS_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_newtonGS=$(cat ../saida.dat | grep -i -A 9 o_newtonGS_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  n_newtonGS_solver=$(cat ../saida.dat | grep -i -A 9 n_newtonGS_solver_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  o_newtonGS_solver=$(cat ../saida.dat | grep -i -A 9 o_newtonGS_solver_$N | grep -i "rdtsc" | head -n 1 | cut -d , -f 2)
  
  echo "$N,$n_newtonDefault,0,$n_newtonDefault_solver,0,$n_hessian,0,$n_gradient,0,$n_newtonGS,0,$n_newtonGS_solver,0" >> generalTime.csv
done