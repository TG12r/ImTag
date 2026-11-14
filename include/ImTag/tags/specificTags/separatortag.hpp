#pragma once
#include "ImTag/tags/tag.hpp"
#include <string>

namespace ImTag {
    class separatorTag : public Tag {
    public:
        separatorTag(int l) {
            this->linea = l;
        }

        std::string traducirACpp() override { 
            return "ImGui::Separator();\n";
        }
    };
} // namespace ImTag
