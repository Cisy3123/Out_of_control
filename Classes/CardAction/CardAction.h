#pragma once
#include "cocos2d.h"
#include "CardSet.h"
#include <vector>
USING_NS_CC;
class CardAction
{
public:
	CardAction();
	~CardAction();
	bool shuffle();//ϴ��
	void deal();//����
	void Sort(vector<int> &arr);//������
	CardGroupData  PutCardType;//���Ҫ���ȥ���Ƶ�����
	void ClearPutCard();//���ƺ����ԭѡ�е���
	void Arrange();//������������

private:
	vector<int> color_CardList;//�������У�0~54
	int CardCount;//���Ƹ���
	vector<int> color_PutCard;//ѡ�е���
};