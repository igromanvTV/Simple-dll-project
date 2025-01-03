#pragma once
#include "EncryptionManager.hpp"


#define globalstate_ttname vm_add_sub //11.12.2024 
#define globalstate_tmname vm_add_sub //11.12.2024

#define luastate_global vm_add_sub //11.12.2024
#define luastate_stacksize vm_add_sub //11.12.2024

#define tstring_hash vm_xor_xor //11.12.2024
#define tstring_len vm_add_sub //11.12.2024

#define udata_metatable vm_add_sub //11.12.2024

#define closure_c_f vm_sub_sub //11.12.2024
#define closure_c_cont vm_sub_add //11.12.2024
#define closure_c_debugname vm_xor_xor //11.12.2024 

#define closure_l_p vm_sub_sub //11.12.2024

#define proto_k vm_sub_sub //11.12.2024
#define proto_code vm_sub_sub //11.12.2024
#define proto_p vm_sub_sub //11.12.2024

#define proto_lineinfo vm_xor_xor //11.12.2024
#define proto_abslineinfo vm_xor_xor //11.12.2024
#define proto_locvars vm_xor_xor //11.12.2024
#define proto_upvalues vm_xor_xor //11.12.2024
#define proto_source vm_xor_xor //11.12.2024

#define proto_debugname vm_sub_sub //11.12.2024
#define proto_debuginsn vm_sub_sub //11.12.2024 

#define proto_typeinfo vm_add_sub //11.12.2024 

#define table_metatable vm_sub_sub //11.12.2024
#define table_array vm_sub_sub //11.12.2024
#define table_node vm_sub_sub //11.12.2024
