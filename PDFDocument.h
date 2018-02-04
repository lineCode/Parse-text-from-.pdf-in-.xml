#ifndef _PDFDOCUMENT_H_
#define _PDFDOCUMENT_H_

#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include <podofo/podofo.h>

/**
 * This class provides an interface of .pdf
 * file. With this class you can get text
 * from .pdf file, which will be loaded.
 * @author Balun Vladimir.
 */
class PDFDocument{
public:
	typedef std::string String;
	typedef std::map<String, String> Map;
	typedef std::vector<String> StrVector;
	void loadFile(const String &filename);
	StrVector getText();
	Map getAttributes();
private:
	PoDoFo::PdfMemDocument pdf;
	StrVector lines;
	Map attrPdf;
	String nameFile;
	bool isCorrectFile(String fileName);
	void parseDocument();
	void parseAttributes();
	void parseText(PoDoFo::PdfVariant &variant);
};

#endif
