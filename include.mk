
############################################################################   CONFIG

# to set speed run as:  make s=o
CXX 	?=  g++
SPEED  	?= DEBUG
VPATH   := ../lvv/
FC	= gfortran

########################################################################################
#SPEED := $(s:o=OPTIMZE)
#SPEED := $(s:d=DEBUG)
# TOTRY -fprefetch-loop-arrays
#######################################################################################  COMPILE SPECIFIC
g++FLAGS          := -pipe -Wno-reorder -Wno-sign-compare  # -Wmissing-braces
g++FLAGS_OPTIMIZE := -O3 -march=native  -fwhole-program --combine

g++FLAGS_CHECK    := -O0 -p -Wpacked -fsignaling-nans -fdelete-null-pointer-checks  -fstack-protector -ftrapv -fbounds-check -D_GLIBCXX_DEBUG  -DGSL_RANGE_CHECK
g++FLAGS_DEBUG    := -O0 -ggdb3 -p -Wpacked -fsignaling-nans 
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

#######################################################################################  NOT COMPILE SPECIFIC
CXXFLAGS_COMMON		 = -Wall -DID='"$(ID)"'  -I . -I .. -I ../.. -I /usr/local/ 
#-frecord-gcc-switches
CXXFLAGS_OPTIMIZE	:= -DNDEBUG  -DGSL_RANGE_CHECK_OFF -DNOCHECK
#CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz -lmudflap
CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz -DNOCHECK -DNOSTATS -DGSL_RANGE_CHECK_OFF 
CXXFLAGS_CHECK		:= -DDEBUG   -lgzstream -lz -DDOCHECK -DDOSTATS   -D_GLIBCXX_DEBUG  

#######################################################################################  EVALUATE CXXFLAGS
CXXFLAGS           += $(CXXFLAGS_COMMON) $(CXXFLAGS_$(SPEED))  $($(CXX)FLAGS) $($(CXX)FLAGS_$(SPEED))  $(CF)

#*: ../lvv/include.mk ../lvv/lvv.h

.SUFFIXES: .cc -r -c -g  -gp

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
	gdb -x /tmp/t $<

%-gr: %
	echo -e "r" > /tmp/t
	gdb -x /tmp/t $<

%-r: %
	./$<

%-r: %.cc
	make $(<:.cc=)
	./$(<:.cc=)

# vim:noexpandtab ft=make:
