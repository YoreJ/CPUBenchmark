#include "XMLAnay.h"
#include <iostream>
using namespace std;

void PrintNode(const pugi::xml_node &Node, std::ofstream &output, int Depth = 0) 
{
    std::string indent(Depth * 2, ' ');
    output << indent << "节点名称: " << Node.name();
    if (Node.text()) output << ", 值: " << Node.text().get();
    output << std::endl;
    for (auto& attr: Node.attributes()) output << indent << "  属性: " << attr.name() << ", 值: " << attr.value() << std::endl;
    for (auto& child: Node.children()) PrintNode(child, output, Depth + 1);
}

Tuple XMLAnal(std::string Path, PerfCounter& pc)
{
    pc.reset();
    pc.start();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(Path.c_str());
    std::ofstream output("parse_results.txt");
    if (!output.is_open()) 
    {
        std::cerr << "无法打开文件写入" << std::endl;
        return Tuple();
    }
    if (result) PrintNode(doc, output);
    else 
    {
        std::cerr << "XML 解析失败: " << result.description() << std::endl;
        output.close();
        return Tuple();
    }
    output.close();
    return pc.stop();
}