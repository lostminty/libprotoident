/*
 *
 * Copyright (c) 2011-2016 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libprotoident.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"

static inline bool match_load_42(uint32_t payload, uint32_t len) {
        if (len == 42 && MATCH(payload, 0x60, 0x0a, 0x00, 0x00))
                return true;
        return false;
}

static inline bool match_load_46(uint32_t payload, uint32_t len) {
        if (len == 46 && MATCH(payload, 0x60, 0x0a, 0x00, 0x00))
                return true;
        return false;
}

static inline bool match_loadout(lpi_data_t *data, lpi_module_t *mod UNUSED) {

        if (match_load_42(data->payload[0], data->payload_len[0])) {
                if (match_load_46(data->payload[1], data->payload_len[1]))
                        return true;
        }

        if (match_load_42(data->payload[1], data->payload_len[1])) {
                if (match_load_46(data->payload[0], data->payload_len[0]))
                        return true;
        }

	return false;
}

static lpi_module_t lpi_loadout = {
	LPI_PROTO_UDP_LOADOUT,
	LPI_CATEGORY_GAMING,
	"Loadout",
	60,
	match_loadout
};

void register_loadout(LPIModuleMap *mod_map) {
	register_protocol(&lpi_loadout, mod_map);
}

