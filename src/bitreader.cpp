#include <math.h>

#include "bitreader.hpp"

BitReader::BitReader(LZMAFILE* file)
    : file(file)
    , buffer(0)
    , offset(0)
{
    //auto c = getc(file);
    char c;
    lzmaread(&c, sizeof(char), 1, file);
    if (c == EOF)
        // TODO: Throw a specified for this case value (not just 0)
        throw 0;
    buffer = c;
}

uint8_t BitReader::read_unaligned_byte()
{
    //auto c = getc(file);
    char c;
    int num = lzmaread(&c, sizeof(char), 1, file);
    // checking an lzmaread char that is later parsed into an uint anyway
    // is dangerous, as the next uint digit may just happen to equal EOF
    // in it's char representation
    // TODO: eventually bring back EOF check, but implemented in a less
    // horribly wrong way
    //if (uint8_t(c) == EOF)
        // TODO: Throw a specified value for this case (not just 0)
        //throw 0;
    // edit: actual solution to the above, as suggested by @UgiNyaa
    if (num == 0) {
        throw 0;
    }
    return uint8_t(c);
}

uint64_t BitReader::read(uint8_t count)
{
    if (offset == 8)
    {
        buffer = read_unaligned_byte();
        offset = 0;
    }
    uint64_t data = 0;
    auto _offset = 0;
    do
    {
        auto bitsLeft = 8 - offset;
        if (bitsLeft >= count)
        {
            data |= (buffer & uint64_t(pow(2, count) - 1)) << _offset;
            offset += count;
            buffer = uint8_t(buffer >> count);
            return data;
        }
        data |= uint64_t(buffer) << _offset;
        count -= uint8_t(bitsLeft);
        _offset += bitsLeft;
        offset = 0;
        buffer = read_unaligned_byte();
    } while(count > 0);
    return data;
}

uint8_t BitReader::read_byte(uint8_t count)
{
    if (offset == 8 && count == 8)
        return read_unaligned_byte();
    return uint8_t(read(count));
}
