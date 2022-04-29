
# hessian and gradient are the same for both newtonDefault and newtonGS
# we use the same function
ALG=$1
OUTPUT_NAME=$2
SEARCH=$3
INPUT_NAME=$4
SIZE=$5

echo "N,n_${ALG},o_${ALG}" > $OUTPUT_NAME.csv
for N in 10 32 50 64 100 128 200 250 256 300 400 512 600 1000 1024 2000 2048 3000 4096
do
  FIRST_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A $SIZE n_${ALG}_$N | grep -i "$SEARCH" | head -n 1 | cut -d , -f 2)
  SECOND_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A $SIZE o_${ALG}_$N | grep -i "$SEARCH" | head -n 1 | cut -d , -f 2)
  
  echo "$N,${FIRST_COLUMN},${SECOND_COLUMN}" >> $OUTPUT_NAME.csv
done