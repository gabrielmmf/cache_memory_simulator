# CACHE MEMORY SIMULATOR

## Project goals

Develop one-level cache simulator

Input => memory accesses

Output => Which line the RAM memory block will be stored

Least Recently Used page replacement policy

## Simulator Specification

Output file name => simulator

Arguments:

1. Cache size (4096 = 4KB)

2. Size of each line (1024 = 1KB)

3. Size of each group (2 = 2-way associative)

4. File name with memory accesses

Fixed parameters:

1. 32-bit addressing

2. Addresses reference bytes

3. LRU Replacement Policy

## Planning

1. Implement a Data Structure representing a memory

2. Initialize memory with cache_size, line_size, group_size parameters

3. Create the access function that receives an address and simulates its access:

    1. Calculates displacement, tag and identifier

    2. Use the tag to access a group

       1. If the identifier is in the group: Move to the last place in the leastRecentlyUsed list

       2. Else:

          1. If the group is full:

             1. Finds the first in the list of leastRecentlyUsed in groups
             2. Replace it
             3. Removes the first from the list of leastRecentlyUsed

          2. Else: Inserts the identifier at the end of the group

          3. Insert the identifier at the end of the leastRecentlyUsed list
