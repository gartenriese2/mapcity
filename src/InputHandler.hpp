#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <mutex>
#include "glm.h"

class InputHandler {
	
	public:
		
		static InputHandler& instance();

		void addQuery(const glm::vec3 &);
		glm::vec3 getQuery();
		bool hasNewQuery() const;

	protected:
		
		static InputHandler* pInstance;

		friend class Cleanup;
		class Cleanup {
			public:
				~Cleanup();
		};
		
	private:

		InputHandler();
		virtual ~InputHandler();
		InputHandler(const InputHandler&);
		InputHandler& operator=(const InputHandler&);
		static std::mutex sMutex;

		glm::vec3 m_query;
		bool m_newQuery = false;
		
	
};

#endif