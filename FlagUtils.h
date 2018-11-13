#ifndef _FLAG_UTILS_H_
#define _FLAG_UTILS_H_

/** INVOKE calls macro(or function) FUNC for each variadic argument
    FUNC should have 2 arguments - first is lvalue (e.g. register), second is rvalue
		Example: #define SET_FLAG(REGISTER, VAL) REGISTER |= VAL
		So, if you call:
		INVOKE(SET_FLAG, 0x04, REG1, REG2);
		It will expand to:
		REG1 |= 0x11;
		REG2 |= 0x11;
		
		Maximum number of variadic arguments is 3, but it can be easily expanded by adding another
		INVOKE4, INVOKE5 etc
*/
#define INVOKE(FUNC, VAL, ...) GET_MACRO(__VA_ARGS__, INVOKE3, INVOKE2, INVOKE1)(FUNC, VAL, __VA_ARGS__)

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define INVOKE1(FUNC, VAL, REG_1) FUNC(REG_1, VAL)
#define INVOKE2(FUNC, VAL, REG_1, REG_2) INVOKE1(FUNC, VAL, REG_1); INVOKE1(FUNC, VAL, REG_2)
#define INVOKE3(FUNC, VAL, REG_1, REG_2, REG_3) INVOKE2(FUNC, VAL, REG_1, REG_2); INVOKE1(FUNC, VAL, REG_3)


#define SET_FLAG(REGISTER, VAL) REGISTER |= (VAL)
#define CLEAR_FLAG(REGISTER, VAL) REGISTER &= ~(VAL)
#define TOGGLE_FLAG(REGISTER, VAL) REGISTER ^= (VAL)

#define PIN0 0x01
#define PIN1 0x02
#define PIN2 0x04
#define PIN3 0x08
#define PIN4 0x10
#define PIN5 0x20
#define PIN6 0x40
#define PIN7 0x80

// Port Mux Control
#define PMC0 0x0000000F // pin 0
#define PMC1 0x000000F0 // pin 1
#define PMC2 0x00000F00 // pin 2
#define PMC3 0x0000F000 // pin 3
#define PMC4 0x000F0000 // pin 4

#endif // _FLAG_UTILS_H_
