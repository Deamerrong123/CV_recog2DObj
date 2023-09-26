########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++14

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)

Cpp_OBJ=image.o image_demo.o

PROGRAM_NAME=image_demo

$(PROGRAM_NAME): $(Cpp_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ) $(INCLUDES) $(LIBS_ALL)

P1_OBJ=image.o p1.o
PROGRAM_1=p1
$(PROGRAM_1): $(P1_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $^ $(INCLUDES) $(LIBS_ALL)

P2_OBJ=image.o p2.o DisjSets.o
PROGRAM_2=p2
$(PROGRAM_2): $(P2_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $^ $(INCLUDES) $(LIBS_ALL)

P3_OBJ=image.o p3.o
PROGRAM_3=p3
$(PROGRAM_3): $(P3_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $^ $(INCLUDES) $(LIBS_ALL)

P4_OBJ=image.o p4.o
PROGRAM_4=p4
$(PROGRAM_4): $(P4_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $^ $(INCLUDES) $(LIBS_ALL)

all: 
	# make $(PROGRAM_NAME) 
	# make $(PROGRAM_1)
	make $(PROGRAM_2)
	# make $(PROGRAM_3)
	# make $(PROGRAM_4)


rundemo:
	./image_demo two_objects.pgm temp_results/output_two_objects_output.pgm;
	open temp_results/output_two_objects_output.pgm

run1:
	./p1 two_objects.pgm 139 temp_results/output_two_objects_output.pgm;
	open temp_results/output_two_objects_output.pgm;

run2:
	./p2 temp_results/output_two_objects_output.pgm temp_results/output_p2_two_objects_ouput.pgm
	open temp_results/output_p2_two_objects_ouput.pgm;

run3:
	./p3 temp_results/output_p2_two_objects_output.pgm Database.txt temp_results/output_p3_two_objects_ouput.pgm
	open temp_results/output_p2_two_objects_ouput.pgm;

clean:
	(rm -f *.o; rm p3)


(:
