#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <stdexcept>
#include <sstream>
using namespace std;

// Grid类定义
class Grid {
private:
    int row_num, col_num;  
    vector<vector<int>> grid;

public:
    // 构造函数
    Grid(int Col_num, int Row_num);
    Grid(const Grid& other);  // 深拷贝构造函数

    // 序列化为字符串
    string serialize() const;

    // 从字符串反序列化
    void deserialize(const string& data);

    // 检查id是否属于[down,up]的工具函数
    void checkIndexRange(int id, int down, int up, const string& err_info);

    // 获取指定行或列的数据
    vector<int> getRowValues(int rowId);
    vector<int> getColValues(int colId);

    // 获取/设置单元格的值
    int getBlockValue(int rowId, int colId);
    void setBlockValue(int rowId, int colId, int val);

    // 比较两个 Grid 对象是否相等
    bool operator==(const Grid& other) const;
};


#endif  // GRID_H