CC = g++
CFLAGS = -c -Wall
LIBS = -lpodofo
OBJ = main.o PDFDocument.o XMLWriter.o tinyxml/tinyxml.o tinyxml/tinystr.o tinyxml/tinyxmlerror.o tinyxml/tinyxmlparser.o
EXE = -o PDFParser

all: main.o PDFDocument.o XMLWriter.o
	$(CC) $(EXE) $(OBJ) $(LIBS)

main.o: PDFDocument.h XMLWriter.h main.cpp
	$(CC) $(CFLAGS) main.cpp PDFDocument.cpp

PDFDocument.o: PDFDocument.cpp PDFDocument.h
	$(CC) $(CFLAGS) PDFDocument.cpp

XMLWriter.o: PDFDocument.h XMLWriter.h XMLWriter.cpp
	$(CC) $(CFLAGS) XMLWriter.cpp

install:
	install ./PDFParser /usr/local/bin

unistall:
	rm -rf /usr/local/bin/PDFParser

clean:
	rm -rf *.o PDFParser