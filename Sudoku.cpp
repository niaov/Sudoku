#include "Sudoku.h"

// Sudoku 类构造函数，接收一个 81 个字符的数独字符串
Sudoku::Sudoku(string input_SudokuValue) : Grid(9, 9), solution_count(0) {
    while(input_SudokuValue.size() > 81)
        input_SudokuValue.pop_back();   // 截断过长的输入
    while(input_SudokuValue.size() < 81)
        input_SudokuValue = input_SudokuValue + '0';  // 补全输入
    deserialize(input_SudokuValue);
}

// 深拷贝构造函数
Sudoku::Sudoku(const Sudoku& other) : Grid(other), solution_count(other.solution_count) {
    for (int i = 0; i < 9; ++i) {
        row[i] = other.row[i];
        col[i] = other.col[i];
        for (int j = 0; j < 3; ++j) {
            squ[i / 3][j] = other.squ[i / 3][j];
        }
        for (int j = 0; j < 9; ++j) {
            in_SquId[i][j] = other.in_SquId[i][j];
        }
    }
}

// // lyw序列化为字符串
// string Sudoku::serialize() const {
//     return Grid::serialize();
// }

// 从字符串反序列化
void Sudoku::deserialize(const string& gridData) {
    checkIndexRange(gridData.size(), 81, 81, "输入长度有误");
    Grid::deserialize(gridData);
    initializeBitsets();  // 初始化bitsets
}

// 将字符转换为数字
int Sudoku::charToNum(char c) {
    checkIndexRange(c, '0', '9', "非数字0~9");
    return c - '0';
}

// 前进到下一个单元格
void Sudoku::advanceBlock(int& rowId, int& colId) {
    ++colId;
    if (colId >= 9) {
        colId = 0;
        ++rowId;
    }
}

// 获取 bitset 中某个数字的状态
bool Sudoku::getBitsetBlock(const bitset<10>& bs, int id) {
    checkIndexRange(id, 1, 9, "非数独值1~9");
    return bs[id];
}

// 修改 bitset 中某个数字的状态
void Sudoku::setBitsetBlock(bitset<10>& bs, int id, bool val) {
    checkIndexRange(id, 1, 9, "非数独值1~9");
    bs[id] = val;
}

// 修改行、列、宫三个 bitset 的状态
void Sudoku::setThreeBitsets(int rowId, int colId, int squRowId, int squColId, int num, bool val) {
    setBitsetBlock(row[rowId], num, val);
    setBitsetBlock(col[colId], num, val);
    setBitsetBlock(squ[squRowId][squColId], num, val);
}

// 将 vector 转换为 bitset
void Sudoku::vectorToBitset(const vector<int>& input, bitset<10>& output) {
    for (int val : input) {
        if (val == 0) continue;
        if (getBitsetBlock(output, val)) {
            cout << "\n输入不满足数独要求，无解。\n";
            return;
        }
        setBitsetBlock(output, val, true);
    }
}

// 初始化 bitset
void Sudoku::initializeBitsets() {
    for (int i = 0; i < 9; ++i) {
        vectorToBitset(getRowValues(i), row[i]);
        vectorToBitset(getColValues(i), col[i]);
    }
    for (int rowId = 0; rowId < 3; ++rowId) {
        for (int colId = 0; colId < 3; ++colId) {
            vector<int> blockValues;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int curRow = rowId * 3 + i;
                    int curCol = colId * 3 + j;
                    blockValues.push_back(getBlockValue(curRow, curCol));
                    in_SquId[curRow][curCol] = { rowId, colId };
                }
            }
            vectorToBitset(blockValues, squ[rowId][colId]);
        }
    }
}

// 深度优先搜索求解数独
void Sudoku::solve(bool ifOutputAns, int rowId, int colId) {
    if (solution_count > 100) return;

    if (rowId >= 9) {
        ++solution_count;
        if(ifOutputAns){
            cout << "第 " << solution_count << " 个解:\n";
            printBoard();
            if (solution_count > 100) {
                cout << "已生成足够多的解答。\n";
            }
        }
        return;
    }

    int nextRow = rowId, nextCol = colId;
    int curValue = getBlockValue(rowId, colId);
    if (curValue > 0) {
        advanceBlock(nextRow, nextCol);
        solve(ifOutputAns, nextRow, nextCol);
    } else {
        for (int num = 1; num <= 9; ++num) {
            int squRow = in_SquId[rowId][colId].first;
            int squCol = in_SquId[rowId][colId].second;

            if (!getBitsetBlock(row[rowId], num) &&
                !getBitsetBlock(col[colId], num) &&
                !getBitsetBlock(squ[squRow][squCol], num)) {

                setThreeBitsets(rowId, colId, squRow, squCol, num, true);
                setBlockValue(rowId, colId, num);

                advanceBlock(nextRow, nextCol);
                solve(ifOutputAns, nextRow, nextCol);
                nextRow = rowId, nextCol = colId;

                setThreeBitsets(rowId, colId, squRow, squCol, num, false);
                setBlockValue(rowId, colId, 0);
            }
        }
    }
}

int Sudoku::getSolution_count(){  
    solution_count = 0;  
    solve(false);
    return solution_count;
}

// 打印数独棋盘
void Sudoku::printBoard() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << getBlockValue(i, j) << " ";
        }
        cout << endl;
    }
}

// 比较两个 Sudoku 对象是否相等
bool Sudoku::operator==(const Sudoku& other) const {
    return Grid::operator==(other);
}
