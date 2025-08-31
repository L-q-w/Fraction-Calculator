#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Fraction
{
    // 分数类，支持基本四则运算、比较、输入输出等
    friend Fraction operator+(const Fraction& frac_1, const Fraction& frac_2); // 重载+运算符，实现分数加法
    friend Fraction operator-(const Fraction& frac_1, const Fraction& frac_2); // 重载-运算符，实现分数减法
    friend Fraction operator*(const Fraction& frac_1, const Fraction& frac_2); // 重载*运算符，实现分数乘法
    friend Fraction operator/(const Fraction& frac_1, const Fraction& frac_2); // 重载/运算符，实现分数除法
    friend bool operator==(const Fraction& frac_1, const Fraction& frac_2);    // 重载==运算符，实现分数相等比较
    friend bool operator>(const Fraction& frac_1, const Fraction& frac_2);     // 重载>运算符，实现分数大于比较
    friend bool operator<(const Fraction& frac_1, const Fraction& frac_2);     // 重载<运算符，实现分数小于比较
    friend ostream& operator<<(ostream& out, const Fraction& frac);            // 重载<<运算符，实现分数输出
    friend istream& operator>>(istream& in, Fraction& frac);                   // 重载>>运算符，实现分数输入
    friend void sort_fraction(vector <Fraction>& frac_arr, char ch_2);         // 对分数数组排序
public:
    Fraction();                              // 无参构造函数，初始化为0/1
    Fraction(int n, int d);                  // 带参构造函数，初始化为n/d
    Fraction(const Fraction& f);             // 复制构造函数
    void set_fraction(int n, int d);         // 设置分数的分子和分母
    int get_numer();                         // 获取分数的分子
    int get_deno();                          // 获取分数的分母
    void reduce_frc();                       // 当前分数约分
private:
    int numer; // 分子
    int deno;  // 分母    
};

int choice;
int main() {
    // 主函数，提供分数计算和分数排序两大功能菜单
    while (true) {
        cout << "请选择功能（键入1或2）：" << endl << "1.分数计算" << endl << "2.分数排序" << endl;
        if (cin >> choice) {
            if (choice != 1 && choice != 2) {
                cout << "输入错误！" << endl;
                continue;
            }
        }
        else {
            cout << "输入错误！" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        while (choice == 1) {    // 选择功能“1.分数计算”时进入的循环 
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "请输入分数计算式（如1_2+1_3回车），输入#号键返回上一层目录：" << endl;
            Fraction frac_1, frac_2;
            char ch_2;
            bool quit_flag = 1;
            try {
                cin >> frac_1;
                quit_flag = 0;
                cin >> ch_2 >> frac_2;
                if (ch_2 != '+' && ch_2 != '-' && ch_2 != '*' && ch_2 != '/') throw invalid_argument("输入错误！");
                cout << '=';
                switch (ch_2) {
                case'+':
                    cout << frac_1 + frac_2 << endl;
                    continue;
                case'-':
                    cout << frac_1 - frac_2 << endl;
                    continue;
                case'*':
                    cout << frac_1 * frac_2 << endl;
                    continue;
                case'/':
                    cout << frac_1 / frac_2 << endl;
                    continue;
                default:
                    continue;
                }
            }
            catch (string& e) {
                if (quit_flag) break;
                else cout << "分式算式输入错误！" << endl;
            }
            catch (invalid_argument& e) {
                cout << "分式算式输入错误！" << endl;
            }
        }
        while (choice == 2) {    // 选择功能“2.分数排序”时进入的循环
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "请输入一组分数，用逗号隔开，如需由小到大排序用符号<结尾，"
                "由大到小排序用符号>结尾（如1_2,1_4,3_5<回车），输入#号键返回上一层目录："
                << endl;
            Fraction frac;
            vector <Fraction> frac_arr;
            char ch_2;
            bool quit_flag = 1;
            try {
                while (true) {
                    cin >> frac;
                    quit_flag = 0;
                    frac_arr.push_back(frac);
                    ch_2 = getchar();
                    if (ch_2 == '<' || ch_2 == '>') break;
                    else if (ch_2 == '\n') throw invalid_argument("输入错误！");
                    else if (ch_2 != ',' && ch_2 != '，') throw invalid_argument("输入错误！");
                }
                sort_fraction(frac_arr, ch_2);
            }
            catch (string& e) {
                cout << 1 << endl;
                if (quit_flag) break;
            }
            catch (invalid_argument& e) {
                cout << "输入错误！" << endl;
                continue;
            }
        }
    }
    return 0;
}

// 重载+运算符，实现分数加法
Fraction operator+(const Fraction& frac_1, const Fraction& frac_2)
{
    if (frac_1.deno == 0 || frac_2.deno == 0) throw invalid_argument("分母不能为0！");
    Fraction frac(frac_1.numer * frac_2.deno + frac_2.numer * frac_1.deno, frac_1.deno * frac_2.deno);
    frac.reduce_frc();
    return frac;
}

// 重载-运算符，实现分数减法
Fraction operator-(const Fraction& frac_1, const Fraction& frac_2)
{
    if (frac_1.deno == 0 || frac_2.deno == 0) throw invalid_argument("分母不能为0！");
    Fraction frac(frac_1.numer * frac_2.deno - frac_2.numer * frac_1.deno, frac_1.deno * frac_2.deno);
    frac.reduce_frc();
    return frac;
}

// 重载*运算符，实现分数乘法
Fraction operator*(const Fraction& frac_1, const Fraction& frac_2)
{
    if (frac_1.deno == 0 || frac_2.deno == 0) throw invalid_argument("分母不能为0！");
    Fraction frac(frac_1.numer * frac_2.numer, frac_1.deno * frac_2.deno);
    frac.reduce_frc();
    return frac;
}

// 重载/运算符，实现分数除法
Fraction operator/(const Fraction& frac_1, const Fraction& frac_2)
{
    if (frac_1.deno == 0 || frac_2.deno == 0 || frac_2.numer == 0) throw invalid_argument("分母不能为0，除数不能为0！");
    Fraction frac(frac_1.numer * frac_2.deno, frac_1.deno * frac_2.numer);
    frac.reduce_frc();
    return frac;
}

// 重载==运算符，实现分数相等比较
bool operator==(const Fraction& frac_1, const Fraction& frac_2)
{
    return (frac_1.numer * frac_2.deno == frac_1.deno * frac_2.numer);
}

// 重载>运算符，实现分数大于比较
bool operator>(const Fraction& frac_1, const Fraction& frac_2)
{
    Fraction f1(frac_1), f2(frac_2);
    f1.reduce_frc();
    f2.reduce_frc();
    return (frac_1.numer * frac_2.deno > frac_1.deno * frac_2.numer);
}

// 重载<运算符，实现分数小于比较
bool operator<(const Fraction& frac_1, const Fraction& frac_2)
{
    Fraction f1(frac_1), f2(frac_2);
    f1.reduce_frc();
    f2.reduce_frc();
    return (frac_1.numer * frac_2.deno < frac_1.deno * frac_2.numer);
}

// 重载<<运算符，实现分数输出
ostream& operator<<(ostream& out, const Fraction& frac)
{
    if (frac.numer == 0 && choice == 1) out << frac.numer;
    else out << frac.numer << '/' << frac.deno;
    return out;
}

// 重载>>运算符，实现分数输入，支持空格、负号、分母为0检测
istream& operator>>(istream& in, Fraction& frac)
{
    string input;
    in >> input;
    if (input == "#") throw string("#返回上一级");

    // 将下划线替换为斜杠，兼容1_2格式
    for (auto& c : input) {
        if (c == '_') c = '/';
    }

    // 去除所有空格
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // 查找分隔符
    size_t slash_pos = input.find('/');
    if (slash_pos == string::npos) throw invalid_argument("输入错误！");

    string numer_str = input.substr(0, slash_pos);
    string deno_str = input.substr(slash_pos + 1);

    // 检查分子和分母是否为空
    if (numer_str.empty() || deno_str.empty()) throw invalid_argument("输入错误！");

    // 转换为整数
    try {
        frac.numer = stoi(numer_str);
        frac.deno = stoi(deno_str);
    } catch (...) {
        throw invalid_argument("输入错误！");
    }

    if (frac.deno == 0) throw invalid_argument("分母不能为0！");

    return in;
}

// 对分数数组排序并输出
void sort_fraction(vector <Fraction>& frac_arr, char ch_2)
{
    for (auto& f : frac_arr) {
        if (f.get_deno() == 0) throw invalid_argument("分母不能为0！");
    }
    if (ch_2 == '<') {
        sort(frac_arr.begin(), frac_arr.end(), [](const Fraction& a, const Fraction& b) { return a < b; });
    } else if (ch_2 == '>') {
        sort(frac_arr.begin(), frac_arr.end(), [](const Fraction& a, const Fraction& b) { return a > b; });
    }
    for (unsigned int i = 0; i < frac_arr.size(); i++) {
        if (i == 0) cout << frac_arr[i];
        else cout << ' ' << frac_arr[i];
    }
    cout << endl;
}

// 无参构造函数，初始化为0/1
Fraction::Fraction()
{
    numer = 0;
    deno = 1;
}

// 带参构造函数，初始化为n/d，分母为0抛异常，分母为负时转正
Fraction::Fraction(int n, int d)
{
    if (d == 0) throw invalid_argument("无效分母！");
    if (d < 0) {
        n = -n;
        d = -d;
    }
    numer = n;
    deno = d;
}

// 复制构造函数
Fraction::Fraction(const Fraction& f)
{
    this->numer = f.numer;
    this->deno = f.deno;
}

// 设置分数的分子和分母，分母为0抛异常，分母为负时转正
void Fraction::set_fraction(int n, int d)
{
    if (d == 0) throw invalid_argument("无效分母！");
    if (d < 0) {
        n = -n;
        d = -d;
    }
    numer = n;
    deno = d;
}

// 获取分数的分子
int Fraction::get_numer()
{
    return numer;
}

// 获取分数的分母
int Fraction::get_deno()
{
    return deno;
}

// 当前分数约分，分子为0时分母置为1，否则用欧几里得算法约分
void Fraction::reduce_frc()
{
    if (numer == 0) {
        deno = 1;
        return;
    }
    int a = abs(numer), b = abs(deno);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    numer /= a;
    deno /= a;
    if (deno < 0) {
        numer = -numer;
        deno = -deno;
    }
}