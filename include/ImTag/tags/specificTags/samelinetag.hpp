#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>

namespace ImTag {
    class sameLineTag : public Tag {
    public:
        sameLineTag(int l) {
            this->linea = l;
        }

        std::string traducirACpp() override { 
            return "ImGui::SameLine();\n";
        }
    };
} // namespace ImTag
