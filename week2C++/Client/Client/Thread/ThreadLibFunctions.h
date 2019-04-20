#ifndef THREADLIBFUNCTIONS_H
#define THREADLIBFUNCTIONS_H

#include <windows.h>
#include <map>

#include "ThreadException.h"

namespace ThreadLib
{
	typedef void(*ThreadFunc)(void*);

	typedef DWORD ThreadID;
	extern std::map< DWORD, HANDLE > g_handlemap;

	class DummyData //虚拟函数系统
	{
	public:
		ThreadFunc m_func;
		void* m_data;
	};

	DWORD WINAPI DummyRun(void* p_data);

	inline ThreadID Create(ThreadFunc p_func, void* p_param)
	{
		ThreadID t;
		DummyData* data = new DummyData;
		data->m_func = p_func;
		data->m_data = p_param;
 
		HANDLE h;
		h = CreateThread(NULL, 0, DummyRun, data, 0, &t);
		if (h != 0)
		{
			g_handlemap[t] = h;//加入线程映射
		}

		if (t == 0)
		{
			delete data;
			throw Exception(CreationFailure);
		}
		return t;
	}

	inline ThreadID GetID() //获得线程ID
	{
		return GetCurrentThreadId();
	}


	inline void WaitForFinish(ThreadID p_thread) //等待p_thread线程完成
	{
		WaitForSingleObject(g_handlemap[p_thread], INFINITE);
		CloseHandle(g_handlemap[p_thread]);
		g_handlemap.erase(p_thread);
	}

	inline void Kill(ThreadID& p_thread) //杀死线程
	{
		TerminateThread(g_handlemap[p_thread], 0);
		CloseHandle(g_handlemap[p_thread]);
		g_handlemap.erase(p_thread);
	}

	inline void YieldThread(int p_milliseconds = 1) //等待
	{
		Sleep(p_milliseconds);
	}
}

#endif