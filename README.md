a) For p1.cc, the threshold number is 139.
b) There are bugges when running segmenting objects. 
   where the cluster does not sink when looping on the
   second phase with equlivance table, which implemented 
   with `DisjdSet.cc`. So I should get re-implement 
   the `unionSet( ) ` method within the .cc file.


c) Please, fell free to use my `Makefile` for debugging and testing.
