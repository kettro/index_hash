#IndexHash

A hash table with smart indexing!

In the spirit of SQL's indexing, indexes files based on a frequency of usage.
When not indexed, it uses a bin-array hash table that expands as it fills.

It uses a hash algorithm used by sdbm via http://www.cse.yorku.ca/~oz/hash.html.
Overhead occurs when the hash fills (obviously), but should be usually 
quite quick when it comes to finding.

Collisions are handled linearly; because each bin has relatively few members,
the overhead in a collision is rarely more than 1 or 2. Bins are resized after
50% capacity is reached in any one bin.
