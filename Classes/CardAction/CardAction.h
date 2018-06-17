#pragma once
#include "cocos2d.h"
#include "CardSet.h"
#include <vector>
USING_NS_CC;
class CardAction
{
	friend class Player;
public:
	CardAction();
	~CardAction();
	bool shuffle();//ϴ��
	void deal();//����
	void Sort(vector<int> &arr);//������

	void ClearPutCard();//���ƺ����ԭѡ�е���
	void Arrange();//������������
	CardGroupData NowCardGroup() //�ṩ��ǰ������Ƶ���Ϣ;
private:
	CardGroupData NowCardGroup;//��ǰ����Ƶ���������
	CardGroupData PutCardType;//ѡ�е��Ƶ���������
	vector<int> color_PutCard;//ѡ�е���
};