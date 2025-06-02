#pragma once

#define GET_SINGLE(classname)	classname::GetInstance()

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}

#ifdef _DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif