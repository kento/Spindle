noinst_PROGRAMS = libgenerator

ABS_TEST_DIR = $(abspath $(top_builddir)/testsuite)
BUILT_SOURCES = libtest10.so libtest50.so libtest100.so libtest500.so libtest1000.so libtest2000.so libtest4000.so libtest6000.so libtest8000.so libtest10000.so libsymlink.so libdepC.so libdepB.so libdepA.so libcxxexceptB.so libcxxexceptA.so libtestoutput.so libfuncdict.so runTests run_driver run_driver_rm preload_file_list test_driver test_driver_libs

if BGQ_BLD
DYNAMIC_FLAG=-dynamic
IS_BLUEGENE=true
else
DYNAMIC_FLAG=
IS_BLUEGENE=false
endif

libgenerator_SOURCES = libgenerator.c

test_driverSOURCES = $(top_srcdir)/testsuite/test_driver.c
test_driverCFLAGS = -DLPATH=$(top_builddir)/testsuite -I$(top_srcdir)/src/client/spindle_api $(MPI_CFLAGS) -Wall
test_driverLDADD = -ldl -ltestoutput -lfuncdict -lspindle
test_driverLDFLAGS = -Wl,-E -L$(top_builddir)/testsuite -L$(top_builddir)/src/client/spindle_api $(MPI_CLDFLAGS) -L. $(DYNAMIC_FLAG) -no-install

test_driver_libsSOURCES = $(top_srcdir)/testsuite/test_driver.c
test_driver_libsCFLAGS = -DLPATH=$(top_builddir)/testsuite -I$(top_srcdir)/src/client/spindle_api $(MPI_CFLAGS) -Wall
test_driver_libsLDADD = -ltest10 -ltest50 -ltest100 -ltest500 -ltest1000 -ltest2000 -ltest4000 -ltest6000 -ltest8000 -ltest10000 -ldepA -lcxxexceptA -ldl -ltestoutput -lfuncdict -ldepB -ldepC -lcxxexceptB -lspindle
test_driver_libsLDFLAGS = -Wl,-E -L$(top_builddir)/testsuite $(MPI_CLDFLAGS) -L$(top_builddir)/src/client/spindle_api -L. $(DYNAMIC_FLAG) -no-install

REGLIB_SRC = $(srcdir)/registerlib.c
LD_FUNCDICT = -L$(top_builddir)/testsuite -lfuncdict

test_driver: $(test_driver_SOURCES) libtestoutput.so libfuncdict.so
	$(AM_V_CCLD) $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(MPICC) -o $@ $(test_driverSOURCES) $(test_driverCFLAGS) $(test_driverLDFLAGS) $(test_driverLDADD)

test_driver_libs: $(test_driver_SOURCES) libtestoutput.so libfuncdict.so libtest10.so libtest100.so libtest500.so libtest1000.so libtest2000.so libtest4000.so libtest6000.so libtest8000.so libtest10000.so libdepA.so libcxxexceptA.so libdepB.so libdepC.so libcxxexceptB.so
	$(AM_V_CCLD) $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(MPICC) -o $@ $(test_driver_libsSOURCES) $(test_driver_libsCFLAGS) $(test_driver_libsLDFLAGS) $(test_driver_libsLDADD)

libtest10.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest10.c 10 t10

libtest50.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest50.c 50 t50

libtest100.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest100.c 100 t100

libtest500.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest500.c 500 t500

libtest1000.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest1000.c 1000 t1000

libtest2000.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest2000.c 2000 t2000

libtest4000.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest4000.c 4000 t4000

libtest6000.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest6000.c 6000 t6000

libtest8000.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest8000.c 8000 t8000

libtest10000.c: libgenerator
	$(AM_V_GEN)./libgenerator libtest10000.c 10000 t10000

libtest10.so: libtest10.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t10_calc $(LD_FUNCDICT)

libtest50.so: libtest50.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t50_calc $(LD_FUNCDICT)

libtest100.so: libtest100.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t100_calc $(LD_FUNCDICT)

libtest500.so: libtest500.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t500_calc $(LD_FUNCDICT)

libtest1000.so: libtest1000.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t1000_calc $(LD_FUNCDICT)

libtest2000.so: libtest2000.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t2000_calc $(LD_FUNCDICT)

libtest4000.so: libtest4000.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t4000_calc $(LD_FUNCDICT)

libtest6000.so: libtest6000.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t6000_calc $(LD_FUNCDICT)

libtest8000.so: libtest8000.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t8000_calc $(LD_FUNCDICT)

libtest10000.so: libtest10000.c $(REGLIB_SRC) libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $^ -shared -DSO_NAME=$@ -DFUNC_NAME=t10000_calc $(LD_FUNCDICT)

libdepA.so: libdepA.c $(REGLIB_SRC) libdepB.so libfuncdict.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $< $(REGLIB_SRC) -shared -L. -ldepB -DSO_NAME=$@ -DFUNC_NAME=depA_calc  $(LD_FUNCDICT)

libsymlink.so: libtest10.so
	$(AM_V_GEN) ln -s $< $@

libdepB.so: libdepB.c libdepC.so
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $< -shared -L. -ldepC

libdepC.so: libdepC.c
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $< -shared

libcxxexceptA.so: libcxxexceptA.cc $(REGLIB_SRC) libcxxexceptB.so libfuncdict.so
	$(AM_V_CCLD)$(MPICXX) -o $@ -fPIC -Wall $< $(REGLIB_SRC) -shared -L. -lcxxexceptB -DSO_NAME=$@ -DFUNC_NAME=cxxexceptA_calc $(LD_FUNCDICT)

libcxxexceptB.so: libcxxexceptB.cc
	$(AM_V_CCLD)$(MPICXX) -o $@ -fPIC -Wall $< -shared

libtestoutput.so: testoutput.c
	$(AM_V_CCLD)$(MPICXX) -o $@ -fPIC -Wall $< -shared

libfuncdict.so: funcdict.c
	$(AM_V_CCLD)$(MPICC) -o $@ -fPIC -Wall $< -shared

runTests: $(srcdir)/runTests_template
	@rm -f ./runTests
	$(AM_V_GEN)$(SED) -e s,BLUEGENE_TEST,$(IS_BLUEGENE),g < $(srcdir)/runTests_template > $(top_builddir)/testsuite/runTests
	@chmod 700 $(top_builddir)/testsuite/runTests

run_driver: $(srcdir)/run_driver_template $(top_builddir)/Makefile
	@rm -f ./run_driver
	$(AM_V_GEN)$(SED) -e s,SPINDLE_EXEC,$(bindir)/spindle,g\;s,TEST_RUN_DIR,$(ABS_TEST_DIR),g\;s,BLUEGENE_TEST,$(IS_BLUEGENE),g < $(srcdir)/run_driver_template > $(top_builddir)/testsuite/run_driver
	@chmod 700 $(top_builddir)/testsuite/run_driver

run_driver_rm: $(srcdir)/run_driver_$(TESTRM) $(top_builddir)/Makefile
	$(AM_V_GEN)cp $(srcdir)/run_driver_$(TESTRM) $(top_builddir)/testsuite/run_driver_rm
	@chmod 700 $(top_builddir)/testsuite/run_driver_rm

preload_file_list: $(srcdir)/preload_file_list_template $(top_builddir)/Makefile
	@rm -f ./preload_file_list
	$(AM_V_GEN)$(SED) -e s,TEST_RUN_DIR,$(ABS_TEST_DIR),g < $(srcdir)/preload_file_list_template > $(top_builddir)/testsuite/preload_file_list

CLEANFILES = libtest10.c libtest10.so libtest50.c libtest50.so libtest100.c libtest100.so libtest500.c libtest500.so libtest1000.c libtest1000.so libtest2000.c libtest2000.so libtest4000.c libtest4000.so libtest6000.c libtest6000.so libtest8000.c libtest8000.so libtest10000.c libtest10000.so libsymlink.so libdepA.so libdepB.so libdepC.so libcxxexceptA.so libcxxexceptB.so libtestoutput.so libfuncdict.so runTests run_driver run_driver_rm test_driver test_driver_libs preload_file_list

