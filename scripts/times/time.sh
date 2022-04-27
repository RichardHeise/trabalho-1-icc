touch generalTime.csv

# hessian and gradient are the same for both newtonDefault and newtonGS
# we use the same function
ALG=$1
OUTPUT_NAME=$2
SEARCH=$3
INPUT_NAME=$4

echo "N,n_${ALG},o_${ALG}" > $OUTPUT_NAME.csv
for N in 10 32 50 64
do
  FIRST_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A 9 n_${ALG}_$N | grep -i "$SEARCH" | head -n 1 | cut -d , -f 2)
  SECOND_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A 9 o_${ALG}_$N | grep -i "$SEARCH" | head -n 1 | cut -d , -f 2)
  
  echo "$N,${FIRST_COLUMN},${SECOND_COLUMN}" >> $OUTPUT_NAME.csv
done