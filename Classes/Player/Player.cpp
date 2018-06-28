#pragma once
#include<iostream>
#include<vector>
#include"CardSet.h"
#include"CardAction.h"
#include"Player.h"
using namespace std;

Player::Player() 
{
	m_isLord = false;
	m_isCall = false;
	m_isOutPk=false;

	m_arrPk = CCArray::create();
	m_arrPk->retain();
}
Player::~Player()
{

}