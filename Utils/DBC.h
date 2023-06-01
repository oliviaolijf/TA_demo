//
// Created by Jonat on 26/05/2023.
//

#ifndef TOG_T_O_GROEPJE_18_DBC_H
#define TOG_T_O_GROEPJE_18_DBC_H

#include <assert.h>

#define REQUIRE(assertion, what) \
	if (!(assertion)) _assert (what, __FILE__, __LINE__)

#define ENSURE(assertion, what) \
	if (!(assertion)) _assert (what, __FILE__, __LINE__)

#endif //TOG_T_O_GROEPJE_18_DBC_H
