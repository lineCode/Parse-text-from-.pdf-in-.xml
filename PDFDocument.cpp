#include "PDFDocument.h"

/**
 * Function loads .pdf file for parsing. Here checks the
 * correctness of the file, clears data of last files
 * and parses data of current .pdf file.
 * @param fileName current file for parsing
 * @throws invalid_argument throw exception, if this file,
 * isn't pdf file.
 * @throws invalid_argument throw exception, if can't
 * load this file.
 */
void PDFDocument::loadFile(const String &fileName){
	if(isCorrectFile(fileName)){
		this->nameFile = fileName;	
		//removes file extension
		this->nameFile.erase(nameFile.end() - 4, nameFile.end());
	} else {
		throw std::invalid_argument(fileName + " isn't PDF file");
	}	
	try{
		pdf.Load(fileName.c_str());
	} catch(...){
		throw std::invalid_argument(fileName + " wasn't loaded");
	}
	lines.clear();
	attrPdf.clear();
	parseDocument();
	parseAttributes();		
}

/**
 * Function checks, does this file is a .pdf file,
 * with regular expression.
 */
bool PDFDocument::isCorrectFile(String fileName){
	std::regex regular("([a-z0-9].*)(.pdf)");
	if(std::regex_match(fileName, regular)){
		return true;
	} else {
		return false;
	}
}

/**
 * Function parses attributes of .pdf file(name, author, 
 * creator and title) and save in Map.
 */
void PDFDocument::parseAttributes(){
	std::string author = pdf.GetInfo()->GetAuthor().GetString();
	std::string title = pdf.GetInfo()->GetTitle().GetString();
	std::string creator = pdf.GetInfo()->GetCreator().GetString();
	attrPdf.insert(Map::value_type("author", author));
	attrPdf.insert(Map::value_type("file_name", nameFile));	
	attrPdf.insert(Map::value_type("creator", creator));	
	attrPdf.insert(Map::value_type("title", title));	
}

/**
 * Function parses all the .pdf document, if fins text, then
 * call function parseText().
 */
void PDFDocument::parseDocument(){
	for(int i = 0; i < pdf.GetPageCount(); i++){
		PoDoFo::PdfPage *page = pdf.GetPage(i);
		PoDoFo::PdfContentsTokenizer token(page);
		PoDoFo::PdfVariant variant;
		PoDoFo::EPdfContentsType type;
		const char* tmp = nullptr;
		while(token.ReadNext(type, tmp, variant)){
			if(type == PoDoFo::ePdfContentsType_Variant){
				parseText(variant);
			}			
		}
	}
}

/**
 * Function parses text of .pdf file ans saves lines of
 * text in Vector.
 * @param variant type of text.
 */
void PDFDocument::parseText(PoDoFo::PdfVariant &variant){
	PoDoFo::PdfString pdfStr;	
	String buf;
	if(variant.IsString() || variant.IsHexString()){		
		buf.clear();		
		pdfStr = variant.GetString();	
		if(!pdfStr.IsUnicode()){
		lines.push_back(pdfStr.GetString());	
		}
    }
	if(variant.IsArray()){	
		PoDoFo::PdfArray &ar = variant.GetArray();
		for(auto it = ar.begin(); it != ar.end(); it++){
			if(it->IsString()){
				pdfStr = it->GetString();
				buf += pdfStr.GetStringUtf8();
				std::cout << buf;					
			}
		}	
		lines.push_back(buf);
	}
}

/**
 * Function returns all the text in this file.
 * Text returns in line.
 * @return text of .pdf file
 * @throws logic_error thows exception, if
 * file doesn't contains of text.
 */
PDFDocument::StrVector PDFDocument::getText(){
	if(lines.empty()){
		throw std::logic_error("File doesn't contain text");
	} else {
		return lines;
	}
}

/**
 * Function returns all the attributes of this file(name,
 * author, creator and title).
 * @return attributes of .pdf file
 * @throws logic_error thows exception, if
 * file doesn't contains of attributes.
 */
PDFDocument::Map PDFDocument::getAttributes(){
	if(lines.empty()){
		throw std::logic_error("File doesn't contain attributes");
	} else {
		return attrPdf;
	}
}
