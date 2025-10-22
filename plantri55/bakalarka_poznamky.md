# Bakalarka

## Vyber z prace

### Kanonicky kod
The method of isomorph rejection used by plantri is the canonical construction
path method of McKay [36] (also called the method of canonical augmentation [34]).

### Vyroba kanonickeho kodu

This method is evidently of quadratic time, but in practice we can make it much
faster on average. Instead of starting at every pair (v, e), we need start only at some
combinatorially-defined subset of such pairs. For example, we could choose v to be a
vertex of maximum degree, and, subject to that, e to be an edge incident with v that
is incident with a face of largest size. Moreover, we can abort a scan as soon as it
becomes apparent that it can give neither an automorphism nor a canonical labelling.
This speedup is improved by using a nontrivial invariant, such as the degree, for the
colour of each vertex.

### numbering
static EDGE $*numbering[2*MAXE][MAXE]$; 
  /* holds numberings produced by canon() or canon_edge() */


### test_canon
testcanon(EDGE *givenedge, int representation[], int colour[])
/* Tests whether starting from a given edge and constructing the code in
   "->next" direction, an automorphism or even a better representation 
   can be found. Returns 0 for failure, 1 for an automorphism and 2 for 
   a better representation.  This function exits as soon as a better 
   representation is found. A function that computes and returns the 
   complete better representation can work pretty similar.*/
{


### find_extensions
find_extensions(int numb_total, int numb_pres,
                EDGE *ext3[], int *numext3, 
                EDGE *ext4[], int *numext4,
                EDGE *ext5[], int *numext5)

/* Find all nonequivalent places for extension.
   These are listed in ext# according to the degree of the future new vertex.  
   The number of cases is returned in next# (#=3,4,5). */
{

## Analyza kodu
Hlavny sposob generacie triangulacii je cez scansimple. Dostava sa tam cez simple_dispatch

Potrebujem si pozriet:
make_colour(
canon(
valid5edge(

## Poznamky
Nezabudnit pri robeni vlastnych operacii nastavit spravne first_edge. Treba aj po extend aj po reduce