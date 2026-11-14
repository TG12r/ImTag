#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>
#include <unordered_map>

namespace ImTag {
    class buttonTag : public Tag {
        public:
            std::string name;
            std::string onClick = "void()";

            buttonTag(std::unordered_map<std::string, std::string> &attrs, int l) {
                this->linea = l;
                this->name = attrs["name"];
                this->onClick = attrs["onClick"].empty() ? this->onClick : attrs["onClick"];
            }

            std::string traducirACpp() override { 
                std::string code = "if (ImGui::Button(\"" + name + "\")){\n";
                code += onClick;
                if(onClick.back() != ';') {
                    code += ";\n";
                }else{
                    code += "\n";
                }
                code += "}\n";
                return code;
            }
        };
} // namespace ImTag
