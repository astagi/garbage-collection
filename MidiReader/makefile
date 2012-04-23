midireader: initialize midiinfo.o main.o
	g++ -o ./build/MidiReader ./build/lib/*.o

initialize:
	mkdir ./build
	mkdir ./build/lib
	cp -r ./midifiles ./build

main.o: main.cpp
	g++ -c main.cpp -o ./build/lib/main.o

midiinfo.o: MidiInfo.h MidiInfo.cpp
	g++ -c MidiInfo.cpp -o ./build/lib/midiinfo.o

clean:
	-rm -r ./build
