//
// Created by Jacek Bednarczyk on 2019-04-08.
//

#ifndef MATRIX_CMATRIX_H
#define MATRIX_CMATRIX_H


/*
 * CMatrix.h
 *
 *  Created on: Apr 8, 2019
 *      Author: jabedn
 */

#ifndef COMPONENTS_MATRIX_MATRIX_H_
#define COMPONENTS_MATRIX_MATRIX_H_

#include <vector>
#include "iostream"

using namespace std;

struct spiralValue{
    int index;
    string content;
};

class CMatrix {
private:
    vector <int> odds;
    vector <int> evens;
    int rowCount;
    int colCount;
    int** contents;
    int above;
    int below;
    int mainCross;
    int offCross;
    string aElems;
    string bElems;
    void loadFromFile(string filePath);

public:
    CMatrix();
    CMatrix(int rows, int cols);
    CMatrix(string filePath);

    void calculate();

    void print();

    void saveToFile(string filePath);

    void deleteContents();

    void transpose();

    void writeResultsToFile(string filePath);

    int ** createPomMatrix();

    void evensAndOdds(int value);

    spiralValue writeRow(spiralValue spiralContent, bool direction, int ** matrix);

    spiralValue writeColumn(spiralValue spiralContent, bool direction, int ** matrix);

    string goAround();

    string toString();

    ~CMatrix();
};



#endif /* COMPONENTS_MATRIX_MATRIX_H_ */



#endif //MATRIX_CMATRIX_H
