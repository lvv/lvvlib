
############################################################################   CONFIG

# to set speed run as:  make s=o
CXX 	?=  g++
FC	= gfortran

TMPDIR ?=/v

################################################################################ LABEL
_cc = $(CXX)-$(shell $(CXX) -v 2>&1 | sed  -n 's/^.*ersion *\([0-9.]*\) .*/\1/p')
_date = $(shell date +'%y%m%d_%H%M%S')
_rev=$(shell git rev-parse HEAD|sed -n 's/^\(........\).*/\1/p')++$(shell git branch |sed -n 's/master/M/; s/^* //p')
ID = $(shell echo $(_date)-$≡$(_cc)-$(SPEED:DEBUG=g)-$(_rev) | tr -d ' ')

########################################################################################
#SPEED := $(s:o=OPTIMZE)
SPEED := $(s:d=DEBUG)
#SPEED := $(c:d=CHECK)
#SPEED = $($($(s:d=DEBUG):c=CHECK):o=OPTIMIZE)
SPEED  	?= DEBUG

#######################################################################################  COMPILE SPECIFIC
g++FLAGS          := -pipe -Wno-reorder -Wno-sign-compare # -fstrict-aliasing # -Wmissing-braces

# SAFE
#g++FLAGS_OPTIMIZE := -O2 -march=native 
#g++FLAGS_OPTIMIZE := -O2 -march=native  -fwhole-program --combine
g++FLAGS_OPTIMIZE :=         -O3 -march=native  -fwhole-program --combine  -fopenmp -fomit-frame-pointer -funsafe-loop-optimizations
# FAST
#g++FLAGS_OPTIMIZE :=        -O3 -march=native  -fwhole-program --combine  -fopenmp -fomit-frame-pointer -fargument-noalias-anything -ffast-math -funsafe-loop-optimizations -fassociative-math -fassociative-math  -mfpmath=sse,387 -fno-builtin -fargument-noalias-anything  -fassociative-math

# DO NOT USE
#-fargument-noalias-anything   (newuoa segfalts at the end)
#-fast-math

# 2try(but deps on libs with exception?): -DBOOST_NO_EXCEPTIONS -fno-exceptions -fno-enforce-eh-specs  -freorder-blocks-and-partition
# -ftree-vectorizer-verbose=3 -fdump-tree-vect 

#g++FLAGS_OPTIMIZE += -fast-math -fstrict-overflow 
##################################################################################33

# CHECK+DEBUG
g++FLAGS_DEBUG    := -O0 -p -Wpacked -fsignaling-nans -fdelete-null-pointer-checks  -fstack-protector -ftrapv -fbounds-check -D_GLIBCXX_DEBUG  -DGSL_RANGE_CHECK -ggdb3 -p -Wpacked -fsignaling-nans 

#g++FLAGS_CHECK    := -O0 -p -Wpacked -fsignaling-nans -fdelete-null-pointer-checks  -fstack-protector -ftrapv -fbounds-check -D_GLIBCXX_DEBUG  -DGSL_RANGE_CHECK
#g++FLAGS_DEBUG    := -O0 -ggdb3 -p -Wpacked -fsignaling-nans 
	#g++FLAGS_DEBUG    += -Wfloat-equal -Weffc++
	#g++FLAGS_DEBUG    += -fmudflap

iccFLAGS          :=  -wd1418 -wd981         -wd424 -wd810 -wd383 
#-gxx-name=/usr/libexec/gcc/x86_64-pc-linux-gnu/4.2.4/
iccFLAGS_OPTIMIZE := -O3 -ipo  -march=core2  -openmp -xT
#iccFLAGS_OPTIMIZE := -ipo  -march=core2  -fomit-frame-pointer -parallel
#iccFLAGS_OPTIMIZE := -ipo  -msse3  -march=core2  -fomit-frame-pointer -parallel
iccFLAGS_DEBUG    := -debug all
#for icc PATH=/usr/x86_64-pc-linux-gnu/gcc-bin/4.2.4:$(PATH)

#######################################################################################  NOT COMPILE SPECIFIC
CXXFLAGS_COMMON		 = -Wall -DID='"$(ID)"'   -I ~/p/  -I /usr/local/include
#-frecord-gcc-switches
CXXFLAGS_OPTIMIZE	:= -DNDEBUG  -DGSL_RANGE_CHECK_OFF -DNOCHECK 
#CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz -lmudflap
CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz -DNOCHECK -DNOSTATS -DGSL_RANGE_CHECK_OFF 
CXXFLAGS_CHECK		:= -DDEBUG   -lgzstream -lz -DDOCHECK -DNOSTATS   -D_GLIBCXX_DEBUG  

#######################################################################################  EVALUATE CXXFLAGS
CXXFLAGS           += $(CXXFLAGS_COMMON) $(CXXFLAGS_$(SPEED))  $($(CXX)FLAGS) $($(CXX)FLAGS_$(SPEED))  $(CF) $(CFLAGS) 


.SUFFIXES: .cc -r -c -g  -gp
.PHONY  = %-r %-g %-gr  %-gp *-r

b-%  u-%  : MAKEFLAGS	+= -B

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

u-%       : CXXFLAGS	+= -Wno-unused-variable
b-%       : SPEED      	 = OPTIMIZE

# vim:noexpandtab ft=make:
