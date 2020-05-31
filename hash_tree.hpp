#ifndef __HASH_TREE_HPP__
#define __HASH_TREE_HPP__

#pragma once

#include <memory>
#include <vector>
#include <map>

typedef unsigned char byte;

/**
 * hash_tree stores hash value in a tree for quick searches for the presence of already stored hash values.
 *
 */
struct hash_tree
{
    std::map<byte, std::shared_ptr<struct hash_tree>> children;

    /**
     * Deletes the entire contents.
     * 
     */
    ~hash_tree()
    {
        children.clear();
    }

    /**
     * Checks whether a hash value already exists
     * @param hash Contains the hash value.
     * @param length The length of the hash.
     */
    int contains(byte *hash, int length)
    {
        auto This = this;

        for (int i = 0; i < length; i++)
        {
            auto next = This->children.find(hash[i]);

            if (next == This->children.end())
            {
                return 0;
            }

            This = next->second.get();
        }
        return 1;
    }

    /**
     * Adds a new hash value. If the hash value already existed, nothing happens.
     * @param hash Contains the hash value.
     * @param length The length of the hash.
     */
    void insert(byte *hash, int length)
    {
        auto This = this;

        for (int i = 0; i < length; i++)
        {
            auto next = This->children.find(hash[i]);

            if (next == This->children.end())
            {
                This->children[hash[i]] = std::make_shared<struct hash_tree>();
                This = This->children[hash[i]].get();
                continue;
            }

            This = next->second.get();
        }
    }

    /**
     * Deletes the entire contents.
     *
     */
    void clear()
    {
        children.clear();
    }
};

#endif
