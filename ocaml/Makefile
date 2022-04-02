PROG=test
OBJECT_FILES=main.o mod.a

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJECT_FILES)
	gcc -o $@ $^ -lcurses -lm 

%.o: %.c
	gcc -c -std=c11 -o $@ $^ -I `ocamlc -where`


%.a: %.ml %_wrap.c
	ocamlopt -output-obj -o $*caml.o $*.ml
	ocamlc -c $*_wrap.c
	cp `ocamlopt -where`/libasmrun.a $*.a
	chmod +w $*.a
	ar r $*.a $*caml.o $*_wrap.o

clean:
	-rm -f *.cmi
	-rm -f *.cmx
	-rm -f *.o
	-rm -f *.a
	-rm -f $(PROG)