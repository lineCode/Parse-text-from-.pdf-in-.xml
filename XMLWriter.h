#ifndef _XMLWriter_H_
#define _XMLWriter_H_

#include <memory>
#include "PDFDocument.h"
#include "tinyxml.h"

/**
 * This provides an interface for write text
 * from .pdf file. This class create new .xml
 * file with name of received .pdf file and 
 * wtite there attributes and text.
 * @author Balun Vladimir.
 */
class XMLWriter{
public:
	typedef std::string String;
	typedef std::map<String, String> Map;
	typedef std::vector<String> StrVector;
	XMLWriter();
	void write(PDFDocument &pdf);
	~XMLWriter();
private:
	TiXmlDocument doc;
	TiXmlDeclaration *decl;
	void writeAttributes(Map &attributes, TiXmlElement *root);
	void writeText(StrVector &text, TiXmlElement *root);
};

#endif
