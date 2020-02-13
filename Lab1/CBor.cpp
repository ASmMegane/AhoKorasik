#include <iostream>
#include "CBor.h"
#include <algorithm>

Bor::Bor() {
	borInit();
};

void Bor::borInit() {
	borVertex v;
	v.numberVertex = 0;
	v.isEnd = false;
	v.suffLink = NULL;
	v.deepValue = -1;
	v.goodSuffLink = NULL;
	bor.push_back(v);
};

void Bor::addChild(borVertex& parentVertex, borVertex& childVertex, char letter) {
	char valueChildeVertex = letter;
	if (parentVertex.nextVertex.find(valueChildeVertex) == parentVertex.nextVertex.end())
	{
		parentVertex.nextVertex[valueChildeVertex] = &childVertex;
	}
};

Bor::borVertex* Bor::getAutoMove(borVertex& vertex, char letter) {
	
	borVertex* nextVertex = NULL;

	if (vertex.autoMove.find(letter) == vertex.autoMove.end()) {
		if (vertex.nextVertex.find(letter) != vertex.nextVertex.end())
		{
			vertex.autoMove[letter] = vertex.nextVertex[letter];
			nextVertex = vertex.nextVertex[letter];
		}
		else
		{
			if (vertex.numberVertex == 0)
			{
				vertex.autoMove[letter] = &vertex;
				nextVertex = &vertex;
			}
			else
			{
				vertex.suffLink = getAutoMove(*getGoodSuffLink(vertex), letter);
				nextVertex = vertex.suffLink;
			}
		}
	}
	else
	{
		nextVertex = vertex.autoMove[letter];
	}
	return nextVertex;
}

Bor::borVertex* Bor::getSuffLink(Bor::borVertex& vertex) {
	if (vertex.suffLink == NULL)
	{
		if (vertex.numberVertex == 0 || vertex.parentVertex->numberVertex == 0)
		{
			vertex.suffLink = vertex.parentVertex;
		}
		else
		{
			vertex.suffLink = getAutoMove(*getSuffLink(*vertex.parentVertex), vertex.valueVertex);
		}
	}
	return vertex.suffLink;
}

Bor::borVertex* Bor::getGoodSuffLink(Bor::borVertex& vertex) {
	int k = 1 + 3;
	if (vertex.goodSuffLink == NULL)
	{
		borVertex* suffLink = getSuffLink(vertex);
		if (suffLink->numberVertex == 0)
		{
			vertex.goodSuffLink = suffLink;
		}
		else
		{
			if (vertex.isEnd)
			{
				vertex.goodSuffLink = suffLink;
			}
			else
			{
				vertex.goodSuffLink = getGoodSuffLink(*suffLink);
			}
		}
	}
	return vertex.goodSuffLink;
}

void Bor::findAllInStr(const std::string& str) {
	std::string newText = str;
	textOrig = str;
	for (int i = 0; i < newText.length(); i++)
	{
		if (newText[i] == '\n')
		{
			numberString[numberString.size()] = i;
			newText[i] = ' ';
		}
		else
		{
			newText[i] = tolower(newText[i]);
		}
	};
	text = newText;
	
	
	borVertex& start = *(bor.begin());
	borVertex* curentVertex = &start;
	for (int i = 0; i < text.length(); i++)
	{
		curentVertex = getAutoMove(*curentVertex, text[i]);
		int kek = 1;
		check((*curentVertex), text[i], i);
	}
	text = "";
}

void Bor::check(borVertex& vertex, char letter, int position) {
	
	for (borVertex* u = &vertex; u->numberVertex != 0; u = getGoodSuffLink(*u))
	{		
		if (u->isEnd)
		{
			int len = u->deepValue + 1;
			
			//auto u = getGoodSuffLink(vertex);
			int startSubstr = position - u->deepValue;
			int numberLine = 1;
			for (int i = 0; i < numberString.size(); i++)
			{
				if (startSubstr < numberString[i])
				{
					numberLine = i + 1;
					break;
				}
			}
			

			std::cout << "Line: "<< numberLine << " Position " << startSubstr << ": " + text.substr(startSubstr, len) << std::endl;
			
		}
	}
}

void Bor::addVertex(borVertex& parentVertex, int numberVertex, bool isEnd, char valueVertex) {

	borVertex v;
	v.parentVertex = &parentVertex;
	v.valueVertex = tolower(valueVertex);
	v.numberVertex = numberVertex;
	v.isEnd = isEnd;
	v.deepValue = parentVertex.deepValue + 1;
	v.suffLink = NULL;
	v.goodSuffLink = NULL;
	bor.push_back(v);
};


void Bor::addStrToBor(const std::string& str) {

	int curentSizeKeyWords = keyWords.size();
	keyWords.insert(str);

	if (curentSizeKeyWords < keyWords.size()) {
		borVertex& start = *(bor.begin());
		borVertex* curentVertex = &start;
		for (int i = 0; i < str.length(); i++)
		{
			char letter = str[i];

			if (curentVertex->nextVertex.find(letter) == curentVertex->nextVertex.end())
			{
				if (i == str.length() - 1)
				{
					int b = 1;
				}
				addVertex(*curentVertex, bor.size(), false, letter);
				borVertex& child = *(--bor.end());
				addChild(*curentVertex, child, letter);
				curentVertex = &(*(--bor.end()));
			}
			else {
				
				curentVertex = (curentVertex->nextVertex[letter]);
			}
		}
		curentVertex->isEnd = true;
	}
	else
	{

	}
};