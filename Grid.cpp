#include "Grid.h"

// Grid 类构造函数
Grid::Grid(int Col_num, int Row_num) : col_num(Col_num), row_num(Row_num) {
    vector<int> single_row(row_num, 0);
    for (int i = 0; i < Col_num; ++i) {
        grid.push_back(single_row);  // 初始化空棋盘
    }
}

// 深拷贝构造函数
Grid::Grid(const Grid& other) : row_num(other.row_num), col_num(other.col_num), grid(other.grid) {}

// 序列化为字符串
string Grid::serialize() const {
    stringstream ss;
    for (const auto& row : grid) {
        for (int val : row) {
            ss << val;
        }
    }
    return ss.str();
}

// 从字符串反序列化
void Grid::deserialize(const string& data) {
    checkIndexRange(data.size(), row_num * col_num, row_num * col_num, "反序列化输入长度有误");
    for (int i = 0; i < row_num; ++i) {
        for (int j = 0; j < col_num; ++j) {
            grid[i][j] = data[i * col_num + j] - '0';
        }
    }
}

// 检查id是否属于[down,up]的工具函数
void Grid::checkIndexRange(int id, int down, int up, const string& err_info) {
    if (id < down || id > up) {
        throw invalid_argument("错误: " + err_info);
    }
}

// 获取指定行的数据
vector<int> Grid::getRowValues(int rowId) {
    checkIndexRange(rowId, 0, row_num - 1, "行下标越界");
    return grid[rowId];
}

// 获取指定列的数据
vector<int> Grid::getColValues(int colId) {
    checkIndexRange(colId, 0, col_num - 1, "列下标越界");
    vector<int> colValues;
    for (int i = 0; i < row_num; ++i) {
        colValues.push_back(grid[i][colId]);
    }
    return colValues;
}

// 获取某个单元格的值
int Grid::getBlockValue(int rowId, int colId) {
    checkIndexRange(rowId, 0, row_num - 1, "行下标越界");
    checkIndexRange(colId, 0, col_num - 1, "列下标越界");
    return grid[rowId][colId];
}

// 修改某个单元格的值
void Grid::setBlockValue(int rowId, int colId, int val) {
    checkIndexRange(rowId, 0, row_num - 1, "行下标越界");
    checkIndexRange(colId, 0, col_num - 1, "列下标越界");
    grid[rowId][colId] = val;
}

// 比较两个 Grid 对象是否相等
bool Grid::operator==(const Grid& other) const {
    return grid == other.grid;
}