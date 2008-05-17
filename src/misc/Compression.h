// Compression.h
// 1.0

//    This file is part of OpenRedAlert.
//
//    OpenRedAlert is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    OpenRedAlert is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with OpenRedAlert.  If not, see <http://www.gnu.org/licenses/>.

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "SDL/SDL_types.h"

/** 
 * Various decompression routines for format80, format40, and 
 * format20 type graphics
 * 
 * @author Olaf van der spek (XCC mixer)
 * @author Kareem Dana (FreeCNC)
 * @author Damien Carol (FreeRA)
 */
class Compression
{
public:
	static int decode80(const Uint8 image_in[], Uint8 image_out[]);
	static int decode40(const Uint8 image_in[], Uint8 image_out[]);
	static int decode20(const Uint8* s, Uint8* d, int cb_s);
	static int dec_base64(const Uint8* src, Uint8* target, size_t length);
};

#endif //COMPRESSION_H