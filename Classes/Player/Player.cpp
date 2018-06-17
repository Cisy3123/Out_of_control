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
void Player::call()//叫地主
{

}


//输入要判断的vector，返回牌型组合数据结构
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


	//单牌类型  
	if (nCount == 1)
	{
		//用于验证的变量  
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
	//对牌类型  
	if (nCount == 2)
	{
		//用于验证的变量  
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
	//三不带 
	if (nCount == 3)
	{
		//用于验证的变量  
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
	//三带一单  
	if (nCount == 4)
	{
		//用于验证的变量  
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
	//三带一对  
	if (nCount == 5)
	{
		//用于验证的变量  
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
	//四带两单  
	if (nCount == 6)
	{
		//用于验证的变量  
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
	//四带两对  
	if (nCount == 8)
	{
		//用于验证的变量  
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
	//炸弹类型-非王炸
	if (nCount == 4)
	{
		//用于验证的变量  
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
	//王炸类型  
	if (nCount == 2)
	{
		if (CardList[13] > 0 && CardList[14] > 0)
		{
			retCardGroupData.nMaxCard = 14;
			retCardGroupData.cType = KING_CARD;
			return retCardGroupData;
		}
	}
	//单连类型  
	if (nCount >= 5)
	{
		//用于验证的变量  
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
	//对连类型  
	if (nCount >= 6)
	{
		//用于验证的变量  
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
	//飞机不带  
	if (nCount >= 6)
	{
		//用于验证的变量  
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
	//飞机带单牌 
	if (nCount >= 8)
	{
		//用于验证的变量  
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
	//飞机带对子类型  
	if (nCount >= 10)
	{
		//用于验证的变量  
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

//找到对于当前牌的解决方案
void Player::find_Cards(CardGroupData NowCardGroup)
{
	//飞机带单
	//验证顺子的标志 
	int prov = 0;
	//飞机起点  
	int start_i = 0;
	//飞机终点  
	int end_i = 0;
	//飞机长度  
	int length = CardAction.NowCardGroup.nCount / 4;

	int tmp_1 = 0;
	int tmp_2 = 0;
	int tmp_3 = 0;
	int tmp_4 = 0;
	//2与王不参与飞机，从当前已打出的飞机最小牌值+1开始遍历  
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

			/*本来想做全排列选取带出的牌然后枚举出最高价值的，但考虑到当飞机长度也就是在2-4之间
			所以干脆做三个分支处理算了*/
			//为两连飞机  
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

								//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正  
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
			//为三连飞机  
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
										//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正  
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
			//为四连飞机  
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
												//选取总权值-轮次*7值最高的策略  因为我们认为剩余的手牌需要n次控手的机会才能出完，若轮次牌型很大（如炸弹） 则其-7的价值也会为正  
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

	大家可以看到我回溯的处理方式和之前的不一样了，因为飞机类型很有可能把对牌当成两个单牌带出，甚至可以拆炸弹。所以每个循环内当确定了一个点就先处理value_aHandCardList状态，这样也相对安全，上一章中在四带二环节我也有提到过这方面。


		飞机带对类似，而且这里是被动出牌，所以不存在4连飞机的情况，因为4连飞机带对的话就有20张牌了。只考虑2连和3连就可以了。





		最后再说一下炸弹，这个炸弹就厉害了，我给的策略就是————————————

		直接炸丫的！不要怂！！



		[cpp] view plain copy
	else if (clsGameSituation.uctNowCardGroup.cgType == cgBOMB_CARD)
	{
		//更大的炸弹——这里直接炸，不考虑拆分后果。因为信仰。  
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
		//王炸  
		if (clsHandCardData.value_aHandCardList[17] > 0 && clsHandCardData.value_aHandCardList[16] > 0)
		{

			clsHandCardData.value_nPutCardList.push_back(17);
			clsHandCardData.value_nPutCardList.push_back(16);

			clsHandCardData.uctPutCardType = clsGameSituation.uctNowCardGroup = get_GroupData(cgKING_CARD, 17, 2);

			return;
		}
		//管不上
	return color_PutCard;
}