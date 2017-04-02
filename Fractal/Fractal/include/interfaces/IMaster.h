#ifndef _IMASTER_H
#define _IMASTER_H

namespace fractal {
	///For "I" classes use to sort data using muti inherit
	class IMaster
	{
	public:
		IMaster();
		virtual ~IMaster();
		inline void setActive(bool active) {
			m_isActive = active;
		}
		inline bool getActive() const {
			return m_isActive;
		}

	private:
		bool m_isActive;
	};
}

#endif