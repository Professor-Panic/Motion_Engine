#include "ttfparser/ttfparser.h"
void font_parsed(void* args, void* _font_data, int error) {
	if (error) {
		*(uint8_t*)args = error;
		printf("Unable to parse font ");
	}
	else {
		TTFFontParser::FontData* font_data = (TTFFontParser::FontData*)_font_data;
		printf("Font: %s %s parsed\n", font_data->font_names.begin()->font_family.c_str(), font_data->font_names.begin()->font_style.c_str());
		printf("Number of glyphs: %d\n", uint32_t(font_data->glyphs.size()));

		//step through glyph geometry
		{
			for (const auto& glyph_iterator : font_data->glyphs) {
				uint32_t num_curves = 0, num_lines = 0;
				for (const auto& path_list : glyph_iterator.second.path_list) {
					for (const auto& geometry : path_list.geometry) {
						if (geometry.is_curve)
							num_curves++;
						else
							num_lines++;
					}
				}
			}
		}

		*(uint8_t*)args = 1;
	}
}