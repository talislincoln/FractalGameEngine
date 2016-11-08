#pragma once
#include "Transform.h"
namespace fractal {

	class Object
	{
	public:
		Object();
		virtual ~Object();
		virtual void update(float deltaTime) = 0;
		virtual void init() = 0;
		virtual void onCreate() = 0;
		virtual void onDestory() = 0;
	};

}