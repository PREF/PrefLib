#ifndef DATAINSPECTOR_H
#define DATAINSPECTOR_H

#define DATA_INSPECTOR_CODE \
    "LittleEndian(); " \
    "union DataInspector {" \
    "  BYTE   __di_byte__;" \
    "  UBYTE  __di_ubyte__;" \
    "  SHORT  __di_short__;" \
    "  USHORT __di_ushort__;" \
    "  INT    __di_int__;" \
    "  UINT   __di_uint__;" \
    "  INT64  __di_int64__;" \
    "  UINT64 __di_uint64__;" \
    "  FLOAT  __di_float__;" \
    "  DOUBLE __di_double__;" \
    "};" \
    "DataInspector __di__;"

#endif // DATAINSPECTOR_H
