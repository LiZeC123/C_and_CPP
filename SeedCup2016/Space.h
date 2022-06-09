#pragma once
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <cctype>

//���ڹ�������ռ����
class Space
{
public:
	Space() = default;

	//����һ����������Ϊ�临�ƣ�ͬ���������Զ�����
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

	//����һ���������������ƶ���ֵ������
	//��������һ���������ֵ��ַ�����������Ӧ������
	int & setValue(const std::string &name) {
		//�����������֣�ֱ�ӷ�������
		if (isNumber(name, returnNum)) {
			return returnNum;
		}

		//�����ڱ����ռ��в��Ҷ�Ӧ���Ƶı���
		auto rtn = data.find(name);
		if (rtn == data.end()) {
			std::cerr << "Exception in setValue: " + name + " is not in Space" << std::endl;
			exit(1);
		}
		else {
			//�������ͬ���ı��������²�������ı���
			if (nameCount.find(name) != nameCount.end()) {
				std::string num = { (char)('0' + nameCount[name]),'_','_' };
				std::string newName = name + num;
				rtn = data.find(newName);
			}
			return *(*rtn).second;
		}
	}

	//�����ƶ����Ƶı������Ӷ�ʹԭ�������ǵı����ָ�֮ǰ��ֵ
	void destroyValue(const std::string &name) {
		auto rtn = data.find(name);
		if (rtn == data.end()) {
			std::cerr << "Exception in destroy: " + name + " is not in Space" << std::endl;
			exit(1);
		}
		else {
			//��ͬ������
			if (nameCount.find(name) != nameCount.end()) {
				//���ٶ�Ӧ���Ƶı���
				std::string num = { (char)('0' + nameCount[name]),'_','_' };
				std::string newName = name + num;
				delete data[newName];
				data.erase(newName);

				//������һ��������	
				if (--nameCount[name] == 1) {
					nameCount.erase(name);
				}
			}
			//û��ͬ����ֱ������
			else {
				delete data[name];
				data.erase(name);
			}		
		}
		
	}

	//�����������ͷ�ԭ�б�������Ŀռ�
	~Space()
	{
		for (const auto &i : data) {
			delete i.second;
		}
	}

private:
	//��Ŷ�Ӧ����������ֵ
	std::map<std::string, int *> data;
	//��Ŷ�Ӧ������������ͬ���ı�������
	std::map<std::string,int> nameCount;

	//�ж������ַ����Ƿ�Ϊ���֣����ҷ����ַ������ֶ�Ӧ��ֵ
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

	//���setValue������ͨ��ֵʱ��ֵ
	int returnNum;
};

