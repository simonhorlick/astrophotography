CXXFLAGS += -g -Wall -D__STDC_CONSTANT_MACROS `pkg-config opencv --cflags`
LIBS = `pkg-config opencv --libs`
GTEST_DIR = third_party/gtest-1.6.0

all: stack

clean:
	rm -f *.o *.a stack

stack: stack.o triangle_similarity_matcher.o
	$(CXX) -o $@ $(CXXFLAGS) $^ $(LIBS)

stack.o: main.cc matcher.h triangle_similarity_matcher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

triangle_similarity_matcher.o: triangle_similarity_matcher.cc triangle_similarity_matcher.h matcher.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

#
# Google Test rules
#
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) -I$(GTEST_DIR)/include -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) -I$(GTEST_DIR)/include -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

