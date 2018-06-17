#pragma once
#include<iostream>
#include<vector>
#include"CardSet.h"
#include"CardAction.h"
#include"Player.h"
using namespace std;

Player::Player()m_isCall(false), m_iCallNum(0), m_isDiZhu(false), m_isOutPk(false)
{
	m_arrPk = CCArray::create();
	m_arrPk->retain();
}
Player::~Player()
{
	CC_SAFE_RELEASE(m_arrPk);
}
void Player::call()//�е���
{

}


//����Ҫ�жϵ�vector����������������ݽṹ
CardGroupData Player:: CardsType(vector<int> color_PutCard)
{
	int CardList[15] = { 0 };
	for (vector<int>::iterator iter = color_PutCard.begin(); iter != color_PutCard.end(); iter++)
	{
		int i = (*iter / 13) < 4 ? *iter % 13 : *iter - 39;
		CardList[i]++;
	}
	int nCount = 0;
	for (int i = 0; i < 15; i++)
	{
		nCount += CardList[i];
	}

	CardGroupData retCardGroupData;
	retCardGroupData.nCount = nCount;


	//��������  
	if (nCount == 1)
	{
		//������֤�ı���  
		int prov = 0;
		for (int i = 0; i < 15; i++)
		{
			if (CardList[i] == 1)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = SINGLE_CARD;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount == 2)
	{
		//������֤�ı���  
		int prov = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 2)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = DOUBLE_CARD;
			return retCardGroupData;
		}
	}
	//������ 
	if (nCount == 3)
	{
		//������֤�ı���  
		int prov = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 3)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = THREE_CARD;
			return retCardGroupData;
		}
	}
	//����һ��  
	if (nCount == 4)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (CardList[i] == 1)
			{
				prov2++;
			}

		}
		if (prov1 == 1 && prov2 == 1)
		{
			retCardGroupData.cType = THREE_ONE_CARD;
			return retCardGroupData;
		}
	}
	//����һ��  
	if (nCount == 5)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (CardList[i] == 2)
			{
				prov2++;

			}
		}
		if (prov1 == 1 && prov2 == 1)
		{
			retCardGroupData.cType = THREE_TWO_CARD;
			return retCardGroupData;
		}
	}
	//�Ĵ�����  
	if (nCount == 6)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 4)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;

			}
			if (CardList[i] == 1)
			{
				prov2 += CardList[i];
			}
		}

		if (prov1 == 1 && prov2 == 2)
		{
			retCardGroupData.cType = BOMB_TWO_CARD;
			return retCardGroupData;
		}
	}
	//�Ĵ�����  
	if (nCount == 8)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 4)
			{
				prov1++;
				retCardGroupData.nMaxCard = i;
			}
			if (CardList[i] == 2)
			{
				prov2 += CardList[i];

			}
		}
		if (prov1 == 1 && prov2 == 4)
		{
			retCardGroupData.cType = BOMB_TWO_CARD;
			return retCardGroupData;
		}
	}
	//ը������-����ը
	if (nCount == 4)
	{
		//������֤�ı���  
		int prov = 0;
		for (int i = 0; i < 13; i++)
		{
			if (CardList[i] == 4)
			{
				prov++;
				retCardGroupData.nMaxCard = i;
			}
		}
		if (prov == 1)
		{
			retCardGroupData.cType = BOMB_CARD;
			return retCardGroupData;
		}
	}
	//��ը����  
	if (nCount == 2)
	{
		if (CardList[13] > 0 && CardList[14] > 0)
		{
			retCardGroupData.nMaxCard = 14;
			retCardGroupData.cType = KING_CARD;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount >= 5)
	{
		//������֤�ı���  
		int prov = 0;
		int i = 0;
		for (; i < 12; i++)
		{
			if (CardList[i] == 1)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}

		if (prov == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = CONNECT_CARD;
			return retCardGroupData;
		}
	}
	//��������  
	if (nCount >= 6)
	{
		//������֤�ı���  
		int prov = 0;
		int i;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 2)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}

		if (prov * 2 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = COMPANY_CARD;
			return retCardGroupData;
		}
	}
	//�ɻ�����  
	if (nCount >= 6)
	{
		//������֤�ı���  
		int prov = 0;

		int SumValue = 0;
		int i;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 3)
			{
				prov++;
			}
			else
			{
				if (prov != 0)
				{
					break;
				}

			}
		}

		if (prov * 3 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = AIRCRAFT_CARD;
			return retCardGroupData;
		}
	}
	//�ɻ������� 
	if (nCount >= 8)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int i, j;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
			}
			else
			{
				if (prov1 != 0)
				{
					break;
				}

			}
		}
		for (j = 0; j < 13; j++)
		{
			if (CardList[j] == 1)
			{
				prov2 += CardList[j];
			}
		}

		if (prov1 = prov2 && prov1 * 4 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = AIRCRAFT_SINGLE_CARD;
			return retCardGroupData;
		}

	}
	//�ɻ�����������  
	if (nCount >= 10)
	{
		//������֤�ı���  
		int prov1 = 0;
		int prov2 = 0;
		int i, j;
		for (i = 0; i < 12; i++)
		{
			if (CardList[i] == 3)
			{
				prov1++;
			}
			else
			{
				if (prov1 != 0)
				{
					break;
				}
			}
		}
		for (j = 0; j < 13; j++)
		{
			if (CardList[j] == 2)
			{
				prov2 += CardList[j] / 2;
			}
		}

		if (prov1 == prov2 && prov1 * 5 == nCount)
		{
			retCardGroupData.nMaxCard = i - 1;
			retCardGroupData.cType = AIRCRAFT_DOUBLE_CARD;
			return retCardGroupData;
		}
	}

	retCardGroupData.cType = ERROR_CARD;
	return retCardGroupData;
}

//�ҵ����ڵ�ǰ�ƵĽ������
void Player::find_Cards(CardGroupData NowCardGroup)
{
	//�ɻ�����
	//��֤˳�ӵı�־ 
	int prov = 0;
	//�ɻ����  
	int start_i = 0;
	//�ɻ��յ�  
	int end_i = 0;
	//�ɻ�����  
	int length = CardAction.NowCardGroup.nCount / 4;

	int tmp_1 = 0;
	int tmp_2 = 0;
	int tmp_3 = 0;
	int tmp_4 = 0;
	//2����������ɻ����ӵ�ǰ�Ѵ���ķɻ���С��ֵ+1��ʼ����  
	for (int i = CardAction.NowCardGroup.nMaxCard - length + 2; i < 12; i++)
	{
		if (CardAction.color_CardList[i] > 2)
		{
			prov++;
		}
		else
		{
			prov = 0;
		}
		if (prov >= length)
		{
			end_i = i;
			start_i = i - length + 1;

			clsHandCardData.nHandCardCount -= clsGameSituation.uctNowCardGroup.nCount;

			/*��������ȫ����ѡȡ��������Ȼ��ö�ٳ���߼�ֵ�ģ������ǵ����ɻ�����Ҳ������2-4֮��
			���Ըɴ���������֧��������*/
			//Ϊ�����ɻ�  
			if (length == 2)
			{
				for (int j = 3; j < 18; j++)
				{
					if (clsHandCardData.value_aHandCardList[j] > 0)
					{
						clsHandCardData.value_aHandCardList[j] -= 1;
						for (int k = 3; k < 18; k++)
						{
							if (clsHandCardData.value_aHandCardList[k] > 0)
							{
								clsHandCardData.value_aHandCardList[k] -= 1;
								HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
								clsHandCardData.value_aHandCardList[k] += 1;

								//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��  
								if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
								{
									BestHandCardValue = tmpHandCardValue;
									BestMaxCard = end_i;
									tmp_1 = j;
									tmp_2 = k;
									PutCards = true;
								}
							}
						}
						clsHandCardData.value_aHandCardList[j] += 1;
					}

				}
			}
			//Ϊ�����ɻ�  
			if (length == 3)
			{
				for (int j = 3; j < 18; j++)
				{
					if (clsHandCardData.value_aHandCardList[j] > 0)
					{
						clsHandCardData.value_aHandCardList[j] -= 1;
						for (int k = 3; k < 18; k++)
						{
							if (clsHandCardData.value_aHandCardList[k] > 0)
							{
								clsHandCardData.value_aHandCardList[k] -= 1;
								for (int l = 3; l < 18; l++)
								{
									if (clsHandCardData.value_aHandCardList[l] > 0)
									{
										clsHandCardData.value_aHandCardList[l] -= 1;
										HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
										//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��  
										if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
										{
											BestHandCardValue = tmpHandCardValue;
											BestMaxCard = end_i;
											tmp_1 = j;
											tmp_2 = k;
											tmp_3 = l;
											PutCards = true;
										}
										clsHandCardData.value_aHandCardList[l] += 1;
									}
								}
								clsHandCardData.value_aHandCardList[k] += 1;
							}
						}
						clsHandCardData.value_aHandCardList[j] += 1;
					}


				}
			}
			//Ϊ�����ɻ�  
			if (length == 4)
			{
				for (int j = 3; j < 18; j++)
				{
					if (clsHandCardData.value_aHandCardList[j] > 0)
					{
						clsHandCardData.value_aHandCardList[j] -= 1;
						for (int k = 3; k < 18; k++)
						{
							if (clsHandCardData.value_aHandCardList[k] > 0)
							{
								clsHandCardData.value_aHandCardList[k] -= 1;
								for (int l = 3; l < 18; l++)
								{
									if (clsHandCardData.value_aHandCardList[l] > 0)
									{
										clsHandCardData.value_aHandCardList[l] -= 1;
										for (int m = 3; m < 18; m++)
										{
											if (clsHandCardData.value_aHandCardList[m] > 0)
											{
												clsHandCardData.value_aHandCardList[m] -= 1;
												HandCardValue tmpHandCardValue = get_HandCardValue(clsHandCardData);
												//ѡȡ��Ȩֵ-�ִ�*7ֵ��ߵĲ���  ��Ϊ������Ϊʣ���������Ҫn�ο��ֵĻ�����ܳ��꣬���ִ����ͺܴ���ը���� ����-7�ļ�ֵҲ��Ϊ��  
												if ((BestHandCardValue.SumValue - (BestHandCardValue.NeedRound * 7)) <= (tmpHandCardValue.SumValue - (tmpHandCardValue.NeedRound * 7)))
												{
													BestHandCardValue = tmpHandCardValue;
													BestMaxCard = end_i;
													tmp_1 = j;
													tmp_2 = k;
													tmp_3 = l;
													tmp_4 = m;
													PutCards = true;
												}
												clsHandCardData.value_aHandCardList[m] += 1;
											}
										}
										clsHandCardData.value_aHandCardList[l] += 1;
									}
								}
								clsHandCardData.value_aHandCardList[k] += 1;
							}
						}
						clsHandCardData.value_aHandCardList[j] += 1;
					}


				}
			}

			for (int j = start_i; j <= end_i; j++)
			{
				clsHandCardData.value_aHandCardList[j] += 3;
			}
			clsHandCardData.nHandCardCount += clsGameSituation.uctNowCardGroup.nCount;
		}
	}

	if (PutCards)
	{
		for (int j = start_i; j <= end_i; j++)
		{
			clsHandCardData.value_nPutCardList.push_back(j);
			clsHandCardData.value_nPutCardList.push_back(j);
			clsHandCardData.value_nPutCardList.push_back(j);
		}

		if (length == 2)
		{
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_2);
		}
		if (length == 3)
		{
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_2);
			clsHandCardData.value_nPutCardList.push_back(tmp_3);

		}
		if (length == 4)
		{
			clsHandCardData.value_nPutCardList.push_back(tmp_1);
			clsHandCardData.value_nPutCardList.push_back(tmp_2);
			clsHandCardData.value_nPutCardList.push_back(tmp_3);
			clsHandCardData.value_nPutCardList.push_back(tmp_4);
		}

		clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgTHREE_TAKE_ONE_LINE, BestMaxCard, clsGameSituation.uctNowCardGroup.nCount);
		return;
	}

	��ҿ��Կ����һ��ݵĴ���ʽ��֮ǰ�Ĳ�һ���ˣ���Ϊ�ɻ����ͺ��п��ܰѶ��Ƶ����������ƴ������������Բ�ը��������ÿ��ѭ���ڵ�ȷ����һ������ȴ���value_aHandCardList״̬������Ҳ��԰�ȫ����һ�������Ĵ���������Ҳ���ᵽ���ⷽ�档


		�ɻ��������ƣ����������Ǳ������ƣ����Բ�����4���ɻ����������Ϊ4���ɻ����ԵĻ�����20�����ˡ�ֻ����2����3���Ϳ����ˡ�





		�����˵һ��ը�������ը���������ˣ��Ҹ��Ĳ��Ծ��ǡ�����������������������

		ֱ��ըѾ�ģ���Ҫ�ˣ���



		[cpp] view plain copy
	else if (clsGameSituation.uctNowCardGroup.cgType == cgBOMB_CARD)
	{
		//�����ը����������ֱ��ը�������ǲ�ֺ������Ϊ������  
		for (int i = clsGameSituation.uctNowCardGroup.nMaxCard + 1; i < 16; i++)
		{
			if (clsHandCardData.value_aHandCardList[i] == 4)
			{
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);
				clsHandCardData.value_nPutCardList.push_back(i);

				clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgBOMB_CARD, i, 4);

				return;
			}
		}
		//��ը  
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{

			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

			return;
		}
		//�ܲ���
	return color_PutCard;
}