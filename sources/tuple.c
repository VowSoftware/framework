////////////////////////////////////////////////////////////////////////////////
// Dependencies
////////////////////////////////////////////////////////////////////////////////

#include <vowframework/tuple.h>

////////////////////////////////////////////////////////////////////////////////
// Functions <vowframework/tuple.h>
////////////////////////////////////////////////////////////////////////////////

VowTuple2i vow_tuple_uniform_2i(int value)
{
    const VowTuple2i tuple =
    {
        value,
        value
    };
    return tuple;
}

VowTuple2f vow_tuple_uniform_2f(float value)
{
    const VowTuple2f tuple =
    {
        value,
        value
    };
    return tuple;
}

VowTuple4i vow_tuple_uniform_4i(int value)
{
    const VowTuple4i tuple =
    {
        value,
        value,
        value,
        value
    };
    return tuple;
}

VowTuple4f vow_tuple_uniform_4f(float value)
{
    const VowTuple4f tuple =
    {
        value,
        value,
        value,
        value
    };
    return tuple;
}