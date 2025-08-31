#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Fraction
{
	friend Fraction operator+(const Fraction& frac1, const Fraction& frac2); //重载+运算符
	friend Fraction operator-(const Fraction& frac1, const Fraction& frac2); //重载-运算符
	friend Fraction operator*(const Fraction& frac1, const Fraction& frac2); //重载*运算符
	friend Fraction operator/(const Fraction& frac1, const Fraction& frac2); //重载/运算符
	friend bool operator==(Fraction frac1, Fraction frac2);                  //重载==运算符
	friend bool operator>(const Fraction& frac1, const Fraction& frac2);     //重载>运算符
	friend bool operator<(const Fraction& frac1, const Fraction& frac2);     //重载<运算符
	friend ostream& operator<<(ostream& out, const Fraction& frac);          //重载<<运算符
	friend istream& operator>>(istream& in, Fraction& frac);                 //重载>>运算符
	friend void sortFraction(vector <Fraction>& fracArr, char ch2);//对分数数组排序
public:
	Fraction();                      //无参造函数
	Fraction(int n, int d);          //带参造函数
	Fraction(const Fraction& f);     //复制造函数
	void setFraction(int n, int d);  //设置分数的分子和分母
	int getNumer();                  //获取分数的分子
	int getDeno();                   //获取分数的分母
	void RdcFrc();                   //当前分数约分
private:
	int numer; //分子
	int deno;  //分母    
};

int choice;
int main() {
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
		while (choice == 1) {    //选择功能“1.分数计算”时进入的循环 
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "请输入分数计算式（如1/2+1/3回车），输入#号键返回上一层目录：" << endl;
			Fraction frac1, frac2;
			char ch2;
			bool quitFlag = 1;
			try {
				cin >> frac1;
				quitFlag = 0;
				cin >> ch2 >> frac2;
				if (ch2 != '+' && ch2 != '-' && ch2 != '*' && ch2 != '/') throw invalid_argument("输入错误！");
				cout << '=';
				switch (ch2) {
				case'+':
					cout << frac1 + frac2 << endl;
					continue;
				case'-':
					cout << frac1 - frac2 << endl;
					continue;
				case'*':
					cout << frac1 * frac2 << endl;
					continue;
				case'/':
					cout << frac1 / frac2 << endl;
					continue;
				default:
					continue;
				}
			}
			catch (string& e) {
				if (quitFlag) break;
				else cout << "分式算式输入错误！" << endl;
			}
			catch (invalid_argument& e) {
				cout << "分式算式输入错误！" << endl;
			}
		}
		while (choice == 2) {    //选择功能“2.分数排序”时进入的循环
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "请输入一组分数，用逗号隔开，如需由小到大排序用符号<结尾，"
				"由大到小排序用符号>结尾（如1/2,1/4,3/5<回车），输入#号键返回上一层目录："
				<< endl;
			Fraction frac;
			vector <Fraction> fracArr;
			char ch2;
			bool quitFlag = 1;
			try {
				while (true) {
					cin >> frac;
					quitFlag = 0;
					fracArr.push_back(frac);
					ch2 = getchar();
					if (ch2 == '<' || ch2 == '>') break;
					else if (ch2 == '\n') throw invalid_argument("输入错误！");
					else if (ch2 != ',' && ch2 != '，') throw invalid_argument("输入错误！");
				}
				sortFraction(fracArr, ch2);
			}
			catch (string& e) {
				cout << 1 << endl;
				if (quitFlag) break;
			}
			catch (invalid_argument& e) {
				cout << "输入错误！" << endl;
				continue;
			}
		}
	}
	return 0;
}

Fraction operator+(const Fraction& frac1, const Fraction& frac2) //重载+运算符
{
	Fraction frac(frac1.numer * frac2.deno + frac2.numer * frac1.deno, frac1.deno * frac2.deno);
	frac.RdcFrc();
	return frac;
}
Fraction operator-(const Fraction& frac1, const Fraction& frac2) //重载-运算符
{
	Fraction frac(frac1.numer * frac2.deno - frac2.numer * frac1.deno, frac1.deno * frac2.deno);
	frac.RdcFrc();
	return frac;
}
Fraction operator*(const Fraction& frac1, const Fraction& frac2) //重载*运算符
{
	Fraction frac(frac1.numer * frac2.numer, frac1.deno * frac2.deno);
	frac.RdcFrc();
	return frac;
}
Fraction operator/(const Fraction& frac1, const Fraction& frac2) //重载/运算符
{
	Fraction frac(frac1.numer * frac2.deno, frac1.deno * frac2.numer);
	frac.RdcFrc();
	return frac;
}
bool operator==(Fraction frac1, Fraction frac2)                  //重载==运算符
{
	return (frac1.numer * frac2.deno == frac1.deno * frac2.numer);
}
bool operator>(const Fraction& frac1, const Fraction& frac2)     //重载>运算符
{
	Fraction f1(frac1), f2(frac2);
	f1.RdcFrc();
	f2.RdcFrc();
	return (frac1.numer * frac2.deno > frac1.deno * frac2.numer);
}
bool operator<(const Fraction& frac1, const Fraction& frac2)     //重载<运算符
{
	Fraction f1(frac1), f2(frac2);
	f1.RdcFrc();
	f2.RdcFrc();
	return (frac1.numer * frac2.deno < frac1.deno * frac2.numer);
}
ostream& operator<<(ostream& out, const Fraction& frac)          //重载<<运算符
{
	if (frac.numer == 0 && choice == 1) out << frac.numer;
	else out << frac.numer << '/' << frac.deno;
	return out;
}
istream& operator>>(istream& in, Fraction& frac)                 //重载>>运算符
{
	char ch;
	if (in >> frac.numer) {}
	else {
		in.clear();
		in >> ch;
		if (ch == '#') throw string("#返回上一级");
		else throw invalid_argument("输入错误！");
	}
	in >> ch;
	if (ch != '/') throw invalid_argument("输入错误！");
	if (in >> frac.deno) {}
	else {
		throw invalid_argument("输入错误！");
	}
	return in;
}
void sortFraction(vector <Fraction>& fracArr, char ch2)//对分数数组排序
{
	Fraction temp;
	if (ch2 == '<') {
		for (unsigned int i = 1; i < fracArr.size(); i++) {
			for (unsigned int j = 0; j < fracArr.size() - i; j++) {
				if (fracArr[j] > fracArr[j + 1]) {
					temp = fracArr[j + 1];
					fracArr[j + 1] = fracArr[j];
					fracArr[j] = temp;
				}
			}
		}
	}
	else if (ch2 == '>') {
		for (unsigned int i = 1; i < fracArr.size(); i++) {
			for (unsigned int j = 0; j < fracArr.size() - i; j++) {
				if (fracArr[j] < fracArr[j + 1]) {
					temp = fracArr[j + 1];
					fracArr[j + 1] = fracArr[j];
					fracArr[j] = temp;
				}
			}
		}
	}
	for (unsigned int i = 0; i < fracArr.size(); i++) {
		if (i == 0) cout << fracArr[i];
		else {
			cout << ' ' << fracArr[i];
		}
	}
	cout << endl;
}
Fraction::Fraction()                      //无参造函数
{
	numer = 0;
	deno = 1;
}
Fraction::Fraction(int n, int d)          //带参造函数
{
	if (d == 0) throw invalid_argument("无效分母！");
	numer = n;
	deno = d;
}
Fraction::Fraction(const Fraction& f)     //复制造函数
{
	this->numer = f.numer;
	this->deno = f.deno;
}
void Fraction::setFraction(int n, int d)  //设置分数的分子和分母
{
	if (d == 0) throw invalid_argument("无效分母！");
	numer = n;
	deno = d;
}
int Fraction::getNumer()                  //获取分数的分子
{
	return numer;
}
int Fraction::getDeno()                   //获取分数的分母
{
	return deno;
}
void Fraction::RdcFrc()                   //当前分数约分
{
	if (numer == 0) {}
	else {
		int temp = (numer < deno) ? numer : deno;
		while (1) {
			if (numer % temp == 0 && deno % temp == 0) {
				numer /= temp;
				deno /= temp;
				break;
			}
			else {
				if (temp > 0) temp--;
				else temp++;
			}
		}
		if (numer > 0 && deno < 0) {
			numer *= -1;
			deno *= -1;
		}
	}
}