#include "header.h"
int hash_buffer[8];

uint32_t sha_right_shift(uint32_t x, uint32_t n)
{
    return x >> n;
}
uint32_t sha_circular_right_shift(uint32_t x, uint32_t n)
{
    return (x >> n) | (x << (32 - n));
}
uint32_t sha_circular_left_shift(uint32_t x, uint32_t n)
{
    return (x << n) | (x >> (32 - n));
}
uint32_t choice(uint32_t x, uint32_t y, uint32_t z)
{
    // choose between bits of y or z
    // say x is 0 then return bit of z
    // say x is 1 then return bit of y
    return (x & y) ^ (~x & z);
}
uint32_t majority(uint32_t x, uint32_t y, uint32_t z)
{
    // return the majority bit of x, y, and z
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t sha_loop_operation1(uint32_t x)
{
    return sha_circular_right_shift(x, 7) ^ sha_circular_right_shift(x, 18) ^ sha_right_shift(x, 3);
}
uint32_t sha_loop_operation2(uint32_t x)
{
    return sha_circular_right_shift(x, 17) ^ sha_circular_right_shift(x, 19) ^ sha_right_shift(x, 10);
}
uint32_t sha_message_function1(uint32_t x)
{
    return sha_circular_right_shift(x, 2) ^ sha_circular_right_shift(x, 13) ^ sha_circular_right_shift(x, 22);
}
uint32_t sha_message_function_2(uint32_t x)
{
    return sha_circular_right_shift(x, 6) ^ sha_circular_right_shift(x, 11) ^ sha_circular_right_shift(x, 25);
}

void init_message_digest(word W[64], const byte data_stream[])
{

    word i = 0, j = 0;
    // data stream is one byte data at a time ( 8 bits ) , to fill first 16 blocks of message digest ( each of size 32 bits)
    // 4 data stream blocks , to fill the places
    // left shifting so as to append 0's to the right of the data stream
    for (; i < 16; i++, j += 4)
    {
        W[i] = (data_stream[j] << 24) | (data_stream[j + 1] << 16) | (data_stream[j + 2] << 8) | data_stream[j + 3];
    }

    for (i = 16; i < 64; i++)
    {
        word tmp1, tmp2;
        tmp1 = sha_loop_operation1(W[i - 15]);
        tmp2 = sha_loop_operation2(W[i - 2]);
        W[i] = W[i - 16] + tmp1 + W[i - 7] + tmp2;
    }
}

void sha256_mainloop(const byte data_stream[])
{
    word a, b, c, d, e, f, g, h;
    word W[64];
    init_message_digest(W, data_stream);
    a = hash_buffer[0];
    b = hash_buffer[1];
    c = hash_buffer[2];
    d = hash_buffer[3];
    e = hash_buffer[4];
    f = hash_buffer[5];
    g = hash_buffer[6];
    h = hash_buffer[7];

    // the main loop starts
    for (word i = 0; i < 64; i++)
    {
        word T1 = h + sha_message_function_2(e) + choice(e, f, g) + sha_256_keys[i] + W[i];
        word T2 = sha_message_function1(a) + majority(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    hash_buffer[0] += a;
    hash_buffer[1] += b;
    hash_buffer[2] += c;
    hash_buffer[3] += d;
    hash_buffer[4] += e;
    hash_buffer[5] += f;
    hash_buffer[6] += g;
    hash_buffer[7] += h;
}

void SHA256(const byte data_stream[], size_t data_length, byte output_hash[])
{

    hash_buffer[0] = 0x6a09e667;
    hash_buffer[1] = 0xbb67ae85;
    hash_buffer[2] = 0x3c6ef372;
    hash_buffer[3] = 0xa54ff53a;
    hash_buffer[4] = 0x510e527f;
    hash_buffer[5] = 0x9b05688c;
    hash_buffer[6] = 0x1f83d9ab;
    hash_buffer[7] = 0x5be0cd19;
    word i = 0;
    word len = 0;
    byte temp_buffer[64];
    // compute the hash of all the possible 512 bit blocks
    for (i = 0; i < data_length; i++)
    {
        temp_buffer[len] = data_stream[i];
        len++;
        if (len == 64)
        {
            sha256_mainloop(temp_buffer);
            len = 0;
        }
    }

    // each character is 8 bits we need to pad data till 448 or 448/8 = 56
    if (len < 56)
    {
        temp_buffer[len] = 0x80; // pad 1 1 bit
        len++;
        while (len < 56)
        {
            temp_buffer[len] = 0x00; // pad rest 0's
            len++;
        }
    }
    else
    {
        // will have to pad
        temp_buffer[len] = 0x80; // pad 1 1 bit
        len++;
        while (len < 64)
        {
            temp_buffer[len] = 0x00; // pad rest 0's
            len++;
        }
        sha256_mainloop(temp_buffer);
        memset(temp_buffer, 0, 56);
    }
    // pad the length of the message in bits
    temp_buffer[56] = (data_length * 8) >> 56;
    temp_buffer[57] = (data_length * 8) >> 48;
    temp_buffer[58] = (data_length * 8) >> 40;
    temp_buffer[59] = (data_length * 8) >> 32;
    temp_buffer[60] = (data_length * 8) >> 24;
    temp_buffer[61] = (data_length * 8) >> 16;
    temp_buffer[62] = (data_length * 8) >> 8;
    temp_buffer[63] = (data_length * 8);
    sha256_mainloop(temp_buffer);

    // copy the hash to the output buffer
    // to reverse the bytes ( convert to big endian )

    for (i = 0; i < 4; i++)
    {
        output_hash[i] = (hash_buffer[0] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 4] = (hash_buffer[1] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 8] = (hash_buffer[2] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 12] = (hash_buffer[3] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 16] = (hash_buffer[4] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 20] = (hash_buffer[5] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 24] = (hash_buffer[6] >> (24 - i * 8)) & 0x000000ff;
        output_hash[i + 28] = (hash_buffer[7] >> (24 - i * 8)) & 0x000000ff;
    }
}

/*
int main(int argc, char *argv[])
{
    // int n;
    // byte data[] = argv[1];

    string s;
    cout << "Enter The String Whose Hash is to be done" << endl;
    cin >> s;
    byte output_hash[64];
    SHA256((const byte *)s.c_str(), s.length(), output_hash);
    cout << "The Hash is : ";
    for (int i = 0; i < 32; i++)
    {
        printf("%02x", output_hash[i]);
    }
    cout << endl;

    return 0;
}
*/