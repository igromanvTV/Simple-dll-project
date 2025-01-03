
#pragma once

#define LUAU_COMMA_SEP ,
#define LUAU_SEMICOLON_SEP ;

#define LUAU_SHUFFLE3(sep, a0, a1, a2) a2 sep a1 sep a0//11.12

#define LUAU_SHUFFLE4(sep, a0, a1, a2, a3) a3 sep a1 sep a2 sep a0 //11.12 

#define LUAU_SHUFFLE5(sep, a0, a1, a2, a3, a4) a4 sep a1 sep a3 sep a2 sep a0  //11.12

#define LUAU_SHUFFLE6(sep, a0, a1, a2, a3, a4, a5) a1 sep a5 sep a3 sep a0 sep a4 sep a2  //11.12

#define LUAU_SHUFFLE7(sep, a0, a1, a2, a3, a4, a5, a6) a1 sep a2 sep a3 sep a0 sep a4 sep a5 sep a6 //11.12

#define LUAU_SHUFFLE8(sep, a0, a1, a2, a3, a4, a5, a6, a7) a7 sep a1 sep a6 sep a0 sep a3 sep a5 sep a4 sep a2 //11.12

#define LUAU_SHUFFLE9(sep, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9) a3 sep a4 sep a8 sep a7 sep a6 sep a5 sep a0 sep a2 sep a1 sep a9 //11.12






