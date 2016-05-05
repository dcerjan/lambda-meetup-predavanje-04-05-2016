#ifndef _Types_h_
#define _Types_h_

#include <stdio.h>
#include <stdint.h>

#include "List.h"

#ifndef __APPLE__
typedef enum Bool {
    True    = 1,
    False   = 0,
    Yes     = 1,
    No      = 0
} Bool;
#endif

/* Basic value types */
typedef char            Char;
typedef char*           String;

typedef char            Byte;
typedef short           Short;
typedef int             Int;
typedef long            Long;
typedef int32_t         Int32;
typedef int64_t         Int64;

typedef unsigned char   UByte;
typedef unsigned short  UShort;
typedef unsigned int    UInt;
typedef unsigned long   ULong;
typedef uint32_t        UInt32;
typedef uint64_t        UInt64;

typedef float           Float;
typedef double          Double;


#define Show(Type, val) Show ## _ ## Type (val)

/* builtin types inspection */
#define Show_Char(var)               fprintf(stdout, "'%c'", var);
#define Show_String(var)             fprintf(stdout, "\"%s\"", var);

#define Show_Byte(var)               fprintf(stdout, "Byte(%d)",  var);
#define Show_Short(var)              fprintf(stdout, "Short(%hd)", var)
#define Show_Int(var)                fprintf(stdout, "%d",  var)
#define Show_Long(var)               fprintf(stdout, "Long(%ld)", var);
#define Show_Int32(var)              fprintf(stdout, "Int32(%d)", var);
#define Show_Int64(var)              fprintf(stdout, "Int64(%ld)", var);

#define Show_UByte(var)              fprintf(stdout, "UByte(%hd)", var;
#define Show_UShort(var)             fprintf(stdout, "UShort(%hu)", var)
#define Show_UInt(var)               fprintf(stdout, "UInt(%u)", var);
#define Show_ULong(var)              fprintf(stdout, "ULong(%lu)", var);
#define Show_UInt32(var)             fprintf(stdout, "UInt32(%u)", var);
#define Show_UInt64(var)             fprintf(stdout, "UInt64(%lu)", var);

#define Show_Float(var)              fprintf(stdout, "%f", var);
#define Show_Double(var)             fprintf(stdout, "Double(%g)", var);

void Log(const char* message) {
    fprintf(stdout, "%s\n", message);
}

void Endl(void) {
    fprintf(stdout, "\n");
}

#endif // _Types_h_ included