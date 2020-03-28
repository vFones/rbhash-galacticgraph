# Red Black hash - Galactic Graph

School project about datastructures and algorithms.

### Red-black tree of hash-tables
Suppose you need to store a set of tuples contained in a file in the following format:
key1:key2:data
where key1 and key2 are integers and data is an alphanumeric string of arbitrary
length. Design and implement a data structure consisting of a red-black tree in which
each node points to a hash table. In particular, key1 is used to identify the node of the
red-black tree and key2 to index the hash table where data is stored. The data
structure must provide methods for inserting, searching and deleting tuples. Provide
the program with a menu from which it is possible to recall the above operations.


### Galactics Travels
With the queen's award, Ros Walker bought her new spaceship and is planning the
first galactic journey. It has a map showing all the known star systems with the
possible routes in hyperspace to move from one point to another, with the necessary
times.
Some of these systems contain a wormhole, a space-time tunnel with which it is
possible to move directly from one point of the universe to another, with a unitary
time.
Having fixed a starting point A in a star system, it is necessary to calculate which is
the fastest path to another star system B.

### TODO
The projects aren't perfect and present two bugs:
* Red black hash doesn't work with CRLR files
* Galactics travels got an error during wormholes load. Must use Ws node instead of last W/B nodes in files.
