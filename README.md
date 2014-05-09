MuZIP: .ppm image compressor
============================

This code was created for a university assignment and may not be sold nor used for any lucrative purposes. We do not take any responsibilities of the injuries it may cause.
Note that there are not many image viewers that open .ppm images. In fact, Apple used to display images in Macs with the QuickView in Snow Leopard. But now in Mountain Lion seems that they dropped support.

![muzip](https://raw.github.com/Catsoft-Studios/MuZIP/master/readme/muzip.png)

Information
-----------

All credit to Martí-Joan Nogué Coll - Catsoft-Studios 2011.
More information about the code can be found at

[mnogue.com/experiments][1]

If you have any questions drop us a line by making use of the contact page.

Installation
------------

Compile with makefile

	make -f Makefile.make all

Or if you have problems using path variable (i did) copy and paste the following line

	g++ data/*.cpp data/*.h io/*.cpp io/*.h gui/*.cpp gui/*.h algorithms/*.cpp algorithms/*.h *.cpp -o muzip.x

To clean the compiled files execute `make -f Makefile.make clean` or `rm -rf *.o *.x`

Usage
-----

To both compress and decompress an image you'll have to start the program by executing `./muzip.x`. You will be prompted with
a command line interface. Follow the steps to compress or decompress a .ppm.mz (which is the extension of compressed files).

Here are a couple of examples to compile the cat image.

### Compress an image

Start the program

	./muzip.x

Select `1` option to compress an image and then write the path to the image. For this example we'll use the cat.ppm image located at the IMGS folder

	IMGS/cat.ppm
	
This may take a while. Wait until the image is compressed into a cat.ppm.mz file.

### Decompress an image

The procedure is the same as the compressing one, but instead of selecting a .ppm file, you select the .ppm.mz one.

	./muzip
	2
	IMGS/cat.ppm.mz
	
### Final lines

Note that when you execute `./muzip` you can modify 3 variables called `p`, `q` and `alpha`. Those values represent the number of quads the image is split.
