/*
*
*	AcceleratorEngine - libace
*
*/
#include "libace.h"

namespace ace {

Ace::Ace() {

}

Ace* Ace::getInstance() {
	static Ace instance;
	return &instance;
}

}