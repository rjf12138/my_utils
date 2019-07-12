/*
 * Xml.cpp
 *
 *  Created on: Jul 15,2016
 *  Author: zhangyalei
 */

/*
*	modify on: Jul 15, 2019
*	Author: rjf12138
*/

#include <codecvt>
#include <locale>

#include "xml.h"

Xml::Xml():
	root_element_()
{

}

Xml::Xml(const char *path):
	root_element_()
{
	try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n"
             << message << "\n";
        XMLString::release(&message);
        exit(EXIT_FAILURE);
    }

	load_xml(path);
}

Xml::~Xml(){
	if(doc_){
		delete parser_;
		delete error_handle_;
		parser_ = nullptr;
		error_handle_ = nullptr;
	}
	std::cout << "xml Deconstruction." << std::endl;
	XMLPlatformUtils::Terminate();
}

void Xml::load_xml(const char *path){
	parser_ = new XercesDOMParser();
    parser_->setValidationScheme(XercesDOMParser::Val_Always);
    parser_->setDoNamespaces(true);    // optional

    error_handle_ = (ErrorHandler*) new HandlerBase();
    parser_->setErrorHandler(error_handle_);
	std::cout << path << std::endl;
    try {
        parser_->parse(path);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        exit(EXIT_FAILURE);
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        exit(EXIT_FAILURE);
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
        exit(EXIT_FAILURE);
    }

	doc_ = parser_->getDocument();
	root_element_ = doc_->getDocumentElement();	// 读取根节点
}

std::string Xml::u16str_to_u8str(const XMLCh *str)
{
	char *str_ptr = XMLString::transcode(str);
	std::string t_str = std::string(str_ptr);
	XMLString::release(&str_ptr);

	return t_str;
}

std::u16string Xml::u8str_to_u16str(const char* str)
{
	char16_t *str_ptr = XMLString::transcode(str);
	std::u16string t_str = std::u16string(str_ptr);
	XMLString::release(&str_ptr);

	return t_str;
}

DOMNode *
Xml::find_child_node(DOMNode *node, const char* node_name)
{
	try
    {
        for (DOMNode *child = node->getFirstChild(); child != 0; child = child->getNextSibling())
        {
    		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
    		{
				if (strlen(node_name) > 0) {
					if (XMLString::compareString(child->getNodeName(), 
									XMLString::transcode(node_name)) == 0)
						return child;
				} else 
    				return child;
    		}
        }
    }
    catch (const XMLException& toCatch)
    {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
    }

    return NULL;
}

DOMNode *Xml::get_root_node(const char *key){
	if(root_element_ == NULL)
		return NULL;

	if(strlen(key) > 0){
		 DOMNode *node = find_child_node(root_element_, key);
		if(node == NULL)
			return NULL;
		return node;
	}

	return find_child_node(root_element_);
}

DOMNode *Xml::enter_node(DOMNode *node, const char *key){	//同级搜索
	do {
		if(node->getNodeType() != DOMNode::ELEMENT_NODE)
			continue;
		std::string key_name = get_key(node);
		if(key_name.compare(std::string(key)) == 0){
			return find_child_node(node);
		}
	} while((node = node->getNextSibling()));
	return NULL;
}

std::string Xml::get_key(DOMNode *node){
	if (node == NULL)
		return "";
// covert u16string to u8string
/* method 1 
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
	std::u16string u16_str(node->getNodeName());
	return convert.to_bytes(u16_str); 
*/
	return u16str_to_u8str(node->getNodeName());
}

bool Xml::has_key(DOMNode *node, const char *key){
	do{
		if(node->getNodeType() != DOMNode::ELEMENT_NODE)
			continue;
		if(get_key(node) == key)
				return true;
	}while((node = node->getNextSibling()));

	return false;
}

std::string Xml::get_val_str(DOMNode *node){
	if(node == NULL)
		return "";
	return u16str_to_u8str(node->getTextContent());
}

int Xml::get_val_int(DOMNode *node){
	if(node == NULL)
		return 0;
	return atoi(u16str_to_u8str(node->getTextContent()).c_str()); 
}

float Xml::get_val_float(DOMNode *node){
	if(node == NULL)
		return 0.0f;
	return atof(u16str_to_u8str(node->getTextContent()).c_str());
}

std::string Xml::get_attr_str(DOMNode* node, const char *key){
	if(node == NULL)
		return "";
	DOMNode* tmp_node = node->getAttributes()->getNamedItem(u8str_to_u16str(key).c_str());
	if (tmp_node == NULL)
		return "";

	return u16str_to_u8str(tmp_node->getNodeValue());
}

int Xml::get_attr_int(DOMNode* node, const char *key){
	if (node == NULL)
		return 0;
	DOMNode* tmp_node = node->getAttributes()->getNamedItem(u8str_to_u16str(key).c_str());
	if (tmp_node == NULL)
		return 0;

	return atoi(u16str_to_u8str(node->getNodeValue()).c_str());
}

float Xml::get_attr_float(DOMNode* node, const char *key){
	if (node == NULL)
		return 0;
	DOMNode* tmp_node = node->getAttributes()->getNamedItem(u8str_to_u16str(key).c_str());
	if (tmp_node == NULL)
		return 0;

	return atof(u16str_to_u8str(node->getNodeValue()).c_str());
}
