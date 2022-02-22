#pragma once

#define require(condition)                                                                 \
	do {                                                                                   \
		if (!(condition)) {                                                                \
			printf("file %s on line %d\n\tfailed '%s'\n", __FILE__, __LINE__, #condition); \
			return 1;                                                                      \
		}                                                                                  \
	} while (false)
