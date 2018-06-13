#pragma once
#include <vector>
const int CardWidth = 70;//宽
const int CardHeight = 95;//高
const int CardSpace = 20;//距
//花色
enum Suit
{
	spade = 0,
	heart,
	club,
	diamond,
	joker,
};
//面值
enum Value
{
	Three = 3, Four, Five, Six, Seven, Eight, Nine, Ten, J, Q, K, A, Two, jokerBlack, jokerRed,
};
//牌型
enum CARD_TYPE
{
	SINGLE_CARD = 1,    //单牌-
	DOUBLE_CARD,        //对子-
	THREE_CARD,         //3不带-
	BOMB_CARD,          //炸弹
	THREE_ONE_CARD,	    //3带1-
	THREE_TWO_CARD,	    //3带2-
	BOMB_TWO_CARD,      //四个带2张单牌
	BOMB_TWOOO_CARD,    //四个带2对
	CONNECT_CARD,       //连牌-
	COMPANY_CARD,       //连队-
	AIRCRAFT_CARD,       //飞机不带-
	AIRCRAFT_SINGLE_CARD,	//飞机带单牌-
	AIRCRAFT_DOBULE_CARD,	//飞机带对子-
	ERROR_CARD				//错误的牌型
};
struct CRAD_INDEX//分析飞机
{
	std::vector<int> single_index;//单张
	std::vector<int> duble_index;//双张
	std::vector<int> three_index;//三张
	std::vector<int> four_index;//四张
};
