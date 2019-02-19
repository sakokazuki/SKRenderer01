//
//  zTexture.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/16.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "zTexture.hpp"



zTexture::zTexture() {

}

void zTexture::render(GLenum target) {
	glActiveTexture(target);
	glBindTexture(GL_TEXTURE_2D, texture);
}

GLuint zTexture::getID() const {
	return texture;
}


bool zTexture::loadTexture(const char *filename) {

	FILE *fp;
	png_structp pPng = NULL;
	png_infop pInfo = NULL;
	int depth, colorType, interlaceType;
	unsigned int width, height;
	int rowSize, imgSize;
	unsigned int i;
	unsigned char *data;
	GLuint tex;


	//PNGファイルを開く
	fopen_s(&fp, filename, "rb");
	if (!fp) {
		fprintf(stderr, "createTextureFromPNGFile: Failed to fopen.");
		return false;
	}

	//PNGファイルを読み込むための構造体を作成
	pPng = png_create_read_struct(
		PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL
	);
	pInfo = png_create_info_struct(pPng);

	//初期化
	png_init_io(pPng, fp);

	//画像情報を読み込み
	//画像の幅、高さ、ビット深度、色の表現方法、インターレースの情報を取得する
	png_read_info(pPng, pInfo);
	png_get_IHDR(pPng, pInfo,
		&width, &height,
		&depth, &colorType,
		&interlaceType, NULL, NULL
	);

	//RGBとRGBAのみに対応
	if (colorType != PNG_COLOR_TYPE_RGB && colorType != PNG_COLOR_TYPE_RGBA) {
		fprintf(stderr, "createTextureFromPNGFile: Supprted color type are RGB and RGBA.");
		return false;
	}

	//インターレースは非対応
	if (interlaceType != PNG_INTERLACE_NONE) {
		fprintf(stderr, "createTextureFromPNGFile: Interlace image is not supprted.");
		return false;
	}

	//1行のデータサイズと画像の高さから必要なメモリ量を計算して、メモリ確保
	rowSize = (int)png_get_rowbytes(pPng, pInfo);
	//    imgSize = rowSize * height;
	imgSize = width * 4 * height;
	data = (unsigned char *)malloc(imgSize);

	//std::cout << rowSize << ": " << height << "  " << width << std::endl;
	//ピクセルの読み込み
	for (i = 0; i < height; i++) {
		png_read_row(pPng, &data[i * rowSize], NULL);
	}

	png_read_end(pPng, pInfo);

	//OpenGLテクスチャの作成
	glGenTextures(1, &tex);

	//テクスチャを選択
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//テクスチャにPNGファイルから読み込んだピクセルを書き込む
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data
	);

	//後片付け
	free(data);
	png_destroy_info_struct(pPng, &pInfo);
	png_destroy_read_struct(&pPng, NULL, NULL);
	fclose(fp);
	texture = tex;
	return true;

}



