#pragma once

/**
 * \brief 事件
 */
enum Transition
{
	NONE, // 无任何事件
	EXPLORE, // 探索副本
	WAITING,	//  等待
};

/**
 * \brief 状态
 */
enum ExploreStatus
{
	WAIT_FOR_EXPLORE_CLICK,
};



