#include"Sudoku.h"
#include"Sudoku.cpp"
using namespace std;

void textSudoku(Sudoku sudoku){
    /// 序列化
    string serializedData = sudoku.serialize();
    cout << "序列化后的数据: " << serializedData << '\n';

    // 反序列化到新的 Sudoku 对象
    Sudoku sudoku2("");  // 初始为空
    sudoku2.deserialize(serializedData);

    // 比较反序列化后的对象
    if (sudoku == sudoku2) {
        cout << "测试反序列化成功，两个对象相等！" << '\n';
    } else {
        cout << "测试反序列化失败，两个对象不相等！" << '\n';
    }

    // 深拷贝
    Sudoku sudoku3(sudoku);
    // 比较深拷贝后的对象（克隆操作可以通过深拷贝实现）
    if (sudoku == sudoku2) {
        cout << "测试深拷贝成功，两个对象相等！" << '\n';
    } else {
        cout << "测试深拷贝失败，两个对象不相等！" << '\n';
    }

    sudoku.solve();
}

// 引入你的 Sudoku 类代码...

void runSudokuTest(const string& input, const string& description, int expected_solution_count = 1) {
    try {
        Sudoku sudoku(input);
        int ans = sudoku.getSolution_count();
        if (ans == expected_solution_count) {
            cout << "测试通过: " << description << '\n';
        } else {
            cout << "代码逻辑错误: " << description << "，解的数量不正确，应为 " 
                 << expected_solution_count << "，但得到 " << ans << '\n' 
                 << "程序结束。\n";
            exit(1);
        }
    } catch (const exception& e) {
        cout << "发生报错: " << description << "，错误信息: " << e.what() << '\n';
    }
}



int main(){
    // 测试用例
    runSudokuTest("017903600000080000900000507072010430000402070064370250701000065000030000005601720", "唯一解示例", 1);
    runSudokuTest("006000200100700090000006075008002030020000060070400500640300000090004001002000400", "多解示例", 8);
    runSudokuTest("530071000600050000098000060800600003400803001700020006000000080060000195000281000", "无解示例", 0);
    runSudokuTest("ABCDE0179036000000900000507072010430000402070064370250701000065000030000005601720", "非法示例", -1); // 非法输入期望抛出异常
    runSudokuTest("000000000000000000000000000000000000000000000000000000000000000000000000000000000", "全0示例", 101); // 全0视为数独初始状态，解的数量高于100
    runSudokuTest("123456789","长度不足示例",101);
    runSudokuTest("000000000000000000000000000000000000000000000000000000000000000000000000000000000000","长度过大示例",101);
    cout<<"输入数独对象，要求长度为81位，且为数字0~9: \n";
    string input;
    cin>>input;  
     // 创建一个数独对象
    Sudoku sudoku(input);
    textSudoku(sudoku);

    
}

