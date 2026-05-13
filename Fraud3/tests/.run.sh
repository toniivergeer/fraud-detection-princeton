touch tests//.timeout
CMD="valgrind --leak-check=full /home/toniverger/Escritorio/MP/MP_FRAUD/Fraud3/build/Fraud3  -K 5 ../Datasets/princeton_training.dts 1> tests//.out10 2>&1"
eval $CMD
rm tests//.timeout
