// ESP WROOM 32 Plotting and manipulating graphics on 160x128 screen
//define commands for matrixes and module + screen constants
#include <SPI.h>
#include <TFT_eSPI.h>
//#include <noDelay.h>

TFT_eSPI myScreen=TFT_eSPI();
static const unsigned char Testcard_F[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xfd, 0xfd, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 
0xbf, 0xff, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xfd, 0x81, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x07, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0x01, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xc0, 
0x00, 0x00, 0x07, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0xfe, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 
0x07, 0xff, 0xff, 0xfe, 0xbf, 0xff, 0xff, 0xff, 0xfe, 0x5f, 0xfa, 0xff, 0xff, 0xff, 0xff, 0xfa, 
0xff, 0xff, 0xff, 0x80, 0x7f, 0xfd, 0xfb, 0xfe, 0x8f, 0xff, 0x7f, 0xf8, 0x7e, 0x5f, 0x92, 0x5f, 
0xfb, 0xf8, 0xcf, 0xfa, 0xbf, 0x3f, 0xef, 0x80, 0x7f, 0xbe, 0xf9, 0xfa, 0x8f, 0xff, 0x7f, 0xb9, 
0xfe, 0x57, 0xb2, 0x1f, 0xfb, 0xf8, 0xde, 0x6a, 0x3b, 0x3f, 0xd7, 0x80, 0x7f, 0xfb, 0xfd, 0xfe, 
0x8f, 0xff, 0x7f, 0xfb, 0xfe, 0x5f, 0xf2, 0x7f, 0xfb, 0xfe, 0xdf, 0xfa, 0x7f, 0xff, 0xab, 0x80, 
0x7f, 0xf5, 0xde, 0xfe, 0x8f, 0xff, 0xff, 0xfb, 0xfc, 0x47, 0xa2, 0x1f, 0xf9, 0xfe, 0xdf, 0xfa, 
0x7d, 0xf7, 0x55, 0xfe, 0x7e, 0xaa, 0xaf, 0x7e, 0x8f, 0xff, 0xff, 0xff, 0xfc, 0x48, 0xa2, 0x1f, 
0xfb, 0xfb, 0xdf, 0xfa, 0x7d, 0xeb, 0xaa, 0xfe, 0x7f, 0x55, 0x57, 0xfa, 0x84, 0x3f, 0xfe, 0xff, 
0xff, 0x5f, 0xfa, 0xff, 0xfe, 0xf8, 0xdf, 0xfa, 0x3f, 0xd5, 0x55, 0xfe, 0x7e, 0xaa, 0xab, 0xfa, 
0x83, 0xff, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfa, 0xcf, 0xfa, 0x3f, 0xaa, 0xaa, 0xfe, 
0x7f, 0x55, 0x55, 0xe2, 0x87, 0xff, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfa, 0xcf, 0xea, 
0x1f, 0xd5, 0x5d, 0xfe, 0x7f, 0xaa, 0xaa, 0xfe, 0x87, 0xff, 0x7e, 0xff, 0xff, 0x7f, 0xfb, 0xff, 
0xfe, 0xfe, 0xcf, 0xe2, 0x3f, 0xae, 0xaf, 0xfe, 0x07, 0xfd, 0x75, 0xf0, 0xa7, 0xff, 0x7e, 0xff, 
0xc0, 0x00, 0x00, 0x03, 0xfe, 0xfe, 0xcf, 0xf2, 0x3f, 0xdf, 0x5f, 0xfe, 0x03, 0xfe, 0xfa, 0xfa, 
0xa7, 0xff, 0xfe, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0xfe, 0xdf, 0xf2, 0x7f, 0xbe, 0xff, 0xfe, 
0x03, 0xff, 0xfd, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfb, 
0xff, 0xff, 0xff, 0xfe, 0x03, 0xfe, 0xfb, 0xff, 0xbf, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03, 
0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xbf, 0xc0, 0x03, 0xfd, 0xf5, 0xfe, 0xbf, 0xff, 0xff, 0xff, 
0x80, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xfa, 0xff, 0xd7, 0x7f, 0x80, 0x03, 0x5e, 0xea, 0xfa, 
0x87, 0xff, 0x7e, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xfa, 0xdf, 0xf2, 0x7f, 0xaf, 0xf1, 0x80, 
0x03, 0x4f, 0x75, 0xfa, 0xaf, 0xff, 0x7e, 0xff, 0xff, 0x7f, 0xfb, 0xff, 0xff, 0xfe, 0xdf, 0xf2, 
0x3f, 0x5b, 0xe1, 0x80, 0x03, 0x4f, 0xfb, 0xf4, 0xa7, 0xef, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xfe, 0xdf, 0xe2, 0x1f, 0xb7, 0xc7, 0x80, 0x03, 0x1f, 0xed, 0xfe, 0xa7, 0xff, 0xfe, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x7a, 0xdf, 0xea, 0x3f, 0xef, 0x87, 0x80, 0x03, 0xdf, 0xf7, 0xfe, 
0x87, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfa, 0xff, 0xff, 0x7a, 0xdf, 0xea, 0x1f, 0xd7, 0x5f, 0x80, 
0x03, 0x7d, 0xef, 0xbe, 0x87, 0xff, 0xff, 0xff, 0xfe, 0x47, 0xe2, 0x5f, 0xfb, 0x78, 0xdf, 0xf2, 
0x3b, 0xef, 0xbf, 0x80, 0x03, 0xfe, 0xff, 0x7e, 0xa7, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 
0xf8, 0xf8, 0xcf, 0xf2, 0x33, 0xfc, 0xff, 0x80, 0x7f, 0xff, 0xfe, 0xfe, 0xaf, 0xff, 0xff, 0xfb, 
0xff, 0xff, 0xff, 0xff, 0xfb, 0xf8, 0xdf, 0xf2, 0x7e, 0xfb, 0xff, 0x80, 0x7f, 0xff, 0xfd, 0xfe, 
0xaf, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xf8, 0xc7, 0xfa, 0x7f, 0x7b, 0xff, 0x80, 
0x7f, 0xff, 0xfb, 0xfe, 0xaf, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7b, 0xf8, 0xdf, 0xfa, 
0x7e, 0x3b, 0xff, 0x80, 0x7f, 0x2f, 0xf9, 0x0e, 0x81, 0xff, 0xf8, 0xbb, 0xff, 0xff, 0xff, 0xff, 
0xba, 0x12, 0xc2, 0x2a, 0x3c, 0x38, 0x01, 0x80, 0x7e, 0x00, 0x10, 0x00, 0x80, 0x06, 0x00, 0x17, 
0xe7, 0xff, 0xff, 0xff, 0xd0, 0x00, 0xc0, 0x02, 0x00, 0x10, 0x00, 0x80, 0x7e, 0x00, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x80, 
0x7e, 0x00, 0x10, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
0x00, 0x30, 0x01, 0x80, 0x7f, 0x3f, 0xfb, 0xf2, 0xff, 0xff, 0xff, 0xfc, 0x01, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xe9, 0x76, 0x00, 0x3b, 0x61, 0x80, 0x7f, 0x7f, 0xfb, 0xfa, 0xff, 0xff, 0xff, 0xf8, 
0x01, 0x7f, 0xff, 0xff, 0xfe, 0xfa, 0xe9, 0x56, 0x0f, 0xbb, 0xff, 0x80, 0x7f, 0x7f, 0xfb, 0xfe, 
0xff, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfe, 0xe9, 0x56, 0x0f, 0xbb, 0xff, 0x80, 
0x7f, 0x7f, 0xfb, 0xfa, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0x78, 0xe9, 0x56, 
0x0f, 0xba, 0x3d, 0xfe, 0x7f, 0x7f, 0xfb, 0xfe, 0xff, 0xff, 0xfb, 0xf0, 0x03, 0x01, 0xff, 0xff, 
0xff, 0xbe, 0xe9, 0x76, 0x0f, 0xbb, 0xff, 0xfe, 0x7f, 0x7f, 0xfb, 0xfe, 0xff, 0xff, 0xff, 0xf0, 
0x03, 0xf0, 0xff, 0xff, 0xff, 0xde, 0xeb, 0x76, 0x1f, 0xfb, 0xff, 0xfe, 0x7f, 0x7f, 0xfb, 0xfe, 
0xff, 0xff, 0xff, 0xf0, 0x03, 0xf8, 0xff, 0xff, 0xff, 0xea, 0xeb, 0x76, 0x18, 0xfb, 0xfd, 0xfe, 
0x7f, 0xcf, 0xfa, 0xfe, 0xff, 0xff, 0xdf, 0xe0, 0x07, 0xfc, 0xff, 0xff, 0xff, 0xfe, 0xe9, 0x76, 
0x00, 0x3b, 0xfd, 0xfe, 0x7f, 0xff, 0xfb, 0xfe, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 
0xff, 0xfe, 0xc9, 0x76, 0x00, 0xbb, 0xf1, 0xfe, 0x7f, 0xff, 0xfb, 0xfe, 0xff, 0xff, 0xff, 0xe0, 
0x07, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc9, 0xb6, 0x38, 0x38, 0xfd, 0xfe, 0x7f, 0x1f, 0xf8, 0xfe, 
0xff, 0xff, 0x7f, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xc9, 0x26, 0x00, 0x38, 0x61, 0xfe, 
0x7f, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc9, 0xa6, 
0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xc0, 0x0e, 0x1f, 0xff, 0xff, 
0xf9, 0xff, 0xc9, 0xa7, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xc0, 
0x0e, 0x78, 0xfe, 0x01, 0x30, 0xff, 0xc9, 0xa7, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x00, 0x38, 0x00, 
0xff, 0xff, 0xef, 0xc0, 0x0f, 0xf8, 0x00, 0x00, 0x1d, 0xfe, 0xc9, 0xb6, 0x00, 0x38, 0x01, 0xfe, 
0x7f, 0x5f, 0xfb, 0xfe, 0xff, 0xff, 0xef, 0xc0, 0x0f, 0xfe, 0x00, 0x00, 0x39, 0xfe, 0xc9, 0xa6, 
0x3f, 0xbb, 0xfd, 0xfe, 0x03, 0x5f, 0xfb, 0xfe, 0xff, 0xff, 0xcf, 0xc0, 0x0f, 0xfe, 0x00, 0x00, 
0x3f, 0xfe, 0xcd, 0xa6, 0x8f, 0xfb, 0xfd, 0xc0, 0x03, 0x1f, 0xfb, 0xfe, 0xff, 0xff, 0xcf, 0x80, 
0x07, 0xfe, 0x00, 0x00, 0x2f, 0xfe, 0xe9, 0xb6, 0x8f, 0xfb, 0xff, 0x80, 0x03, 0x1f, 0xfb, 0xfe, 
0xff, 0xff, 0xcf, 0x80, 0x07, 0xe6, 0x00, 0x20, 0x07, 0xff, 0xff, 0xfe, 0xff, 0xfb, 0xfd, 0x80, 
0x03, 0x1f, 0xd5, 0xfe, 0xff, 0xff, 0xc7, 0x80, 0x03, 0xfe, 0x00, 0x20, 0xc7, 0xf7, 0xff, 0xfe, 
0xff, 0xd7, 0xff, 0x80, 0x03, 0x3f, 0xd5, 0xfe, 0xff, 0xff, 0x87, 0x00, 0x03, 0x7c, 0x00, 0x00, 
0xc6, 0x77, 0xff, 0xfe, 0xff, 0xd5, 0xff, 0x80, 0x03, 0x3f, 0xd5, 0xfe, 0xff, 0xff, 0x86, 0x00, 
0x03, 0xc4, 0x02, 0x00, 0xf0, 0x77, 0xff, 0xfe, 0xff, 0xd1, 0xff, 0x80, 0x03, 0x3f, 0xd5, 0xfe, 
0xff, 0xff, 0x82, 0x00, 0x01, 0xf8, 0x02, 0x00, 0x06, 0x77, 0xff, 0xfe, 0xff, 0xd5, 0xff, 0x80, 
0x07, 0xff, 0xd5, 0xfe, 0xff, 0xff, 0x84, 0x00, 0x01, 0xf0, 0x02, 0x00, 0x1c, 0xf7, 0xff, 0xfe, 
0xff, 0xd5, 0xff, 0xc0, 0x0f, 0x7f, 0xd4, 0xfe, 0xff, 0xff, 0x80, 0x00, 0x00, 0xf0, 0x00, 0x00, 
0x01, 0xf7, 0xff, 0xfe, 0xff, 0xd1, 0xff, 0xe0, 0x3e, 0x00, 0x10, 0x00, 0xff, 0xff, 0x88, 0x00, 
0x00, 0x00, 0x00, 0x10, 0x07, 0xf3, 0xff, 0xfe, 0x00, 0x10, 0x00, 0xf8, 0x7f, 0x01, 0x50, 0x00, 
0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x02, 0x10, 0x1f, 0xe7, 0xff, 0xfe, 0x00, 0x50, 0x01, 0xfe, 
0x7f, 0xff, 0xff, 0xff, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x10, 0x07, 0xe3, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xfe, 0x3e, 0x00, 0x10, 0x00, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x20, 0x10, 
0x01, 0xe1, 0xff, 0xfe, 0x00, 0x10, 0x00, 0xf8, 0x0e, 0x03, 0xd4, 0x7e, 0xc0, 0x07, 0x80, 0x00, 
0x03, 0x00, 0x60, 0x10, 0x0f, 0xc1, 0xff, 0xfe, 0x38, 0xd4, 0x13, 0xe0, 0x03, 0x1f, 0xd5, 0x7e, 
0xc0, 0x07, 0x80, 0x00, 0x03, 0x00, 0x13, 0xf0, 0x1f, 0xe3, 0xff, 0xfe, 0x3f, 0x54, 0x3f, 0xc0, 
0x03, 0x7f, 0xd5, 0xfe, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x7f, 0xf3, 0xff, 0xfe, 
0x7f, 0x54, 0x7f, 0x80, 0x03, 0xff, 0xd5, 0xfe, 0xc0, 0x07, 0x80, 0x01, 0x80, 0x01, 0x07, 0xf0, 
0x7f, 0xf3, 0xff, 0xfe, 0x7f, 0xd1, 0xfd, 0x80, 0x03, 0x5f, 0xd5, 0xfe, 0xc0, 0x07, 0x80, 0x01, 
0x88, 0x00, 0x0f, 0xe0, 0xff, 0xfb, 0xff, 0xfe, 0x7f, 0x51, 0xff, 0x80, 0x03, 0x5f, 0xf9, 0xfa, 
0xc0, 0x07, 0xc0, 0x01, 0xa8, 0x00, 0x1f, 0xf0, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfb, 0xff, 0x80, 
0x03, 0x5f, 0xfb, 0xfe, 0xc0, 0x07, 0xc0, 0x00, 0x08, 0x00, 0x1f, 0xe1, 0xff, 0xff, 0xff, 0xfe, 
0xff, 0xfb, 0xff, 0x80, 0x03, 0x5f, 0xfb, 0xfe, 0xc0, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xe3, 
0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfb, 0xff, 0x80, 0x03, 0x5f, 0xfb, 0xfe, 0xc0, 0x07, 0xc0, 0x38, 
0x00, 0x00, 0x7f, 0xe3, 0xff, 0xfe, 0xff, 0xfe, 0xbf, 0xf8, 0xff, 0x80, 0x07, 0xdf, 0xfa, 0x7e, 
0xc0, 0x07, 0xe0, 0x3e, 0x02, 0x00, 0xff, 0xc7, 0xff, 0xfe, 0xff, 0xfe, 0x06, 0x38, 0x01, 0xc0, 
0x67, 0x00, 0x38, 0x02, 0xc0, 0x07, 0xe0, 0x7f, 0x00, 0x01, 0xff, 0x87, 0xff, 0xfe, 0xff, 0xfe, 
0x00, 0x38, 0x01, 0xfe, 0x67, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xe0, 0x7f, 0x80, 0x03, 0xff, 0x03, 
0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x77, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xf0, 0x7f, 
0x80, 0x07, 0xfc, 0x03, 0xff, 0xff, 0xf3, 0xef, 0xff, 0xff, 0xff, 0xfe, 0x77, 0xff, 0xff, 0xfe, 
0xc0, 0x07, 0xf0, 0x7f, 0xc0, 0x07, 0xf8, 0x03, 0xff, 0xff, 0xd3, 0xee, 0xff, 0xff, 0xff, 0xfe, 
0x77, 0x3f, 0x7f, 0xfa, 0xc0, 0x07, 0x38, 0x7f, 0xc0, 0x0f, 0xf0, 0x06, 0xef, 0xff, 0xd3, 0xee, 
0x0c, 0xb8, 0x01, 0xfe, 0x76, 0xff, 0xfb, 0xfe, 0xc0, 0x07, 0x38, 0x7f, 0xc0, 0x1f, 0xf0, 0x06, 
0x0f, 0xff, 0xd3, 0xfe, 0x1f, 0xb9, 0xf1, 0xfe, 0x77, 0xff, 0xfb, 0xfe, 0xc0, 0x03, 0x3c, 0x3f, 
0xc0, 0x3f, 0xe0, 0x0f, 0x07, 0xf2, 0xdf, 0xfe, 0x3f, 0xfb, 0xf9, 0xfe, 0x77, 0xff, 0xfb, 0xfe, 
0xc0, 0x03, 0x1c, 0x3f, 0xe0, 0x7f, 0xc0, 0x0f, 0x83, 0xe0, 0xdf, 0xfe, 0x3f, 0xbb, 0xfd, 0xfe, 
0x77, 0xff, 0xfb, 0xfe, 0xc0, 0x03, 0x0e, 0x3f, 0xe0, 0xff, 0x80, 0x0f, 0xe3, 0xe0, 0xdf, 0xfe, 
0x3f, 0xbb, 0xfd, 0xfe, 0x77, 0xff, 0xfb, 0xfe, 0xc0, 0x03, 0x17, 0x1f, 0xe1, 0xff, 0x00, 0x1f, 
0xc3, 0xd8, 0xdb, 0xfe, 0x3f, 0xbb, 0xfd, 0xfe, 0x77, 0x7f, 0xfb, 0xfe, 0xc0, 0x03, 0x03, 0x9f, 
0xe3, 0xff, 0x00, 0x1f, 0xc7, 0xac, 0xdf, 0xfe, 0x9f, 0xbb, 0xfd, 0xfe, 0x77, 0x7f, 0xfb, 0xfe, 
0xc0, 0x03, 0x1f, 0xdf, 0xef, 0xfe, 0x00, 0x0f, 0xcf, 0x08, 0xdf, 0xfe, 0x3f, 0xbb, 0xff, 0xfe, 
0x77, 0xff, 0xfb, 0xfe, 0xc0, 0x03, 0x13, 0xff, 0xff, 0xff, 0x01, 0xff, 0x9f, 0x98, 0xdf, 0xfe, 
0x3f, 0xfa, 0xfd, 0x80, 0x77, 0x7f, 0xfb, 0xfe, 0xc0, 0x03, 0x1d, 0xff, 0xff, 0xfb, 0xff, 0xff, 
0xfe, 0x9a, 0xdf, 0xfe, 0x1f, 0xba, 0x67, 0x80, 0x77, 0xff, 0xf9, 0xf6, 0xc0, 0x03, 0x0f, 0xff, 
0xff, 0xf0, 0xff, 0xff, 0xff, 0xfe, 0xdf, 0xfe, 0x00, 0x7a, 0x01, 0x80, 0x66, 0x00, 0x18, 0x00, 
0xc0, 0x07, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x30, 0x01, 0x80, 
0x76, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 
0x00, 0x00, 0x00, 0x80, 0x76, 0x00, 0x10, 0x00, 0x80, 0x06, 0x00, 0x17, 0xff, 0x80, 0xff, 0xff, 
0xd0, 0x00, 0xc0, 0x02, 0x00, 0x10, 0x00, 0x80, 0x77, 0x04, 0x38, 0x00, 0x80, 0x07, 0x00, 0x3b, 
0xff, 0x07, 0xff, 0xff, 0xb8, 0x00, 0xc0, 0x02, 0x00, 0x38, 0x01, 0x80, 0x77, 0xff, 0xfb, 0xfe, 
0xaf, 0xff, 0x7f, 0xfd, 0xfe, 0x07, 0xff, 0xff, 0x7b, 0xfe, 0xcf, 0xf2, 0x7f, 0xbb, 0xfd, 0x80, 
0x77, 0xff, 0xfd, 0xfe, 0x8f, 0xff, 0x7f, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xfb, 0xfa, 0xdf, 0xfa, 
0x7f, 0xfb, 0xff, 0x80, 0x57, 0xff, 0xff, 0xfe, 0x8f, 0xff, 0x7f, 0xfb, 0xff, 0xff, 0xff, 0xff, 
0xfb, 0xfa, 0xcf, 0xfa, 0x3e, 0xfb, 0xfd, 0x80, 0x03, 0x7f, 0xff, 0xfe, 0x8f, 0xff, 0x7f, 0xff, 
0xfe, 0x7f, 0xfe, 0xff, 0xfb, 0xfa, 0xdf, 0xfa, 0x7f, 0xfd, 0xff, 0x80, 0x03, 0x5f, 0xef, 0xfe, 
0xaf, 0xff, 0x7f, 0xfb, 0xfe, 0x5f, 0xf2, 0xff, 0xfb, 0xfa, 0xdf, 0xfa, 0xff, 0xee, 0xff, 0x80, 
0x03, 0x0f, 0xf7, 0xfe, 0xaf, 0xff, 0x7f, 0xfb, 0xfc, 0x5f, 0xe2, 0xff, 0xfb, 0xfa, 0xdf, 0xf2, 
0x7f, 0xf7, 0x3f, 0x80, 0x03, 0x4f, 0xed, 0xee, 0xaf, 0xff, 0xff, 0xff, 0xfe, 0x5f, 0xe2, 0xff, 
0xfb, 0xfa, 0xdf, 0xf2, 0x4f, 0xcf, 0xef, 0x80, 0x03, 0xdf, 0xfb, 0xfe, 0xaf, 0xff, 0xff, 0xff, 
0xfe, 0x5f, 0xf2, 0xff, 0xfb, 0xfe, 0xdf, 0xfa, 0x3f, 0xb7, 0xcd, 0x80, 0x03, 0xdf, 0x75, 0xf6, 
0xaf, 0xff, 0x7f, 0xff, 0xfe, 0x5f, 0xf2, 0xff, 0xfb, 0xfe, 0xdf, 0xfa, 0x7f, 0xdb, 0xe5, 0x80, 
0x03, 0x5e, 0xea, 0xfa, 0xaf, 0xff, 0x7f, 0xff, 0xfe, 0x4f, 0xf2, 0xfe, 0xfb, 0xfa, 0xdf, 0xf2, 
0x7f, 0xae, 0xf1, 0x80, 0x03, 0xfd, 0x55, 0xfe, 0xbf, 0xff, 0xff, 0xff, 0xfe, 0x5f, 0xfa, 0xff, 
0xff, 0xff, 0xff, 0xfa, 0xff, 0x57, 0x7f, 0x80, 0x03, 0xfa, 0xea, 0xbf, 0xbf, 0xff, 0xff, 0xff, 
0xff, 0x7f, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xae, 0xbf, 0xc0, 0x03, 0xfd, 0xf5, 0x5f, 
0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xd7, 0x5f, 0xfe, 
0x03, 0xfa, 0xfa, 0xfa, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 
0xff, 0xbf, 0xbf, 0xfe, 0x07, 0xfd, 0x75, 0xf2, 0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf2, 0x3f, 0x57, 0x5f, 0xfe, 0x47, 0xba, 0xaa, 0xe0, 0xaf, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xf2, 0x1f, 0xaa, 0xaf, 0xfe, 0x57, 0x55, 0x55, 0xe2, 
0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xf2, 0x0f, 0x57, 0x55, 0xfe, 
0x76, 0xaa, 0xab, 0xce, 0xa7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xdf, 0xff, 0xf2, 
0x5f, 0xaa, 0xaa, 0xfe, 0x77, 0x55, 0x57, 0x0e, 0xa7, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 
0xfd, 0xdf, 0xff, 0xe2, 0x7b, 0xd5, 0x55, 0xfe, 0x76, 0xaa, 0xae, 0x4e, 0xaf, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfd, 0xdf, 0xff, 0xf2, 0x79, 0xea, 0xaa, 0xfe, 0x67, 0xd4, 0xdc, 0x3e, 
0x8f, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xfd, 0xdf, 0xff, 0xf2, 0x3c, 0xf5, 0xd5, 0x80, 
0x67, 0xeb, 0x78, 0x7e, 0xaf, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xfd, 0xdf, 0xff, 0xf2, 
0x3f, 0xfb, 0x2b, 0x80, 0x77, 0xbe, 0xf9, 0xfe, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe2, 0x07, 0xbf, 0xf7, 0x80, 0x07, 0x7d, 0xfb, 0xfe, 0xbf, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe2, 0x00, 0x3f, 0x5d, 0x80, 0x07, 0xbb, 0xfb, 0xfe, 
0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0xff, 0xff, 0xbf, 0x80, 
0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0x01, 0xf8, 0x07, 0xe0, 0x3f, 0x01, 
0xf8, 0x07, 0xe0, 0x3f, 0x01, 0xf8, 0x0f, 0xc0, 0x3f, 0x01, 0xf8, 0x00, 0x00, 0x37, 0x00, 0xf8, 
0x05, 0xe0, 0x2f, 0x01, 0xf8, 0x07, 0xc0, 0x2f, 0x01, 0x38, 0x07, 0xc0, 0x37, 0x01, 0xb8, 0x00, 
0xe0, 0x21, 0x00, 0x18, 0x04, 0x60, 0x23, 0x01, 0x08, 0x03, 0x80, 0x23, 0x01, 0x18, 0x04, 0x40, 
0x22, 0x00, 0x18, 0x0e, 0xe0, 0x33, 0x00, 0x98, 0x04, 0xe0, 0x27, 0x01, 0xb8, 0x03, 0x80, 0x23, 
0x01, 0x18, 0x04, 0xc0, 0x26, 0x01, 0x38, 0x0e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xc0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06
};
//noDelay resetTimer (3000);
	
const byte SCREENWIDTH = 160;
const byte SCREENHEIGHT = 128;
void setup(){
  myScreen.init();
  myScreen.setRotation(1);
  myScreen.fillScreen(TFT_BLACK);
  myScreen.drawXBitmap(0 ,0, Testcard_F, 160, 128, TFT_WHITE);
  delay(5000);
}
void loop() {
//below flickers massively when redrawing the background image. Kinda cool but also awful
//draws a bar of static moving down the screen
  for (byte i = 0; i < SCREENHEIGHT; i += 2){		
//		myScreen.fillScreen(TFT_BLACK);
    for (byte y = i; y < (i + 10); y +=2){
      for (byte j = 0; j < SCREENWIDTH; j += 2){
				byte pixel = random(0, 10);
				if (pixel <= 5){
					myScreen.fillRect(j, y, 2, 2, TFT_WHITE);
				}
				else {
					myScreen.fillRect(j, y, 2, 2, TFT_BLACK);
				}
			}
			delay(1);
		}
		myScreen.fillRect(0, i, SCREENWIDTH, 2, TFT_BLACK);
    myScreen.drawXBitmap(0 ,0, Testcard_F, 160, 128, TFT_WHITE);
		delay(2);
//		delay(1);
	}
}
