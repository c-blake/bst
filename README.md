This one set of files implements well factored/layered binary search trees
(BSTs) with 5 balancing schemes (none, AVL, red-black, L(k), and splay) and 3
indexing styles (keyed & ranked, only by key, or only by position).  API choice
to use `seek_keyS.c:seek_keyS` & `seek_push` supports duplicate keys or not
(with FIFO | LIFO discipline) for all the above.  Optional parent pointers are
also available for all the above.

These 5x3x3x2=90 styles of trees are often be implemented with distinct APIs
(even with type-parameterized template implementations).  The amortized source
complexity here is something like 259 LoC/90=2.88 lines per such tree style.

# Syntactic notes
The generics style is a Cpp `#include/#define _()` namespacing macro style of my
own design dating back to the mid 1990s.  Perhaps the easiest to follow example
instance is [`test/bst-insdel.c`](test/bst-insdel.c).  The idea is `_(_x)` is a
guarded name which the instantiation context makes into a real name. { I tweaked
my editor's code colorizing to make those P)urple for P)rotected, P)rivate,
P)refixed. } This is just one simple way to handle multiple instantiations in
ANSI C, and to my feeling the most direct.[^1]

The macro name convention is to prefix with `BST_` and for CAPITALS to mean SET
{ eg. `BST_WT(node, w)` to set the weight `wt` to `w` } while lowercase means
get { `BST_wt(node)` to read it }.[^2]

# Algorithmic notes

While books/classes usually teach recursive variants, function calls have only
become more expensive relative to alternatives since the 1980s.  Compilers
inlining recursion is limited & finicky.  So, non-recursive root-to-node
path[]-oriented ideas are used when possible.  This is an optimization everyone
mentions yet no one seems to do.  DB folk sometimes call this sort of path a
"cursor", but its most easy to think of it as a more complete pointer into the
data structure.

The binary symmetry of all these algorithms is made explicit via a "direction
index" into a link array of size 2, `s` for s)ide, say.  The complement (`!s`)
is easy with C syntax.  Explicit use of this symmetry can result in much code
reduction (up to 8x in some cases) as well as reasoning reduction (though I have
never tried to teach trees this way).

Up links/parent pointers are allowed & maintained optionally, but this is often
a waste of both space to store & time to update.  Sometime you may really need a
node pointer be enough to delete itself, though (like doubly linked lists).

What I call here "ell"- or L(k)-balance comes from: A New Method for Balancing
Binary Search Trees by Salvador Roura, 2001.  It can be convenient if you want
rank operations but do not want to waste any (post-padding) space on AVL/RB bal
bits.  The other styles are very well known. (Personally, I think splay trees
are overrated - locality of ref must be unrealistically skewed to pay off.)
BSTs are so well studied that there are surely many other balancing schemes that
might be added.  B-trees are usually better (though they often need an "in-node
scalable search" for which BSTs are not a bad answer).

Split & catenate are sort of missing operations, but not useful in a B-tree node
context (since there every B-tree node is its own allocation arena anyway).
Oh, and adding support for interval search trees / other augmentations is likely
little more work than some tweaks to `rot.c` & a new `seek_`.

# API notes

Operations are factored/layered for maximum generality rather than being a
"turn-key/one shot" style.  It is easy to build the latter on top of the former.
For example, there are five `seek_` operations that populate `path[]` arrays.
Any of these can be used first, and then linking into or unlinking from the tree
can be done afterward.  This means only 5+2=7 instead of 5\*3=15 find/put/del
operations.  Missing entries are indicated to the caller by a negative depth and
zero depth is often only possible for the empty tree.  Similarly, for duplicate
keys, rather than 2 types (set/multiset) or a parameter specifying FIFO/etc
order among dup keys, callers use another call, `seek_keyS`, to move the path to
the [01]-extreme of a block of dups.

This clean factoring combined with symmetry and other choices leads the entire
package to be smaller than naive/-\>left/-\>right implementations I've seen of
just red-black-tree delete.

To allow generalization of how to dereference "pointers", a `BST_ctx` context
parameter is present in all API calls, declared as `BST_CTX` in client parameter
lists.  For virtual memory addresses this can be the empty macro.  It will be a
non-empty parameter decl & reference for other allocation schemes, e.g. node
pools/nodes in files.

# Example Usage
[`test/`](test/) has several programs that use all of this machinery to do some
non-trivial calculations like sorting and moving median.  There is also a nice
"shell" (foo-interact) to play around with various tree types & operations and
print colorized trees to terminals.

A more detailed guide to all the files/factoring is as follows:

LoC | File         | Purpose
----|--------------|---------------------------------------------------------
 18 | splay.c      | amortized balance; No metadata BUT caller MUST splay()
  . | .            | [ path[] must also be big to handle lop-sided trees. ]
 16 | ell.c        | rebal for L(k)-pseudo weight balance; only weight metadata
 33 | avl.c        | rebal for height-balance/AVL/Fibonacci
 61 | rb.c         | rebal for Red-Black/binary symmetric B-tree balance
 12 | rot.c        | single-rotation primitive; Also fixes metadata as needed
  9 | init.c       | node metadata init (NOTE: node alloc is external)
  6 | seek\_most.c | query an extremum (min/max)
  8 | seek\_adj.c  | query an adjacent neighbor (predecessor/successor)
  7 | seek\_key.c  | query by key
 23 | seek\_keyS.c | &seek\_push: path=> structural mn/mx in block of eqkey
 10 | seek\_nth.c  | query by rank (when augmented)
 10 | seek\_node.c | compute path given a node (when nodes have up links)
  6 | linkin.c     | link node into tree (after a seek)
 27 | unlink.c     | unlink node from tree (after a seek)
  5 | weight\_up.c | helper func to update weight metadata after linkin/unlink
  8 | rank.c       | compute rank of a path (when augmented)
259 | total        | .
  . | .            | .
  9 | stats.c      | compute tree height, interior path length, num. nodes
 11 | print.c      | print a tree (rotated so depth goes rightward in ttys)
 57 | ck.c         | impl of \_ck to verify tree properties/invariants
  . | .            | .
 52 | MEMBER.h     | inst helper: defines a struct, Clinkage, feature macros
 34 | METHODS.h    | prototypes for all the core API calls
 76 | METHODS.c    | assembles via #include the core API calls
  . | .            | .
  7 | POOL.h       | pool (array of struct) allocator decls
 31 | POOL.c       | pool (array of struct) allocator impl
  2 | VMEM.h       | virtual memory allocator decls
  6 | VMEM.c       | virtual memory allocator impl
  . | .            | .
 40 | UNDEF.h      | clean up macro namespace (for mult.instance per xl unit)

[^1]: In fact, it lacking only relatively backward compatible syntax support in
the pre-processor to have "parameterized files" where a user could add a list
of defines to an inclusion directive say `#include "bst.h" _(_x)=myName_##_x`.
This manual monomorphization has many virtues, but the world has generally been
more warmly receiving of automated instantiation.

[^2]: There may be a violation or two of this general convention such as
`BST_CTX`/`BST_NODE`.
