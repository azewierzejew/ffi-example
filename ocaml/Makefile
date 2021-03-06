PROG=test
DEPS=dep_haskell.d dep_c.d dep_ocaml.d
HASKELL_FILES=$(wildcard *.hs)
C_FILES=$(wildcard *.c)
OCAML_FILES=mod.ml
OBJECT_FILES=$(C_FILES:.c=.o) $(HASKELL_FILES:.hs=.o) ocaml_object.o

.PHONY: all clean

all: $(PROG)

%.o %.hi %_stub.h: %.hs
	ghc -c -no-keep-hi-files $<

%.o: %.c
	gcc -c -std=c11 -Wall -Wextra -o $@ $< -I `ocamlc -where` -I /usr/lib/ghc-9.0.2/include

ocaml_object.o: $(OCAML_FILES)
	ocamlopt -output-obj -o $@ $^

camlruntime.a: $(OCAML_FILES)
	cp `ocamlopt -where`/libasmrun.a $@

clean:
	-rm -f *.o
	-rm -f *.hi
	-rm -f *.cmi
	-rm -f *.cmx
	-rm -f *.a
	-rm -f *.d
	-rm -f *.d.bak
	-rm -f $(PROG)

ifneq ($(HASKELL_FILES),)
%_haskell.d: $(HASKELL_FILES)
	ghc -M -dep-suffix=. -dep-makefile $@ $^
else
%_haskell.d:
	touch $@
endif

%_c.d: $(C_FILES)
	rm -f $@
	gcc -MM $^ >$@

%_ocaml.d: $(OCAML_FILES)
	rm -f $@
	ocamldep -all $^ $(^:.ml=.mli) >$@


$(PROG): $(OBJECT_FILES)
	@echo Linking program.
	@echo Linked files: $^
	@gcc \
	-Wl,--no-as-needed \
	-no-pie \
	-fno-PIC \
	-o $@ \
	$^ \
	/usr/lib/ocaml/libasmrun.a \
	-Wl,--gc-sections \
	-L/usr/lib/ghc-9.0.2/base-4.15.1.0 \
	-L/usr/lib/ghc-9.0.2/ghc-bignum-1.1 \
	-L/usr/lib/ghc-9.0.2/ghc-prim-0.7.0 \
	-L/usr/lib/ghc-9.0.2/rts \
	-Wl,-u,base_GHCziTopHandler_runIO_closure \
	-Wl,-u,base_GHCziTopHandler_runNonIO_closure \
	-Wl,-u,ghczmprim_GHCziTuple_Z0T_closure \
	-Wl,-u,ghczmprim_GHCziTypes_True_closure \
	-Wl,-u,ghczmprim_GHCziTypes_False_closure \
	-Wl,-u,base_GHCziPack_unpackCString_closure \
	-Wl,-u,base_GHCziWeak_runFinalizzerBatch_closure \
	-Wl,-u,base_GHCziIOziException_stackOverflow_closure \
	-Wl,-u,base_GHCziIOziException_heapOverflow_closure \
	-Wl,-u,base_GHCziIOziException_allocationLimitExceeded_closure \
	-Wl,-u,base_GHCziIOziException_blockedIndefinitelyOnMVar_closure \
	-Wl,-u,base_GHCziIOziException_blockedIndefinitelyOnSTM_closure \
	-Wl,-u,base_GHCziIOziException_cannotCompactFunction_closure \
	-Wl,-u,base_GHCziIOziException_cannotCompactPinned_closure \
	-Wl,-u,base_GHCziIOziException_cannotCompactMutable_closure \
	-Wl,-u,base_GHCziIOPort_doubleReadException_closure \
	-Wl,-u,base_ControlziExceptionziBase_nonTermination_closure \
	-Wl,-u,base_ControlziExceptionziBase_nestedAtomically_closure \
	-Wl,-u,base_GHCziEventziThread_blockedOnBadFD_closure \
	-Wl,-u,base_GHCziExceptionziType_divZZeroException_closure \
	-Wl,-u,base_GHCziExceptionziType_underflowException_closure \
	-Wl,-u,base_GHCziExceptionziType_overflowException_closure \
	-Wl,-u,base_GHCziConcziSync_runSparks_closure \
	-Wl,-u,base_GHCziConcziIO_ensureIOManagerIsRunning_closure \
	-Wl,-u,base_GHCziConcziIO_interruptIOManager_closure \
	-Wl,-u,base_GHCziConcziIO_ioManagerCapabilitiesChanged_closure \
	-Wl,-u,base_GHCziConcziSignal_runHandlersPtr_closure \
	-Wl,-u,base_GHCziTopHandler_flushStdHandles_closure \
	-Wl,-u,base_GHCziTopHandler_runMainIO_closure \
	-Wl,-u,ghczmprim_GHCziTypes_Czh_con_info \
	-Wl,-u,ghczmprim_GHCziTypes_Izh_con_info \
	-Wl,-u,ghczmprim_GHCziTypes_Fzh_con_info \
	-Wl,-u,ghczmprim_GHCziTypes_Dzh_con_info \
	-Wl,-u,ghczmprim_GHCziTypes_Wzh_con_info \
	-Wl,-u,base_GHCziPtr_Ptr_con_info \
	-Wl,-u,base_GHCziPtr_FunPtr_con_info \
	-Wl,-u,base_GHCziInt_I8zh_con_info \
	-Wl,-u,base_GHCziInt_I16zh_con_info \
	-Wl,-u,base_GHCziInt_I32zh_con_info \
	-Wl,-u,base_GHCziInt_I64zh_con_info \
	-Wl,-u,base_GHCziWord_W8zh_con_info \
	-Wl,-u,base_GHCziWord_W16zh_con_info \
	-Wl,-u,base_GHCziWord_W32zh_con_info \
	-Wl,-u,base_GHCziWord_W64zh_con_info \
	-Wl,-u,base_GHCziStable_StablePtr_con_info \
	-Wl,-u,hs_atomic_add8 \
	-Wl,-u,hs_atomic_add16 \
	-Wl,-u,hs_atomic_add32 \
	-Wl,-u,hs_atomic_add64 \
	-Wl,-u,hs_atomic_sub8 \
	-Wl,-u,hs_atomic_sub16 \
	-Wl,-u,hs_atomic_sub32 \
	-Wl,-u,hs_atomic_sub64 \
	-Wl,-u,hs_atomic_and8 \
	-Wl,-u,hs_atomic_and16 \
	-Wl,-u,hs_atomic_and32 \
	-Wl,-u,hs_atomic_and64 \
	-Wl,-u,hs_atomic_nand8 \
	-Wl,-u,hs_atomic_nand16 \
	-Wl,-u,hs_atomic_nand32 \
	-Wl,-u,hs_atomic_nand64 \
	-Wl,-u,hs_atomic_or8 \
	-Wl,-u,hs_atomic_or16 \
	-Wl,-u,hs_atomic_or32 \
	-Wl,-u,hs_atomic_or64 \
	-Wl,-u,hs_atomic_xor8 \
	-Wl,-u,hs_atomic_xor16 \
	-Wl,-u,hs_atomic_xor32 \
	-Wl,-u,hs_atomic_xor64 \
	-Wl,-u,hs_cmpxchg8 \
	-Wl,-u,hs_cmpxchg16 \
	-Wl,-u,hs_cmpxchg32 \
	-Wl,-u,hs_cmpxchg64 \
	-Wl,-u,hs_xchg8 \
	-Wl,-u,hs_xchg16 \
	-Wl,-u,hs_xchg32 \
	-Wl,-u,hs_xchg64 \
	-Wl,-u,hs_atomicread8 \
	-Wl,-u,hs_atomicread16 \
	-Wl,-u,hs_atomicread32 \
	-Wl,-u,hs_atomicread64 \
	-Wl,-u,hs_atomicwrite8 \
	-Wl,-u,hs_atomicwrite16 \
	-Wl,-u,hs_atomicwrite32 \
	-Wl,-u,hs_atomicwrite64 \
	-lHSbase-4.15.1.0 \
	-lHSghc-bignum-1.1 \
	-lHSghc-prim-0.7.0 \
	-lHSrts \
	-lgmp \
	-lc \
	-lm \
	-lrt \
	-ldl \
	-lffi \
	-lnuma \
	-lpthread \
	-lcurses


include $(DEPS)