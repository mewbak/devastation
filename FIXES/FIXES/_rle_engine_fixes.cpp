for(j = 32; j != 0; j -= rle, m <<= rle) {
	rle = *src++;
	if(rle >= 0) {
		RenderLine(&dst, &src, rle, tbl, m);
	} else {
		dst += rle = -rle;
	}
}

// change width to rle

// remove cel capping
	if(((WORD *)pRLEBytes)[0] == 0xA)
	{
		nDataSize -= 10;
		pRLEBytes += 10;
	}