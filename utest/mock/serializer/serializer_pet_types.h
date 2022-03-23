/*
 * Generated using zcbor version 0.3.99
 * https://github.com/NordicSemiconductor/zcbor
 * Generated with a --default-max-qty of 3
 */

#ifndef SERIALIZER_PET_TYPES_H__
#define SERIALIZER_PET_TYPES_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "zcbor_encode.h"

/** Which value for --default-max-qty this file was created with.
 *
 *  The define is used in the other generated file to do a build-time
 *  compatibility check.
 *
 *  See `zcbor --help` for more information about --default-max-qty
 */
#define DEFAULT_MAX_QTY 3

struct Pet {
	struct zcbor_string _Pet_name_tstr[3];
	uint_fast32_t _Pet_name_tstr_count;
	struct zcbor_string _Pet_birthday;
	enum {
		_Pet_species_cat = 1,
		_Pet_species_dog = 2,
		_Pet_species_other = 3,
	} _Pet_species_choice;
};


#endif /* SERIALIZER_PET_TYPES_H__ */
