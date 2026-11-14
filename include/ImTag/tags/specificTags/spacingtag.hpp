#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>

namespace ImTag {
    class spacingTag : public Tag {
    public:
        spacingTag(int l) {
            this->linea = l;
        }

        std::string traducirACpp() override { 
            return "ImGui::Spacing();\n";
        }
    };
} // namespace ImTag
