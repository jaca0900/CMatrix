/*
 * CMatrix.cpp
 *
 *  Created on: Apr 8, 2019
 *      Author: jabedn
 */

#include "CMatrix.h"
#include "fstream"
#include "iostream"
#include <vector>
#include <cstring>

using namespace std;

CMatrix::CMatrix() {
    rowCount = 0;
    colCount = 0;
    above = 0;
    below = 0;
    mainCross = 0;
    offCross = 0;
    aElems = "";
    bElems = "";
    contents = new int * [rowCount];
    for (int i = 0; i< colCount; i++) {
        contents[i] = new int[colCount];
    }
}

CMatrix::CMatrix(int rows, int cols) {
    rowCount = rows;
    colCount = cols;
    above = 0;
    below = 0;
    mainCross = 0;
    offCross = 0;
    aElems = "";
    bElems = "";
//    odds = new Vector();
//    evens = new Vector();
    contents = new int*[rowCount];
    for (int i = 0; i< rowCount; i++) {
        contents[i] = new int[colCount];
        for (int j = 0; j < colCount; j++) {
            contents[i][j] = random() % 20 - 10;
        }
    }
}

CMatrix::CMatrix(string filePath) {
    rowCount = 0;
    colCount = 0;
    above = 0;
    below = 0;
    mainCross = 0;
    offCross = 0;
    aElems = "";
    bElems = "";

    this->loadFromFile(filePath);
}

void CMatrix::calculate() {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (i == j) {
                if (contents[i][j] < 0) {
                    mainCross += contents[i][j];
                }
            } else if (i > j) {
                bElems += to_string(contents[i][j]) + " ";
                below += contents[i][j];
            } else {
                aElems += to_string(contents[i][j]) + " ";
                above += contents[i][j];
            }
            if (rowCount - 1 - i == j) {
                if (contents[i][j] > 0) {
                    offCross += contents[i][j];
                }
            }
        }
    }
}

void CMatrix::print() {
    cout << toString();
}

int sumVector(vector<int> vec) {
    int sum = 0;
    for (vector<int>::iterator it = vec.begin() ; it != vec.end(); ++it) {
        sum += *it;
    }

    return sum;
}

string vectorToString(vector<int> vec) {
    string content = "";

    for (vector<int>::iterator it = vec.begin() ; it != vec.end(); ++it) {
        content += to_string(*it) + "\t";
    }

    return content;
}

string CMatrix::toString() {
    string content = "This is a CMatrix: " + to_string(rowCount) + " x " + to_string(colCount) + "\n";

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            content += to_string(contents[i][j]) + "\t";
        }
        content += "\n";
    }

    content += "Sum on main cross is: " + to_string(mainCross) + "\n";
    content += "Sum on off cross is: " + to_string(offCross) + "\n";
    content += "Elements to sum above: " + aElems + "\n";
    content += "Sum above the main cross is: " + to_string(above) + "\n";
    content += "Elements to sum below: " + bElems + "\n";
    content += "Sum below main cross is: " + to_string(below) + "\n";

    content += "\n\nThe matrix written in a circular mannor going in a spiral clockWise \n";
    content += goAround() + "\n";
    content += "Evens: \n";
    content += vectorToString(evens) + "\n";
    content += "Sum:\n";
    content += to_string(sumVector(evens)) + "\n";
    content += "Odds: \n";
    content += vectorToString(odds) + "\n";
    content += "Sum:\n";
    content += to_string(sumVector(odds)) + "\n";

    return content;
}

void CMatrix::transpose() {
    int** helperMatrix = new int * [colCount];

    for (int i = 0; i < colCount; i++) {
        helperMatrix[i] = new int[rowCount];
        for (int j = 0; j < rowCount; j++) {
            helperMatrix[i][j] = contents[j][i];
        }
    }

    contents = helperMatrix;
}

vector<string> split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current != NULL){
        arr.push_back(current);
        current=strtok(NULL, sep.c_str());
    }
    return arr;
}

void CMatrix::loadFromFile(string filePath) {
    ifstream in;
    in.open(filePath);

    if (!in) {
        cerr << "Unable to open " << filePath;
        exit(1);   // call system to stop
    }

    string line = "";
    getline(in, line);

    vector<string> loaded = split(line, ";");

    if (loaded.size() == 2) {
        rowCount = stoi(loaded[0]);
        colCount = stoi(loaded[0]);
    } else {
        cerr << "Invalid file format";
        exit(1);   // call system to stop
    }

    contents = new int * [rowCount];

    for (int i = 0; i < rowCount; i++) {
        getline(in, line);
        loaded = split(line, ";");
        contents[i] = new int[colCount];
        for (int j = 0; j < colCount; j++) {
            contents[i][j] = stoi(loaded[j]);
        }
    }
}

void CMatrix::saveToFile(string filePath) {
    ofstream out;
    out.open(filePath);
    out << to_string(rowCount) << ";" << to_string(colCount) << "\n";

    for (int i = 0; i < rowCount; i++) {
        string line = "";
        for (int j = 0; j < colCount; j++) {
            line += to_string(contents[i][j]) + ";";
        }
        line += "\n";
        out << line;
    }

    out.close();
}

void CMatrix::writeResultsToFile(string filePath) {
    ofstream out;
    out.open(filePath);
    out << toString();
    out.close();
}

void CMatrix::deleteContents() {

    for (int i = 0; i < rowCount; i++) {
        delete [] contents[i];
    }
    delete [] contents;
}

string CMatrix::goAround() {
    int ** toIterate = createPomMatrix();
    spiralValue spiralContent = {
        index: 0,
        content: ""
    };

    for (int i = 0; i < colCount; i++) {
        spiralContent = writeRow(spiralContent, true, toIterate);
        spiralContent = writeColumn(spiralContent, true, toIterate);
        spiralContent = writeRow(spiralContent, false, toIterate);
        spiralContent = writeColumn(spiralContent, false, toIterate);
    }

    return spiralContent.content;
}

int ** CMatrix::createPomMatrix() {
    int ** pomContents;
    pomContents = new int*[rowCount];
    for (int i = 0; i< rowCount; i++) {
        pomContents[i] = new int[colCount];
        for (int j = 0; j < colCount; j++) {
            pomContents[i][j] = contents[i][j];
        }
    }

    return pomContents;
}

void CMatrix::evensAndOdds(int value) {
    if (value % 2 == 0) {
        evens.push_back(value);
    } else {
        odds.push_back(value);
    }
}

spiralValue CMatrix::writeRow(spiralValue spiralContent, bool direction, int ** matrix) {
    spiralValue currentContent = spiralContent;

    if (direction) {
        for (int i = 0; i < colCount; i++) {
            if (matrix[spiralContent.index][i] < 999999) {
                evensAndOdds(matrix[spiralContent.index][i]);
                currentContent.content += to_string(matrix[spiralContent.index][i]) + " ";
                matrix[spiralContent.index][i] = 999999;
                currentContent.index = i;
            }
        }
    } else {
        for (int i = colCount - 1; i >= 0; i--) {
            if (matrix[spiralContent.index][i] < 999999) {
                evensAndOdds(matrix[spiralContent.index][i]);
                currentContent.content += to_string(matrix[spiralContent.index][i]) + " ";
                matrix[spiralContent.index][i] = 999999;
                currentContent.index = i;
            }
        }
    }

    return currentContent;
}

spiralValue CMatrix::writeColumn(spiralValue spiralContent, bool direction, int ** matrix) {
    spiralValue currentContent = spiralContent;

    if (direction) {
        for (int i = 0; i < rowCount; i++) {
            if (matrix[i][spiralContent.index] < 999999) {
                evensAndOdds(matrix[i][spiralContent.index]);
                currentContent.content += to_string(matrix[i][spiralContent.index]) + " ";
                matrix[i][spiralContent.index] = 999999;
                currentContent.index = i;
            }
        }
    } else {
        for (int i = rowCount - 1; i >= 0; i--) {
            if (matrix[i][spiralContent.index] < 999999) {
                evensAndOdds(matrix[i][spiralContent.index]);
                currentContent.content += to_string(matrix[i][spiralContent.index]) + " ";
                matrix[i][spiralContent.index] = 999999;
                currentContent.index = i;
            }
        }
    }

    return currentContent;
}

CMatrix::~CMatrix() {
    this->deleteContents();
}
