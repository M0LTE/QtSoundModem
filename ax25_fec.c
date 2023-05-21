/*
Copyright (C) 2019-2020 Andrei Kopanchuk UZ7HO

This file is part of QtSoundModem

QtSoundModem is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QtSoundModem is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with QtSoundModem.  If not, see http://www.gnu.org/licenses

*/

// UZ7HO Soundmodem Port by John Wiseman G8BPQ

#include "UZ7HOStuff.h"

//void fx25_encode_rs(byte * data, byte * parity, int pad, int rs_size);

//int fx25_decode_rs(byte * data, int * eras_pos, int no_eras, int pad, int rs_size);

#define  FX25_FCR 1
#define  FX25_PRIM 1
#define  FX25_IPRIM 1
#define  FX25_MM 8
#define  FX25_NN 255
#define  FX25_A0 FX25_NN

Byte FX25_ALPHA_TO[256] = {

 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26,
 0x4c, 0x98, 0x2d, 0x5a, 0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0,
 0x9d, 0x27, 0x4e, 0x9c, 0x25, 0x4a, 0x94, 0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee, 0xc1, 0x9f, 0x23,
 0x46, 0x8c, 0x05, 0x0a, 0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba, 0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1,
 0x5f, 0xbe, 0x61, 0xc2, 0x99, 0x2f, 0x5e, 0xbc, 0x65, 0xca, 0x89, 0x0f, 0x1e, 0x3c, 0x78, 0xf0,
 0xfd, 0xe7, 0xd3, 0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe, 0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71, 0xe2,
 0xd9, 0xaf, 0x43, 0x86, 0x11, 0x22, 0x44, 0x88, 0x0d, 0x1a, 0x34, 0x68, 0xd0, 0xbd, 0x67, 0xce,
 0x81, 0x1f, 0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93, 0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33, 0x66, 0xcc,
 0x85, 0x17, 0x2e, 0x5c, 0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e, 0x21, 0x42, 0x84, 0x15, 0x2a, 0x54,
 0xa8, 0x4d, 0x9a, 0x29, 0x52, 0xa4, 0x55, 0xaa, 0x49, 0x92, 0x39, 0x72, 0xe4, 0xd5, 0xb7, 0x73,
 0xe6, 0xd1, 0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e, 0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6, 0xf1, 0xff,
 0xe3, 0xdb, 0xab, 0x4b, 0x96, 0x31, 0x62, 0xc4, 0x95, 0x37, 0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41,
 0x82, 0x19, 0x32, 0x64, 0xc8, 0x8d, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xdd, 0xa7, 0x53, 0xa6,
 0x51, 0xa2, 0x59, 0xb2, 0x79, 0xf2, 0xf9, 0xef, 0xc3, 0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x09,
 0x12, 0x24, 0x48, 0x90, 0x3d, 0x7a, 0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb, 0x8b, 0x0b, 0x16,
 0x2c, 0x58, 0xb0, 0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36, 0x6c, 0xd8, 0xad, 0x47, 0x8e, 0x00
};

Byte FX25_INDEX_OF[256] = {

255,  0,  1, 25,  2, 50, 26,198,  3,223, 51,238, 27,104,199, 75,
  4,100,224, 14, 52,141,239,129, 28,193,105,248,200,  8, 76,113,
  5,138,101, 47,225, 36, 15, 33, 53,147,142,218,240, 18,130, 69,
 29,181,194,125,106, 39,249,185,201,154,  9,120, 77,228,114,166,
  6,191,139, 98,102,221, 48,253,226,152, 37,179, 16,145, 34,136,
 54,208,148,206,143,150,219,189,241,210, 19, 92,131, 56, 70, 64,
 30, 66,182,163,195, 72,126,110,107, 58, 40, 84,250,133,186, 61,
202, 94,155,159, 10, 21,121, 43, 78,212,229,172,115,243,167, 87,
  7,112,192,247,140,128, 99, 13,103, 74,222,237, 49,197,254, 24,
227,165,153,119, 38,184,180,124, 17, 68,146,217, 35, 32,137, 46,
 55, 63,209, 91,149,188,207,205,144,135,151,178,220,252,190, 97,
242, 86,211,171, 20, 42, 93,158,132, 60, 57, 83, 71,109, 65,162,
 31, 45, 67,216,183,123,164,118,196, 23, 73,236,127, 12,111,246,
108,161, 59, 82, 41,157, 85,170,251, 96,134,177,187,204, 62, 90,
203, 89, 95,176,156,169,160, 81, 11,245, 22,235,122,117, 44,215,
 79,174,213,233,230,231,173,232,116,214,244,234,168, 80, 88,175
};


Byte FX25_CCSDS_poly_8[9] =
{ 29, 188, 142, 221, 118, 206, 52, 168, 0 };

Byte FX25_CCSDS_poly_16[17] =
	{136,240,208,195,181,158,201,100, 11, 83,167,107,113,110,106,121, 0 };


Byte FX25_CCSDS_poly_32[33] = {
 18,251,215, 28, 80,107,248, 53, 84,194, 91, 59,176, 99,203,137,
 43,104,137,  0, 44,149,148,218, 75, 11,173,254,194,109,  8, 11,
0 };

Byte FX25_CCSDS_poly_64[65] = {
 40, 21,218, 23, 48,237, 69,  6, 87, 42, 29,193,160,150,113, 32,
 35,172,241,240,184, 90,188,225, 87,130,254, 41,245,253,184,241,
188,176, 54, 58,240,226,119,185, 77,150, 48,140,169,160, 96,217,
 15,202,218,190,135,103,129, 77, 57,166,164, 12, 13,178, 53, 46,
0 };



integer  FX25_NROOTS ;
Byte FX25_GENPOLY[256];

Byte  MODNN(int x)
{
	return x % 255;
}


void encode_rs(Byte * data, Byte * parity, int pad)
{
	int  i, j;
	Byte feedback;

	memset(parity, 0, FX25_NROOTS);

	i = 0;

	while (i < FX25_NN - FX25_NROOTS - pad)
	{
		feedback = FX25_INDEX_OF[data[i] ^ parity[0]];
	
		if (feedback != FX25_A0)
		{
			j = 1;
			while (j < FX25_NROOTS)
			{
				parity[j] = parity[j] ^ FX25_ALPHA_TO[MODNN(feedback + FX25_GENPOLY[FX25_NROOTS - j])];
				j++;
			}
		}
		move(&parity[1], &parity[0], FX25_NROOTS - 1);
	
		if (feedback != FX25_A0)
			parity[FX25_NROOTS - 1] = FX25_ALPHA_TO[MODNN(feedback + FX25_GENPOLY[0])];
		else
			parity[FX25_NROOTS - 1] = 0;
		i++;
	}
}


int FX25_MIN(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}


int decode_rs(Byte * data, int * eras_pos, int no_eras, int pad)
{
	int  deg_lambda, el, deg_omega;
	int   i, j, r, k;
	Byte  q, tmp, num1, num2, den, discr_r;
	Byte s[256];
	Byte lambda[256];
	Byte b[256];
	Byte t[256];
	Byte omega[256];
	Byte root[256];
	Byte reg[256];
	Byte loc[256];
	int syn_error, count = 0;

	if (pad < 0 || pad>238)
		return -1;

	i = 0;
	while (i < FX25_NROOTS)
	{
		s[i] = data[0];
		i++;

	}
	j = 1;
	while (j < FX25_NN - pad)
	{
		i = 0;
		while (i < FX25_NROOTS)
		{
			if (s[i] == 0)
				s[i] = data[j];
			else
				s[i] = data[j] ^ FX25_ALPHA_TO[MODNN(FX25_INDEX_OF[s[i]] + (FX25_FCR + i)*FX25_PRIM)];
			i++;
		}
		j++;

	}
	syn_error = 0;
	i = 0;
	while (i < FX25_NROOTS)
	{
		syn_error = syn_error | s[i];
		s[i] = FX25_INDEX_OF[s[i]];
		i++;
	}
	if (syn_error == 0)
		return count;

	memset(&lambda[1], 0, FX25_NROOTS);
	lambda[0] = 1;
	i = 0;
	while (i < FX25_NROOTS + 1)
	{
		b[i] = FX25_INDEX_OF[lambda[i]];
		i++;
	}

	r = no_eras;
	el = no_eras;
	r++;
	while (r <= FX25_NROOTS)
	{
		discr_r = 0;
		i = 0;
		while (i < r)
		{
			if (lambda[i] != 0 && s[r - i - 1] != FX25_A0)
				discr_r = discr_r ^ FX25_ALPHA_TO[MODNN(FX25_INDEX_OF[lambda[i]] + s[r - i - 1])];
			i++;
		}
		discr_r = FX25_INDEX_OF[discr_r];
		if (discr_r == FX25_A0)
		{
			move(&b[0], &b[1], FX25_NROOTS);
			b[0] = FX25_A0;
		}
		else
		{
			t[0] = lambda[0];
			i = 0;
			while (i < FX25_NROOTS)
			{
				if (b[i] != FX25_A0)
					t[i + 1] = lambda[i + 1] ^ FX25_ALPHA_TO[MODNN(discr_r + b[i])];
				else
					t[i + 1] = lambda[i + 1];
				i++;
			}

			if (2 * el <= r + no_eras - 1)
			{
				el = r + no_eras - el;
				i = 0;
				while (i <= FX25_NROOTS)
				{
					if (lambda[i] == 0)
						b[i] = FX25_A0;
					else
						b[i] = MODNN(FX25_INDEX_OF[lambda[i]] - discr_r + FX25_NN);
					i++;
				}
			}
			else
			{
				move(&b[0], &b[1], FX25_NROOTS);
				b[0] = FX25_A0;
			}
			move(t, lambda, FX25_NROOTS + 1);
		}
		r++;
	}
	deg_lambda = 0;
	i = 0;
	while (i < FX25_NROOTS + 1)
	{
		lambda[i] = FX25_INDEX_OF[lambda[i]];
		if (lambda[i] != FX25_A0)
			deg_lambda = i;
		i++;
	}
	move(&lambda[1], &reg[1], FX25_NROOTS);
	count = 0;
	i = 1;
	k = FX25_IPRIM - 1;
	while (i <= FX25_NN)
	{
		q = 1;
		j = deg_lambda;
		while (j > 0)
		{
			if (reg[j] != FX25_A0)
			{
				reg[j] = MODNN(reg[j] + j);
				q = q ^ FX25_ALPHA_TO[reg[j]];
			}
			j--;
		}
		if (q == 0)
		{
			root[count] = i;
			loc[count] = k;
			count++;
			if (count == deg_lambda)
				break;
		}
		i++;
		k = MODNN(k + FX25_IPRIM);
	}
	if (deg_lambda != count)
		return -1;

	deg_omega = deg_lambda - 1;
	i = 0;
	while (i <= deg_omega)
	{
		tmp = 0;
		j = i;
		while (j >= 0)
		{
			if (s[i - j] != FX25_A0 && lambda[j] != FX25_A0)
				tmp = tmp ^ FX25_ALPHA_TO[MODNN(s[i - j] + lambda[j])];
			j--;
		}
		omega[i] = FX25_INDEX_OF[tmp];
		i++;
	}
	j = count - 1;
	while (j >= 0)
	{
		num1 = 0;
		i = deg_omega;
		while (i >= 0)
		{
			if (omega[i] != FX25_A0)
				num1 = num1 ^ FX25_ALPHA_TO[MODNN(omega[i] + i * root[j])];
			i--;
		}

		num2 = FX25_ALPHA_TO[MODNN(root[j] * (FX25_FCR - 1) + FX25_NN)];
		den = 0;
		i = FX25_MIN(deg_lambda, FX25_NROOTS - 1) & 0xFE;
		while (i >= 0)
		{
			if (lambda[i + 1] != FX25_A0)
				den = den ^ FX25_ALPHA_TO[MODNN(lambda[i + 1] + i * root[j])];
			i = i - 2;
		}
		if (num1 != 0 && loc[j] >= pad)
			data[loc[j] - pad] = data[loc[j] - pad] ^ FX25_ALPHA_TO[MODNN(FX25_INDEX_OF[num1] + FX25_INDEX_OF[num2] + FX25_NN - FX25_INDEX_OF[den])];
		j--;
	}

	return count;
}


void fx25_encode_rs(Byte * data, Byte *parity, int pad, int rs_size)
{
	switch (rs_size)
	{
	case 8:
		move(&FX25_CCSDS_poly_8[0], &FX25_GENPOLY[0], 9);
		FX25_NROOTS = rs_size;
		encode_rs(data, parity, 0);
		return;

	case 16:
		move(&FX25_CCSDS_poly_16[0], &FX25_GENPOLY[0], 17);
		FX25_NROOTS = rs_size;
		encode_rs(data, parity, 0);
		return;



	case 32:

		move(&FX25_CCSDS_poly_32[0], &FX25_GENPOLY[0], 33);
		FX25_NROOTS = rs_size;
		encode_rs(data, parity, 0);
		return;

	case 64: 
		
		move(&FX25_CCSDS_poly_64[0], &FX25_GENPOLY[0], 65);
		FX25_NROOTS = rs_size;
		encode_rs(data, parity, 0);
		return;

	}
}

int fx25_decode_rs(Byte * data, int * eras_pos, int no_eras, int pad, int rs_size)
{
	switch (rs_size)
	{
	case 8:

		move(&FX25_CCSDS_poly_8[0], &FX25_GENPOLY[0], 9);
		FX25_NROOTS = rs_size;
		return decode_rs(data, eras_pos, no_eras, pad);

	case 16:
		
		move(&FX25_CCSDS_poly_16[0], &FX25_GENPOLY[0], 17);
		FX25_NROOTS = rs_size;
		return decode_rs(data, eras_pos, no_eras, pad);
		
	case 32:
		
		move(&FX25_CCSDS_poly_32[0], &FX25_GENPOLY[0], 33);
		FX25_NROOTS = rs_size;
		return decode_rs(data, eras_pos, no_eras, pad);

	case 64:
		
		move(&FX25_CCSDS_poly_64[0], &FX25_GENPOLY[0], 65); 
		FX25_NROOTS = rs_size;
		return decode_rs(data, eras_pos, no_eras, pad);

	default:

		return -1;
	}
}


