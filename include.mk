
############################################################################   CONFIG

# to set speed run as:  make s=o
CXX 	?=  g++
FC	= gfortran

TMPDIR ?=/v

################################################################################  ID
_cc := $(CXX)-$(shell $(CXX) -v 2>&1 | sed  -n 's/^.*ersion *\(4[^ ]*\) .*/\1/p')
#_date := $(shell date +'%y%m%d_%H%M%S')
_rev :=$(shell test -d .git && git rev-parse HEAD|sed -n 's/^\(........\).*/\1/p' )
#_cpu=$(shell uname -m -p  |sed 's/Intel(R)//;s/(TM)//;s/@//;s/CPU//;s/ \+/-/g')
_cpu :=$(shell sed -n '/^model name/!d; s/.*: //; s/(tm) Processor//; s/Intel(R)//; s/(TM)//; s/@//; s/^ //; s/ \+/-/g;p;q' /proc/cpuinfo )
_cores := $(shell awk '/^processor/{cores=$$3+1}; END{print cores}' /proc/cpuinfo)
_mhz := $(shell awk '/^cpu MHz/{mhz=$$4}; END{print mhz}' /proc/cpuinfo |sed 's/\.[0-9]\+//')
ID := $(shell echo "$(_rev)-$(_cc)-$(SPEED:DEBUG=g)-$(_cpu)-x$(_cores)@$(_mhz)" | tr -d ' ')

########################################################################################
#SPEED := $(s:o=OPTIMZE)
SPEED := $(s:d=DEBUG)
#SPEED := $(s:d=CHECK)
#SPEED = $($($(s:d=DEBUG):c=CHECK):o=OPTIMIZE)
SPEED  	?= DEBUG



#######################################################################################  GCC

g++FLAGS          :=-Wno-reorder -Wno-sign-compare # -fstrict-aliasing # -Wmissing-braces
#g++FLAGS+=  -march=native -I /usr/local/include -l:/opt/intel/Compiler/11.0/074/lib/intel64/libimf.so  -Wstrict-aliasing=2
g++FLAGS+= -pipe  -Wstrict-aliasing=2

g++FLAGS_OPTIMIZE :=   -O3   -march=native -fno-stack-protector -D_FORTIFY_SOURCE=0 
#g++FLAGS_OPTIMIZE +=   -fomit-frame-pointer -funsafe-loop-optimizations
g++FLAGS_OPTIMIZE +=   -fwhole-program
#g++FLAGS_OPTIMIZE +=   -fopenmp  -D_GLIBCXX_PARALLEL
#g++FLAGS_OPTIMIZE :=    -ffast-math -fassociative-math -mfpmath=sse,387 -fno-builtin -fargument-noalias-anything


g++FLAGS_PROFILE := -pg -g -O2 -march=native -fno-omit-frame-pointer -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls -fno-default-inline -fno-inline

# CHECK+DEBUG
g++FLAGS_DEBUG    :=  -g -O0 -D_GLIBCXX_DEBUG  
g++FLAGS_CHECK    :=  $(g++FLAGS_DEBUG) -fdelete-null-pointer-checks -fstack-protector -ftrapv -fbounds-check  -fsignaling-nans 
#g++FLAGS_CHECK    :=  -fmudflap  -lmudflap 

#g++FLAGS_CHECK    := -O0 -p -Wpacked -fsignaling-nans -fdelete-null-pointer-checks  -fstack-protector -ftrapv -fbounds-check -D_GLIBCXX_DEBUG  -DGSL_RANGE_CHECK
#g++FLAGS_DEBUG    := -O0 -ggdb3 -p -Wpacked -fsignaling-nans 
	#g++FLAGS_DEBUG    += -Wfloat-equal -Weffc++
	#g++FLAGS_DEBUG    += -fmudflap

########3##################################################################################  ICC

iccFLAGS          := -vec-report0 -Wformat -openmp-report0 -wd1418 -wd981 -wd424 -wd810 -wd383  -wd82 -wd1572 -wd2259 -wd11001 -wd11005 
#-gxx-name=/usr/libexec/gcc/x86_64-pc-linux-gnu/4.2.4/
iccFLAGS_OPTIMIZE := -O3 -ipo  -march=core2  -openmp -xT -openmp-lib compat
#iccFLAGS_OPTIMIZE := -ipo  -march=core2  -fomit-frame-pointer -parallel
#iccFLAGS_OPTIMIZE := -ipo  -msse3  -march=core2  -fomit-frame-pointer -parallel
iccFLAGS_DEBUG    := -debug all 
iccFLAGS_CHECK    := -check-uninit -fmudflap -fstack-security-check -ftrapuv -Wcheck
#for icc PATH=/usr/x86_64-pc-linux-gnu/gcc-bin/4.2.4:$(PATH)


#######################################################################################   NON-COMPILER SPECIFIC
CXXFLAGS		+= -Wall -std=c++0x -DID='"$(ID)"'   -I /home/lvv/p/ 
CXXFLAGS_OPTIMIZE	:= -DNDEBUG  -DGSL_RANGE_CHECK_OFF -DNOCHECK 
CXXFLAGS_DEBUG		:= -DDEBUG   -DNOCHECK -DNOSTATS -DGSL_RANGE_CHECK_ON
CXXFLAGS_CHECK		:= -DDEBUG   -DDOCHECK -DDOSTATS   -D_GLIBCXX_DEBUG  

#######################################################################################  BUILD CXXFLAGS
CXXFLAGS		+= $(CXXFLAGS_$(SPEED))   $($(CXX)FLAGS) $($(CXX)FLAGS_$(SPEED))  $(CF) $(CFLAGS) 


.SUFFIXES:	.cc -r -c -g  
.PHONY:		%-r %-g  %-c 

b-%  u-%  : MAKEFLAGS	+= -B


%-r %-c: %
	@tput sgr0; tput setaf 2
	$< 
	@tput sgr0

#%-c: %
#	@tput sgr0; tput setaf 2
#	$< 
#	@tput sgr0

%-g: %
	echo -e "br main\nr" > /tmp/t
	gdb -q -x /tmp/t $<



#%-d %-r: %
#	./$<


%-r       : SPEED 	= OPTIMIZE
%-c       : SPEED 	= CHECK
%-g       : SPEED 	= DEBUG

a-%       : CXXFLAGS	+= -O3 -save-temps
u-%       : CXXFLAGS	+= -Wno-unused-variable

# vim:noexpandtab ft=make:
