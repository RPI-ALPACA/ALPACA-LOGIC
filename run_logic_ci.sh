set -e
sudo apt install -y valgrind
cmake . && make logic-test
valgrind --leak-check=full --error-exitcode=1 ./logic-test
make first-order
valgrind --leak-check=full --error-exitcode=1 ./first-order
