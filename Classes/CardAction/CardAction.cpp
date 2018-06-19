#include"CardAction.h"
#include"Poker.h"
#include"Player.h"
#include<time.h> 
#include<stdlib.h>
#include<vector>
#include<algorithm>
USING_NS_CC;

CardAction::CardAction();
CardAction::~CardAction();

CardAction::CardAction()
{

}

CardAction::~CardAction()
{

}

bool CardAction::shuffle()//随机洗牌
{
	bool isRet = false;
	do
	{
		for (int i = 0; i<54; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPokers->randomObject();
			Poker* pk2 = (Poker*)m_arrPokers->randomObject();
			m_arrPokers->exchangeObject(pk1, pk2);
		}
		isRet = true;
	} while (0);
	return isRet;
};

void CardAction::deal()//发牌
{
	Poker* pk;
	if (m_iSendPk<51 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		if (m_iSendPk % 3 == 0)//给玩家1发牌
			MovePk(m_player1, pk);
		else if (m_iSendPk % 3 == 1)//给玩家2发牌
			MovePk(m_player2, pk);
		else if (m_iSendPk % 3 == 2)//给玩家3发牌
			MovePk(m_player3, pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if (m_iSendPk>50 && m_iSendPk<54 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		pk->showFront();
		MovePk(m_Three, pk);
		++m_iSendPk;
		m_isSend = false;
	}
	else if (m_iSendPk>53)
	{
		FenChaiNpcPai(m_npcOne);
		FenChaiNpcPai(m_npcTwo);
		m_iSendPk = 0;
		m_iState = 1;
	}
}

bool cmp(int a, int b)
{
	int i = (a / 13)<4 ? a % 13 : a - 39;
	int j = (b / 13)<4 ? b % 13 : b - 39;
	return a>b;
}

void CardAction::Sort(vector<int> &arr)//整理牌
{
	sort(arr.begin(), arr.end(), cmp);
}

//输入要判断的vector，返回牌型组合数据结构
CardGroupData CardAction::CardsType(vector<int> Card)
{
	int CardList[15] = { 0 };
	for (vector<int>::iterator iter = Card.begin(); iter != Card.end(); iter++)
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

void CardAction::changeNowCard()
{
	NowCardGroup.cType = PutCardType.cType;
	NowCardGroup.nCount = PutCardType.nCount;
	NowCardGroup.nMaxCard = PutCardType.nMaxCard;
}

void CardAction::ClearPutCard()//出牌后，清空原选中的牌
{
	color_PutCard.clear();
}

void CardAction::Arrange()//整理现有手牌
{
	Sort(color_CardList);
	CardCount = color_CardList.size();
}

void CardAction::getCardList()
{
	for (vector<int>::iterator iter = color_CardList.begin(); iter != color_CardList.end(); iter++)
	{
		int i = (*iter / 13) < 4 ? *iter % 13 : *iter - 39;
		HandCardList[i]++;
	}
}

void CardAction::copyTOtemp()//copy场上牌到temp
{
	for (vector<int>::iterator iter = NowCard.begin(); iter != NowCard.end(); iter++)
		temp.push_back(*iter);
}

bool CardAction::find_Cards()//根据temp给出不同的提示
{
	CardGroupData tempCardGroup= CardsType(vector<int> temp);
	if (tempCardGroup.cType = SINGLE_CARD)//单牌
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 15; i++)
		{
			if (HandCardList[i] > 0)
			{
				temp.clear();
				temp.push_back(i);
				return true;
			}
		}
	}
	else if (tempCardGroup.cType = DOUBLE_CARD)//对子
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 15; i++)
		{
			if (HandCardList[i] > 1)
			{
				temp.clear();
				temp.push_back(i);
				temp.push_back(i);
				return true;
			}
		}
	}
	else if (tempCardGroup.cType = THREE_CARD)//三不带
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 12; i++)
		{
			if (HandCardList[i] > 2)
			{
				temp.clear();
				temp.push_back(i);
				temp.push_back(i);
				temp.push_back(i);
				return true;
			}
		}
	}
	else if (tempCardGroup.cType = BOMB_CARD)//炸弹-非王炸
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (tempHandCardList[i] == 4)
			{
				temp.clear();
				temp.push_back(i);
				temp.push_back(i);
				temp.push_back(i);
				temp.push_back(i);
				return true;
			}
		}
	}
	else if (tempCardGroup.cType = THREE_ONE_CARD)//三带一
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] > 2)
			{
				for (int j = 0; j < 15; j++)
				{
					//选出一张以上的牌且不是选择三张的那个牌  
					if (HandCardList[j] > 0 && j != i)
					{
						temp.clear();
						temp.push_back(i);
						temp.push_back(i);
						temp.push_back(i);
						temp.push_back(j);
						return true;
					}
				}
			}
		}
	}
	else if (tempCardGroup.cType = THREE_TWO_CARD)//三带对
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] > 2)
			{
				for (int j = 0; j < 13; j++)
				{
					//选出一张以上的牌且不是选择三张的那个牌  
					if (HandCardList[j] > 1 && j != i)
					{
						temp.clear();
						temp.push_back(i);
						temp.push_back(i);
						temp.push_back(i);
						temp.push_back(j);
						temp.push_back(j);
						return true;
					}
				}
			}
		}
	}
	else if (tempCardGroup.cType = BOMB_TWO_CARD)//四带两单
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] == 4)
			{
				for (int j = 0; j < 15; j++)
				{
					//先选出一张以上的牌且不是选择四张的那个牌  
					if (HandCardList[j] > 0 && j != i)
					{
						//再选出一张以上的牌且不是选择四张的那个牌且不是第一次选的那个牌（策略里四带二不带一对）  
						for (int k = j + 1; k < 15; k++)
						{
							if (HandCardList[k] > 0 && k != i)
							{
								temp.clear();
								temp.push_back(i);
								temp.push_back(i);
								temp.push_back(i);
								temp.push_back(i);
								temp.push_back(j);
								temp.push_back(k);
								return true;
							}
						}
					}
				}
			}
		}
	}
	else if (tempCardGroup.cType = BOMB_TWOOO_CARD)//四带两对
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] == 4)
			{
				for (int j = 0; j < 15; j++)
				{
					//先选出两张以上的牌且不是选择四张的那个牌  
					if (HandCardList[j] > 1 && j != i)
					{
						//再选出两张张以上的牌且不是选择四张的那个牌且不是第一次选的那个牌  
						for (int k = j + 1; k < 15; k++)
						{
							if (HandCardList[k] > 1 && k != i)
							{
								temp.clear();
								temp.push_back(i);
								temp.push_back(i);
								temp.push_back(i);
								temp.push_back(i);
								temp.push_back(j);
								temp.push_back(j);
								temp.push_back(k);
								temp.push_back(k);
								return true;
							}
						}
					}
				}
			}
		}
	}
	else if (tempCardGroup.cType = CONNECT_CARD)//单连
	{
		int prov = 0;//用于验证的变量
		int start;
		int end;   //记录开始与结束
		int length = tempCardGroup.nCount;//单连长度
		for (int i = tempCardGroup.nMaxCard - length + 2; i < 12; i++)
		{
			if (HandCardList[i] > 0)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov == length)
			{
				end = i;
				start = i - length + 1;
				temp.clear();
				for (int j = start; j <= end; j++)
				{
					temp.push_back(j);
				}
				return true;
			}
		}
	}
	else if (tempCardGroup.cType = COMPANY_CARD)//连队
	{
		int prov = 0;//用于验证的变量
		int start;
		int end;
		int length = tempCardGroup.nCount/2;//单连长度
		//2与王不参与飞机，从当前已打出的飞机最小牌值+1开始遍历  
		for (int i = tempCardGroup.nMaxCard - length + 2; i < 12; i++)
		{
			if (HandCardList[i] > 1)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov == length)
			{
				end = i;
				start = i - length + 1;
				temp.clear();
				for (int j = start; j <= end; j++)
				{
					temp.push_back(j);
					temp.push_back(j);
				}
				return true;
			}
		}
				
	}
	else if (tempCardGroup.cType = AIRCRAFT_CARD)//飞机不带
	{
		int prov = 0;  
		int start_i = 0;//飞机起点
		int end_i = 0;//飞机终点
		int length = clsGameSituation.uctNowCardGroup.nCount / 3;//飞机长度  
		//2与王不参与飞机，从当前已打出的飞机最小牌值+1开始遍历  
		for (int i = tempCardGroup.nMaxCard - length + 2; i < 12; i++)
		{
			if (HandCardList[i] > 2)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov == length)
			{
				end_i = i;
				start_i = i - length + 1;
				temp.clear();
				for (int j = start_i; j <= end_i; j++)
				{
					temp.push_back(j);
					temp.push_back(j);
					temp.push_back(j);
				}
				return true;
			}
		}
	}
	else if (tempCardGroup.cType = AIRCRAFT_SINGLE_CARD)//飞机带单牌
	{
		//验证飞机的标志  
		int prov = 0;
		//飞机起点  
		int start_i = 0;
		//飞机终点  
		int end_i = 0;
		//飞机长度  
		int length = clsGameSituation.uctNowCardGroup.nCount / 4;
		//2与王不参与飞机，从当前已打出的飞机最小牌值+1开始遍历  
		for (int i = tempCardGroup.nMaxCard - length + 2; i < 12; i++)
		{
			if (HandCardList[i] > 2)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov == length)
			{
				end_i = i;
				start_i = i - length + 1;
				//考虑到当飞机长度也就是在2-4之间，所以做三个分支处理
				//为两连飞机  
				if (length == 2)
				{
					for (int j = 0; j < 15; j++)
					{
						if (HandCardList[j] > 0)
						{
							for (int k = 0; k < 15; k++)
							{
								if (HandCardList[k] > 0)
								{
									temp.clear();
									for (int l = start_i; l <= end_i; l++)
									{
										temp.push_back(l);
										temp.push_back(l);
										temp.push_back(l);
									}
									temp.push_back(j);
									temp.push_back(k);
									return true;
								}
							}
						}
					}
				}
				//为三连飞机
				if (length == 3)
				{
					for (int j = 0; j < 15; j++)
					{
						if (HandCardList[j] > 0)
						{
							for (int k = 0; k < 15; k++)
							{
								if (HandCardList[k] > 0)
								{
									for (int l = 0; l < 15; l++)
									{
										if (HandCardList[l] > 0)
										{
											temp.clear();
											for (int m = start_i; m <= end_i; m++)
											{
												temp.push_back(m);
												temp.push_back(m);
												temp.push_back(m);
											}
											temp.push_back(j);
											temp.push_back(k);
											temp.push_back(l);
											return true;
										}
									}
								}
							}
						}
					}
				}
				//为四连飞机
				if (length == 4)
				{
					for (int j = 0; j < 15; j++)
					{
						if (HandCardList[j] > 0)
						{
							for (int k = 0; k < 15; k++)
							{
								if (HandCardList[k] > 0)
								{
									for (int l = 0; l < 15; l++)
									{
										if (HandCardList[l] > 0)
										{
											for (int m = 3; m < 18; m++)
											{
												if (HandCardList[m] > 0)
												{
													temp.clear();
													for (int n = start_i; n <= end_i; n++)
													{
														temp.push_back(n);
														temp.push_back(n);
														temp.push_back(n);
													}
													temp.push_back(j);
													temp.push_back(k);
													temp.push_back(l);
													temp.push_back(m);
													return true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (tempCardGroup.cType = AIRCRAFT_DOUBLE_CARD)//飞机带对子
	{

		//验证飞机的标志  
		int prov = 0;
		//飞机起点  
		int start_i = 0;
		//飞机终点  
		int end_i = 0;
		//飞机长度  
		int length = clsGameSituation.uctNowCardGroup.nCount / 4;
		//2与王不参与飞机，从当前已打出的飞机最小牌值+1开始遍历  
		for (int i = tempCardGroup.nMaxCard - length + 2; i < 12; i++)
		{
			if (HandCardList[i] > 2)
			{
				prov++;
			}
			else
			{
				prov = 0;
			}
			if (prov == length)
			{
				end_i = i;
				start_i = i - length + 1;
				//考虑到当飞机长度也就是在2-3之间，所以做两个分支处理
				//为两连飞机  
				if (length == 2)
				{
					for (int j = 0; j < 15; j++)
					{
						if (HandCardList[j] > 1)
						{
							for (int k = 0; k < 15; k++)
							{
								if (HandCardList[k] > 1)
								{
									temp.clear();
									for (int l = start_i; l <= end_i; l++)
									{
										temp.push_back(l);
										temp.push_back(l);
										temp.push_back(l);
									}
									temp.push_back(j);
									temp.push_back(j);
									temp.push_back(k);
									temp.push_back(k);
									return true;
								}
							}
						}
					}
				}
				//为三连飞机
				if (length == 3)
				{
					for (int j = 0; j < 15; j++)
					{
						if (HandCardList[j] > 1)
						{
							for (int k = 0; k < 15; k++)
							{
								if (HandCardList[k] > 1)
								{
									for (int l = 0; l < 15; l++)
									{
										if (HandCardList[l] > 1)
										{
											temp.clear();
											for (int m = start_i; m <= end_i; m++)
											{
												temp.push_back(m);
												temp.push_back(m);
												temp.push_back(m);
											}
											temp.push_back(j);
											temp.push_back(j);
											temp.push_back(k);
											temp.push_back(k);
											temp.push_back(l);
											temp.push_back(l);
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//直接出炸弹
	else if (tempCardGroup.cType != BOMB_CARD && tempCardGroup.cType != KING_CARD)
	{
		for (int i = 0; i < 13; i++)
		{
			if (HandCardList[i] == 4)
			{
				temp.clear();
				temp.push_back(i);
				temp.push_back(i);
				temp.push_back(i);
				temp.push_back(i);
				return true;
			}
		}
	}
	return false;
}

//点击提示就copy场上牌，调用find_Cards函数，把temp传递到PutCard,如果继续点提示，就再次调用find_Cards函数，把temp传递到PutCard
void CardAction::tempTOput()
{
	for (vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
		color_PutCard.push_back(*iter);
}
