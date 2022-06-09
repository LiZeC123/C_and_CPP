#include"analysisCut.h"
#include"../zz/CutStatement.h"

using namespace std;
/*判断字符串是否为空*/
static bool is_notvoid(string str);
/*对于{后面的句子进行判断*/
static void analysis_two(string &former, StatementNode &node);
/*for的第一个要执行的句子的判断*/
static void deal_for(string &former, StatementNode &node);


BracketStatu analysis_one(string &former, StatementNode &node)
{
	/*对于必要的变量初始化*/
	bool create = 0;
	char *p_1 = new char[2];
	p_1[1] = '\0';
	string t;
	int brackets = 0;
	CutStatement cut;
	node.attr = NORMAL;
	/*判断非空*/
	if (former.empty()) {
		node.attr = EMPTY;
		return NO_BRACKET;
	}

	/*处理int的情况*/
	if (former.find("int") == 0) {
		if (former[3] == ' ') {
			node.attr = INT;
			int i = 0;
			for (i = 4; former[i] != ';'; i++) {
				if (former[i] == ' ')
					continue;
				if (former[i] == ',')
					create = 1;
				if (create == 1) {
					node.left.push_back(t);
					t.clear();
					create = 0;

				}
				else {
					p_1[0] = former[i];
					t.append(p_1);
				}
			}
			node.left.push_back(t);
			t.clear();
			if (is_notvoid(former.substr(i + 1, former.length()))) {
				analysis_one(former.substr(i + 1, former.length()), node);
			}
		}
	}


	/*处理if的情况*/
	else if (former.find("if") == 0) {
		if (former[2] == ' ' || former[2] == '(') {
			node.attr = IF;
			int i = 0;
			for (i = 3; former[i] != ')'; i++) {
				if (former[i] == ' ' || former[i] == '(')
					continue;
				else {
					p_1[0] = former[i];
					t.append(p_1);
				}

			}
			node.judgement = t;
			t.clear();
			if (is_notvoid(former.substr(i + 1, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(i + 1, former.length()))) {
					analysis_two(i, node);
				}
			}
			for (i++; former[i] != '\0'; i++) {

				if (former[i] == '{') {
					brackets = 1;
					
				}

				if (former[i] == '}') {
					brackets = 3;
				}
			}

		}
	}

	/*处理else if的情况*/
	else if (former.find("else if") == 0) {
		if (former[7] == ' ' || former[7] == '(') {
			node.attr = ELSE_IF;
			int i = 0;
			for (i = 8; former[i] != ')'; i++) {
				if (former[i] == ' ' || former[i] == '(')
					continue;
				else {
					p_1[0] = former[i];
					t.append(p_1);
				}

			}
			node.judgement = t;
			t.clear();
			if (is_notvoid(former.substr(i + 1, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(i + 1, former.length()))) {
					analysis_two(i, node);
				}
			}
			for (i++; former[i] != '\0'; i++) {
				if (former[i] == '{') {
					brackets = 1;
				}
				if (former[i] == '}') {
					brackets = 3;
				}
			}

		}
	}
	/*处理else的情况*/
	else if (former.find("else") == 0) {
		if (former[4] == ' ' || former[4] == '{' || former[4] == '\0') {
			node.attr = ELSE;
			int i = 4;
			if (is_notvoid(former.substr(i, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(i, former.length()))) {
					analysis_two(i, node);/////////////////////////////////////////////////////////
				}
			}
			for (; former[i] != '\0'; i++) {
				if (former[i] == '{') {
					brackets = 1;
				}
				if (former[i] == '}') {
					brackets = 3;
				}
			}
			
		}
	}

	/*处理for的情况*/
	else if (former.find("for") == 0) {
		if (former[3] == ' ' || former[3] == '(') {
			node.attr = FOR_NORMAL;
			int i = 0, j = 0;
			for (i = 4; former[i] != ')'; i++) {
				if (former[i] == ' ' || former[i] == '(')
					continue;
				if (former[i] == ';')
					create = 1;
				if (create == 1) {
					switch (j)
					{
					case 0:
						
						if (t.size()>3&&t.substr(0,3) == "int") {
							deal_for(t.substr(3, t.size()), node);
						}
						else {
							
							node.left.push_back(t);
						}
						t.clear();
						break;
					case 1:
						node.judgement = t;
						break;
					case 2:
						node.right.push_back(t);
						break;
					default:
						break;
					}
					t.clear();
					create = 0;
					j++;
				}
				else {
					p_1[0] = former[i];
					t.append(p_1);
				}
			}
			node.right.push_back(t);
			t.clear();
			if (is_notvoid(former.substr(i + 1, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(i + 1, former.length()))) {
					analysis_two(i, node);
				}
			}
			for (i++; former[i] != '\0'; i++) {
				if (former[i] == '{') {
					brackets = 1;

				}
				if (former[i] == '}') {
					brackets = 3;
				}
			}
		}
	}

	/*处理else if的情况*/
	else if (former.find("do") == 0) {
		if (former[2] == ' ' || former[2] == '{') {
			node.attr = DO;
			//判断do后面
			int i = 2;
			if (is_notvoid(former.substr(i, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(i, former.length()))) {
					analysis_two(i, node);/////////////////////////////////////////////////////////
				}
			}
			for (; former[i] != '\0'; i++) {
				if (former[i] == '{') {
					brackets = 1;
				}
				if (former[i] == '}') {
					brackets = 3;//两个括号都在一行
				}
			}
		}
	}

	/*处理while的情况*/
	else if (former.find("while") == 0) {//有没有|| &&
		if (former[5] == ' ' || former[5] == '(') {
			node.attr = WHILE;
			int i = 0;
			for (i = 5; former[i] != ')'; i++) {
				if (former[i] == ' ' || former[i] == '(')
					continue;
				p_1[0] = former[i];
				t.append(p_1);
			}
			node.judgement = t;
			t.clear();
			//判断后面
			if (is_notvoid(former.substr(i + 1, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(i + 1, former.length()))) {
					analysis_two(i, node);/////////////////////////////////////////////////////////
				}
			}
			for (int i = 2; former[i] != '\0'; i++) {
				if (former[i] == '{') {
					brackets = 1;
				}
				if (former[i] == '}') {
					brackets = 3;//两个括号都在一行
				}
			}
		}
	}

	/*处理break的情况*/
	else if (former.find("break") == 0) {
		if (former[5] == ' ' || former[5] == ';') {
			node.attr = BREAK;
			for (int i = 6; former[i] != '\0'; i++) {
				if (former[i] == '}') {
					brackets = 2;
				}
			}
		}
	}


	/*处理其他情况*/
	else {
		if (former[0] == '{') {
			brackets = 1;		
			if (is_notvoid(former.substr(1, former.length()))) {

				for (auto &i : cut.cutStatement(former.substr(1, former.length()))) {
					analysis_two(i, node);
				}
			}
		}
		else if (former[0] == '}') {
			brackets = 2;
			int i = 0;
			node.attr = EMPTY;
			if (former.size() >= 3) {
				for ( i = 0; i <= former.size(); i++) {
					if (former[i] == ' ' || former[i] == '}') {
						continue;
					}
					break;
				}
				analysis_one(former.substr(i, former.size()),node);
			}
		}
		else {
			if (former.substr(0, 6) == "printf") {
				node.attr = PRINTF;
				int _flag = -1;
				int _temp = former.rfind("\""); 
				for (int i = _temp; former[i] != ')'; i++) {
					if (former[i] == ' ' || former[i] == '\"')
						continue;
					if (former[i] == ',') {
						if (_flag == -1) {
							_flag += 1;
							continue;
						}
						_flag += 1;
						
					}
					if (_flag >= 1) {
						node.left.push_back(t);
						t.clear();
						_flag = 0;

					}
					else {
						p_1[0] = former[i];
						t.append(p_1);
					}
				}
				if (!t.empty()) {
					node.left.push_back(t);
					t.clear();
				}
			}


			else {
				int i = 0;
				for (; former[i] != ';'; i++) {
					if (former[i] == ' ')
						continue;
					else {
						p_1[0] = former[i];
						t.append(p_1);
					}

				}
				node.left.push_back(t);
				if (is_notvoid(former.substr(i + 1, former.length()))) {

					for (auto &i : cut.cutStatement(former.substr(i + 1, former.length()))) {
						analysis_two(i, node);
					}
				}
			}
		}

	}
	delete p_1;
	switch (brackets)
	{
	case 0:
		return NO_BRACKET;
	case 1:
		return LEFT_BRACKET;
	case 2:
		return RIGHT_BRACKET;
	case 3:
		return BOTH_BRACKET;
	default:
		break;
	}
}
void analysis_two(string & former, StatementNode & node) {
	string str;
	CutStatement cut;
	for (int i = 0; i < former.length(); i++) {
		if (former[i] == '{' || former[i] == '}' || former[i] == ' ' || former[i] == ';') {
			continue;
		}
		str.push_back(former[i]);
	}
	if (str == "\0") {
		return;
	}
	node.left.push_back(str);
}
bool is_notvoid(string str) {
	if (str.size() == 0) {
		return false;
	}
	for (int i = 0; i <= str.length(); i++) {
		if (str[i] == '{' || str[i] == '}' || str[i] == ' ' || str[i] == ';') {
			continue;
		}
		return true;
	}
	return false;
}
void deal_for(string &former, StatementNode &node) {
	int i = 0;
	int create = 0;
	string t;
	node.attr = FOR_INT;
	char *p_1;
	p_1 = new char[2];
	p_1[1] = '\0';
	for (; former[i] != '\0'; i++) {
		if (former[i] == ' ')
			continue;
		if (former[i] == ',')
			create = 1;
		if (create == 1) {
			node.left.push_back(t);
			t.clear();
			create = 0;

		}
		else {
			p_1[0] = former[i];
			t.append(p_1);
		}
	}
	node.left.push_back(t);
}
