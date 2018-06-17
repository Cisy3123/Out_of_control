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
void Player::call()//½ÐµØÖ÷
{

}