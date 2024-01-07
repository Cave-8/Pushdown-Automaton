gcc main.c -o PDA
./PDA < ./tests/inputs/input0.txt > ./tests/outputs/output0.txt
./PDA < ./tests/inputs/input1.txt > ./tests/outputs/output1.txt
./PDA < ./tests/inputs/input2.txt > ./tests/outputs/output2.txt
./PDA -v < ./tests/inputs/input2.txt > ./tests/outputs/output2verbose.txt