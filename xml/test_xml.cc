#include "xml.h"

#define TEST_ATTR

int main(void)
{
    std::string label_name;
    Xml xml("./user_info.xml");
	DOMNode *root_node = xml.get_root_node(), *sub_node = NULL; 
	std::string struct_name = xml.get_key(root_node);
	std::cout << "xml_loop_begin." << std::endl;
#ifdef TEST_ATTR
	sub_node = xml.enter_node(root_node, "group_member");
	if (sub_node == NULL) {
		std::cout << "sub_node is null" << std::endl;
		return 0;
	}
	XML_LOOP_BEGIN(sub_node)
		std::cout << "key: " << xml.get_key(sub_node) << std::endl;
		std::cout << "type: " << xml.get_attr_str(sub_node, "type") << std::endl;
		std::cout << "name: " << xml.get_attr_str(sub_node, "name") << std::endl;
		std::cout << "key_type: " << xml.get_attr_str(sub_node, "key_type") << std::endl;
		std::cout << "key_name: " << xml.get_attr_str(sub_node, "key_name") << std::endl;
	XML_LOOP_END(sub_node)
#else
	sub_node = xml.enter_node(root_node, "data_type");
	if (sub_node == NULL) {
		std::cout << "sub_node is null" << std::endl;
		return 0;
	}
	int i = 0;
	XML_LOOP_BEGIN(sub_node)
		switch (i)
		{
		case 0:
			std::cout << "int_type: " << xml.get_val_int(sub_node) << std::endl;
			i++;
			break;
		case 1:
			std::cout << "float_type: " << xml.get_val_float(sub_node) << std::endl;
			i++;
			break;
		case 2:
			std::cout << "string_type: " << xml.get_val_str(sub_node) << std::endl;
			break;
		default:
			break;
		}
	XML_LOOP_END(sub_node)
#endif

	std::cout << "test program end." << std::endl;
    return 0;
}