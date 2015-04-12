/* For Capstone Engine. AUTO-GENERATED FILE, DO NOT EDIT */

#include "sparc_const.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void set_sparc_const(lua_State* l)
{
	/* Enums corresponding to Sparc condition codes, both icc's and fcc's. */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "SPARC_CC_INVALID");

	/* Integer condition codes */
	lua_pushinteger(l, 8+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_A");
	lua_pushinteger(l, 0+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_N");
	lua_pushinteger(l, 9+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_NE");
	lua_pushinteger(l, 1+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_E");
	lua_pushinteger(l, 10+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_G");
	lua_pushinteger(l, 2+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_LE");
	lua_pushinteger(l, 11+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_GE");
	lua_pushinteger(l, 3+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_L");
	lua_pushinteger(l, 12+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_GU");
	lua_pushinteger(l, 4+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_LEU");
	lua_pushinteger(l, 13+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_CC");
	lua_pushinteger(l, 5+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_CS");
	lua_pushinteger(l, 14+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_POS");
	lua_pushinteger(l, 6+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_NEG");
	lua_pushinteger(l, 15+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_VC");
	lua_pushinteger(l, 7+256);
	lua_setfield(l, -2, "SPARC_CC_ICC_VS");

	/* Floating condition codes */
	lua_pushinteger(l, 8+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_A");
	lua_pushinteger(l, 0+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_N");
	lua_pushinteger(l, 7+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_U");
	lua_pushinteger(l, 6+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_G");
	lua_pushinteger(l, 5+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_UG");
	lua_pushinteger(l, 4+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_L");
	lua_pushinteger(l, 3+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_UL");
	lua_pushinteger(l, 2+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_LG");
	lua_pushinteger(l, 1+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_NE");
	lua_pushinteger(l, 9+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_E");
	lua_pushinteger(l, 10+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_UE");
	lua_pushinteger(l, 11+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_GE");
	lua_pushinteger(l, 12+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_UGE");
	lua_pushinteger(l, 13+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_LE");
	lua_pushinteger(l, 14+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_ULE");
	lua_pushinteger(l, 15+16+256);
	lua_setfield(l, -2, "SPARC_CC_FCC_O");

	/* Branch hint */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "SPARC_HINT_INVALID");
	lua_pushinteger(l, 1<<0);
	lua_setfield(l, -2, "SPARC_HINT_A");
	lua_pushinteger(l, 1<<1);
	lua_setfield(l, -2, "SPARC_HINT_PT");
	lua_pushinteger(l, 1<<2);
	lua_setfield(l, -2, "SPARC_HINT_PN");

	/* Operand type for instruction's operands */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "SPARC_OP_INVALID");
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "SPARC_OP_REG");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "SPARC_OP_IMM");
	lua_pushinteger(l, 3);
	lua_setfield(l, -2, "SPARC_OP_MEM");

	/* SPARC registers */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "SPARC_REG_INVALID");
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "SPARC_REG_F0");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "SPARC_REG_F1");
	lua_pushinteger(l, 3);
	lua_setfield(l, -2, "SPARC_REG_F2");
	lua_pushinteger(l, 4);
	lua_setfield(l, -2, "SPARC_REG_F3");
	lua_pushinteger(l, 5);
	lua_setfield(l, -2, "SPARC_REG_F4");
	lua_pushinteger(l, 6);
	lua_setfield(l, -2, "SPARC_REG_F5");
	lua_pushinteger(l, 7);
	lua_setfield(l, -2, "SPARC_REG_F6");
	lua_pushinteger(l, 8);
	lua_setfield(l, -2, "SPARC_REG_F7");
	lua_pushinteger(l, 9);
	lua_setfield(l, -2, "SPARC_REG_F8");
	lua_pushinteger(l, 10);
	lua_setfield(l, -2, "SPARC_REG_F9");
	lua_pushinteger(l, 11);
	lua_setfield(l, -2, "SPARC_REG_F10");
	lua_pushinteger(l, 12);
	lua_setfield(l, -2, "SPARC_REG_F11");
	lua_pushinteger(l, 13);
	lua_setfield(l, -2, "SPARC_REG_F12");
	lua_pushinteger(l, 14);
	lua_setfield(l, -2, "SPARC_REG_F13");
	lua_pushinteger(l, 15);
	lua_setfield(l, -2, "SPARC_REG_F14");
	lua_pushinteger(l, 16);
	lua_setfield(l, -2, "SPARC_REG_F15");
	lua_pushinteger(l, 17);
	lua_setfield(l, -2, "SPARC_REG_F16");
	lua_pushinteger(l, 18);
	lua_setfield(l, -2, "SPARC_REG_F17");
	lua_pushinteger(l, 19);
	lua_setfield(l, -2, "SPARC_REG_F18");
	lua_pushinteger(l, 20);
	lua_setfield(l, -2, "SPARC_REG_F19");
	lua_pushinteger(l, 21);
	lua_setfield(l, -2, "SPARC_REG_F20");
	lua_pushinteger(l, 22);
	lua_setfield(l, -2, "SPARC_REG_F21");
	lua_pushinteger(l, 23);
	lua_setfield(l, -2, "SPARC_REG_F22");
	lua_pushinteger(l, 24);
	lua_setfield(l, -2, "SPARC_REG_F23");
	lua_pushinteger(l, 25);
	lua_setfield(l, -2, "SPARC_REG_F24");
	lua_pushinteger(l, 26);
	lua_setfield(l, -2, "SPARC_REG_F25");
	lua_pushinteger(l, 27);
	lua_setfield(l, -2, "SPARC_REG_F26");
	lua_pushinteger(l, 28);
	lua_setfield(l, -2, "SPARC_REG_F27");
	lua_pushinteger(l, 29);
	lua_setfield(l, -2, "SPARC_REG_F28");
	lua_pushinteger(l, 30);
	lua_setfield(l, -2, "SPARC_REG_F29");
	lua_pushinteger(l, 31);
	lua_setfield(l, -2, "SPARC_REG_F30");
	lua_pushinteger(l, 32);
	lua_setfield(l, -2, "SPARC_REG_F31");
	lua_pushinteger(l, 33);
	lua_setfield(l, -2, "SPARC_REG_F32");
	lua_pushinteger(l, 34);
	lua_setfield(l, -2, "SPARC_REG_F34");
	lua_pushinteger(l, 35);
	lua_setfield(l, -2, "SPARC_REG_F36");
	lua_pushinteger(l, 36);
	lua_setfield(l, -2, "SPARC_REG_F38");
	lua_pushinteger(l, 37);
	lua_setfield(l, -2, "SPARC_REG_F40");
	lua_pushinteger(l, 38);
	lua_setfield(l, -2, "SPARC_REG_F42");
	lua_pushinteger(l, 39);
	lua_setfield(l, -2, "SPARC_REG_F44");
	lua_pushinteger(l, 40);
	lua_setfield(l, -2, "SPARC_REG_F46");
	lua_pushinteger(l, 41);
	lua_setfield(l, -2, "SPARC_REG_F48");
	lua_pushinteger(l, 42);
	lua_setfield(l, -2, "SPARC_REG_F50");
	lua_pushinteger(l, 43);
	lua_setfield(l, -2, "SPARC_REG_F52");
	lua_pushinteger(l, 44);
	lua_setfield(l, -2, "SPARC_REG_F54");
	lua_pushinteger(l, 45);
	lua_setfield(l, -2, "SPARC_REG_F56");
	lua_pushinteger(l, 46);
	lua_setfield(l, -2, "SPARC_REG_F58");
	lua_pushinteger(l, 47);
	lua_setfield(l, -2, "SPARC_REG_F60");
	lua_pushinteger(l, 48);
	lua_setfield(l, -2, "SPARC_REG_F62");
	lua_pushinteger(l, 49);
	lua_setfield(l, -2, "SPARC_REG_FCC0");
	lua_pushinteger(l, 50);
	lua_setfield(l, -2, "SPARC_REG_FCC1");
	lua_pushinteger(l, 51);
	lua_setfield(l, -2, "SPARC_REG_FCC2");
	lua_pushinteger(l, 52);
	lua_setfield(l, -2, "SPARC_REG_FCC3");
	lua_pushinteger(l, 53);
	lua_setfield(l, -2, "SPARC_REG_FP");
	lua_pushinteger(l, 54);
	lua_setfield(l, -2, "SPARC_REG_G0");
	lua_pushinteger(l, 55);
	lua_setfield(l, -2, "SPARC_REG_G1");
	lua_pushinteger(l, 56);
	lua_setfield(l, -2, "SPARC_REG_G2");
	lua_pushinteger(l, 57);
	lua_setfield(l, -2, "SPARC_REG_G3");
	lua_pushinteger(l, 58);
	lua_setfield(l, -2, "SPARC_REG_G4");
	lua_pushinteger(l, 59);
	lua_setfield(l, -2, "SPARC_REG_G5");
	lua_pushinteger(l, 60);
	lua_setfield(l, -2, "SPARC_REG_G6");
	lua_pushinteger(l, 61);
	lua_setfield(l, -2, "SPARC_REG_G7");
	lua_pushinteger(l, 62);
	lua_setfield(l, -2, "SPARC_REG_I0");
	lua_pushinteger(l, 63);
	lua_setfield(l, -2, "SPARC_REG_I1");
	lua_pushinteger(l, 64);
	lua_setfield(l, -2, "SPARC_REG_I2");
	lua_pushinteger(l, 65);
	lua_setfield(l, -2, "SPARC_REG_I3");
	lua_pushinteger(l, 66);
	lua_setfield(l, -2, "SPARC_REG_I4");
	lua_pushinteger(l, 67);
	lua_setfield(l, -2, "SPARC_REG_I5");
	lua_pushinteger(l, 68);
	lua_setfield(l, -2, "SPARC_REG_I7");
	lua_pushinteger(l, 69);
	lua_setfield(l, -2, "SPARC_REG_ICC");
	lua_pushinteger(l, 70);
	lua_setfield(l, -2, "SPARC_REG_L0");
	lua_pushinteger(l, 71);
	lua_setfield(l, -2, "SPARC_REG_L1");
	lua_pushinteger(l, 72);
	lua_setfield(l, -2, "SPARC_REG_L2");
	lua_pushinteger(l, 73);
	lua_setfield(l, -2, "SPARC_REG_L3");
	lua_pushinteger(l, 74);
	lua_setfield(l, -2, "SPARC_REG_L4");
	lua_pushinteger(l, 75);
	lua_setfield(l, -2, "SPARC_REG_L5");
	lua_pushinteger(l, 76);
	lua_setfield(l, -2, "SPARC_REG_L6");
	lua_pushinteger(l, 77);
	lua_setfield(l, -2, "SPARC_REG_L7");
	lua_pushinteger(l, 78);
	lua_setfield(l, -2, "SPARC_REG_O0");
	lua_pushinteger(l, 79);
	lua_setfield(l, -2, "SPARC_REG_O1");
	lua_pushinteger(l, 80);
	lua_setfield(l, -2, "SPARC_REG_O2");
	lua_pushinteger(l, 81);
	lua_setfield(l, -2, "SPARC_REG_O3");
	lua_pushinteger(l, 82);
	lua_setfield(l, -2, "SPARC_REG_O4");
	lua_pushinteger(l, 83);
	lua_setfield(l, -2, "SPARC_REG_O5");
	lua_pushinteger(l, 84);
	lua_setfield(l, -2, "SPARC_REG_O7");
	lua_pushinteger(l, 85);
	lua_setfield(l, -2, "SPARC_REG_SP");
	lua_pushinteger(l, 86);
	lua_setfield(l, -2, "SPARC_REG_Y");
	lua_pushinteger(l, 87);
	lua_setfield(l, -2, "SPARC_REG_XCC");
	lua_pushinteger(l, 88);
	lua_setfield(l, -2, "SPARC_REG_ENDING");
	lua_pushinteger(l, SPARC_REG_SP);
	lua_setfield(l, -2, "SPARC_REG_O6");
	lua_pushinteger(l, SPARC_REG_FP);
	lua_setfield(l, -2, "SPARC_REG_I6");

	/* SPARC instruction */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "SPARC_INS_INVALID");
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "SPARC_INS_ADDCC");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "SPARC_INS_ADDX");
	lua_pushinteger(l, 3);
	lua_setfield(l, -2, "SPARC_INS_ADDXCC");
	lua_pushinteger(l, 4);
	lua_setfield(l, -2, "SPARC_INS_ADDXC");
	lua_pushinteger(l, 5);
	lua_setfield(l, -2, "SPARC_INS_ADDXCCC");
	lua_pushinteger(l, 6);
	lua_setfield(l, -2, "SPARC_INS_ADD");
	lua_pushinteger(l, 7);
	lua_setfield(l, -2, "SPARC_INS_ALIGNADDR");
	lua_pushinteger(l, 8);
	lua_setfield(l, -2, "SPARC_INS_ALIGNADDRL");
	lua_pushinteger(l, 9);
	lua_setfield(l, -2, "SPARC_INS_ANDCC");
	lua_pushinteger(l, 10);
	lua_setfield(l, -2, "SPARC_INS_ANDNCC");
	lua_pushinteger(l, 11);
	lua_setfield(l, -2, "SPARC_INS_ANDN");
	lua_pushinteger(l, 12);
	lua_setfield(l, -2, "SPARC_INS_AND");
	lua_pushinteger(l, 13);
	lua_setfield(l, -2, "SPARC_INS_ARRAY16");
	lua_pushinteger(l, 14);
	lua_setfield(l, -2, "SPARC_INS_ARRAY32");
	lua_pushinteger(l, 15);
	lua_setfield(l, -2, "SPARC_INS_ARRAY8");
	lua_pushinteger(l, 16);
	lua_setfield(l, -2, "SPARC_INS_B");
	lua_pushinteger(l, 17);
	lua_setfield(l, -2, "SPARC_INS_JMP");
	lua_pushinteger(l, 18);
	lua_setfield(l, -2, "SPARC_INS_BMASK");
	lua_pushinteger(l, 19);
	lua_setfield(l, -2, "SPARC_INS_FB");
	lua_pushinteger(l, 20);
	lua_setfield(l, -2, "SPARC_INS_BRGEZ");
	lua_pushinteger(l, 21);
	lua_setfield(l, -2, "SPARC_INS_BRGZ");
	lua_pushinteger(l, 22);
	lua_setfield(l, -2, "SPARC_INS_BRLEZ");
	lua_pushinteger(l, 23);
	lua_setfield(l, -2, "SPARC_INS_BRLZ");
	lua_pushinteger(l, 24);
	lua_setfield(l, -2, "SPARC_INS_BRNZ");
	lua_pushinteger(l, 25);
	lua_setfield(l, -2, "SPARC_INS_BRZ");
	lua_pushinteger(l, 26);
	lua_setfield(l, -2, "SPARC_INS_BSHUFFLE");
	lua_pushinteger(l, 27);
	lua_setfield(l, -2, "SPARC_INS_CALL");
	lua_pushinteger(l, 28);
	lua_setfield(l, -2, "SPARC_INS_CASX");
	lua_pushinteger(l, 29);
	lua_setfield(l, -2, "SPARC_INS_CAS");
	lua_pushinteger(l, 30);
	lua_setfield(l, -2, "SPARC_INS_CMASK16");
	lua_pushinteger(l, 31);
	lua_setfield(l, -2, "SPARC_INS_CMASK32");
	lua_pushinteger(l, 32);
	lua_setfield(l, -2, "SPARC_INS_CMASK8");
	lua_pushinteger(l, 33);
	lua_setfield(l, -2, "SPARC_INS_CMP");
	lua_pushinteger(l, 34);
	lua_setfield(l, -2, "SPARC_INS_EDGE16");
	lua_pushinteger(l, 35);
	lua_setfield(l, -2, "SPARC_INS_EDGE16L");
	lua_pushinteger(l, 36);
	lua_setfield(l, -2, "SPARC_INS_EDGE16LN");
	lua_pushinteger(l, 37);
	lua_setfield(l, -2, "SPARC_INS_EDGE16N");
	lua_pushinteger(l, 38);
	lua_setfield(l, -2, "SPARC_INS_EDGE32");
	lua_pushinteger(l, 39);
	lua_setfield(l, -2, "SPARC_INS_EDGE32L");
	lua_pushinteger(l, 40);
	lua_setfield(l, -2, "SPARC_INS_EDGE32LN");
	lua_pushinteger(l, 41);
	lua_setfield(l, -2, "SPARC_INS_EDGE32N");
	lua_pushinteger(l, 42);
	lua_setfield(l, -2, "SPARC_INS_EDGE8");
	lua_pushinteger(l, 43);
	lua_setfield(l, -2, "SPARC_INS_EDGE8L");
	lua_pushinteger(l, 44);
	lua_setfield(l, -2, "SPARC_INS_EDGE8LN");
	lua_pushinteger(l, 45);
	lua_setfield(l, -2, "SPARC_INS_EDGE8N");
	lua_pushinteger(l, 46);
	lua_setfield(l, -2, "SPARC_INS_FABSD");
	lua_pushinteger(l, 47);
	lua_setfield(l, -2, "SPARC_INS_FABSQ");
	lua_pushinteger(l, 48);
	lua_setfield(l, -2, "SPARC_INS_FABSS");
	lua_pushinteger(l, 49);
	lua_setfield(l, -2, "SPARC_INS_FADDD");
	lua_pushinteger(l, 50);
	lua_setfield(l, -2, "SPARC_INS_FADDQ");
	lua_pushinteger(l, 51);
	lua_setfield(l, -2, "SPARC_INS_FADDS");
	lua_pushinteger(l, 52);
	lua_setfield(l, -2, "SPARC_INS_FALIGNDATA");
	lua_pushinteger(l, 53);
	lua_setfield(l, -2, "SPARC_INS_FAND");
	lua_pushinteger(l, 54);
	lua_setfield(l, -2, "SPARC_INS_FANDNOT1");
	lua_pushinteger(l, 55);
	lua_setfield(l, -2, "SPARC_INS_FANDNOT1S");
	lua_pushinteger(l, 56);
	lua_setfield(l, -2, "SPARC_INS_FANDNOT2");
	lua_pushinteger(l, 57);
	lua_setfield(l, -2, "SPARC_INS_FANDNOT2S");
	lua_pushinteger(l, 58);
	lua_setfield(l, -2, "SPARC_INS_FANDS");
	lua_pushinteger(l, 59);
	lua_setfield(l, -2, "SPARC_INS_FCHKSM16");
	lua_pushinteger(l, 60);
	lua_setfield(l, -2, "SPARC_INS_FCMPD");
	lua_pushinteger(l, 61);
	lua_setfield(l, -2, "SPARC_INS_FCMPEQ16");
	lua_pushinteger(l, 62);
	lua_setfield(l, -2, "SPARC_INS_FCMPEQ32");
	lua_pushinteger(l, 63);
	lua_setfield(l, -2, "SPARC_INS_FCMPGT16");
	lua_pushinteger(l, 64);
	lua_setfield(l, -2, "SPARC_INS_FCMPGT32");
	lua_pushinteger(l, 65);
	lua_setfield(l, -2, "SPARC_INS_FCMPLE16");
	lua_pushinteger(l, 66);
	lua_setfield(l, -2, "SPARC_INS_FCMPLE32");
	lua_pushinteger(l, 67);
	lua_setfield(l, -2, "SPARC_INS_FCMPNE16");
	lua_pushinteger(l, 68);
	lua_setfield(l, -2, "SPARC_INS_FCMPNE32");
	lua_pushinteger(l, 69);
	lua_setfield(l, -2, "SPARC_INS_FCMPQ");
	lua_pushinteger(l, 70);
	lua_setfield(l, -2, "SPARC_INS_FCMPS");
	lua_pushinteger(l, 71);
	lua_setfield(l, -2, "SPARC_INS_FDIVD");
	lua_pushinteger(l, 72);
	lua_setfield(l, -2, "SPARC_INS_FDIVQ");
	lua_pushinteger(l, 73);
	lua_setfield(l, -2, "SPARC_INS_FDIVS");
	lua_pushinteger(l, 74);
	lua_setfield(l, -2, "SPARC_INS_FDMULQ");
	lua_pushinteger(l, 75);
	lua_setfield(l, -2, "SPARC_INS_FDTOI");
	lua_pushinteger(l, 76);
	lua_setfield(l, -2, "SPARC_INS_FDTOQ");
	lua_pushinteger(l, 77);
	lua_setfield(l, -2, "SPARC_INS_FDTOS");
	lua_pushinteger(l, 78);
	lua_setfield(l, -2, "SPARC_INS_FDTOX");
	lua_pushinteger(l, 79);
	lua_setfield(l, -2, "SPARC_INS_FEXPAND");
	lua_pushinteger(l, 80);
	lua_setfield(l, -2, "SPARC_INS_FHADDD");
	lua_pushinteger(l, 81);
	lua_setfield(l, -2, "SPARC_INS_FHADDS");
	lua_pushinteger(l, 82);
	lua_setfield(l, -2, "SPARC_INS_FHSUBD");
	lua_pushinteger(l, 83);
	lua_setfield(l, -2, "SPARC_INS_FHSUBS");
	lua_pushinteger(l, 84);
	lua_setfield(l, -2, "SPARC_INS_FITOD");
	lua_pushinteger(l, 85);
	lua_setfield(l, -2, "SPARC_INS_FITOQ");
	lua_pushinteger(l, 86);
	lua_setfield(l, -2, "SPARC_INS_FITOS");
	lua_pushinteger(l, 87);
	lua_setfield(l, -2, "SPARC_INS_FLCMPD");
	lua_pushinteger(l, 88);
	lua_setfield(l, -2, "SPARC_INS_FLCMPS");
	lua_pushinteger(l, 89);
	lua_setfield(l, -2, "SPARC_INS_FLUSHW");
	lua_pushinteger(l, 90);
	lua_setfield(l, -2, "SPARC_INS_FMEAN16");
	lua_pushinteger(l, 91);
	lua_setfield(l, -2, "SPARC_INS_FMOVD");
	lua_pushinteger(l, 92);
	lua_setfield(l, -2, "SPARC_INS_FMOVQ");
	lua_pushinteger(l, 93);
	lua_setfield(l, -2, "SPARC_INS_FMOVRDGEZ");
	lua_pushinteger(l, 94);
	lua_setfield(l, -2, "SPARC_INS_FMOVRQGEZ");
	lua_pushinteger(l, 95);
	lua_setfield(l, -2, "SPARC_INS_FMOVRSGEZ");
	lua_pushinteger(l, 96);
	lua_setfield(l, -2, "SPARC_INS_FMOVRDGZ");
	lua_pushinteger(l, 97);
	lua_setfield(l, -2, "SPARC_INS_FMOVRQGZ");
	lua_pushinteger(l, 98);
	lua_setfield(l, -2, "SPARC_INS_FMOVRSGZ");
	lua_pushinteger(l, 99);
	lua_setfield(l, -2, "SPARC_INS_FMOVRDLEZ");
	lua_pushinteger(l, 100);
	lua_setfield(l, -2, "SPARC_INS_FMOVRQLEZ");
	lua_pushinteger(l, 101);
	lua_setfield(l, -2, "SPARC_INS_FMOVRSLEZ");
	lua_pushinteger(l, 102);
	lua_setfield(l, -2, "SPARC_INS_FMOVRDLZ");
	lua_pushinteger(l, 103);
	lua_setfield(l, -2, "SPARC_INS_FMOVRQLZ");
	lua_pushinteger(l, 104);
	lua_setfield(l, -2, "SPARC_INS_FMOVRSLZ");
	lua_pushinteger(l, 105);
	lua_setfield(l, -2, "SPARC_INS_FMOVRDNZ");
	lua_pushinteger(l, 106);
	lua_setfield(l, -2, "SPARC_INS_FMOVRQNZ");
	lua_pushinteger(l, 107);
	lua_setfield(l, -2, "SPARC_INS_FMOVRSNZ");
	lua_pushinteger(l, 108);
	lua_setfield(l, -2, "SPARC_INS_FMOVRDZ");
	lua_pushinteger(l, 109);
	lua_setfield(l, -2, "SPARC_INS_FMOVRQZ");
	lua_pushinteger(l, 110);
	lua_setfield(l, -2, "SPARC_INS_FMOVRSZ");
	lua_pushinteger(l, 111);
	lua_setfield(l, -2, "SPARC_INS_FMOVS");
	lua_pushinteger(l, 112);
	lua_setfield(l, -2, "SPARC_INS_FMUL8SUX16");
	lua_pushinteger(l, 113);
	lua_setfield(l, -2, "SPARC_INS_FMUL8ULX16");
	lua_pushinteger(l, 114);
	lua_setfield(l, -2, "SPARC_INS_FMUL8X16");
	lua_pushinteger(l, 115);
	lua_setfield(l, -2, "SPARC_INS_FMUL8X16AL");
	lua_pushinteger(l, 116);
	lua_setfield(l, -2, "SPARC_INS_FMUL8X16AU");
	lua_pushinteger(l, 117);
	lua_setfield(l, -2, "SPARC_INS_FMULD");
	lua_pushinteger(l, 118);
	lua_setfield(l, -2, "SPARC_INS_FMULD8SUX16");
	lua_pushinteger(l, 119);
	lua_setfield(l, -2, "SPARC_INS_FMULD8ULX16");
	lua_pushinteger(l, 120);
	lua_setfield(l, -2, "SPARC_INS_FMULQ");
	lua_pushinteger(l, 121);
	lua_setfield(l, -2, "SPARC_INS_FMULS");
	lua_pushinteger(l, 122);
	lua_setfield(l, -2, "SPARC_INS_FNADDD");
	lua_pushinteger(l, 123);
	lua_setfield(l, -2, "SPARC_INS_FNADDS");
	lua_pushinteger(l, 124);
	lua_setfield(l, -2, "SPARC_INS_FNAND");
	lua_pushinteger(l, 125);
	lua_setfield(l, -2, "SPARC_INS_FNANDS");
	lua_pushinteger(l, 126);
	lua_setfield(l, -2, "SPARC_INS_FNEGD");
	lua_pushinteger(l, 127);
	lua_setfield(l, -2, "SPARC_INS_FNEGQ");
	lua_pushinteger(l, 128);
	lua_setfield(l, -2, "SPARC_INS_FNEGS");
	lua_pushinteger(l, 129);
	lua_setfield(l, -2, "SPARC_INS_FNHADDD");
	lua_pushinteger(l, 130);
	lua_setfield(l, -2, "SPARC_INS_FNHADDS");
	lua_pushinteger(l, 131);
	lua_setfield(l, -2, "SPARC_INS_FNOR");
	lua_pushinteger(l, 132);
	lua_setfield(l, -2, "SPARC_INS_FNORS");
	lua_pushinteger(l, 133);
	lua_setfield(l, -2, "SPARC_INS_FNOT1");
	lua_pushinteger(l, 134);
	lua_setfield(l, -2, "SPARC_INS_FNOT1S");
	lua_pushinteger(l, 135);
	lua_setfield(l, -2, "SPARC_INS_FNOT2");
	lua_pushinteger(l, 136);
	lua_setfield(l, -2, "SPARC_INS_FNOT2S");
	lua_pushinteger(l, 137);
	lua_setfield(l, -2, "SPARC_INS_FONE");
	lua_pushinteger(l, 138);
	lua_setfield(l, -2, "SPARC_INS_FONES");
	lua_pushinteger(l, 139);
	lua_setfield(l, -2, "SPARC_INS_FOR");
	lua_pushinteger(l, 140);
	lua_setfield(l, -2, "SPARC_INS_FORNOT1");
	lua_pushinteger(l, 141);
	lua_setfield(l, -2, "SPARC_INS_FORNOT1S");
	lua_pushinteger(l, 142);
	lua_setfield(l, -2, "SPARC_INS_FORNOT2");
	lua_pushinteger(l, 143);
	lua_setfield(l, -2, "SPARC_INS_FORNOT2S");
	lua_pushinteger(l, 144);
	lua_setfield(l, -2, "SPARC_INS_FORS");
	lua_pushinteger(l, 145);
	lua_setfield(l, -2, "SPARC_INS_FPACK16");
	lua_pushinteger(l, 146);
	lua_setfield(l, -2, "SPARC_INS_FPACK32");
	lua_pushinteger(l, 147);
	lua_setfield(l, -2, "SPARC_INS_FPACKFIX");
	lua_pushinteger(l, 148);
	lua_setfield(l, -2, "SPARC_INS_FPADD16");
	lua_pushinteger(l, 149);
	lua_setfield(l, -2, "SPARC_INS_FPADD16S");
	lua_pushinteger(l, 150);
	lua_setfield(l, -2, "SPARC_INS_FPADD32");
	lua_pushinteger(l, 151);
	lua_setfield(l, -2, "SPARC_INS_FPADD32S");
	lua_pushinteger(l, 152);
	lua_setfield(l, -2, "SPARC_INS_FPADD64");
	lua_pushinteger(l, 153);
	lua_setfield(l, -2, "SPARC_INS_FPMERGE");
	lua_pushinteger(l, 154);
	lua_setfield(l, -2, "SPARC_INS_FPSUB16");
	lua_pushinteger(l, 155);
	lua_setfield(l, -2, "SPARC_INS_FPSUB16S");
	lua_pushinteger(l, 156);
	lua_setfield(l, -2, "SPARC_INS_FPSUB32");
	lua_pushinteger(l, 157);
	lua_setfield(l, -2, "SPARC_INS_FPSUB32S");
	lua_pushinteger(l, 158);
	lua_setfield(l, -2, "SPARC_INS_FQTOD");
	lua_pushinteger(l, 159);
	lua_setfield(l, -2, "SPARC_INS_FQTOI");
	lua_pushinteger(l, 160);
	lua_setfield(l, -2, "SPARC_INS_FQTOS");
	lua_pushinteger(l, 161);
	lua_setfield(l, -2, "SPARC_INS_FQTOX");
	lua_pushinteger(l, 162);
	lua_setfield(l, -2, "SPARC_INS_FSLAS16");
	lua_pushinteger(l, 163);
	lua_setfield(l, -2, "SPARC_INS_FSLAS32");
	lua_pushinteger(l, 164);
	lua_setfield(l, -2, "SPARC_INS_FSLL16");
	lua_pushinteger(l, 165);
	lua_setfield(l, -2, "SPARC_INS_FSLL32");
	lua_pushinteger(l, 166);
	lua_setfield(l, -2, "SPARC_INS_FSMULD");
	lua_pushinteger(l, 167);
	lua_setfield(l, -2, "SPARC_INS_FSQRTD");
	lua_pushinteger(l, 168);
	lua_setfield(l, -2, "SPARC_INS_FSQRTQ");
	lua_pushinteger(l, 169);
	lua_setfield(l, -2, "SPARC_INS_FSQRTS");
	lua_pushinteger(l, 170);
	lua_setfield(l, -2, "SPARC_INS_FSRA16");
	lua_pushinteger(l, 171);
	lua_setfield(l, -2, "SPARC_INS_FSRA32");
	lua_pushinteger(l, 172);
	lua_setfield(l, -2, "SPARC_INS_FSRC1");
	lua_pushinteger(l, 173);
	lua_setfield(l, -2, "SPARC_INS_FSRC1S");
	lua_pushinteger(l, 174);
	lua_setfield(l, -2, "SPARC_INS_FSRC2");
	lua_pushinteger(l, 175);
	lua_setfield(l, -2, "SPARC_INS_FSRC2S");
	lua_pushinteger(l, 176);
	lua_setfield(l, -2, "SPARC_INS_FSRL16");
	lua_pushinteger(l, 177);
	lua_setfield(l, -2, "SPARC_INS_FSRL32");
	lua_pushinteger(l, 178);
	lua_setfield(l, -2, "SPARC_INS_FSTOD");
	lua_pushinteger(l, 179);
	lua_setfield(l, -2, "SPARC_INS_FSTOI");
	lua_pushinteger(l, 180);
	lua_setfield(l, -2, "SPARC_INS_FSTOQ");
	lua_pushinteger(l, 181);
	lua_setfield(l, -2, "SPARC_INS_FSTOX");
	lua_pushinteger(l, 182);
	lua_setfield(l, -2, "SPARC_INS_FSUBD");
	lua_pushinteger(l, 183);
	lua_setfield(l, -2, "SPARC_INS_FSUBQ");
	lua_pushinteger(l, 184);
	lua_setfield(l, -2, "SPARC_INS_FSUBS");
	lua_pushinteger(l, 185);
	lua_setfield(l, -2, "SPARC_INS_FXNOR");
	lua_pushinteger(l, 186);
	lua_setfield(l, -2, "SPARC_INS_FXNORS");
	lua_pushinteger(l, 187);
	lua_setfield(l, -2, "SPARC_INS_FXOR");
	lua_pushinteger(l, 188);
	lua_setfield(l, -2, "SPARC_INS_FXORS");
	lua_pushinteger(l, 189);
	lua_setfield(l, -2, "SPARC_INS_FXTOD");
	lua_pushinteger(l, 190);
	lua_setfield(l, -2, "SPARC_INS_FXTOQ");
	lua_pushinteger(l, 191);
	lua_setfield(l, -2, "SPARC_INS_FXTOS");
	lua_pushinteger(l, 192);
	lua_setfield(l, -2, "SPARC_INS_FZERO");
	lua_pushinteger(l, 193);
	lua_setfield(l, -2, "SPARC_INS_FZEROS");
	lua_pushinteger(l, 194);
	lua_setfield(l, -2, "SPARC_INS_JMPL");
	lua_pushinteger(l, 195);
	lua_setfield(l, -2, "SPARC_INS_LDD");
	lua_pushinteger(l, 196);
	lua_setfield(l, -2, "SPARC_INS_LD");
	lua_pushinteger(l, 197);
	lua_setfield(l, -2, "SPARC_INS_LDQ");
	lua_pushinteger(l, 198);
	lua_setfield(l, -2, "SPARC_INS_LDSB");
	lua_pushinteger(l, 199);
	lua_setfield(l, -2, "SPARC_INS_LDSH");
	lua_pushinteger(l, 200);
	lua_setfield(l, -2, "SPARC_INS_LDSW");
	lua_pushinteger(l, 201);
	lua_setfield(l, -2, "SPARC_INS_LDUB");
	lua_pushinteger(l, 202);
	lua_setfield(l, -2, "SPARC_INS_LDUH");
	lua_pushinteger(l, 203);
	lua_setfield(l, -2, "SPARC_INS_LDX");
	lua_pushinteger(l, 204);
	lua_setfield(l, -2, "SPARC_INS_LZCNT");
	lua_pushinteger(l, 205);
	lua_setfield(l, -2, "SPARC_INS_MEMBAR");
	lua_pushinteger(l, 206);
	lua_setfield(l, -2, "SPARC_INS_MOVDTOX");
	lua_pushinteger(l, 207);
	lua_setfield(l, -2, "SPARC_INS_MOV");
	lua_pushinteger(l, 208);
	lua_setfield(l, -2, "SPARC_INS_MOVRGEZ");
	lua_pushinteger(l, 209);
	lua_setfield(l, -2, "SPARC_INS_MOVRGZ");
	lua_pushinteger(l, 210);
	lua_setfield(l, -2, "SPARC_INS_MOVRLEZ");
	lua_pushinteger(l, 211);
	lua_setfield(l, -2, "SPARC_INS_MOVRLZ");
	lua_pushinteger(l, 212);
	lua_setfield(l, -2, "SPARC_INS_MOVRNZ");
	lua_pushinteger(l, 213);
	lua_setfield(l, -2, "SPARC_INS_MOVRZ");
	lua_pushinteger(l, 214);
	lua_setfield(l, -2, "SPARC_INS_MOVSTOSW");
	lua_pushinteger(l, 215);
	lua_setfield(l, -2, "SPARC_INS_MOVSTOUW");
	lua_pushinteger(l, 216);
	lua_setfield(l, -2, "SPARC_INS_MULX");
	lua_pushinteger(l, 217);
	lua_setfield(l, -2, "SPARC_INS_NOP");
	lua_pushinteger(l, 218);
	lua_setfield(l, -2, "SPARC_INS_ORCC");
	lua_pushinteger(l, 219);
	lua_setfield(l, -2, "SPARC_INS_ORNCC");
	lua_pushinteger(l, 220);
	lua_setfield(l, -2, "SPARC_INS_ORN");
	lua_pushinteger(l, 221);
	lua_setfield(l, -2, "SPARC_INS_OR");
	lua_pushinteger(l, 222);
	lua_setfield(l, -2, "SPARC_INS_PDIST");
	lua_pushinteger(l, 223);
	lua_setfield(l, -2, "SPARC_INS_PDISTN");
	lua_pushinteger(l, 224);
	lua_setfield(l, -2, "SPARC_INS_POPC");
	lua_pushinteger(l, 225);
	lua_setfield(l, -2, "SPARC_INS_RD");
	lua_pushinteger(l, 226);
	lua_setfield(l, -2, "SPARC_INS_RESTORE");
	lua_pushinteger(l, 227);
	lua_setfield(l, -2, "SPARC_INS_RETT");
	lua_pushinteger(l, 228);
	lua_setfield(l, -2, "SPARC_INS_SAVE");
	lua_pushinteger(l, 229);
	lua_setfield(l, -2, "SPARC_INS_SDIVCC");
	lua_pushinteger(l, 230);
	lua_setfield(l, -2, "SPARC_INS_SDIVX");
	lua_pushinteger(l, 231);
	lua_setfield(l, -2, "SPARC_INS_SDIV");
	lua_pushinteger(l, 232);
	lua_setfield(l, -2, "SPARC_INS_SETHI");
	lua_pushinteger(l, 233);
	lua_setfield(l, -2, "SPARC_INS_SHUTDOWN");
	lua_pushinteger(l, 234);
	lua_setfield(l, -2, "SPARC_INS_SIAM");
	lua_pushinteger(l, 235);
	lua_setfield(l, -2, "SPARC_INS_SLLX");
	lua_pushinteger(l, 236);
	lua_setfield(l, -2, "SPARC_INS_SLL");
	lua_pushinteger(l, 237);
	lua_setfield(l, -2, "SPARC_INS_SMULCC");
	lua_pushinteger(l, 238);
	lua_setfield(l, -2, "SPARC_INS_SMUL");
	lua_pushinteger(l, 239);
	lua_setfield(l, -2, "SPARC_INS_SRAX");
	lua_pushinteger(l, 240);
	lua_setfield(l, -2, "SPARC_INS_SRA");
	lua_pushinteger(l, 241);
	lua_setfield(l, -2, "SPARC_INS_SRLX");
	lua_pushinteger(l, 242);
	lua_setfield(l, -2, "SPARC_INS_SRL");
	lua_pushinteger(l, 243);
	lua_setfield(l, -2, "SPARC_INS_STBAR");
	lua_pushinteger(l, 244);
	lua_setfield(l, -2, "SPARC_INS_STB");
	lua_pushinteger(l, 245);
	lua_setfield(l, -2, "SPARC_INS_STD");
	lua_pushinteger(l, 246);
	lua_setfield(l, -2, "SPARC_INS_ST");
	lua_pushinteger(l, 247);
	lua_setfield(l, -2, "SPARC_INS_STH");
	lua_pushinteger(l, 248);
	lua_setfield(l, -2, "SPARC_INS_STQ");
	lua_pushinteger(l, 249);
	lua_setfield(l, -2, "SPARC_INS_STX");
	lua_pushinteger(l, 250);
	lua_setfield(l, -2, "SPARC_INS_SUBCC");
	lua_pushinteger(l, 251);
	lua_setfield(l, -2, "SPARC_INS_SUBX");
	lua_pushinteger(l, 252);
	lua_setfield(l, -2, "SPARC_INS_SUBXCC");
	lua_pushinteger(l, 253);
	lua_setfield(l, -2, "SPARC_INS_SUB");
	lua_pushinteger(l, 254);
	lua_setfield(l, -2, "SPARC_INS_SWAP");
	lua_pushinteger(l, 255);
	lua_setfield(l, -2, "SPARC_INS_TADDCCTV");
	lua_pushinteger(l, 256);
	lua_setfield(l, -2, "SPARC_INS_TADDCC");
	lua_pushinteger(l, 257);
	lua_setfield(l, -2, "SPARC_INS_T");
	lua_pushinteger(l, 258);
	lua_setfield(l, -2, "SPARC_INS_TSUBCCTV");
	lua_pushinteger(l, 259);
	lua_setfield(l, -2, "SPARC_INS_TSUBCC");
	lua_pushinteger(l, 260);
	lua_setfield(l, -2, "SPARC_INS_UDIVCC");
	lua_pushinteger(l, 261);
	lua_setfield(l, -2, "SPARC_INS_UDIVX");
	lua_pushinteger(l, 262);
	lua_setfield(l, -2, "SPARC_INS_UDIV");
	lua_pushinteger(l, 263);
	lua_setfield(l, -2, "SPARC_INS_UMULCC");
	lua_pushinteger(l, 264);
	lua_setfield(l, -2, "SPARC_INS_UMULXHI");
	lua_pushinteger(l, 265);
	lua_setfield(l, -2, "SPARC_INS_UMUL");
	lua_pushinteger(l, 266);
	lua_setfield(l, -2, "SPARC_INS_UNIMP");
	lua_pushinteger(l, 267);
	lua_setfield(l, -2, "SPARC_INS_FCMPED");
	lua_pushinteger(l, 268);
	lua_setfield(l, -2, "SPARC_INS_FCMPEQ");
	lua_pushinteger(l, 269);
	lua_setfield(l, -2, "SPARC_INS_FCMPES");
	lua_pushinteger(l, 270);
	lua_setfield(l, -2, "SPARC_INS_WR");
	lua_pushinteger(l, 271);
	lua_setfield(l, -2, "SPARC_INS_XMULX");
	lua_pushinteger(l, 272);
	lua_setfield(l, -2, "SPARC_INS_XMULXHI");
	lua_pushinteger(l, 273);
	lua_setfield(l, -2, "SPARC_INS_XNORCC");
	lua_pushinteger(l, 274);
	lua_setfield(l, -2, "SPARC_INS_XNOR");
	lua_pushinteger(l, 275);
	lua_setfield(l, -2, "SPARC_INS_XORCC");
	lua_pushinteger(l, 276);
	lua_setfield(l, -2, "SPARC_INS_XOR");
	lua_pushinteger(l, 277);
	lua_setfield(l, -2, "SPARC_INS_RET");
	lua_pushinteger(l, 278);
	lua_setfield(l, -2, "SPARC_INS_RETL");
	lua_pushinteger(l, 279);
	lua_setfield(l, -2, "SPARC_INS_ENDING");

	/* Group of SPARC instructions */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "SPARC_GRP_INVALID");

	/* Generic groups */
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "SPARC_GRP_JUMP");

	/* Architecture-specific groups */
	lua_pushinteger(l, 128);
	lua_setfield(l, -2, "SPARC_GRP_HARDQUAD");
	lua_pushinteger(l, 129);
	lua_setfield(l, -2, "SPARC_GRP_V9");
	lua_pushinteger(l, 130);
	lua_setfield(l, -2, "SPARC_GRP_VIS");
	lua_pushinteger(l, 131);
	lua_setfield(l, -2, "SPARC_GRP_VIS2");
	lua_pushinteger(l, 132);
	lua_setfield(l, -2, "SPARC_GRP_VIS3");
	lua_pushinteger(l, 133);
	lua_setfield(l, -2, "SPARC_GRP_32BIT");
	lua_pushinteger(l, 134);
	lua_setfield(l, -2, "SPARC_GRP_64BIT");
	lua_pushinteger(l, 135);
	lua_setfield(l, -2, "SPARC_GRP_ENDING");
}

} // namespace Capstone
} // namespace Core
} // namespace PrefLib
