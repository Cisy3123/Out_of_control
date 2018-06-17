#pragma once
#include "cocos2d.h"
#include "CardSet.h"
#include"Player.h"
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
	CardGroupData CardsType(vector<int> color_PutCard); //�����������
	void changeNowCard();//���ƺ󣬸ı䵱ǰ������Ƶ���������
	void ClearPutCard();//���ƺ����ԭѡ�е���
	void Arrange();//������������
	CardGroupData NowCardGroup() //�ṩ��ǰ������Ƶ���Ϣ;
	bool find_Cards(CardGroupData temp);//�ҵ����ڵ�ǰ�ƵĽ������
private:
	CardGroupData NowCardGroup;//��ǰ����Ƶ���������
	CardGroupData PutCardType;//ѡ�е��Ƶ���������
	vector<int> color_PutCard;//ѡ�е���
	int CardCount;//���Ƹ���
	CardGroupData temp;//��Ե�ǰ�Ƶ���ʱ�������
	vector<int> color_CardList;//�������У�0~54
};