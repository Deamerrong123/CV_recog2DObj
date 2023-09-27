a) For p1.cc, the threshold number is 139.
b) There are bugges when running segmenting objects. 
   where the cluster does not sink when looping on the
   second phase with equlivance table, which implemented 
   with `DisjdSet.cc`. So I should get re-implement 
   the `unionSet( ) ` method within the .cc file.

**NOTE** Should include the `DisjSets.cc` while compliing. Since I had modified the `unionSets( )` on this file.


c) Please, fell free to use my `Makefile` for debugging and testing.
