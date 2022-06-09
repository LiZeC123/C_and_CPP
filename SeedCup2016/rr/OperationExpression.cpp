#include "OperationExpression.h"
#include <string>

using namespace std;

//��ֵ��䴦������ֵexecution�����ִ��
runState OperationExpression::assignOperDeal(vector<string> &Oper) {
	
	runState ifRun = non_execution;
	for (int i = 0; i < Oper.size(); i++) {
		if (Oper[i].find_first_of(" ") != -1) {
			continue;
		}
		int plusPos = Oper[i].find("++");
		int minusPos = Oper[i].find("--");
		string value;
		if (plusPos != -1) {  //����++
			value = Oper[i].substr(0, plusPos);
			ValueSpace.setValue(value)++;
		}
		else if (minusPos != -1) { //����--
			value = Oper[i].substr(0, minusPos);
			ValueSpace.setValue(value)--;
		}
		else {
			int evalNum = Oper[i].find_first_of("="); //=��λ��
			exitEqual(Oper[i], evalNum);
		}
		ifRun = execution;
	}
	return ifRun;
}

//������䴦������ֵexecution�����ִ��,non_execution����䲻ִ��
runState OperationExpression::stateOperDeal(vector<string> &evalOper) {
	runState ifRun=non_execution;
	int evalNum;  //=��λ��
	for (int i = 0; i < evalOper.size(); i++) {
		evalNum = evalOper[i].find("=");
		if (evalNum != -1) {  //���ڵȺ�
			string lvalue = evalOper[i].substr(0, evalNum);
			string rvalue = evalOper[i].substr(evalNum + 1, evalOper[i].size() - evalNum - 1);
			ValueSpace.initValue(lvalue, 999999);
			ValueSpace.setValue(lvalue) = caculate(rvalue);
			ifRun = execution;
		}
		else if(evalOper[i].find_first_of(" ")!=-1){//�����
		}
		else {  //���������
			ValueSpace.initValue(evalOper[i], 999999);
		}
	}
	return ifRun;
}

//��ֵ���ʽ���ڵȺ�
void OperationExpression::exitEqual(string evalOper,int evalNum) {//evalNumΪ�Ⱥ�λ��
	string lvalue = evalOper.substr(0, evalNum);
	string rvalue = evalOper.substr(evalNum+1, evalOper.size()-evalNum-1);
	ValueSpace.setValue(lvalue) = caculate(rvalue);
}

//���ʽ�����ڵȺ�,����ֵΪ999999
void OperationExpression::exitNoEqual(string evalOper) {
	ValueSpace.initValue(evalOper, 999999);
}

//������ʽ
int OperationExpression::caculate(string operLink) {
	vector<string> minOper;
	vector<string> lastOper;
	analyzeString(operLink, minOper);
	changeExp(minOper, lastOper);
	return caculateLastOper(lastOper);
}

//����+-*/����ֽ����ַ��������㸳ֵ���м䲽�裩
void OperationExpression::analyzeString(string operLink,vector<string> &operSplit) {
	int operIndex1 = 0;
	int operIndex2 = 0;

	//�滻���ʽ�е�++��--
	int i = operLink.find("++");
	while (i != -1) {//��$�滻++
		operLink.replace(i, 2,"$");
		i = operLink.find("++");
	}
	i = operLink.find("--");
	while (i != -1) {//��%�滻--
		operLink.replace(i, 2,"%");
		i = operLink.find("--");
	}
	
	while (operIndex2 !=-1) {
		operIndex2 = operLink.find_first_of("+-*/", operIndex1);  //��operIndex1Ϊ��ʼλ�ÿ�ʼ��
		if (operIndex2 == -1) {
			operSplit.push_back(operLink.substr(operIndex1, operLink.size() - operIndex1));//�����
		}
		else {
			operSplit.push_back(operLink.substr(operIndex1, operIndex2 - operIndex1));//���������operIndex1��ʼȡ��operIndex2-operIndex1����Ԫ��
			operSplit.push_back(operLink.substr(operIndex2, 1));//�������
		}
		operIndex1 = operIndex2;
		operIndex1++;
	}
}

//��׺ʽ���׺ʽ�����㸳ֵ���м䲽�裩
void OperationExpression::changeExp(vector<string> minExp, vector<string> &lastExp) {
	stack<string> OPTR_STACK;
	OPTR_STACK.push("#");	
	for (int mi = 0; mi < minExp.size(); mi++) {
			if (matchOptr(minExp[mi])==-1) {
				lastExp.push_back(minExp[mi]);
			}
			else {
				switch (preceed(OPTR_STACK.top(), minExp[mi])) {
				case '<': {
					OPTR_STACK.push(minExp[mi]);
					break;
				}
				case '=':
				case '>': {
					lastExp.push_back(OPTR_STACK.top());
					OPTR_STACK.pop();
					mi--;
					break;
				        }
				}
			}
		}
	while (OPTR_STACK.top() != "#") {
			lastExp.push_back(OPTR_STACK.top());
			OPTR_STACK.pop();
		}
}

//ƥ����������ǲ�����������Ӧ�������Ƿ���-1��change�����м䲽�裩
int OperationExpression::matchOptr(string str) { //+��0��-��1��*��2��/��3��#��4
	string optr[5] = { "+","-","*","/" ,"#" };
	for (int i = 0; i < 5; i++) {
		if (str == optr[i]) {
			return i;
		}
	}
	return -1;
}


//�жϲ����������ȼ���change�������м䲽�裩
char OperationExpression::preceed(string stackOptr, string minOptr) {//min�ҲΣ�stack��Ρ�
	int pre[5][5]{
		1,1,0,0,1,
		1,1,0,0,1,
		1,1,1,1,1,
		1,1,1,1,1,
		0,0,0,0,2,
	};
	int mini, stacki;
	switch (minOptr[0] - '*') {
	case 0:mini = 2; break;  //*
	case 1:mini = 0; break;  //+
	case 3:mini = 1; break; //-
	case 5:mini = 3; break; // '/'
	case -7:mini = 4; break; //#
	default:return -1; break; //����
	}
	switch (stackOptr[0] - '*') {
	case 0:stacki = 2; break; //*
	case 1:stacki = 0; break; //+
	case 3:stacki = 1; break; //-
	case 5:stacki = 3; break; // '/'
	case -7:stacki = 4; break; //#
	default:return -1; break;  //����
	}
	switch (pre[stacki][mini]) {
	case 1:return '>';
	case 0:return '<';
	case 2:return '=';
	default:return 'F';
	}
}

int OperationExpression::caculateLastOper(vector<string> &lastOper) {
	stack<int> OPND_STACK;//������ջ
	int a, b;
	int m;//��¼++��λ��
	int n;//��¼--��λ��
	for (int i = 0; i < lastOper.size(); i++) {
			if (matchOptr(lastOper[i])!=-1) { //�ǲ�����
				a = OPND_STACK.top();
				OPND_STACK.pop();
				b = OPND_STACK.top();
				OPND_STACK.pop();
				OPND_STACK.push(oper(a, b, lastOper[i]));
			}
			else {
				m = lastOper[i].find("$");
				n = lastOper[i].find("%");
				if (m != -1) {
					lastOper[i].erase(m, 1);
					OPND_STACK.push(ValueSpace.setValue(lastOper[i]));
					ValueSpace.setValue(lastOper[i])++;
				}
				else if (n != -1) {
					lastOper[i].erase(n, 1);
					OPND_STACK.push(ValueSpace.setValue(lastOper[i]));
					ValueSpace.setValue(lastOper[i])--;
				}
				else OPND_STACK.push(ValueSpace.setValue(lastOper[i]));
			}
	}
	return OPND_STACK.top();
}

//����
int OperationExpression::oper(int a, int b, string optr) {
	switch (matchOptr(optr)) {
	case 0:return b+a;
	case 1:return b-a;
	case 2:return b*a;
	case 3:return b/a;
	}
}

//�Ƚϱ��ʽ
bool OperationExpression::compareExp(string exp) {

	int pos = 0;
	int expType=-1;
	string lValue,rValue;

	for (int i = 0; i < exp.size(); i++) {
		if (exp[i] == '=') {
			expType = 2;
			pos = i;
		}
		else if (exp[i] == '<') {
			expType = 1;
			pos = i;
		}
		else if (exp[i] == '>') {
			expType = 0;
			pos = i;
		}
	}
	switch (expType) {
	case 2: {//����=��
		lValue = exp.substr(0, pos - 1);
		rValue = exp.substr(pos + 1, exp.size() - pos - 1);
		string sign = exp.substr(pos-1, 2);
		if (sign == "==") {
			if (caculate(lValue) == caculate(rValue))  return 1;
			else return 0;
		}
		else if (sign == "!=") {
			if (caculate(lValue) != caculate(rValue))  return 1;
			else return 0;
		}
		else if (sign == ">=") {
			if (caculate(lValue) >= caculate(rValue))  return 1;
			else return 0;
		}
		else if (sign == "<=") {
			if (caculate(lValue) <= caculate(rValue))  return 1;
			else return 0;
		}
		break;
	}
	case 1: {//����<��
		lValue = exp.substr(0,pos);
		rValue = exp.substr(pos + 1, exp.size() - 1);
		if (caculate(lValue) < caculate(rValue))  return 1;
		else return 0;
	}
	case 0: {//����>��
		lValue = exp.substr(0, pos);
		rValue = exp.substr(pos + 1, exp.size() - 1);
		if (caculate(lValue) > caculate(rValue))  return 1;
		else return 0;
	}
	default: {//Ϊ������ĸ������
		if (caculate(exp) != 0)  return 1;
		else return 0;
	}
	}
}
