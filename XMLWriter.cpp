#include "XMLWriter.h"

XMLWriter::XMLWriter(){
	decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
}

/**
 * Funtion provides interface for write text from
 * .pdf file in .xml file. Here gets text and attributes
 * from .pdf file, writes in .xml file and this .xml file saves.
 * @param pdf .pdf file for write text in .xml file.
 */
void XMLWriter::write(PDFDocument &pdf){
	StrVector text = pdf.getText();
	Map attributes = pdf.getAttributes();
	TiXmlElement *root = new TiXmlElement("document");
	doc.LinkEndChild(root);
	writeAttributes(attributes, root);
	writeText(text, root);
	String nameFile = attributes.find("file_name")->second;
	doc.SaveFile(nameFile.append(".xml"));
	//Release memory(*root, *node, *text)	
	decl->Clear();
}

/**
 * Function writes attributes(name, author, creator and title) 
 * in .xml file from was received .pdf file.
 * @param attributes attributes was receided from .pdf file.
 * @param root root-element of .xml file, in which will write attributes.
 */
void XMLWriter::writeAttributes(Map &attributes, TiXmlElement *root){
	for(auto &attr : attributes){
		root->SetAttribute(attr.first.c_str(), attr.second.c_str());
	}	
}

/**
 * Function writes text in .xml file from was received .pdf file.
 * @param text text was receided from .pdf file.
 * @param root root-element of .xml file, for which the text will
 * be written.
 */
void XMLWriter::writeText(StrVector &text, TiXmlElement *root){
	for(auto &line : text){	
		TiXmlElement *node = new TiXmlElement("line");
		TiXmlText* text = new TiXmlText(line.c_str());
		root->LinkEndChild(node);
		node->LinkEndChild(text);
	}
}

XMLWriter::~XMLWriter(){

}
