pagetable: logicalToPage.o byu_tracereader.o output_mode_helpers.o
	g++ logicalToPage.o byu_tracereader.o output_mode_helpers.o -o pagetable

logicalToPage.o: logicalToPage.cpp output_mode_helpers.h byutr.h
	g++ -c logicalToPage.cpp

byu_tracereader.o: byu_tracereader.c byutr.h
	gcc -c byu_tracereader.c

output_mode_helpers.o: output_mode_helpers.c output_mode_helpers.h
	gcc -c output_mode_helpers.c

clean:
	rm *.o pagetable