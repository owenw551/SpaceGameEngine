//#pragma once
//#include "Components.h"
//#include <iostream>
//#include <cmath>
//
//
//
//	******************
//  *NO LONGER IN USE*
//  ******************
//	Used to be a child of the transform component that caused an entity to follow the player
//
//
//class TransformCFollower : public TransformComponent
//{
//private:
//	TransformComponent *follower;
//
//public:
//	TransformCFollower(TransformComponent& followee)
//		: TransformComponent(500.0f , 500.0f, 32, 32, 1)
//	{
//		std::cout << "TransformCFollower Created" << std::endl;
//		follower = &followee;
//	}
//
//	void update() override
//	{
//
//
//		if (std::abs(follower->getx() - position.getx()) > 30.0f)
//		{
//			if (follower->getx() > position.getx())
//			{
//				velocity.setx(0.7f);
//			}
//			else
//			{
//				velocity.setx(-0.7f);
//			}
//		}
//		else
//		{
//			velocity.setx(0);
//		}
//
//		if (std::abs(follower->gety() - position.gety()) > 30.0f)
//		{
//			if (follower->gety() > position.gety())
//			{
//				velocity.sety(0.7f);
//			}
//			else
//			{
//				velocity.sety(-0.7f);
//			}
//		}
//		else
//		{
//			velocity.sety(0);
//		}
//		position += velocity;
//		
//	}
//	
//
//};