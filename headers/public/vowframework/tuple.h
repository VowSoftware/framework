#ifndef VOW_GUARD_TUPLE
#define VOW_GUARD_TUPLE

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
// Creates a two-integer tuple, where each field is initialized to `value`.
//
// Parameters
//   * `value`: Initialization value.
//
// Returns
//   * [Success] `VowTuple2i`
////////////////////////////////////////////////////////////////////////////////
VowTuple2i vow_tuple_uniform_2i(int value);

////////////////////////////////////////////////////////////////////////////////
// Creates a two-float tuple, where each field is initialized to `value`.
//
// Parameters
//   * `value`: Initialization value.
//
// Returns
//   * [Success] `VowTuple2f`
////////////////////////////////////////////////////////////////////////////////
VowTuple2f vow_tuple_uniform_2f(float value);

////////////////////////////////////////////////////////////////////////////////
// Creates a four-integer tuple, where each field is initialized to `value`.
//
// Parameters
//   * `value`: Initialization value.
//
// Returns
//   * [Success] `VowTuple4i`
////////////////////////////////////////////////////////////////////////////////
VowTuple4i vow_tuple_uniform_4i(int value);

////////////////////////////////////////////////////////////////////////////////
// Creates a four-float tuple, where each field is initialized to `value`.
//
// Parameters
//   * `value`: Initialization value.
//
// Returns
//   * [Success] `VowTuple4f`
////////////////////////////////////////////////////////////////////////////////
VowTuple4f vow_tuple_uniform_4f(float value);

#endif