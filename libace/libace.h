/*
*
*	AcceleratorEngine - libace
*
*/
#ifndef LIBACE_H
#define LIBACE_H

namespace ace {

/**
*	@class Ace
*
*	@brief Singleton class which represents the whole engine.
*/
class Ace {

private: 

    Ace();
    Ace( const Ace& ) {};

public:

	/**
	* @brief Starting point: returns the singleton engine instance.
	*/
	static Ace* getInstance();

};

}

#endif // LIBACE_H