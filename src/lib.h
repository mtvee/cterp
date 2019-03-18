#ifndef __CT_LIB_H__
#define __CT_LIB_H__

#include "def.h"

extern _CONST math_const_table[];

extern _CONST stdio_const_table[];
	
extern _CONST stdlib_const_table[];
	
extern _CONST stdbool_const_table[];
	
extern _CONST time_const_table[];

#ifdef _WIN32
extern _CONST conio_const_table[];
#endif

extern _CONST string_const_table[];

// stdio
void call_putchar(void);
void call_getchar(void);
void call_puts(void);
void call_printf(void);
void call_scanf(void);
void call_gets(void);
void call_fopen(void);
void call_fclose(void);
void call_fputc(void);
void call_fgetc(void);
void call_feof(void);
void call_fseek(void);
void call_ferror(void);
void call_rewind(void);
void call_remove(void);
void call_ftell(void);
void call_fflush(void);

// stdlib
void call_system(void);
void call_malloc(void);
void call_free(void);
void call_rand(void);

// string
void call_strlen(void);
void call_strchr(void);
void call_strstr(void);
void call_strcat(void);
void call_strcpy(void);
void call_strcmp(void);

// math
void call_sin(void);
void call_cos(void);
void call_tan(void);
void call_asin(void);
void call_acos(void);
void call_atan(void);
void call_atan2(void);
void call_ln(void);
void call_log(void);
void call_exp(void);
void call_sinh(void);
void call_asinh(void);
void call_cosh(void);
void call_acosh(void);
void call_tanh(void);
void call_atanh(void);
void call_sqrt(void);
void call_ceil(void);
void call_floor(void);
void call_max(void);
void call_min(void);
void call_trunc(void);
void call_round(void);
void call_abs(void);
void call_eval(void);
void call_pow(void);
void call_erf(void);
void call_gamma(void);
void call_zeta(void);
void call_avrg(void);
void call_todeg(void);
void call_torad(void);
void call_signum(void);
void call_fact(void);
void call_iseven(void);
void call_isodd(void);
void call_isprime(void);
void call_nCk(void);

int factorial(int N);

// conio
#ifdef _WIN32
void call_kbhit(void);
void call_getch(void);
void call_getche(void);
void call_clrscr(void);
void call_putch(void);
#endif

void call_asctime(void);
void call_clock(void);
void call_time(void);

extern _LIB stdio_lib[];

extern _LIB stdlib_lib[];

extern _LIB math_lib[];

extern _LIB string_lib[];

#ifdef _WIN32
extern _LIB conio_lib[];
#endif

extern _LIB time_lib[];

extern _LIB stdbool_lib[];

typedef struct {
	char *lib_name;
	_LIB *libp;
	_CONST *constp;
} lib_table;

extern lib_table libs[];

#endif
