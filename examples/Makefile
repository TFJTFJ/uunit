# Add more tests here
TESTS=\
	test_ExampleTest \
	test_ExampleTest2

CXX ?= g++
CXXFLAGS ?= -g -std=c++17 -I..

all: ${TESTS}

check: all
	@F="0"; \
		for T in ${TESTS}; do echo -n "\n$$T: "; ./$$T 2> $$T.log; F=$$(($$F+$$?)); done; \
		echo '\n-----'; echo "Failed tests: $$F"; echo '-----'; \
		[ $$F -eq 0 ]

EXAMPLE_TEST_SRC = \
	getbaud.cc \
	ExampleTest.cc

EXAMPLE_TEST_2_SRC = \
	getbaud.cc \
	ExampleTest2.cc


test_ExampleTest: $(EXAMPLE_TEST_SRC)
	$(CXX) $(CXXFLAGS) -DOUTPUT=\"$@\" -o $@ ../uunit.cc $(EXAMPLE_TEST_SRC)

test_ExampleTest2: $(EXAMPLE_TEST_2_SRC)
	$(CXX) $(CXXFLAGS) -DOUTPUT=\"$@\" -o $@ ../uunit.cc $(EXAMPLE_TEST_2_SRC)


clean:
	rm -f ${TESTS}
	rm -f *.xml
	rm -f *.log
