#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;

std::string xmlGenerator(xml_document<>& doc) {
	std::string xmlStr;

	xml_node<>* sensor = doc.allocate_node(node_element, "Sensor");
	sensor->append_node(doc.allocate_node(node_element, "Message", "Example Message"));
	xml_node<>* positions = doc.allocate_node(node_element, "Positions");
	xml_node<>* current = doc.allocate_node(node_element, "Current");
	current->append_attribute(doc.allocate_attribute("X", "4645.2"));
	xml_node<>* before = doc.allocate_node(node_element, "Before");
	before->append_node(doc.allocate_node(node_element, "X", "0.9842"));
	positions->append_node(current);
	positions->append_node(before);
	sensor->append_node(positions);
	doc.append_node(sensor);

	print(std::back_inserter(xmlStr), doc, 0);
	return xmlStr;
}


std::vector<std::map<std::string, std::string>> xmlParser(xml_document<>& doc, std::string str) {
	std::vector<std::map<std::string, std::string>> v;
	std::map<std::string, std::string> m;
	doc.parse<0>(const_cast<char*>(str.c_str()));
	std::cout << *(doc.first_node()->document()) << std::endl;
	return v;
}


int main() {
	std::string str;
	xml_document<> doc;
	
	std::ifstream in("recv.xml");
	
	str = xmlGenerator(doc);
	xmlParser(doc, str);

	std::cout << str << std::endl;
}