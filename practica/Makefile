OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Especie.o Cjt_Especies.o Cjt_Clusters.o
	g++ -o program.exe program.o Especie.o Cjt_Especies.o Cjt_Clusters.o
	rm *.o

Especie.o: Especie.cc Especie.hh
	g++ -c Especie.cc $(OPCIONS)

Cjt_Especies.o: Cjt_Especies.cc Cjt_Especies.hh Especie.hh
	g++ -c Cjt_Especies.cc $(OPCIONS)

Cjt_Clusters.o: Cjt_Clusters.cc BinTree.hh Cjt_Clusters.hh Cjt_Especies.hh Especie.hh
	g++ -c Cjt_Clusters.cc $(OPCIONS)

program.o: program.cc Especie.hh Cjt_Especies.hh Cjt_Clusters.hh BinTree.hh
	g++ -c program.cc $(OPCIONS)

clean:	
	rm *.exe
