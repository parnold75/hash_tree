#include <gtest/gtest.h>
#include <hash_tree.hpp>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/eccrypto.h>
#include <cryptopp/sha.h>

static const int HASH_SIZE = CryptoPP::SHA256::DIGESTSIZE;

/**
 * Hilfsfunktion zum Erstellen eines Hashes.
 * @param value A hash value is generated from this value.
 * @param hash_value The generated hash value is written into this buffer.
 */
byte *gen_hash_by_uint(uint32_t value, byte *hash_value)
{
    CryptoPP::SHA256 hash;

    byte data_buffer[sizeof(uint32_t)] = {0};

    memcpy(data_buffer, &value, sizeof(uint32_t));
    hash.Update(data_buffer, sizeof(uint32_t));
    hash.Final(hash_value);

    return hash_value;
}

/**
 * Check Empty
 * 
 */
TEST(HashTreeTest, CheckEmpty)
{
    byte hash[CryptoPP::SHA256::DIGESTSIZE];
    gen_hash_by_uint(0u, hash);
    hash_tree sut;
    EXPECT_EQ(0, sut.contains(hash, CryptoPP::SHA256::DIGESTSIZE));
}

/**
 * Add a hash value multiple times.
 * 
 */
TEST(HashTreeTest, Add_a_hash_value_multiple_times)
{
    byte hash[CryptoPP::SHA256::DIGESTSIZE];
    gen_hash_by_uint(0u, hash);
    hash_tree sut;

    EXPECT_EQ(0, sut.contains(hash, CryptoPP::SHA256::DIGESTSIZE));
    sut.insert(hash, CryptoPP::SHA256::DIGESTSIZE);
    sut.insert(hash, CryptoPP::SHA256::DIGESTSIZE);
    EXPECT_EQ(1, sut.contains(hash, CryptoPP::SHA256::DIGESTSIZE));
}

/**
 * Add multiple hash value. It is tested before and after if this hash value is present.
 * 
 */
TEST(HashTreeTest, ContainsInsertTest)
{
    const uint32_t number_of_inserts = 100;
    hash_tree sut;

    byte hash[HASH_SIZE] = {0};
    uint32_t value = 0;

    while (true)
    {
        gen_hash_by_uint(value, hash);

        auto actual = sut.contains(hash, HASH_SIZE);
        EXPECT_EQ(0, actual);
        if (actual != 0)
        {
            break;
        }

        sut.insert(hash, HASH_SIZE);

        actual = sut.contains(hash, HASH_SIZE);
        EXPECT_EQ(1, actual);
        if (actual != 1)
        {
            break;
        }
        value++;

        if (value > number_of_inserts)
        {
            break;
        }
    }

    sut.clear();
}

/**
 * Run all tests
 * 
 */
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
