#pragma once
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <cctype>

//用于构造变量空间的类
class Space
{
public:
	Space() = default;

	//新增一个变量，并为其复制，同名变量，自动覆盖
	void initValue(const std::string &name, int value) {
		auto rtn = data.find(name);
		if (rtn == data.end()) {
			data[name] = new int(value);
		}
		else {
			if (nameCount.find(name) == nameCount.end()) {
				nameCount[name] = 2;
			}
			else {
				nameCount[name]++;
			}
			std::string num = { (char)('0' + nameCount[name]) ,'_','_'};
			std::string newName = name + num;
			data[newName] = new int(value);		
		}
	}

	//输入一个变量名，返回制定的值的引用
	//或者输入一个包含数字的字符串，返回相应的数字
	int & setValue(const std::string &name) {
		//如果读入的数字，直接返回数字
		if (isNumber(name, returnNum)) {
			return returnNum;
		}

		//否则在变量空间中查找对应名称的变量
		auto rtn = data.find(name);
		if (rtn == data.end()) {
			std::cerr << "Exception in setValue: " + name + " is not in Space" << std::endl;
			exit(1);
		}
		else {
			//如果存在同名的变量，重新查找最近的变量
			if (nameCount.find(name) != nameCount.end()) {
				std::string num = { (char)('0' + nameCount[name]),'_','_' };
				std::string newName = name + num;
				rtn = data.find(newName);
			}
			return *(*rtn).second;
		}
	}

	//销毁制定名称的变量，从而使原本被覆盖的变量恢复之前的值
	void destroyValue(const std::string &name) {
		auto rtn = data.find(name);
		if (rtn == data.end()) {
			std::cerr << "Exception in destroy: " + name + " is not in Space" << std::endl;
			exit(1);
		}
		else {
			//有同名变量
			if (nameCount.find(name) != nameCount.end()) {
				//销毁对应名称的变量
				std::string num = { (char)('0' + nameCount[name]),'_','_' };
				std::string newName = name + num;
				delete data[newName];
				data.erase(newName);

				//计数减一或者销毁	
				if (--nameCount[name] == 1) {
					nameCount.erase(name);
				}
			}
			//没有同名，直接销毁
			else {
				delete data[name];
				data.erase(name);
			}		
		}
		
	}

	//析构函数，释放原有变量分配的空间
	~Space()
	{
		for (const auto &i : data) {
			delete i.second;
		}
	}

private:
	//存放对应变量名和其值
	std::map<std::string, int *> data;
	//存放对应变量名和其中同名的变量数量
	std::map<std::string,int> nameCount;

	//判读输入字符串是否为数字，并且返回字符串数字对应的值
	bool isNumber(const std::string& s, int & returnNum) {
		returnNum = 0;
		for (const auto & i : s) {
			if (!isdigit(i)) {
				return false;
			}
			else {
				returnNum = returnNum * 10 + (i - '0');
			}
		}
		return true;
	}

	//存放setValue返回普通数值时的值
	int returnNum;
};

