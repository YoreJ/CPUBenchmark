#include "Param.h"
using namespace std;

void Load1(std::string Tar, ParamType1& Param, pugi::xml_node& Node)
{
    for (pugi::xml_node test : Node.children("test")) {
        string testName = test.attribute("name").value();
        if (testName == Tar) {
            for (pugi::xml_node param : test.children("parameter")) 
            {
                string paramName = param.attribute("name").value();
                if (paramName == "TestSize" || paramName == "Size") Param.Size = param.attribute("value").as_int();
                else if (paramName == "Iter") Param.Iter = param.attribute("value").as_int();
            }
            break;
        }
    }
}

void Load2(std::string Tar, ParamType2& Param, pugi::xml_node& Node)
{
    for (pugi::xml_node test : Node.children("test")) {
        string testName = test.attribute("name").value();
        if (testName == Tar) {
            for (pugi::xml_node param : test.children("parameter")) 
            {
                string paramName = param.attribute("name").value();
            }
            break;
        }
    }
}

void Load3(std::string Tar, ParamType3& Param, pugi::xml_node& Node)
{
    for (pugi::xml_node test : Node.children("test")) {
        string testName = test.attribute("name").value();
        if (testName == Tar) {
            for (pugi::xml_node param : test.children("parameter")) 
            {
                string paramName = param.attribute("name").value();
            }
            break;
        }
    }
}