include defs.mk
I = -I../..
C = $(CFLAGS) -I../.. $(Ow) -Wno-unused-value

PROGS = mmed-cmd splay-interact splay-insdel splay-sort \
	ell-interact ell-mmed ell-mmed2 ell-insdel ell-sort \
	avl-interact avl-mmed avl-mmed2 avl-insdel avl-sort \
	rb-interact  rb-mmed  rb-mmed2  rb-insdel  rb-sort

all: $(PROGS)

mmed-cmd: mmed-cmd.c
	$(CC) $(C) -o $@ $< $(LDFLAGS)

splay-interact	: bst-interact.c; $(CC) $(C)                -o $@ $< $(LDFLAGS)
ell-interact	: bst-interact.c; $(CC) $(C) -DBST_WEIGHTED -o $@ $< $(LDFLAGS)
avl-interact	: bst-interact.c; $(CC) $(C) -DBST_AVL      -o $@ $< $(LDFLAGS)
rb-interact	: bst-interact.c; $(CC) $(C) -DBST_RB       -o $@ $< $(LDFLAGS)

splay-insdel	: bst-insdel.c; $(CC) $(C)                -o $@ $< $(LDFLAGS)
ell-insdel	: bst-insdel.c; $(CC) $(C) -DBST_WEIGHTED -o $@ $< $(LDFLAGS)
avl-insdel	: bst-insdel.c; $(CC) $(C) -DBST_AVL      -o $@ $< $(LDFLAGS)
rb-insdel	: bst-insdel.c; $(CC) $(C) -DBST_RB       -o $@ $< $(LDFLAGS)

ell-mmed	: bst-mmed.c  ; $(CC) $(C)           -o $@ $< $(LDFLAGS)
avl-mmed	: bst-mmed.c  ; $(CC) $(C) -DBST_AVL -o $@ $< $(LDFLAGS)
rb-mmed		: bst-mmed.c  ; $(CC) $(C) -DBST_RB  -o $@ $< $(LDFLAGS)

ell-mmed2	: bst-mmed.c  ; $(CC) $(C) -DPOOL           -o $@ $< $(LDFLAGS)
avl-mmed2	: bst-mmed.c  ; $(CC) $(C) -DPOOL -DBST_AVL -o $@ $< $(LDFLAGS)
rb-mmed2	: bst-mmed.c  ; $(CC) $(C) -DPOOL -DBST_RB  -o $@ $< $(LDFLAGS)

splay-sort	: bst-sort.c  ; $(CC) $(C)            -o $@ $< $(LDFLAGS)
ell-sort	: bst-sort.c  ; $(CC) $(C) -DWEIGHTED -o $@ $< $(LDFLAGS)
avl-sort	: bst-sort.c  ; $(CC) $(C) -DBST_AVL  -o $@ $< $(LDFLAGS)
rb-sort		: bst-sort.c  ; $(CC) $(C) -DBST_RB   -o $@ $< $(LDFLAGS)

clean:
	rm -f $(PROGS) *.gmon *.out *core*
