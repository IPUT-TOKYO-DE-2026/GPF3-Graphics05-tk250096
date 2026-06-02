#include "FrameBufferEmulator.h"

int N = 6; 
constexpr int MAX_CNT = 10000; //操作回数の最大許容値 
int b[MAX_CNT] = { 1, 4, 1, 3, 2, 4 }; // 現在のブロックの各列の高さを格納する配列 
int tmp[MAX_CNT]; // 操作の途中、一時的に新しい列の高さを格納するための作業用配列 
int cnt; 
unsigned char rectColor[] = { 0, 200, 0 }; 
unsigned char gridColor[] = { 200, 200, 200 }; 

// 長方形を描画する 
void drawRectangle(unsigned char* buff, int width, int height, int sx, int sy, int w, int h, unsigned char color[3]) 
{
	int ex = sx + w; 
	int ey = sy + h; 
	unsigned char* pixel; 
	for (int i = sy; i < ey; i++) { // 縦方向のループ 
		pixel = buff + i * width * 3 + sx * 3; // フレームバッファ上で1行書き始める位置 
		for (int j = sx; j < ex; j++) { // 横方向のループ 
			*pixel++ = color[0]; // B 
			*pixel++ = color[1]; // G 
			*pixel++ = color[2]; // R 
		} 
	} 
}

// 格子を描画する 
void drawGrids(unsigned char* buff, int width, int height, int w, int h, unsigned char color[3]) 
{ 
	// 横線 
	for (int y = 0; y < height; y += h) { // 縦方向のループ 
		unsigned char* p = buff + (y * width * 3); // 書き込み始める位置を求める（行） 
		for (int x = 0; x < width; x++) { // 横方向のループ 
			*p++ = color[0]; 
			*p++ = color[1]; 
			*p++ = color[2]; 
		} 
	}
	
	// 縦線 
	for (int x = 0; x < width; x += w) { // 横方向のループ 
		for (int y = 0; y < height; y++) { // 縦方向のループ 
			unsigned char* p = buff + ((y * width + x) * 3); // 書き込み始める位置を求める（列） 
			*p++ = color[0]; 
			*p++ = color[1]; 
			*p++ = color[2]; 
		} 
	} 
}

void FrameBufferEmulator::initUser() 
{ 
	cnt = 0; 
}