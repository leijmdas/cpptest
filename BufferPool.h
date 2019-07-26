#pragma once
#include <map>

typedef std::map <void*,void*> TMapContainer;

class CBufferPool
{
public:
	CBufferPool(void);
public:
	~CBufferPool(void);
	static TMapContainer & getMapContainer()
	{
		static TMapContainer mapContainer;
		return mapContainer;
	};
};
