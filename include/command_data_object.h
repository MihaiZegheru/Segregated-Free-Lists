#ifndef COMMAND_DATA_OBJECT_H__
#define COMMAND_DATA_OBJECT_H__

#include <inttypes.h>

#include <command_type.h>

#define CDO_IH_PARAMS (4 + 1)
#define CDO_M_PARAMS  (1 + 1)
#define CDO_F_PARAMS  (1 + 1)
#define CDO_R_PARAMS  (2 + 1)
#define CDO_W_PARAMS  (3 + 1)
#define CDO_DM_PARAMS (0 + 1)
#define CDO_DH_PARAMS (0 + 1)

inline size_t cdo_get_number_of_params(e_command_type_t command_type) {
	switch (command_type) {
	case CT_INIT_HEAP:
		return CDO_IH_PARAMS;
	case CT_MALLOC:
		return CDO_M_PARAMS;
	case CT_FREE:
		return CDO_F_PARAMS;
	case CT_READ:
		return CDO_R_PARAMS;
	case CT_WRITE:
		return CDO_W_PARAMS;
	case CT_DUMP_MEMORY:
		return CDO_DM_PARAMS;
	case CT_DESTROY_HEAP:
		return CDO_DH_PARAMS;
	default:
		break;
	}
}

#endif // COMMAND_DATA_OBJECT_H__