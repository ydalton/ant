##
# Project Title
#
# @file
# @version 0.1

ant: ant.o
	gcc -lGL -lGLU -lglut -o ant ant.o
clean: 
	rm -f ant.o ant


# end
