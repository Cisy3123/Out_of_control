#pragma once
#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

class Player : public CCObject
{
public:
	Player();
	~Player();
<<<<<<< HEAD:Classes/Player/Player.h
	void updatePkWeiZhi();//�����Ƶ�λ��

=======
>>>>>>> be0b47c8f2d34895abe1c9bcb3781cc72d987b96:Classes/Player.h
private:
	CC_SYNTHESIZE(bool, m_isDiZhu, IsDiZhu);//�Ƿ�Ϊ����
	CC_SYNTHESIZE(bool, m_isCall, Call);//�Ƿ��ѽе���
	CC_SYNTHESIZE(int, m_iCallNum, CallNum);//�е����ķ���
	CC_SYNTHESIZE(CCArray*, m_arrPk, ArrPk);//����ӵ�е��˿���
	CC_SYNTHESIZE(CCPoint, m_point, Point);//��������ĳ�ʼλ��
	CC_SYNTHESIZE(int, m_iPlayerClass, PlayerClass);//�������:0Ϊ��ң�1Ϊ���ԣ�2Ϊ��ʾ��������,3Ϊ���Ҫ�����ƣ�4Ϊ����1Ҫ�����ƣ�5Ϊ����2Ҫ������
	std::vector<PaiXing> m_vecPX;//��������
	CC_SYNTHESIZE(bool, m_isOutPk, IsOutPk);//����Ƿ����true:�� false:����
};
