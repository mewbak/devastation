DWORD hackpal[256];
void HackPalette() // call from palette_update()
{
	for(int i = 0; i < 256; i++)
	{
		//PALETTEENTRY pal = orig_palette[i];
		//hackpal[i] = pal.peBlue | (pal.peGreen << 8) | (pal.peRed << 16) | (pal.peFlags << 24);
		// RGBF -> BGRF
		DWORD tmp = ((DWORD *)orig_palette)[i] << 8;
		__asm {
			mov eax, tmp
			bswap eax
			mov tmp, eax
		}
		hackpal[i] = tmp;
	}
}

		for(hgt = 0; hgt < dwHgt; hgt++, src += nSrcWdt, dst += nDstWdt) {
			for(wdt = 0; wdt < 4 * dwWdt; wdt++) {
#ifndef RGBMODE
				*dst++ = *src++;
#else
				// PALETTEENTRY pal = system_palette[*src++];
				// dst[0] = pal.peBlue;
				// dst[1] = pal.peGreen;
				// dst[2] = pal.peRed;
				((DWORD *)dst)[0] = hackpal[*src++];
				dst += 4;
#endif
			}
		}