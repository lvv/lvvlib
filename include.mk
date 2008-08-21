
############################################################################   CONFIG

# to set speed run as:  make s=o
CXX 	?=  g++
SPEED  	?= DEBUG
VPATH   := ../lvv/

########################################################################################
#SPEED := $(s:o=OPTIMZE)
#SPEED := $(s:d=DEBUG)

g++FLAGS          := -pipe -Wno-reorder
g++FLAGS_OPTIMIZE := -O3 -march=native 

g++FLAGS_DEBUG    := -O0 -ggdb3 -p -fdelete-null-pointer-checks  -Wpacked -fsignaling-nans -fstack-protector -ftrapv -D_GLIBCXX_DEBUG  -fbounds-check
#g++FLAGS_DEBUG    := -O0 -g3 -gstabs+ -p -fdelete-null-pointer-checks  -Wpacked -fsignaling-nans -fstack-protector -ftrapv -D_GLIBCXX_DEBUG  -fbounds-check
#g++FLAGS_DEBUG    := -O0 -g3 -gdwarf-2 -p -fdelete-null-pointer-checks  -Wpacked -fsignaling-nans -fstack-protector -ftrapv -D_GLIBCXX_DEBUG  -fbounds-check

g++FLAGS_STATS    := -O3           -fdelete-null-pointer-checks  -Wpacked -fsignaling-nans -fstack-protector -ftrapv -D_GLIBCXX_DEBUG  -fbounds-check -DSTATS
#g++FLAGS_DEBUG    += -Wfloat-equal -Weffc++
#g++FLAGS_DEBUG    += -fmudflap
#g++FLAGS_OPTIMIZE += -fast-math -fstrict-overflow 

iccFLAGS          :=  -wd1418 -wd981         -wd424 -wd810 -wd383 
#-gxx-name=/usr/libexec/gcc/x86_64-pc-linux-gnu/4.2.4/
iccFLAGS_OPTIMIZE := -O3 -ipo  -march=core2 
#iccFLAGS_OPTIMIZE := -ipo  -march=core2  -fomit-frame-pointer -parallel
#iccFLAGS_OPTIMIZE := -ipo  -msse3  -march=core2  -fomit-frame-pointer -parallel
iccFLAGS_DEBUG    := -debug all
#for icc PATH=/usr/x86_64-pc-linux-gnu/gcc-bin/4.2.4:$(PATH)

CXXFLAGS_COMMON		 = -Wall -DID='"$(ID)"' -I ../lvv/
CXXFLAGS_OPTIMIZE	:= -DNDEBUG  -DGSL_RANGE_CHECK_OFF
#CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz -lmudflap
CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz
CXXFLAGS           = $(CXXFLAGS_COMMON) $(CXXFLAGS_$(SPEED))  $($(CXX)FLAGS) $($(CXX)FLAGS_$(SPEED))  $(CF)

*: ../lvv/include.mk ../lvv/lvv.h

% : %.cc
	@tput sgr0; tput setaf 4
	$(CXX)	 $< -o $(name_prefix)$@     $(CXXFLAGS)  $(LDFLAGS)
	@tput sgr0

	#@make $<

%-gp: %
	@tput sgr0; tput setaf 4
	$< | gp
	@tput sgr0
%-g: %
	echo -e "br main\nr" > /tmp/t
	gdb -x /tmp/t ./$<

%-r: %
	./$<

# vim:noexpandtab ft=make:
