#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>
#include <unordered_map>

namespace ImTag {
    class checkboxTag : public Tag {
        public:
            std::unordered_map<std::string, std::string> attrs;

            checkboxTag(std::unordered_map<std::string, std::string> &attrs, int l) {
                this->linea = l;
                this->attrs = attrs;
            }

            std::string traducirACpp() override { 

                std::string code = "if (ImGui::Checkbox(\"" + attrs["name"] + "\", &" + attrs["bind"] + ")) {";
                code += attrs["onChange"];
                if(attrs["onChange"].back() != ';') {
                    code += ";\n";
                }else{
                    code += "\n";
                }
                code += "}";
                return code;
            }
        };
} // namespace ImTag
