/*
 * Generated using zcbor version 0.3.99
 * https://github.com/NordicSemiconductor/zcbor
 * Generated with a --default-max-qty of 3
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "zcbor_encode.h"
#include "serializer_pet_encode.h"

#if DEFAULT_MAX_QTY != 3
#error "The type file was generated with a different default_max_qty than this file"
#endif


static bool encode_Pet(
		zcbor_state_t *state, const struct Pet *input)
{
	zcbor_print("%s\r\n", __func__);

	bool tmp_result = (((zcbor_list_start_encode(state, 3) && ((((zcbor_list_start_encode(state, 3) && ((zcbor_multi_encode_minmax(1, 3, &(*input)._Pet_name_tstr_count, (zcbor_encoder_t *)zcbor_tstr_encode, state, (&(*input)._Pet_name_tstr), sizeof(struct zcbor_string))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 3)))
	&& (((((((*input)._Pet_birthday.len >= 8)
	&& ((*input)._Pet_birthday.len <= 8)) || (zcbor_error(state, ZCBOR_ERR_WRONG_RANGE), false))) || (zcbor_error(state, ZCBOR_ERR_WRONG_RANGE), false))
	&& (zcbor_bstr_encode(state, (&(*input)._Pet_birthday))))
	&& ((((*input)._Pet_species_choice == _Pet_species_cat) ? ((zcbor_uint32_put(state, (1))))
	: (((*input)._Pet_species_choice == _Pet_species_dog) ? ((zcbor_uint32_put(state, (2))))
	: (((*input)._Pet_species_choice == _Pet_species_other) ? ((zcbor_uint32_put(state, (3))))
	: false))))) || (zcbor_list_map_end_force_encode(state), false)) && zcbor_list_end_encode(state, 3))));

	if (!tmp_result)
		zcbor_trace();

	return tmp_result;
}



uint_fast8_t cbor_encode_Pet(
		uint8_t *payload, size_t payload_len,
		const struct Pet *input,
		size_t *payload_len_out)
{
	zcbor_state_t states[4];

	zcbor_new_state(states, sizeof(states) / sizeof(zcbor_state_t), payload, payload_len, 1);

	bool ret = encode_Pet(states, input);

	if (ret && (payload_len_out != NULL)) {
		*payload_len_out = MIN(payload_len,
				(size_t)states[0].payload - (size_t)payload);
	}

	if (!ret) {
		uint_fast8_t ret = zcbor_pop_error(states);
		return (ret == ZCBOR_SUCCESS) ? ZCBOR_ERR_UNKNOWN : ret;
	}
	return ZCBOR_SUCCESS;
}
