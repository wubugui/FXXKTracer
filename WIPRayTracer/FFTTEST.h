#include "FFT.h"
#include <iostream>

int main()
{
	const unsigned int n = 16;
	RBVector2 *in = new RBVector2[n];

	
	for (int i = 0; i <= n; i++)
	{
		in[i] = RBVector2(0.5751, 0);
	}

	for (int i = 0; i < n; i+=4)
	{
		in[i+0] = RBVector2(-0.441589, -0.705566);
		in[i+1] = RBVector2(-0.845459, -0.818726);
		in[i+2] = RBVector2(0.845154, -0.0748291);
		in[i+3] = RBVector2(-0.440918, -0.231201);
	}
	
	
	
	in[0] = RBVector2(5.83513, 0.489553);
	in[1] = RBVector2(6.85783, 9.57747);
	in[2] = RBVector2(5.98824, 2.9015);
	in[3] = RBVector2(4.69128, 0.46084);
	in[4] = RBVector2(5.31559, 2.81987);
	in[5] = RBVector2(5.21735, 1.65519);
	in[6] = RBVector2(7.74409, 3.08523);
	in[7] = RBVector2(2.11002, 8.97445);
	in[8] = RBVector2(2.51188, 3.08636);
	in[9] = RBVector2(3.0608, 3.60008);
	in[10] = RBVector2(8.25512, 7.28959);
	in[11] = RBVector2(0.126546, 1.19202);
	in[12] = RBVector2(6.11569, 9.75939);
	in[13] = RBVector2(0.445616, 8.16461);
	in[14] = RBVector2(8.65337, 0.891299);
	in[15] = RBVector2(7.23475, 9.7252);
	
	
	RBVector2* out = new RBVector2[2*n];

	
	std::cout << "====input====" << std::endl;
	for (int i = 0; i < n; ++i)
		in[i].out();


	//RBFFTTools::iterative_fft(in, out, 4);

	RBFFTTools::iterative_fft_2d(in, out, sqrt (n ));
	RBFFTTools::iterative_ifft_2d(out, &out[n], sqrt(n));

	std::cout << "====fft====" << std::endl;
	for (int i = 0; i < n; ++i)
		out[i].out();


	std::cout << "====ifft====" << std::endl;
	for (int i = 0; i < n; ++i)
		out[i+n].out();

		
	int pu = 0;
	std::cin >> pu;
	return 0;
}