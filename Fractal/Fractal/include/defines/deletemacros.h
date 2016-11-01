#ifndef _DELETEMACRO_H
#define _DELETEMACRO_H

	//Defines
	#define SafeDelete(x) { if(x) {delete x; x = nullptr;} } // Macro for deleting objects

#endif