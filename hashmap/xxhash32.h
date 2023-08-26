#ifndef XXHASH_BPF_H
#define XXHASH_BPF_H

static inline unsigned int rotateLeft(unsigned int x, unsigned char bits)
{
    return (x << bits) | (x >> (32 - bits));
}

static inline unsigned int xxhash32(const unsigned char *data, unsigned int length, unsigned int seed)
{
    const unsigned int prime1 = 2654435761U;
    const unsigned int prime2 = 2246822519U;
    const unsigned int prime3 = 3266489917U;
    const unsigned int prime4 = 668265263U;
    const unsigned int prime5 = 374761393U;

    unsigned int s0 = seed + prime1 + prime2;
    unsigned int s1 = seed + prime2;
    unsigned int s2 = seed;
    unsigned int s3 = seed - prime1;

    const unsigned char *stop = data + length;
    const unsigned char *stop_block = stop - 16;

    while (data <= stop_block)
    {
        const unsigned int *block = (const unsigned int *)data;
        s0 = rotateLeft(s0 + block[0] * prime2, 13) * prime1;
        s1 = rotateLeft(s1 + block[1] * prime2, 13) * prime1;
        s2 = rotateLeft(s2 + block[2] * prime2, 13) * prime1;
        s3 = rotateLeft(s3 + block[3] * prime2, 13) * prime1;
        data += 16;
    }

    unsigned int result = length;
    if (length >= 16)
    {
        result += rotateLeft(s0, 1) +
                  rotateLeft(s1, 7) +
                  rotateLeft(s2, 12) +
                  rotateLeft(s3, 18);
    }
    else
    {
        result += s2 + prime5;
    }

    for (; data + 4 <= stop; data += 4)
    {
        result = rotateLeft(result + *(unsigned int *)data * prime3, 17) * prime4;
    }

    while (data != stop)
    {
        result = rotateLeft(result + (*data++) * prime5, 11) * prime1;
    }

    result ^= result >> 15;
    result *= prime2;
    result ^= result >> 13;
    result *= prime3;
    result ^= result >> 16;

    return result;
}

#endif