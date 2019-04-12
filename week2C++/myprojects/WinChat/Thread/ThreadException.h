#ifndef THREADEXCEPTION_H
#define THREADEXCEPTION_H

#include <exception>
#include <windows.h>


namespace ThreadLib
{

	enum Error
	{
		Unspecified,                // 未定义错误
		InitFailure,                // 线程库没有初始化
		CreationFailure             // 线程不可以被创建
	};


	class Exception : public std::exception//异常
	{
	public:
		Exception(Error p_error = Unspecified)
		{
			m_error = p_error;
		}

		Error GetError() const //获得异常
		{
			return m_error;
		}

	protected:
		Error m_error;
	};
}

#endif
