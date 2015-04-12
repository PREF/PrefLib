/* For Capstone Engine. AUTO-GENERATED FILE, DO NOT EDIT */

#include "xcore_const.h"

namespace PrefLib {
namespace Core {
namespace Capstone {

void set_xcore_const(lua_State* l)
{
	/* Operand type for instruction's operands */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "XCORE_OP_INVALID");
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "XCORE_OP_REG");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "XCORE_OP_IMM");
	lua_pushinteger(l, 3);
	lua_setfield(l, -2, "XCORE_OP_MEM");

	/* XCore registers */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "XCORE_REG_INVALID");
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "XCORE_REG_CP");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "XCORE_REG_DP");
	lua_pushinteger(l, 3);
	lua_setfield(l, -2, "XCORE_REG_LR");
	lua_pushinteger(l, 4);
	lua_setfield(l, -2, "XCORE_REG_SP");
	lua_pushinteger(l, 5);
	lua_setfield(l, -2, "XCORE_REG_R0");
	lua_pushinteger(l, 6);
	lua_setfield(l, -2, "XCORE_REG_R1");
	lua_pushinteger(l, 7);
	lua_setfield(l, -2, "XCORE_REG_R2");
	lua_pushinteger(l, 8);
	lua_setfield(l, -2, "XCORE_REG_R3");
	lua_pushinteger(l, 9);
	lua_setfield(l, -2, "XCORE_REG_R4");
	lua_pushinteger(l, 10);
	lua_setfield(l, -2, "XCORE_REG_R5");
	lua_pushinteger(l, 11);
	lua_setfield(l, -2, "XCORE_REG_R6");
	lua_pushinteger(l, 12);
	lua_setfield(l, -2, "XCORE_REG_R7");
	lua_pushinteger(l, 13);
	lua_setfield(l, -2, "XCORE_REG_R8");
	lua_pushinteger(l, 14);
	lua_setfield(l, -2, "XCORE_REG_R9");
	lua_pushinteger(l, 15);
	lua_setfield(l, -2, "XCORE_REG_R10");
	lua_pushinteger(l, 16);
	lua_setfield(l, -2, "XCORE_REG_R11");

	/* pseudo registers */
	lua_pushinteger(l, 17);
	lua_setfield(l, -2, "XCORE_REG_PC");
	lua_pushinteger(l, 18);
	lua_setfield(l, -2, "XCORE_REG_SCP");
	lua_pushinteger(l, 19);
	lua_setfield(l, -2, "XCORE_REG_SSR");
	lua_pushinteger(l, 20);
	lua_setfield(l, -2, "XCORE_REG_ET");
	lua_pushinteger(l, 21);
	lua_setfield(l, -2, "XCORE_REG_ED");
	lua_pushinteger(l, 22);
	lua_setfield(l, -2, "XCORE_REG_SED");
	lua_pushinteger(l, 23);
	lua_setfield(l, -2, "XCORE_REG_KEP");
	lua_pushinteger(l, 24);
	lua_setfield(l, -2, "XCORE_REG_KSP");
	lua_pushinteger(l, 25);
	lua_setfield(l, -2, "XCORE_REG_ID");
	lua_pushinteger(l, 26);
	lua_setfield(l, -2, "XCORE_REG_ENDING");

	/* XCore instruction */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "XCORE_INS_INVALID");
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "XCORE_INS_ADD");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "XCORE_INS_ANDNOT");
	lua_pushinteger(l, 3);
	lua_setfield(l, -2, "XCORE_INS_AND");
	lua_pushinteger(l, 4);
	lua_setfield(l, -2, "XCORE_INS_ASHR");
	lua_pushinteger(l, 5);
	lua_setfield(l, -2, "XCORE_INS_BAU");
	lua_pushinteger(l, 6);
	lua_setfield(l, -2, "XCORE_INS_BITREV");
	lua_pushinteger(l, 7);
	lua_setfield(l, -2, "XCORE_INS_BLA");
	lua_pushinteger(l, 8);
	lua_setfield(l, -2, "XCORE_INS_BLAT");
	lua_pushinteger(l, 9);
	lua_setfield(l, -2, "XCORE_INS_BL");
	lua_pushinteger(l, 10);
	lua_setfield(l, -2, "XCORE_INS_BF");
	lua_pushinteger(l, 11);
	lua_setfield(l, -2, "XCORE_INS_BT");
	lua_pushinteger(l, 12);
	lua_setfield(l, -2, "XCORE_INS_BU");
	lua_pushinteger(l, 13);
	lua_setfield(l, -2, "XCORE_INS_BRU");
	lua_pushinteger(l, 14);
	lua_setfield(l, -2, "XCORE_INS_BYTEREV");
	lua_pushinteger(l, 15);
	lua_setfield(l, -2, "XCORE_INS_CHKCT");
	lua_pushinteger(l, 16);
	lua_setfield(l, -2, "XCORE_INS_CLRE");
	lua_pushinteger(l, 17);
	lua_setfield(l, -2, "XCORE_INS_CLRPT");
	lua_pushinteger(l, 18);
	lua_setfield(l, -2, "XCORE_INS_CLRSR");
	lua_pushinteger(l, 19);
	lua_setfield(l, -2, "XCORE_INS_CLZ");
	lua_pushinteger(l, 20);
	lua_setfield(l, -2, "XCORE_INS_CRC8");
	lua_pushinteger(l, 21);
	lua_setfield(l, -2, "XCORE_INS_CRC32");
	lua_pushinteger(l, 22);
	lua_setfield(l, -2, "XCORE_INS_DCALL");
	lua_pushinteger(l, 23);
	lua_setfield(l, -2, "XCORE_INS_DENTSP");
	lua_pushinteger(l, 24);
	lua_setfield(l, -2, "XCORE_INS_DGETREG");
	lua_pushinteger(l, 25);
	lua_setfield(l, -2, "XCORE_INS_DIVS");
	lua_pushinteger(l, 26);
	lua_setfield(l, -2, "XCORE_INS_DIVU");
	lua_pushinteger(l, 27);
	lua_setfield(l, -2, "XCORE_INS_DRESTSP");
	lua_pushinteger(l, 28);
	lua_setfield(l, -2, "XCORE_INS_DRET");
	lua_pushinteger(l, 29);
	lua_setfield(l, -2, "XCORE_INS_ECALLF");
	lua_pushinteger(l, 30);
	lua_setfield(l, -2, "XCORE_INS_ECALLT");
	lua_pushinteger(l, 31);
	lua_setfield(l, -2, "XCORE_INS_EDU");
	lua_pushinteger(l, 32);
	lua_setfield(l, -2, "XCORE_INS_EEF");
	lua_pushinteger(l, 33);
	lua_setfield(l, -2, "XCORE_INS_EET");
	lua_pushinteger(l, 34);
	lua_setfield(l, -2, "XCORE_INS_EEU");
	lua_pushinteger(l, 35);
	lua_setfield(l, -2, "XCORE_INS_ENDIN");
	lua_pushinteger(l, 36);
	lua_setfield(l, -2, "XCORE_INS_ENTSP");
	lua_pushinteger(l, 37);
	lua_setfield(l, -2, "XCORE_INS_EQ");
	lua_pushinteger(l, 38);
	lua_setfield(l, -2, "XCORE_INS_EXTDP");
	lua_pushinteger(l, 39);
	lua_setfield(l, -2, "XCORE_INS_EXTSP");
	lua_pushinteger(l, 40);
	lua_setfield(l, -2, "XCORE_INS_FREER");
	lua_pushinteger(l, 41);
	lua_setfield(l, -2, "XCORE_INS_FREET");
	lua_pushinteger(l, 42);
	lua_setfield(l, -2, "XCORE_INS_GETD");
	lua_pushinteger(l, 43);
	lua_setfield(l, -2, "XCORE_INS_GET");
	lua_pushinteger(l, 44);
	lua_setfield(l, -2, "XCORE_INS_GETN");
	lua_pushinteger(l, 45);
	lua_setfield(l, -2, "XCORE_INS_GETR");
	lua_pushinteger(l, 46);
	lua_setfield(l, -2, "XCORE_INS_GETSR");
	lua_pushinteger(l, 47);
	lua_setfield(l, -2, "XCORE_INS_GETST");
	lua_pushinteger(l, 48);
	lua_setfield(l, -2, "XCORE_INS_GETTS");
	lua_pushinteger(l, 49);
	lua_setfield(l, -2, "XCORE_INS_INCT");
	lua_pushinteger(l, 50);
	lua_setfield(l, -2, "XCORE_INS_INIT");
	lua_pushinteger(l, 51);
	lua_setfield(l, -2, "XCORE_INS_INPW");
	lua_pushinteger(l, 52);
	lua_setfield(l, -2, "XCORE_INS_INSHR");
	lua_pushinteger(l, 53);
	lua_setfield(l, -2, "XCORE_INS_INT");
	lua_pushinteger(l, 54);
	lua_setfield(l, -2, "XCORE_INS_IN");
	lua_pushinteger(l, 55);
	lua_setfield(l, -2, "XCORE_INS_KCALL");
	lua_pushinteger(l, 56);
	lua_setfield(l, -2, "XCORE_INS_KENTSP");
	lua_pushinteger(l, 57);
	lua_setfield(l, -2, "XCORE_INS_KRESTSP");
	lua_pushinteger(l, 58);
	lua_setfield(l, -2, "XCORE_INS_KRET");
	lua_pushinteger(l, 59);
	lua_setfield(l, -2, "XCORE_INS_LADD");
	lua_pushinteger(l, 60);
	lua_setfield(l, -2, "XCORE_INS_LD16S");
	lua_pushinteger(l, 61);
	lua_setfield(l, -2, "XCORE_INS_LD8U");
	lua_pushinteger(l, 62);
	lua_setfield(l, -2, "XCORE_INS_LDA16");
	lua_pushinteger(l, 63);
	lua_setfield(l, -2, "XCORE_INS_LDAP");
	lua_pushinteger(l, 64);
	lua_setfield(l, -2, "XCORE_INS_LDAW");
	lua_pushinteger(l, 65);
	lua_setfield(l, -2, "XCORE_INS_LDC");
	lua_pushinteger(l, 66);
	lua_setfield(l, -2, "XCORE_INS_LDW");
	lua_pushinteger(l, 67);
	lua_setfield(l, -2, "XCORE_INS_LDIVU");
	lua_pushinteger(l, 68);
	lua_setfield(l, -2, "XCORE_INS_LMUL");
	lua_pushinteger(l, 69);
	lua_setfield(l, -2, "XCORE_INS_LSS");
	lua_pushinteger(l, 70);
	lua_setfield(l, -2, "XCORE_INS_LSUB");
	lua_pushinteger(l, 71);
	lua_setfield(l, -2, "XCORE_INS_LSU");
	lua_pushinteger(l, 72);
	lua_setfield(l, -2, "XCORE_INS_MACCS");
	lua_pushinteger(l, 73);
	lua_setfield(l, -2, "XCORE_INS_MACCU");
	lua_pushinteger(l, 74);
	lua_setfield(l, -2, "XCORE_INS_MJOIN");
	lua_pushinteger(l, 75);
	lua_setfield(l, -2, "XCORE_INS_MKMSK");
	lua_pushinteger(l, 76);
	lua_setfield(l, -2, "XCORE_INS_MSYNC");
	lua_pushinteger(l, 77);
	lua_setfield(l, -2, "XCORE_INS_MUL");
	lua_pushinteger(l, 78);
	lua_setfield(l, -2, "XCORE_INS_NEG");
	lua_pushinteger(l, 79);
	lua_setfield(l, -2, "XCORE_INS_NOT");
	lua_pushinteger(l, 80);
	lua_setfield(l, -2, "XCORE_INS_OR");
	lua_pushinteger(l, 81);
	lua_setfield(l, -2, "XCORE_INS_OUTCT");
	lua_pushinteger(l, 82);
	lua_setfield(l, -2, "XCORE_INS_OUTPW");
	lua_pushinteger(l, 83);
	lua_setfield(l, -2, "XCORE_INS_OUTSHR");
	lua_pushinteger(l, 84);
	lua_setfield(l, -2, "XCORE_INS_OUTT");
	lua_pushinteger(l, 85);
	lua_setfield(l, -2, "XCORE_INS_OUT");
	lua_pushinteger(l, 86);
	lua_setfield(l, -2, "XCORE_INS_PEEK");
	lua_pushinteger(l, 87);
	lua_setfield(l, -2, "XCORE_INS_REMS");
	lua_pushinteger(l, 88);
	lua_setfield(l, -2, "XCORE_INS_REMU");
	lua_pushinteger(l, 89);
	lua_setfield(l, -2, "XCORE_INS_RETSP");
	lua_pushinteger(l, 90);
	lua_setfield(l, -2, "XCORE_INS_SETCLK");
	lua_pushinteger(l, 91);
	lua_setfield(l, -2, "XCORE_INS_SET");
	lua_pushinteger(l, 92);
	lua_setfield(l, -2, "XCORE_INS_SETC");
	lua_pushinteger(l, 93);
	lua_setfield(l, -2, "XCORE_INS_SETD");
	lua_pushinteger(l, 94);
	lua_setfield(l, -2, "XCORE_INS_SETEV");
	lua_pushinteger(l, 95);
	lua_setfield(l, -2, "XCORE_INS_SETN");
	lua_pushinteger(l, 96);
	lua_setfield(l, -2, "XCORE_INS_SETPSC");
	lua_pushinteger(l, 97);
	lua_setfield(l, -2, "XCORE_INS_SETPT");
	lua_pushinteger(l, 98);
	lua_setfield(l, -2, "XCORE_INS_SETRDY");
	lua_pushinteger(l, 99);
	lua_setfield(l, -2, "XCORE_INS_SETSR");
	lua_pushinteger(l, 100);
	lua_setfield(l, -2, "XCORE_INS_SETTW");
	lua_pushinteger(l, 101);
	lua_setfield(l, -2, "XCORE_INS_SETV");
	lua_pushinteger(l, 102);
	lua_setfield(l, -2, "XCORE_INS_SEXT");
	lua_pushinteger(l, 103);
	lua_setfield(l, -2, "XCORE_INS_SHL");
	lua_pushinteger(l, 104);
	lua_setfield(l, -2, "XCORE_INS_SHR");
	lua_pushinteger(l, 105);
	lua_setfield(l, -2, "XCORE_INS_SSYNC");
	lua_pushinteger(l, 106);
	lua_setfield(l, -2, "XCORE_INS_ST16");
	lua_pushinteger(l, 107);
	lua_setfield(l, -2, "XCORE_INS_ST8");
	lua_pushinteger(l, 108);
	lua_setfield(l, -2, "XCORE_INS_STW");
	lua_pushinteger(l, 109);
	lua_setfield(l, -2, "XCORE_INS_SUB");
	lua_pushinteger(l, 110);
	lua_setfield(l, -2, "XCORE_INS_SYNCR");
	lua_pushinteger(l, 111);
	lua_setfield(l, -2, "XCORE_INS_TESTCT");
	lua_pushinteger(l, 112);
	lua_setfield(l, -2, "XCORE_INS_TESTLCL");
	lua_pushinteger(l, 113);
	lua_setfield(l, -2, "XCORE_INS_TESTWCT");
	lua_pushinteger(l, 114);
	lua_setfield(l, -2, "XCORE_INS_TSETMR");
	lua_pushinteger(l, 115);
	lua_setfield(l, -2, "XCORE_INS_START");
	lua_pushinteger(l, 116);
	lua_setfield(l, -2, "XCORE_INS_WAITEF");
	lua_pushinteger(l, 117);
	lua_setfield(l, -2, "XCORE_INS_WAITET");
	lua_pushinteger(l, 118);
	lua_setfield(l, -2, "XCORE_INS_WAITEU");
	lua_pushinteger(l, 119);
	lua_setfield(l, -2, "XCORE_INS_XOR");
	lua_pushinteger(l, 120);
	lua_setfield(l, -2, "XCORE_INS_ZEXT");
	lua_pushinteger(l, 121);
	lua_setfield(l, -2, "XCORE_INS_ENDING");

	/* Group of XCore instructions */

	lua_pushinteger(l, 0);
	lua_setfield(l, -2, "XCORE_GRP_INVALID");

	/* Generic groups */
	lua_pushinteger(l, 1);
	lua_setfield(l, -2, "XCORE_GRP_JUMP");
	lua_pushinteger(l, 2);
	lua_setfield(l, -2, "XCORE_GRP_ENDING");
}

} // namespace Capstone
} // namespace Core
} // namespace PrefLib
