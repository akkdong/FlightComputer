// dither.c
//

typedef unsigned char pixel;

const int BAYER_PATTERN_2X2[2][2] = 
{
	// 2x2 Bayer Dithering Matrix. Color levels: 5
	{  51, 206 },
	{ 153, 102 }
};

void makeDitherBayer2(unsigned char* pixels, int width, int height)
{
	int	col	= 0;
	int	row	= 0;

	for( int y = 0; y < height; y++ )
	{
		row	= y & 1;	//	y % 2

		for( int x = 0; x < width; x++ )
		{
			col	= x & 1;	//	x % 2

			const pixel	blue	= pixels[x * 3 + 0];
			const pixel	green	= pixels[x * 3 + 1];
			const pixel	red		= pixels[x * 3 + 2];

			pixel	color	= ((red + green + blue)/3 < BAYER_PATTERN_2X2[col][row] ? 0 : 255);

			pixels[x * 3 + 0]	= color;	//	blue
			pixels[x * 3 + 1]	= color;	//	green
			pixels[x * 3 + 2]	= color;	//	red
		}

		pixels	+= width * 3;
	}
}
