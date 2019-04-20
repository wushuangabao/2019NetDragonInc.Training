#ifndef THREADLIBMUTEX_H
#define THREADLIBMUTEX_H

#include <windows.h>
#include <string>

namespace ThreadLib
{
	// 互斥锁
	class Mutex
	{
	public:
		Mutex()
		{
			InitializeCriticalSection(&m_mutex);
		}

		~Mutex()
		{

			DeleteCriticalSection(&m_mutex);
		}

		inline void Lock() //锁住资源
		{
			EnterCriticalSection(&m_mutex);
		}

		inline void Unlock() //释放资源
		{
			LeaveCriticalSection(&m_mutex);
		}

	protected:
		CRITICAL_SECTION m_mutex;
	};


}

#endif
