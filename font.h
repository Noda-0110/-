#pragma once

//フォント処理のヘッダファイル


//ゲームのメインヘッダ
#include "game.h"

//- - - - -マクロ定義- - - - -

//フォント系の定義
#define FONT_JIYU_PATH TEXT(".\\FONT\\Jiyucho.ttf")	//フォントの場所
#define FONT_JIYU_NAME TEXT("じゆうちょうフォント")	//フォントの名前

#define FONT_CAP_PATH TEXT(".\\FONT\\cinecaption227.TTF")	//フォントの場所
#define FONT_CAP_NAME TEXT("しねきゃぷしょん")	//フォントの名前

#define FONT_FF_PATH TEXT(".\\FONT\\ferrum.otf")	//フォントの場所
#define FONT_FF_NAME TEXT("Ferrum")	//フォントの名前

#define FONT_MSGOTH_NAME TEXT("MS ゴシック")		//フォントの名前

#define DEF_FONT_NAME  FONT_JIYU_NAME			//デフォルトのフォントの名前
#define DEF_FONT_SIZE 20						//デフォルトのサイズ
#define DEF_FONT_THINCK 1						//デフォルトの太さ
#define DEF_FONT_TYPE DX_FONTTYPE_ANTIALIASING	//デフォルトのタイプ　ジャギーを防ぐ

//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE		TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE		TEXT("フォント作成エラー")

//フォント構造体
struct FONT
{
	int handle;			//フォントハンドル
	int Size;			//フォントのサイズ
	int Thinck;			//フォントの太さ
	int Type = DX_FONTTYPE_ANTIALIASING;	//フォントのタイプ　ジャギーを防ぐ
	char Name[STR_MAX];	//フォントの名前
};

//フォント関連
extern FONT fontdef;	//デフォルトのフォント

extern FONT sampleFont1;	//サンプルフォント（PCにありそうなやつ）
extern FONT sampleFont2;	//サンプルフォント（フォントファイルから読み込んだやつ

extern FONT capFont1;	//練習で入れたフォント（字幕風）
extern FONT ffFont1;	//練習で入れたフォント（FF風）


extern BOOL FontAdd(VOID);					//フォントの読込
extern BOOL FontCreate(VOID);				//フォント作成
extern VOID SetFont(FONT* f, const char* name, int size, int thinck, int type);	//フォントに設定する
extern BOOL FontCreateHandle(FONT* f);		//フォントハンドルを作成
extern VOID SetDefaultFont(FONT f);			//フォントを全体に反映させる
extern VOID FontDelete(VOID);				//フォント削除
extern VOID FontRemove(VOID);				//フォントの削除