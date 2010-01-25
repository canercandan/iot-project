CXX		= g++
CXXFLAGS	= -W -Wall -Werror -Wextra -O2
INCLUDE		= -I headers -I /usr/local/boost_1_39_0
LIB		= -lboost_system-gcc43-mt-1_39 -lboost_thread-gcc43-mt

SAMPLE_SRC	= $(wildcard src/*.cpp)
SAMPLE_OBJ	= $(SAMPLE_SRC:.cpp=.o)

UT_SRC		= $(wildcard unitTesting/*.cpp)
UT_OBJ		= $(UT_SRC:.cpp=.o)

OUTPUT		= ZiaParserSample
UNIT_TESTING	= UnitTesting
RM		= rm -rfv

all:		sample unit-testing

sample:		$(SAMPLE_OBJ)
		$(CXX) $(SAMPLE_OBJ) $(LIB) -o $(OUTPUT)

unit-testing:	$(UT_OBJ)
		$(CXX) $(UT_OBJ) $(LIB) -o $(UNIT_TESTING)

.cpp.o:
		$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
		$(RM) *~ $(SAMPLE_OBJ) $(UT_OBJ)

fclean:		clean
		$(RM) $(OUTPUT) $(UNIT_TESTING)

re:		fclean all

.SUFFIXES:	.o .cpp .cc .cxx
.PHONY:		all clean fclean re
