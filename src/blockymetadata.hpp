#ifndef BLOCKYMETADATA_HPP
#define BLOCKYMETADATA_HPP

#include <vector>
#include <memory>

#include "bitreader.hpp"
#include "bitwriter.hpp"
#include "blockynumber.hpp"

using namespace std;

class BlockyMetadata
{
public:
    int32_t ValueCount;
    uint8_t MaxNeededBitsNumber;
    uint8_t MaxNeededBitsNeededBitsNumber;
    uint8_t MaxNeededBitsExponent;
    bool IsAbsolute;
    bool IsNegative;
    bool NoExponent;
    uint64_t LargestPossibleValue;

    BlockyMetadata()
        : ValueCount(0)
        , MaxNeededBitsNumber(0)
        , MaxNeededBitsNeededBitsNumber(0)
        , MaxNeededBitsExponent(0)
        , IsAbsolute(0)
        , IsNegative(0) { }

    void write(BitWriter& writer);

    static BlockyMetadata from_bit_stream(BitReader& reader);
    //static BlockyMetadata from_compressed_data(LZMAFILE* data);
    static BlockyMetadata from_data(shared_ptr<BlockyNumber>* values, size_t n);
};

#endif /* end of include guard: BLOCKYMETADATA_HPP */
