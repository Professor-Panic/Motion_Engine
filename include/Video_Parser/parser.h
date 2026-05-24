#pragma once
#include "structs.h"
#include "json/json.hpp"
#include "Font_Parser/font_parser.h"
void ParseCircles(nlohmann::json &animFile,AnimData& anim);
void ParseText(nlohmann::json &animFile,AnimData& anim,TTFFontParser::FontData &font_data);
