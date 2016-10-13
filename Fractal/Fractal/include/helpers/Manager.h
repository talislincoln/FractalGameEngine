#ifndef _MANAGER_H
#define _MANAGER_H

namespace fractal {
	class Manager
	{
	public:
		Manager() {}
		virtual ~Manager() {}

		virtual bool initialize() = 0;
		virtual bool shutdown() = 0;
	};
}


#endif //_MANAGER_H