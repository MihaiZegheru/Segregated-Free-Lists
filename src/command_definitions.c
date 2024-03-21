#include <command_definitions.h>

size_t command_definitions_get_number_of_params(e_command_type_t command_type) {
	switch (command_type) {
	case CT_INIT_HEAP:
		return IH_PARAMS;
	case CT_MALLOC:
		return M_PARAMS;
	case CT_FREE:
		return F_PARAMS;
	case CT_READ:
		return R_PARAMS;
	case CT_WRITE:
		return W_PARAMS;
	case CT_DUMP_MEMORY:
		return DM_PARAMS;
	case CT_DESTROY_HEAP:
		return DH_PARAMS;
	default:
		break;
	}

	return 0;
}

e_command_type_t command_definitions_get_command_type(char *name) {
	if (!strcmp(name, IH_STRING)) {
		return CT_INIT_HEAP;
	}
	else if (!strcmp(name, M_STRING)) {
		return CT_MALLOC;
	}
	else if (!strcmp(name, F_STRING)) {
		return CT_FREE;
	}
	else if (!strcmp(name, R_STRING)) {
		return CT_READ;
	}
	else if (!strcmp(name, W_STRING)) {
		return CT_WRITE;
	}
	else if (!strcmp(name, DM_STRING)) {
		return CT_DUMP_MEMORY;
	}
	else if (!strcmp(name, DH_STRING)) {
		return CT_DESTROY_HEAP;
	}

	return CT_NONE;
}

void command_definitions_construct_command(u_command_t *ptr,
		char buffer[][MAX_LINE_SIZE]) {

	e_command_type_t command_type = ptr->m_default_cmd.command_type;

	switch (command_type) {
	case CT_INIT_HEAP:
		ptr->m_IH_cmd.m_heap_start_addr = string_utils_addr_to_uint(buffer[1]);
		ptr->m_IH_cmd.m_list_count = string_utils_str_to_uint(buffer[2]);
		ptr->m_IH_cmd.m_list_size = string_utils_str_to_uint(buffer[3]);
		ptr->m_IH_cmd.m_should_reconstitute = string_utils_str_to_int(buffer[4]);
		break;
	case CT_MALLOC:
		ptr->m_M_cmd.m_size = string_utils_str_to_uint(buffer[1]);
		break;
	case CT_FREE:
		ptr->m_F_cmd.m_addr = string_utils_addr_to_uint(buffer[1]);
		break;
	case CT_READ:
		ptr->m_R_cmd.m_src = string_utils_addr_to_uint(buffer[1]);
		ptr->m_R_cmd.m_size = string_utils_str_to_uint(buffer[2]);
		break;
	case CT_WRITE:
		ptr->m_W_cmd.m_dest = string_utils_addr_to_uint(buffer[1]);
		ptr->m_W_cmd.m_src = buffer[2];
		ptr->m_W_cmd.m_size = string_utils_str_to_uint(buffer[3]);
		break;
	case CT_DUMP_MEMORY:
		break;
	case CT_DESTROY_HEAP:
		break;
	default:
		break;
	}
}
