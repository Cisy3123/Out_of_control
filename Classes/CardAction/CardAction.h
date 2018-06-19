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
	CardGroupData CardsType(vector<int> Card); //�����������
	void changeNowCard();//���ƺ󣬸��µ�ǰ�������
	void ClearPutCard();//���ƺ����ԭѡ�е���
	void Arrange();//������������
	void copyTOtemp();//�ѵ�ǰ���ϵ�copy��temp
	void tempTOput();//��temp���ݵ�color_PutCard
	bool find_Cards();//�ҵ����ڵ�ǰ�ƵĽ������
	void getCardList();//���������еõ�״̬����
private:
	int CardCount;//���Ƹ���
	int HandCardList[15];//����״̬����
	vector<int> NowCard;//��ǰ�������
	vector<int> color_PutCard;//ѡ�е���
	vector<int> temp;//��Ե�ǰ�Ƶ���ʱ�������
	vector<int> color_CardList;//�������У�0~54
};