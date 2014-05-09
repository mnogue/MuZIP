# MuZIP: .ppm image compressor makefile

all: buildall cleandoto
	
	
buildall: data io gui algorithms main.o
	g++ -o muzip.x Block.o Huffman.o GHT.o Image.o Pixel.o IO.o Gui.o Compression.o Decompression.o main.o
	
main: main.cpp
	g++ -c main.cpp
	
data: Block.o GHT.o Huffman.o Image.o Pixel.o
	
io: IO.o
	
gui: Gui.o
	
algorithms: Compression.o Decompression.o
	
## CLEANERS ##

clean:
	rm -rf *.exe *.x *.o
	
cleandoto:
	rm -rf *.o
	
## PRIVATE DEPENDENCES ##

Block.o: data/Block.cpp
	g++ -c data/Block.cpp
	
GHT.o: data/GHT.cpp
	g++ -c data/GHT.cpp
	
Huffman.o: data/Huffman.cpp
	g++ -c data/Huffman.cpp
	
Image.o: data/Image.cpp
	g++ -c data/Image.cpp
	
Pixel.o: data/Pixel.cpp
	g++ -c data/Pixel.cpp
	
IO.o: io/IO.cpp
	g++ -c io/IO.cpp
	
Gui.o: gui/Gui.cpp
	g++ -c gui/Gui.cpp
	
Compression.o: algorithms/Compression.cpp
	g++ -c algorithms/Compression.cpp
	
Decompression.o: algorithms/Decompression.cpp
	g++ -c algorithms/Decompression.cpp
	
