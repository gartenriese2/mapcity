#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <mutex>
#include <vector>
#include <iostream>
#include "glm.h"

typedef std::vector<std::pair<std::vector<glm::vec3>, int>> zoneVector;

class InputHandler {

	public:
		
		static InputHandler& instance();

		void addQuery(const glm::vec3 &);
		glm::vec3 getQuery();
		bool hasNewQuery() const;

		void addZone(const std::vector<glm::vec3> &, int);
		void addZone(int);
		void addZonePoint(const glm::vec3 &);
		zoneVector getZones();
		bool hasNewZones() const;

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

		zoneVector m_zones;
		std::vector<glm::vec3> m_newZone;
		
	
};

#endif