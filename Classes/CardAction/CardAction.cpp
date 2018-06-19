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

bool CardAction::shuffle()//���ϴ��
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

void CardAction::deal()//����
{
	Poker* pk;
	if (m_iSendPk<51 && m_isSend)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk);
		if (m_iSendPk % 3 == 0)//�����1����
			MovePk(m_player1, pk);
		else if (m_iSendPk % 3 == 1)//�����2����
			MovePk(m_player2, pk);
		else if (m_iSendPk % 3 == 2)//�����3����
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

void CardAction::Sort(vector<int> &arr)//������
{
	sort(arr.begin(), arr.end(), cmp);
}

//����Ҫ�жϵ�vector����������������ݽṹ
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

void CardAction::changeNowCard()
{
	NowCardGroup.cType = PutCardType.cType;
	NowCardGroup.nCount = PutCardType.nCount;
	NowCardGroup.nMaxCard = PutCardType.nMaxCard;
}

void CardAction::ClearPutCard()//���ƺ����ԭѡ�е���
{
	color_PutCard.clear();
}

void CardAction::Arrange()//������������
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

void CardAction::copyTOtemp()//copy�����Ƶ�temp
{
	for (vector<int>::iterator iter = NowCard.begin(); iter != NowCard.end(); iter++)
		temp.push_back(*iter);
}

bool CardAction::find_Cards()//����temp������ͬ����ʾ
{
	CardGroupData tempCardGroup= CardsType(vector<int> temp);
	if (tempCardGroup.cType = SINGLE_CARD)//����
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
	else if (tempCardGroup.cType = DOUBLE_CARD)//����
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
	else if (tempCardGroup.cType = THREE_CARD)//������
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
	else if (tempCardGroup.cType = BOMB_CARD)//ը��-����ը
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
	else if (tempCardGroup.cType = THREE_ONE_CARD)//����һ
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] > 2)
			{
				for (int j = 0; j < 15; j++)
				{
					//ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ���  
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
	else if (tempCardGroup.cType = THREE_TWO_CARD)//������
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] > 2)
			{
				for (int j = 0; j < 13; j++)
				{
					//ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ���  
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
	else if (tempCardGroup.cType = BOMB_TWO_CARD)//�Ĵ�����
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] == 4)
			{
				for (int j = 0; j < 15; j++)
				{
					//��ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ���  
					if (HandCardList[j] > 0 && j != i)
					{
						//��ѡ��һ�����ϵ����Ҳ���ѡ�����ŵ��Ǹ����Ҳ��ǵ�һ��ѡ���Ǹ��ƣ��������Ĵ�������һ�ԣ�  
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
	else if (tempCardGroup.cType = BOMB_TWOOO_CARD)//�Ĵ�����
	{
		for (int i = tempCardGroup.nMaxCard + 1; i < 13; i++)
		{
			if (HandCardList[i] == 4)
			{
				for (int j = 0; j < 15; j++)
				{
					//��ѡ���������ϵ����Ҳ���ѡ�����ŵ��Ǹ���  
					if (HandCardList[j] > 1 && j != i)
					{
						//��ѡ�����������ϵ����Ҳ���ѡ�����ŵ��Ǹ����Ҳ��ǵ�һ��ѡ���Ǹ���  
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
	else if (tempCardGroup.cType = CONNECT_CARD)//����
	{
		int prov = 0;//������֤�ı���
		int start;
		int end;   //��¼��ʼ�����
		int length = tempCardGroup.nCount;//��������
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
	else if (tempCardGroup.cType = COMPANY_CARD)//����
	{
		int prov = 0;//������֤�ı���
		int start;
		int end;
		int length = tempCardGroup.nCount/2;//��������
		//2����������ɻ����ӵ�ǰ�Ѵ���ķɻ���С��ֵ+1��ʼ����  
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
	else if (tempCardGroup.cType = AIRCRAFT_CARD)//�ɻ�����
	{
		int prov = 0;  
		int start_i = 0;//�ɻ����
		int end_i = 0;//�ɻ��յ�
		int length = clsGameSituation.uctNowCardGroup.nCount / 3;//�ɻ�����  
		//2����������ɻ����ӵ�ǰ�Ѵ���ķɻ���С��ֵ+1��ʼ����  
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
	else if (tempCardGroup.cType = AIRCRAFT_SINGLE_CARD)//�ɻ�������
	{
		//��֤�ɻ��ı�־  
		int prov = 0;
		//�ɻ����  
		int start_i = 0;
		//�ɻ��յ�  
		int end_i = 0;
		//�ɻ�����  
		int length = clsGameSituation.uctNowCardGroup.nCount / 4;
		//2����������ɻ����ӵ�ǰ�Ѵ���ķɻ���С��ֵ+1��ʼ����  
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
				//���ǵ����ɻ�����Ҳ������2-4֮�䣬������������֧����
				//Ϊ�����ɻ�  
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
				//Ϊ�����ɻ�
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
				//Ϊ�����ɻ�
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
	else if (tempCardGroup.cType = AIRCRAFT_DOUBLE_CARD)//�ɻ�������
	{

		//��֤�ɻ��ı�־  
		int prov = 0;
		//�ɻ����  
		int start_i = 0;
		//�ɻ��յ�  
		int end_i = 0;
		//�ɻ�����  
		int length = clsGameSituation.uctNowCardGroup.nCount / 4;
		//2����������ɻ����ӵ�ǰ�Ѵ���ķɻ���С��ֵ+1��ʼ����  
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
				//���ǵ����ɻ�����Ҳ������2-3֮�䣬������������֧����
				//Ϊ�����ɻ�  
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
				//Ϊ�����ɻ�
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
	//ֱ�ӳ�ը��
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

//�����ʾ��copy�����ƣ�����find_Cards��������temp���ݵ�PutCard,�����������ʾ�����ٴε���find_Cards��������temp���ݵ�PutCard
void CardAction::tempTOput()
{
	for (vector<int>::iterator iter = temp.begin(); iter != temp.end(); iter++)
		color_PutCard.push_back(*iter);
}
