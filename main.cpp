#include <iostream>
#include "./components/CMatrix.h"

using namespace std;

int main(int argc, char **argv) {
//    CMatrix *matrix = new CMatrix(3, 3);
    CMatrix *matrix = new CMatrix("matrix.txt");
    matrix->print();
//    matrix->transpose();
//    matrix->calculate();
//    matrix->print();
    matrix->saveToFile("matrix.txt");
    matrix->writeResultsToFile("results.txt");
    matrix->~CMatrix();
    return 0;
}
