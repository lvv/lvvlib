
############################################################################   CONFIG

# to set speed run as:  make s=o
CXX 	?=  g++
FC	= gfortran

TMPDIR ?=/v

################################################################################ LABEL
_cc := $(CXX)-$(shell $(CXX) -v 2>&1 | sed  -n 's/^.*ersion *\(4[^ ]*\) .*/\1/p')
_date := $(shell date +'%y%m%d_%H%M%S')
_rev :=$(shell test -d .git && git rev-parse HEAD|sed -n 's/^\(........\).*/\1/p')++$(shell test -d .git && git branch |sed -n 's/master/M/; s/^* //p')
#_cpu=$(shell uname -m -p  |sed 's/Intel(R)//;s/(TM)//;s/@//;s/CPU//;s/ \+/-/g')
_cpu :=$(shell sed -n '/^model name/!d; s/.*: //; s/(tm) Processor//; s/Intel(R)//; s/(TM)//; s/@//; s/^ //; s/ \+/-/g;p;q' /proc/cpuinfo )
_cores := $(shell awk '/^processor/{cores=$$3+1}; END{print cores}' /proc/cpuinfo)
_mhz := $(shell awk '/^cpu MHz/{mhz=$$4}; END{print mhz}' /proc/cpuinfo |sed 's/\.[0-9]\+//')
ID := $(shell echo "$(_date)-$(_cc)-$(SPEED:DEBUG=g)-$(_rev)-$(_cpu)-x$(_cores)@$(_mhz)" | tr -d ' ')

########################################################################################
#SPEED := $(s:o=OPTIMZE)
SPEED := $(s:d=DEBUG)
#SPEED := $(c:d=CHECK)
#SPEED = $($($(s:d=DEBUG):c=CHECK):o=OPTIMIZE)
SPEED  	?= DEBUG

#######################################################################################  COMPILE SPECIFIC
#
#  TO TRY (new in 4.4.1)
#  	-findirect-inlining
#  	-ftree-switch-conversion
#   	-floop-block
#   	-floop-strip-mine
#   	-floop-interchange
g++FLAGS          := -pipe -Wno-reorder -Wno-sign-compare # -fstrict-aliasing # -Wmissing-braces

# SAFE
#g++FLAGS_OPTIMIZE := -O2 -march=native 
#g++FLAGS_OPTIMIZE := -O2 -march=native  -fwhole-program --combine
g++FLAGS_OPTIMIZE :=         -O3 -fwhole-program --combine  -fopenmp -fomit-frame-pointer -funsafe-loop-optimizations -fno-stack-protector -D_FORTIFY_SOURCE=0 
# FAST
#g++FLAGS_OPTIMIZE :=        -O3 -march=native  -fwhole-program --combine  -fopenmp -fomit-frame-pointer -fargument-noalias-anything -ffast-math -funsafe-loop-optimizations -fassociative-math -fassociative-math  -mfpmath=sse,387 -fno-builtin -fargument-noalias-anything  -fassociative-math
g++FLAGS_PROFILE := -pg -g -O2 -march=native -fno-omit-frame-pointer -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls -fno-default-inline -fno-inline


# DO NOT USE
#-fargument-noalias-anything   (newuoa segfalts at the end)
#-fast-math

# 2try(but deps on libs with exception?): -DBOOST_NO_EXCEPTIONS -fno-exceptions -fno-enforce-eh-specs  -freorder-blocks-and-partition
# -ftree-vectorizer-verbose=3 -fdump-tree-vect 
#
#g++FLAGS_COMMON +=  -march=native -I /usr/local/include -l:/opt/intel/Compiler/11.0/074/lib/intel64/libimf.so  -Wstrict-aliasing=2
g++FLAGS_COMMON +=  -march=native -I /usr/local/include  -Wstrict-aliasing=2
##################################################################################33

# CHECK+DEBUG
g++FLAGS_DEBUG    :=  -ggdb3 -O0 -p -Wpacked -fsignaling-nans -fdelete-null-pointer-checks  -fstack-protector -ftrapv -fbounds-check -D_GLIBCXX_DEBUG  -DGSL_RANGE_CHECK

#g++FLAGS_CHECK    := -O0 -p -Wpacked -fsignaling-nans -fdelete-null-pointer-checks  -fstack-protector -ftrapv -fbounds-check -D_GLIBCXX_DEBUG  -DGSL_RANGE_CHECK
#g++FLAGS_DEBUG    := -O0 -ggdb3 -p -Wpacked -fsignaling-nans 
	#g++FLAGS_DEBUG    += -Wfloat-equal -Weffc++
	#g++FLAGS_DEBUG    += -fmudflap

iccFLAGS          := -vec-report0 -Wformat -openmp-report0 -wd1418 -wd981 -wd424 -wd810 -wd383  -wd82 -wd1572 -wd2259 -wd11001 -wd11005 
#-gxx-name=/usr/libexec/gcc/x86_64-pc-linux-gnu/4.2.4/
iccFLAGS_OPTIMIZE := -O3 -ipo  -march=core2  -openmp -xT -openmp-lib compat
#iccFLAGS_OPTIMIZE := -ipo  -march=core2  -fomit-frame-pointer -parallel
#iccFLAGS_OPTIMIZE := -ipo  -msse3  -march=core2  -fomit-frame-pointer -parallel
iccFLAGS_DEBUG    := -debug all 
iccFLAGS_CHECK    := -check-uninit -fmudflap -fstack-security-check -ftrapuv -Wcheck
#for icc PATH=/usr/x86_64-pc-linux-gnu/gcc-bin/4.2.4:$(PATH)

#######################################################################################  NOT COMPILE SPECIFIC
CXXFLAGS_COMMON		 = -Wall -std=c++0x -DID='"$(ID)"'   -I /home/lvv/p/ 
#CXXFLAGS_COMMON		 = -Wall -std=c++0x -DID='"$(ID)"'   -I /home/lvv/p/ -I /usr/include/boost-1_37/ 
#-frecord-gcc-switches
CXXFLAGS_OPTIMIZE	:= -DNDEBUG  -DGSL_RANGE_CHECK_OFF -DNOCHECK 
#-D_GLIBCXX_PARALLEL
#CXXFLAGS_DEBUG		:= -DDEBUG   -lgzstream -lz -lmudflap
CXXFLAGS_DEBUG		:= -DDEBUG   -DNOCHECK -DNOSTATS -DGSL_RANGE_CHECK_ON
CXXFLAGS_CHECK		:= -DDEBUG   -DDOCHECK -DDOSTATS   -D_GLIBCXX_DEBUG  

#######################################################################################  EVALUATE CXXFLAGS
CXXFLAGS           += $(CXXFLAGS_COMMON) $(CXXFLAGS_$(SPEED))  $($(CXX)FLAGS_COMMON)  $($(CXX)FLAGS) $($(CXX)FLAGS_$(SPEED))  $(CF) $(CFLAGS) 


.SUFFIXES:	.cc -r -c -g  -gr -gp -d 
.PHONY:		%-r %-g %-gr  %-gp *-r

b-%  u-%  : MAKEFLAGS	+= -B


%-gp: %
	@tput sgr0; tput setaf 4
	$< | gp
	@tput sgr0

%-g: %
	echo -e "br main\nr" > /tmp/t
	gdb -q -x /tmp/t $<

%-gr: %
	echo -e "r" > /tmp/t
	gdb -q -x /tmp/t $<


%-d %-r: %
	./$<


%-g       : SPEED 	= DEBUG
%-gr      : SPEED 	= DEBUG
%-d       : SPEED 	= DEBUG

a-%       : CXXFLAGS	+= -O3 -save-temps
u-%       : CXXFLAGS	+= -Wno-unused-variable
#b-%       : SPEED      	 = OPTIMIZE

# vim:noexpandtab ft=make:
