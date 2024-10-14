#ifndef VOW_GUARD_TUPLE
#define VOW_GUARD_TUPLE

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

typedef struct VowTuple2i
{
    int x;
    int y;
}
VowTuple2i;

typedef struct VowTuple2f
{
    float x;
    float y;
}
VowTuple2f;

typedef struct VowTuple4i
{
    int x;
    int y;
    int z;
    int w;
}
VowTuple4i;

typedef struct VowTuple4f
{
    float x;
    float y;
    float z;
    float w;
}
VowTuple4f;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

VowTuple2i vow_tuple_uniform_2i(int value);
VowTuple2f vow_tuple_uniform_2f(float value);

VowTuple4i vow_tuple_uniform_4i(int value);
VowTuple4f vow_tuple_uniform_4f(float value);

#endif