ALG=$1
OUTPUT_NAME=$2
INPUT_NAME=$3
SIZE=$4

echo "N,n_${ALG}_DP,o_${ALG}_DP,n_${ALG}_AVX,o_${ALG}_AVX" > $OUTPUT_NAME.csv
for N in 10 32 50 64 100
do
  FIRST_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A $SIZE n_${ALG}_$N | grep -i "^DP" | head -n 1 | cut -d , -f 2)
  SECOND_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A $SIZE o_${ALG}_$N | grep -i "^DP" | head -n 1 | cut -d , -f 2)
  THIRD_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A $SIZE n_${ALG}_$N | grep -i "^AVX" | head -n 1 | cut -d , -f 2)
  FOURTH_COLUMN=$(cat ../${INPUT_NAME}.dat | grep -i -A $SIZE o_${ALG}_$N | grep -i "^AVX" | head -n 1 | cut -d , -f 2)

  echo "$N,${FIRST_COLUMN},${SECOND_COLUMN},${THIRD_COLUMN},${FOURTH_COLUMN}" >> $OUTPUT_NAME.csv
done

