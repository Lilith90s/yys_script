#pragma once

/**
 * \brief 事件
 */

namespace transition
{
	enum Transition
	{
		NONE, // 无任何事件
		EXPLORE, // 探索副本
		WAITING,	//  等待
	};
}




/**
 * \brief 状态
 */
namespace explore
{
	enum Explore
	{
		NONE,						// 错误状态
		WAIT_FOR_CHAPTER_CLICK,		// 等待点击章节
		WAIT_FOR_EXPLORE_CLICK,		// 查找探索按钮
		FINDING_MONSTER,			// 查找怪
		FINDING_LEADER,				// 查找首领
		IN_CHALLENGING,				// 挑战中
		PICKING_UP_CHEST,			// 捡宝箱
		WALKING,					// 走动
	};
}






