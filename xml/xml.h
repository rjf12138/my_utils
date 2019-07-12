#ifndef __XML_H__
#define __XML_H__

#include <iostream>
#include <string>
#include <cstdlib>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>


using namespace xercesc;

// 遍历同级的节点
#define XML_LOOP_BEGIN(NODE)\
	do { \
		if(NODE->getNodeType() != DOMNode::ELEMENT_NODE) \
			continue;

#define XML_LOOP_END(NODE)\
	} while ((NODE = NODE->getNextSibling()) != NULL);

class Xml {
public:
	Xml();
	Xml(const char *path);
	~Xml();
	// 加载 xml 文件
	void load_xml(const char *path);

	// 获取根节点下的第一个子节点， 或根据key指定根节点下的某一子节点， 失败返回 NULL
	DOMNode *get_root_node(const char *key = "");
	// 根据 node 进入该节点下的第一个子节点, 失败返回 NULL
	DOMNode *enter_node(DOMNode *node, const char *key);
	// 根据node_name搜寻 node 节点下的匹配的节点， 失败返回 NULL
	DOMNode *find_child_node(DOMNode *node, const char* node_name = "");

	// 返回 node name 失败返回 ""
	std::string get_key(DOMNode *node);
	// 确定该node下是否存在 node_name 和 key 一样的节点， 成功返回true, 失败返回false
	bool has_key(DOMNode *node, const char *key);

	// 获取该节点的字符串值
	std::string get_val_str(DOMNode *node);
	// 获取该节点的整型值
	int get_val_int(DOMNode *node);
	// 获取该节点的浮点值
	float get_val_float(DOMNode *node);

	// 获取该节点属性的字符串值
	std::string get_attr_str(DOMNode* node, const char *key = NULL);
	// 获取该节点属性的整型值
	int get_attr_int(DOMNode* node, const char *key = NULL);
	// 获取该节点属性的浮点值
	float get_attr_float(DOMNode* node, const char *key = NULL);
private:
	// 将 XMLCh 字符串转换为 std::string
	std::string u16str_to_u8str(const XMLCh *str);
	// 将 char 字符串转换为 std::u16string
	std::u16string u8str_to_u16str(const char* str);
private:
	DOMDocument* doc_;
	XercesDOMParser* parser_;
	DOMElement* root_element_;
	ErrorHandler* error_handle_;
};

#endif