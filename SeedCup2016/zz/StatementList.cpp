#include "StatementList.h"
#include "CutStatement.h"

using iterator = std::list<StatementNode>::iterator;

StatementList::StatementList(std::ifstream & inf)
{
	
	int edx = 1;
	iterator this_t;
	std::string lineString;
	CutStatement Cs;
	
	//利用peek()函数保证不多读取
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
				//没有括号直接存入
				data.push_back(t);
				break;
			case LEFT_BRACKET:
				//左括号，先存入堆栈，之后和对应右括号匹配
				data.push_back(t);
				this_t = (--data.end());
				BracketStack.push(this_t);
				break;
			case RIGHT_BRACKET:
				//右括号，弹出对应的左括号，形成匹配
				t.Goto = BracketStack.top();
				data.push_back(t);
				BracketStack.top()->Goto = (--data.end());
				BracketStack.pop();	
				break;
			case BOTH_BRACKET:
				//都是括号，指向自己
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

	//遍历生成的链表结构，产生最后的顺序
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
	
	//输出答案
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
	//如果是和while匹配的右括号
	if (it->Goto->attr == WHILE) {
		if (Oe.compareExp(it->Goto->judgement)) {
			it = it->Goto;
		}
		//表达式结果为假，且第一次出现，不回跳，直接加上该行
		else if (it->Goto->lastAnswer) {
			printList.push_back(it->Goto->lineNo);
			++it;
		}
		else {
			++it;
		}
		return it;
	}
	//如果是和for匹配的右括号
	if (it->Goto->attr == FOR_INT || it->Goto->attr == FOR_NORMAL) {
		Oe.assignOperDeal(it->Goto->right);
		printList.push_back(it->Goto->lineNo);
		if (Oe.compareExp(it->Goto->judgement)) {
			it = it->Goto;
		}
		return ++it;
	}
	//其他空白情况
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
		//统计之间的判断的结果
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
	//进行判断
	it->lastAnswer = Oe.compareExp(it->judgement);
	//为真，执行下一句
	if (it->lastAnswer) {
		++it;
	}
	//为假，跳转至匹配的右括号
	else {
		it = it->Goto;
	}
	return it;
}

iterator StatementList::doElseIf(iterator it)
{
	it->lastAnswer = Oe.compareExp(it->judgement);
	//如果当前条件为假，直接跳过
	if (!it->lastAnswer) {
		it = it->Goto;	
	}
	else {
		//否则回溯之前的结果
		bool  ifReturn = getBackBool(it);

		//如果之前已经执行过，这跳过这一段
		if (ifReturn) {
			it = it->Goto;
		}
		else {
			//否则执行这一段
			printList.push_back(it->lineNo);
			++it;
		}
	}
	return it;
}

iterator StatementList::doElse(iterator it)
{
	//回溯之前的结果
	bool  ifReturn = getBackBool(it);

	//如果之前已经执行过，这跳过这一句
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
	//先初始化第一句
	Oe.stateOperDeal(it->left);
	//判断条件
	if (!Oe.compareExp(it->judgement)) {
		it = it->Goto;
		++it;
	}
	return it;
}

iterator StatementList::doForNormal(iterator it)
{
	printList.push_back(it->lineNo);
	//先执行第一句
	Oe.stateOperDeal(it->left);
	//判断条件
	if (!Oe.compareExp(it->judgement)) {
		it = it->Goto;
	}
	return ++it;
}

iterator StatementList::doDo(iterator it)
{
	//直接执行下一句
	return ++it;
}

iterator StatementList::doWhile(iterator it)
{
	printList.push_back(it->lineNo);
	//如果是DO-WHILE判断是否回跳
	it->lastAnswer = Oe.compareExp(it->judgement);
	if (it->Goto->attr == DO) {
		//条件为真，返回继续执行
		if (it->lastAnswer) {
			it = it->Goto;
		}
		//条件为假，执行下一句
		else {
			++it;
		}
		return it;
	}

	//普通while语句
	//条件为真，执行下一句
	if (it->lastAnswer) {
		++it;
	}
	//条件为假，跳转至匹配的右括号
	else {
		it = it->Goto;
	}
	return it;
}
