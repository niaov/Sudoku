#ifndef SUDOKU_H
#define SUDOKU_H

#include "Grid.h"
#include "Grid.cpp"
using namespace std;


// Sudoku类定义，继承自Grid
class Sudoku : public Grid {
private:
    bitset<10> row[9];
    bitset<10> col[9];
    bitset<10> squ[3][3];
    pair<int, int> in_SquId[9][9];
    int solution_count=0;

public:
    // 构造函数
    Sudoku(string input_SudokuValue);

    Sudoku(const Sudoku& other);  // 深拷贝构造函数

    // 序列化和反序列化
    // string serialize() const;
    void deserialize(const string& gridData);

    // 数独求解
    void solve(bool ifOutputAns = true, int rowId = 0, int colId = 0);

    // 打印棋盘
    void printBoard();

    // 比较两个 Sudoku 对象是否相等
    bool operator==(const Sudoku& other) const;

    // 获取解的数量
    int getSolution_count();

private:
    // 内部辅助函数
    int charToNum(char c);
    void advanceBlock(int& rowId, int& colId);
    bool getBitsetBlock(const bitset<10>& bs, int id);
    void setBitsetBlock(bitset<10>& bs, int id, bool val);
    void setThreeBitsets(int rowId, int colId, int squRowId, int squColId, int num, bool val);
    void vectorToBitset(const vector<int>& input, bitset<10>& output);
    void initializeBitsets();
};

#endif  // SUDOKU_H
