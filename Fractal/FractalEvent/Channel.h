#ifndef _CHANNEL_H
#define _CHANNEL_H

#include <vector>
#include <functional>

namespace fractal {
	namespace fevent {
		/*this class was based on the implementation from GrandMaster at
		http://www.grandmaster.nu/blog/?page_id=191
		*/

		/* The implementation for a template class needs to stay in the header file.
		This happens because whenever the compile finds a new implementation for a template class,
		it will create a new class and can't find the implementations for the methods of that class.
		One solution to this problem is to create a different type of file (.tpp) that would hold
		the implementation for the header file, but include this new file at the end of this header file.
		For more information: http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
		*/
		class Channel
		{
		public:
			template <typename tEvent, typename tHandler>
			static void addHandler(tHandler* handler) {
				InternalChannel<tEvent>::instance().add(handler);
			}

			template <typename tEvent, typename tHandler>
			static void removeHandler(tHandler* handler) {
				InternalChannel<tEvent>::instance().remove(handler);
			}

			template <typename tEvent>
			static void broadcast(const tEvent& evt) {
				InternalChannel<tEvent>::instance().broadcast(evt);
			}

		private:
			template<typename tEvent>
			class InternalChannel {
			public:
				static InternalChannel& instance() {
					static InternalChannel result;
					return result; // return a reference to an internal static
				}

				template <typename tHandler>
				void add(tHandler* handler) {
					m_Handlers.push_back([handler](const tEvent& evt) { (*handler)(evt); });
					m_originalPointers.push_back(handler);
				}

				template <typename tHandler>
				void remove(tHandler* handler) {
					auto it = std::find(m_originalPointers.begin(), m_originalPointers.end(), handler);
					if (it == m_originalPointers.end()) {
						throw  std::runtime_error("Tried to remove a handler that was not in the handler list");
					}

					auto index = (it - m_originalPointers.begin()); //convert iterator to index
					m_Handlers.erase(m_Handlers.begin() + index);
					m_originalPointers.erase(it);
				}

				void broadcast(const tEvent& evt) {
					auto localQueue = m_Handlers;

					for (auto& handler : localQueue)
						handler(evt);
				}

			private:
				InternalChannel() {} // private constructor -- only access through static interface

				typedef std::function<void(const tEvent&)> Handler;
				std::vector<Handler> m_Handlers;
				std::vector<void*> m_originalPointers;
			};
		};
	}
}

#endif // !_CHANNEL_H


