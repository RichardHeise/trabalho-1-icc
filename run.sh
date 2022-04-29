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

cd ../scripts/times
python3 teste.py
