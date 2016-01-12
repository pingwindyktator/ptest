#ifndef TESTING_PCTEST_MACRO_HPP
#define TESTING_PCTEST_MACRO_HPP

#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...) N
#define __RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

// general definition for any function name
#define _VFUNC_(name, n) name##n
#define _VFUNC(name, n) _VFUNC_(name, n)
#define VFUNC(func, ...) _VFUNC(func, __NARG__(__VA_ARGS__)) (__VA_ARGS__)

// definition for run_suite_test
#define run_suite_test(...) VFUNC(run_suite_test, __VA_ARGS__)

// run_test definitions
#define run_suite_test4(suite,func,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{});\
}
#define run_suite_test5(suite,func,x0,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0},x0);\
}
#define run_suite_test6(suite,func,x0,x1,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1},x0,x1);\
}
#define run_suite_test7(suite,func,x0,x1,x2,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2},x0,x1,x2);\
}
#define run_suite_test8(suite,func,x0,x1,x2,x3,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3},x0,x1,x2,x3);\
}
#define run_suite_test9(suite,func,x0,x1,x2,x3,x4,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4},x0,x1,x2,x3,x4);\
}
#define run_suite_test10(suite,func,x0,x1,x2,x3,x4,x5,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5},x0,x1,x2,x3,x4,x5);\
}
#define run_suite_test11(suite,func,x0,x1,x2,x3,x4,x5,x6,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6},x0,x1,x2,x3,x4,x5,x6);\
}
#define run_suite_test12(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7},x0,x1,x2,x3,x4,x5,x6,x7);\
}
#define run_suite_test13(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8},x0,x1,x2,x3,x4,x5,x6,x7,x8);\
}
#define run_suite_test14(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9);\
}
#define run_suite_test15(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10);\
}
#define run_suite_test16(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11);\
}
#define run_suite_test17(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12);\
}
#define run_suite_test18(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13);\
}
#define run_suite_test19(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14);\
}
#define run_suite_test20(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15);\
}
#define run_suite_test21(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16);\
}
#define run_suite_test22(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17);\
}
#define run_suite_test23(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18);\
}
#define run_suite_test24(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19);\
}
#define run_suite_test25(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20);\
}
#define run_suite_test26(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21);\
}
#define run_suite_test27(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22);\
}
#define run_suite_test28(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23);\
}
#define run_suite_test29(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24);\
}
#define run_suite_test30(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25);\
}
#define run_suite_test31(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26);\
}
#define run_suite_test32(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27);\
}
#define run_suite_test33(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28);\
}
#define run_suite_test34(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29);\
}
#define run_suite_test35(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30);\
}
#define run_suite_test36(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31);\
}
#define run_suite_test37(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32);\
}
#define run_suite_test38(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33);\
}
#define run_suite_test39(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34);\
}
#define run_suite_test40(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35);\
}
#define run_suite_test41(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36);\
}
#define run_suite_test42(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37);\
}
#define run_suite_test43(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38);\
}
#define run_suite_test44(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39);\
}
#define run_suite_test45(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40);\
}
#define run_suite_test46(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41);\
}
#define run_suite_test47(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42);\
}
#define run_suite_test48(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43);\
}
#define run_suite_test49(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44);\
}
#define run_suite_test50(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45);\
}
#define run_suite_test51(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46);\
}
#define run_suite_test52(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47);\
}
#define run_suite_test53(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48);\
}
#define run_suite_test54(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49);\
}
#define run_suite_test55(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50);\
}
#define run_suite_test56(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51);\
}
#define run_suite_test57(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52);\
}
#define run_suite_test58(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52,#x53},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53);\
}
#define run_suite_test59(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52,#x53,#x54},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54);\
}
#define run_suite_test60(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52,#x53,#x54,#x55},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55);\
}
#define run_suite_test61(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52,#x53,#x54,#x55,#x56},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56);\
}
#define run_suite_test62(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,x57,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52,#x53,#x54,#x55,#x56,#x57},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,x57);\
}
#define run_suite_test63(suite,func,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,x57,x58,expected_result,equality)\
{\
suite.run_test(func,#func,expected_result,equality,{#x0,#x1,#x2,#x3,#x4,#x5,#x6,#x7,#x8,#x9,#x10,#x11,#x12,#x13,#x14,#x15,#x16,#x17,#x18,#x19,#x20,#x21,#x22,#x23,#x24,#x25,#x26,#x27,#x28,#x29,#x30,#x31,#x32,#x33,#x34,#x35,#x36,#x37,#x38,#x39,#x40,#x41,#x42,#x43,#x44,#x45,#x46,#x47,#x48,#x49,#x50,#x51,#x52,#x53,#x54,#x55,#x56,#x57,#x58},x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37,x38,x39,x40,x41,x42,x43,x44,x45,x46,x47,x48,x49,x50,x51,x52,x53,x54,x55,x56,x57,x58);\
}


#endif //TESTING_PCTEST_MACRO_HPP
