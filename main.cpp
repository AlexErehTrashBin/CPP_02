#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

using namespace std;

// C++ 11 - trailing return type
auto getAllElementsInFile(
    ifstream&iss
) -> int {
    const auto prevPos = iss.tellg();
    int result = 0;
    int tempForReadAllElements;
    while (!iss.eof()) {
        iss >> tempForReadAllElements;
        result++;
    }

    iss.seekg(prevPos, ios::beg);
    iss.clear();
    return result;
}

// C++ 11 - trailing return type
auto getAllSpacesInFile(
    ifstream& iss
) -> int {
    const auto prevPos = iss.tellg();
    int result = 0;
    char symbol;
    while (!iss.eof()) {
        iss.get(symbol);
        if (symbol == ' ') result++;
        if (symbol == '\n') break;
    }

    iss.clear();
    iss.seekg(prevPos, ios::beg);
    return result;
}

// C++ 11 - trailing return type
auto parseMatrixFromFile(
    const string&filename,
    int&rows,
    int&cols
) -> optional<vector<vector<int>>> {
    vector<vector<int>> matrix;
    ifstream inputFileStream(filename);

    if (!inputFileStream) {
        cerr << "Ошибка при открытии файла." << endl;
        return nullopt;
    }

    const int allElementsInFile = getAllElementsInFile(inputFileStream);
    const int allSpacesInFile = getAllSpacesInFile(inputFileStream);

    cols = allSpacesInFile + 1;
    rows = allElementsInFile / cols;

    matrix.resize(rows);
    for (int i = 0; i < rows; i++) {
        vector<int> column;
        column.resize(cols);
        matrix[i] = column;
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            inputFileStream >> matrix[i][j];

    inputFileStream.close();
    return matrix;
}

// C++ 11 - trailing return type
auto printMatrix(
    const vector<vector<int>> &matrix
) -> void {
    cout << "Матрица: " << endl;

    for (const auto & i : matrix) {
        // C++ 11 - templated std::begin and std::end
        for (auto j = std::begin(i); j != std::end(i); ++j) {
            cout.width(5);
            cout << *j;
        }
        cout << endl;
    }
}

// C++ 11 - trailing return type
auto getAscendingRowsCount(
    const vector<vector<int>>&matrix,
    const int rows,
    const int cols
    ) -> int {
    int resultCount = 0;
    for (int i = 0; i < rows; i++) {
        bool isAscendingRow = true;
        for (int j = 0; j < cols - 1; j++) {
            if (j + 1 > cols) continue;
            const int currentElement = matrix[i][j];
            const int nextElement = matrix[i][j + 1];
            if (currentElement > nextElement) {
                isAscendingRow = false;
                break;
            }
        }
        if (isAscendingRow) resultCount++;
    }
    return resultCount;
}

int main() {
    string filename;

    int rows, cols;
    optional<vector<vector<int>>> matrix = nullopt;

    while (matrix == nullopt) {
        cout << "Введите название файла с прямоугольной матрицей: ";
        cin >> filename;
        matrix = parseMatrixFromFile(filename, rows, cols);
    }
    printMatrix(matrix.value());
    const int result = getAscendingRowsCount(matrix.value(), rows, cols);
    cout << "Количество возрастающих строк: " << result << endl;
    matrix.value().clear();

    system("pause");
    return 0;
}