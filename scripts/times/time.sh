touch generalTime.csv

# hessian and gradient are the same for both newtonDefault and newtonGS
# we use the same function
NOPT=$1
OPT=$2
OUTPUT_NAME=$3
SEARCH=$4

echo "N,${NOPT},${OPT}" > $OUTPUT_NAME.csv
for N in 10 32 50 64
do
  FIRST_COLUMN=$(cat ../saida.dat | grep -i -A 9 ${NOPT}_$N | grep -i "$SEARCH" | head -n 1 | cut -d , -f 2)
  SECOND_COLUMN=$(cat ../saida.dat | grep -i -A 9 ${OPT}_$N | grep -i "$SEARCH" | head -n 1 | cut -d , -f 2)
  
  echo "$N,${FIRST_COLUMN},${SECOND_COLUMN}" >> $OUTPUT_NAME.csv
done