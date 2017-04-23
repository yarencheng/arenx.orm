CXXFLAGS     =	-O2 -g -Wall -fmessage-length=0
LIBS         =

BUILD_FOLDER := ./build/

SOURCES_HPP  := ./src/include
SOURCES_CPP  := $(shell find src/cpp -name "*.cpp")
OBJS         := $(basename $(SOURCES_CPP)) 

#HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
#SRC_CXX = $(filter-out %.c,$(SOURCES))

#OBJS =		arenx_orm.o






all:
	@make pre_compile
	@make compile
	@make post_compile
	@make pre_compile_test
	@make compile_test
	@make post_compile_test
	@make pre_test
	@make test
	@make post_test

pre_compile:
	@echo BUILD_FOLDER = $(BUILD_FOLDER)
	mkdir -p $(BUILD_FOLDER)

compile: $(OBJS)

$(OBJS):
	@echo "@ = " $@ 
	@echo "^ = " $^
	@echo "< = " $< 
	@echo "dir = " $(dir $@)
	mkdir -p $(BUILD_FOLDER)/$(dir $@)
	$(CXX) $(CXXFLAGS) -c $@.cpp -o $(BUILD_FOLDER)/$@.o -I$(SOURCES_HPP)
	
post_compile:

pre_compile_test:

compile_test:

post_compile_test:

pre_test:

test:

post_test:

clean:
	rm -r $(BUILD_FOLDER)
