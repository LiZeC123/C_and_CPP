#include "StatementList.h"
#include "CutStatement.h"

using iterator = std::list<StatementNode>::iterator;

StatementList::StatementList(std::ifstream & inf)
{
	
	int edx = 1;
	iterator this_t;
	std::string lineString;
	CutStatement Cs;
	
	//����peek()������֤�����ȡ
	while (inf.peek() != EOF)
	{	
		StatementNode t;
		std::getline(inf, lineString);
		for (auto & statement : Cs.cutStatement(lineString)) {
			BracketStatu s = analysis_one(statement, t);
			t.lineNo = edx;
			switch (s)
			{
			case NO_BRACKET:
				//û������ֱ�Ӵ���
				data.push_back(t);
				break;
			case LEFT_BRACKET:
				//�����ţ��ȴ����ջ��֮��Ͷ�Ӧ������ƥ��
				data.push_back(t);
				this_t = (--data.end());
				BracketStack.push(this_t);
				break;
			case RIGHT_BRACKET:
				//�����ţ�������Ӧ�������ţ��γ�ƥ��
				t.Goto = BracketStack.top();
				data.push_back(t);
				BracketStack.top()->Goto = (--data.end());
				BracketStack.pop();	
				break;
			case BOTH_BRACKET:
				//�������ţ�ָ���Լ�
				data.push_back(t);
				this_t = (--data.end());
				this_t->Goto = this_t;
				break;
			default:
				break;
			}
		}

		++edx;
	}
}

void StatementList::Run()
{
	auto it = data.begin();

	//�������ɵ�����ṹ����������˳��
	while (it!=data.end())
	{
		switch (it->attr)
		{
		case EMPTY:
			it = doEmpty(it);
			break;
		case INT:
			it = doInt(it);
			break;
		case NORMAL:
			it = doNormal(it);
			break;
		case IF:
			it = doIf(it);
			break;
		case ELSE_IF:	
			it = doElseIf(it);
			break;
		case ELSE:
			it = doElse(it);
			break;
		case FOR_INT:
			it = doForInt(it);
			break;
		case FOR_NORMAL:
			it = doForNormal(it);
			break;
		case DO:
			it = doDo(it);
			break;
		case WHILE:
			it = doWhile(it);
			break;
		case BREAK:
			it = doBreak(it);
			break;
		case PRINTF:
			it = doPrintf(it);
			break;
		default:
			break;
		}
	}
	
	//�����
	printAnswer();
}

void StatementList::Print()
{

	for (auto i = data.begin(); i != data.end(); ++i) {
		std::cout << "No:" << i->lineNo << " attr:" << i->attr;
		if (!i->left.empty()) {
			std::cout <<" left:" << i->left[0];
		}
		else {
			std::cout << " left:" << "  ";
		}
		std::cout << " judement " << i->judgement;
		if (!i->right.empty()) {
			std::cout << " right:" << i->right[0];
		}
		else {
			std::cout << " right:" << " ";
		}
		std::cout << std::endl;	
	}
}

iterator StatementList::doEmpty(iterator it)
{
	//����Ǻ�whileƥ���������
	if (it->Goto->attr == WHILE) {
		if (Oe.compareExp(it->Goto->judgement)) {
			it = it->Goto;
		}
		//���ʽ���Ϊ�٣��ҵ�һ�γ��֣���������ֱ�Ӽ��ϸ���
		else if (it->Goto->lastAnswer) {
			printList.push_back(it->Goto->lineNo);
			++it;
		}
		else {
			++it;
		}
		return it;
	}
	//����Ǻ�forƥ���������
	if (it->Goto->attr == FOR_INT || it->Goto->attr == FOR_NORMAL) {
		Oe.assignOperDeal(it->Goto->right);
		printList.push_back(it->Goto->lineNo);
		if (Oe.compareExp(it->Goto->judgement)) {
			it = it->Goto;
		}
		return ++it;
	}
	//�����հ����
	return ++it;
}

iterator StatementList::doInt(iterator it)
{
	switch (Oe.stateOperDeal(it->left))
	{
	case execution:
		printList.push_back(it->lineNo);
		break;
	case non_execution:
		break;
	default:
		break;
	}
	return ++it;
}

iterator StatementList::doNormal(iterator it)
{
	switch (Oe.assignOperDeal(it->left))
	{
	case execution:
		printList.push_back(it->lineNo);
		break;
	case non_execution:
		break;
	default:
		break;
	}
	return ++it;
}

iterator StatementList::doBreak(iterator it)
{
	printList.push_back(it->lineNo);
	auto outIt = it;
	while (true)
	{
		if (outIt->attr != EMPTY) {
			++outIt;
		}
		else if (outIt->Goto->attr == FOR_INT || outIt->Goto->attr == FOR_NORMAL ||
			     outIt->Goto->attr == WHILE   || outIt->Goto->attr == DO) {
			++outIt;
			break;
		}
		else {
			++outIt;
		}
	}

	return outIt;
}

iterator StatementList::doPrintf(iterator it)
{
	printList.push_back(it->lineNo);
	Oe.assignOperDeal(it->left);
	return ++it;
}

bool StatementList::getBackBool(iterator it)
{
	auto outIt = --it;
	bool ifReturn = false;
	while (outIt->lineNo != 1)
	{
		//ͳ��֮����жϵĽ��
		if (outIt->attr == ELSE_IF) {
			ifReturn = ifReturn || outIt->lastAnswer;
			--outIt;
		}
		else if (outIt->attr == IF) {
			ifReturn = ifReturn || outIt->lastAnswer;
			break;
		}
		else {
			--outIt;
		}
	}
	return ifReturn;
}

void StatementList::printAnswer()
{
	FILE *fp = fopen("output.txt", "w");
	int size = printList.size();
	int lastOne = size - 1;
	for (int i = 0; i < size; ++i) {
		if (i == lastOne) {
			fprintf(fp,"%d", printList[i]);
		}
		else {
			fprintf(fp,"%d ", printList[i]);
		}
	}
}

iterator StatementList::doIf(iterator it)
{
	printList.push_back(it->lineNo);
	//�����ж�
	it->lastAnswer = Oe.compareExp(it->judgement);
	//Ϊ�棬ִ����һ��
	if (it->lastAnswer) {
		++it;
	}
	//Ϊ�٣���ת��ƥ���������
	else {
		it = it->Goto;
	}
	return it;
}

iterator StatementList::doElseIf(iterator it)
{
	it->lastAnswer = Oe.compareExp(it->judgement);
	//�����ǰ����Ϊ�٣�ֱ������
	if (!it->lastAnswer) {
		it = it->Goto;	
	}
	else {
		//�������֮ǰ�Ľ��
		bool  ifReturn = getBackBool(it);

		//���֮ǰ�Ѿ�ִ�й�����������һ��
		if (ifReturn) {
			it = it->Goto;
		}
		else {
			//����ִ����һ��
			printList.push_back(it->lineNo);
			++it;
		}
	}
	return it;
}

iterator StatementList::doElse(iterator it)
{
	//����֮ǰ�Ľ��
	bool  ifReturn = getBackBool(it);

	//���֮ǰ�Ѿ�ִ�й�����������һ��
	if (ifReturn) {
		it = it->Goto;	
	}
	else {
		++it;
	}
	return it;
}

iterator StatementList::doForInt(iterator it)
{
	printList.push_back(it->lineNo);
	//�ȳ�ʼ����һ��
	Oe.stateOperDeal(it->left);
	//�ж�����
	if (!Oe.compareExp(it->judgement)) {
		it = it->Goto;
		++it;
	}
	return it;
}

iterator StatementList::doForNormal(iterator it)
{
	printList.push_back(it->lineNo);
	//��ִ�е�һ��
	Oe.stateOperDeal(it->left);
	//�ж�����
	if (!Oe.compareExp(it->judgement)) {
		it = it->Goto;
	}
	return ++it;
}

iterator StatementList::doDo(iterator it)
{
	//ֱ��ִ����һ��
	return ++it;
}

iterator StatementList::doWhile(iterator it)
{
	printList.push_back(it->lineNo);
	//�����DO-WHILE�ж��Ƿ����
	it->lastAnswer = Oe.compareExp(it->judgement);
	if (it->Goto->attr == DO) {
		//����Ϊ�棬���ؼ���ִ��
		if (it->lastAnswer) {
			it = it->Goto;
		}
		//����Ϊ�٣�ִ����һ��
		else {
			++it;
		}
		return it;
	}

	//��ͨwhile���
	//����Ϊ�棬ִ����һ��
	if (it->lastAnswer) {
		++it;
	}
	//����Ϊ�٣���ת��ƥ���������
	else {
		it = it->Goto;
	}
	return it;
}
