// TODO: remove underline
// TODO: what are you waiting for, remove them! you can do it!
// - noby
// TODO: think of a good naming convention for the de-/compression parsers
// as parser as a name is already taken, I opted for decompression.hpp, maybe do the same for this file?
// - noby
#ifndef PARSER_HPP_
#define PARSER_HPP_

#define TRY_PARSE_BUFFER_SHORT -1
#define TRY_PARSE_INVALID -2

#include <vector>

#include "../parsing/hooker.hpp"

/*
    This class is responsible for parsing records

    Records consist of two parts:
    1. constant part
    2. variable part

    constant part:
    * MUST be available
    * its size MUST be fixed

    variable part:
    * MAY be available
    * its size MUST be dynamic
        * its end MUST be defined by an escape sequence
    * MAY span over the size of a buffer
*/
class Parser
{
protected:
    /*

    */
    Hooker& hooker;

public:
    Parser(Hooker& hooker)
        : hooker(hooker) { }

    /*
        This method decides whether the provided buffer can be parsed or not
        It communicates this information via the returned bool

        It MUST be called first
    */
    virtual int try_parse
    (
        const char* buffer,
        int offset,
        int count
    ) = 0;

    /*
        This method parses the constant part of the provided record

        If the record spans over the size of a buffer:
        * it MUST called only once at the beginning of the record

        It MUST be called before parse_variable()

        It returns the size it has parsed
    */
    virtual int parse_constant
    (
        const char* buffer,
        int offset,
        int count
    ) = 0;

    /*
        This method parses the variable part of the provided record

        If the record spans over the size of a buffer:
        * it MUST called every time the buffer is refilled

        It MUST be called after parse_constant()

        If it was declared, then
        * It returns the size it has parsed
        * or an error (below 0)
        If not then
        * it returns a not implemented error (-404)
    */
    virtual int parse_variable
    (
        const char* buffer,
        int offset,
        int count
    ) { return -404; } // TODO: throw meaningful errors
};

#endif /* end of include guard: PARSER_HPP_ */
