#pragma once
#include <map>
#include <list>
#include <set>

class Bor {
private:
	
	struct borVertex {
		bool isEnd;
		int numberVertex;
		int deepValue;
		char valueVertex;
		borVertex* parentVertex;
		borVertex* suffLink;
		std::map<char, borVertex*> autoMove;
		borVertex* goodSuffLink;
		std::map<char, borVertex*> nextVertex;
	};	
	std::string text;
	std::string textOrig;
	std::list<borVertex> bor;
	std::set<std::string> keyWords;
	std::map<int, int> numberString;

	void addVertex(borVertex& parentVertex, int numberVertex, bool isEnd, char valueVertex); //добавление вершины в бор
	void borInit(); //создание бора, добавление пустой(нулевой) вершины
	void addChild(borVertex& parentVertex, borVertex& childVertex, char letter); // добавление ветки в вершину
	borVertex* getSuffLink(borVertex& vertex);
	borVertex* getAutoMove(borVertex& vertex, char letter);
	borVertex* getGoodSuffLink(borVertex& vertex);
	void check(borVertex& vertex, char letter, int position);


public:

	Bor();
	void addStrToBor(const std::string & str); // добавление строки в бор
	void findAllInStr(const std::string& str);
};
