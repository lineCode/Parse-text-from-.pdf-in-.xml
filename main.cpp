#include <iostream>
#include <cstring>
#include "PDFDocument.h"
#include "XMLWriter.h"

/**
 * Main function of this program. Here gets arguments of 
 * command-line(name of .pdf files), then its parse and
 * result of parsing writes in .xml file.
 * @exception exception here catches all the exception from
 * PDFDocument and XMLWriter, and are printered to the user.
 */
int main(int argc, char* argv[]){
	PDFDocument pdf;
	XMLWriter writer;

	if(argc <= 1){
		std::cerr << "You didn't enter files for parsing" << std::endl;
		return 1;  
	}

	for(int i = 1; i < argc; i++){
		try{
			pdf.loadFile(argv[i]);
			writer.write(pdf);
			std::cout << "Text of " << argv[i] << " was written in .xml file"; 
		} catch(std::exception &e){
			std::cerr << e.what() << std::endl;
		}	
	}

	return 0;
}
