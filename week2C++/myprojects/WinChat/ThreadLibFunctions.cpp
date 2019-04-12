
#include "ThreadLib.h"

namespace ThreadLib
{
#ifdef WIN32
	std::map< DWORD, HANDLE > g_handlemap;
#endif

#ifdef WIN32
	DWORD WINAPI DummyRun(void* p_data)
#else
	void* DummyRun(void* p_data)
#endif
	{
		DummyData* data = (DummyData*)p_data;

		data->m_func(data->m_data);

		delete data;

		return 0;
	}


}
