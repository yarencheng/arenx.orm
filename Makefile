CXXFLAGS     =	-O2 -g -Wall -Werror -fmessage-length=0
LIBS         = -lsqlite3

BUILD_FOLDER := ./build/

##########################################################

all:
	mkdir -p $(BUILD_FOLDER)
	@echo "\n========== pre_compile ==========\n"
	$(MAKE) pre_compile
	@echo "\n========== compile ==========\n"
	$(MAKE) compile
	@echo "\n========== post_compile ==========\n"
	$(MAKE) post_compile
	@echo "\n========== pre_compile_test ==========\n"
	$(MAKE) pre_compile_test
	@echo "\n========== compile_test ==========\n"
	$(MAKE) compile_test
	@echo "\n========== post_compile_test ==========\n"
	$(MAKE) post_compile_test
	@echo "\n========== pre_do_test ==========\n"
	$(MAKE) pre_do_test
	@echo "\n========== do_test ==========\n"
	$(MAKE) do_test
	@echo "\n========== post_do_test ==========\n"
	$(MAKE) post_do_test

##########################################################

SOURCES_HPP  := ./src/include
SOURCES_CPP  := $(shell find src/cpp -name "*.cpp")
OBJS         := $(basename $(SOURCES_CPP)) 

pre_compile:

compile: $(OBJS)

$(OBJS):
	mkdir -p $(BUILD_FOLDER)/$(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SOURCES_HPP) -c $@.cpp -o $(BUILD_FOLDER)/$@.o 
	
post_compile:

##########################################################

GTEST_DIR    := test/googletest/
GMOCK_DIR    := test/googlemock/
TEST_CPP     := $(shell find test/ -type f -name "*.cpp" ! -path "*$(GTEST_DIR)*" ! -path "*$(GMOCK_DIR)*")
TEST_OBJS    := $(basename $(TEST_CPP)) 

pre_compile_test: 
	mkdir -p $(BUILD_FOLDER)/test/

compile_test: google_test google_mock $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -I$(SOURCES_HPP) -I$(GTEST_DIR)/include -I$(GMOCK_DIR)/include -c $(GMOCK_DIR)/src/gmock_main.cc -o $(BUILD_FOLDER)/test/gmock_main.o
	$(CXX) $(CXXFLAGS) -o $(BUILD_FOLDER)/test/test -pthread \
		$(foreach obj, $(OBJS), $(BUILD_FOLDER)/$(obj).o)  \
		$(foreach obj, $(TEST_OBJS), $(BUILD_FOLDER)/$(obj).o) \
		$(BUILD_FOLDER)/test/gmock_main.o \
		$(BUILD_FOLDER)/test/gtest-all.o \
		$(BUILD_FOLDER)/test/gmock-all.o \
		$(LIBS)		
	
$(TEST_OBJS):
	mkdir -p $(BUILD_FOLDER)/$(dir $@)
	$(CXX) $(CXXFLAGS) -I$(SOURCES_HPP) -I$(GTEST_DIR)/include -I$(GMOCK_DIR)/include -c $@.cpp -o $(BUILD_FOLDER)/$@.o 

post_compile_test:	

google_test:
	$(CXX) $(CXXFLAGS) -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread -c ${GTEST_DIR}/src/gtest-all.cc \
		-o $(BUILD_FOLDER)/test/gtest-all.o

google_mock:
	$(CXX) $(CXXFLAGS) -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -isystem ${GMOCK_DIR}/include -I${GMOCK_DIR} -pthread -c ${GMOCK_DIR}/src/gmock-all.cc \
		-o $(BUILD_FOLDER)/test/gmock-all.o
	

##########################################################

pre_do_test:

do_test:
	@cd $(BUILD_FOLDER)/test/ && \
		./test --gtest_color=yes --gtest_output=xml

post_do_test:

##########################################################

clean:
	rm -r $(BUILD_FOLDER)
