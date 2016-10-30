# Makefile edited by Abdullah Khan

#FLAGS
C++FLAGS = -g -std=c++14 -Wall -pedantic

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAGS) $(INCLUDES) -c $< -o $@

.cpp.o:
	g++ $(C++FLAGS) $(INCLUDES) -c $< -o $@


#Including
INCLUDES=  -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib

s1_obj=image.o s1.o
s2_obj=image.o s2.o
s3_obj=image.o s3.o
s4_obj=image.o s4.o

PROGRAM1=s1
PROGRAM2=s2
PROGRAM3=s3
PROGRAM4=s4

THRESHOLD=180
BINARY_THRESHOLD=100

all: $(PROGRAM1) # $(PROGRAM2) $(PROGRAM3) $(PROGRAM4)

$(PROGRAM1): $(s1_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(s1_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM2): $(s2_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(s2_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM3): $(s3_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(s3_obj) $(INCLUDES) $(LIBS_ALL)

$(PROGRAM4): $(s4_obj)
	g++ $(C++FLAGS) -o $(EXEC_DIR)/$@ $(s4_obj) $(INCLUDES) $(LIBS_ALL)

package:
	(zip KHAN_HW4.zip *.h *.cc *.cpp Makefile README.txt)

clean:
	(rm -f *.o;)
	(rm -f s1;)
	(rm -f s2;)
	(rm -f s3;)
	(rm -f s4;)
