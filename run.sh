echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

cd ./rosenbrock
./gera_rosenbrock.sh > entrada.dat
make runL2 > ../scripts/saidaL2.dat
make runL3 > ../scripts/saidaL3.dat
make runFLOPS_DP > ../scripts/saidaFDP.dat

cd ../rosenbrock-opt
cp ../rosenbrock/entrada.dat .
make runL2 >> ../scripts/saidaL2.dat
make runL3 >> ../scripts/saidaL3.dat
make runFLOPS_DP >> ../scripts/saidaFDP.dat

cd ../scripts/graphs
python3 makeGraphs.py

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor