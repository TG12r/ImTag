#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>
#include <unordered_map>

namespace ImTag {
    class textTag : public Tag {
        public:
            std::string value;

            textTag(std::unordered_map<std::string, std::string> &attrs, int l) {
                this->linea = l;
                this->value = attrs["value"];
            }

            std::string traducirACpp() override { 
                std::string code = "ImGui::Text(\"" + value + "\");\n";
                return code;
            }
        };
} // namespace ImTag
