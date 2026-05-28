#pragma once
#include "raylib.h"
#include "raymath.h"
#include "structs.h"
#include "ttfparser/ttfparser.h"
#include "extras.h"
void ParsePath(Path& c_path,std::vector<TTFFontParser::Path>paths,float unitsPerEm,float fontSize);
WordPath GetPathsForText(const char* text, TTFFontParser::FontData &font_data,float wordSpacing);