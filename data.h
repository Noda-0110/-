#pragma once

//ヘッダ読み込み
#include "game.h"

//マクロ定義

//エラーメッセージ
#define CSV_LOAD_ERR_TITLE		TEXT("CSV読み込みエラー")
#define CSV_DATANUM_ERR_TITLE	TEXT("CSV数エラー")

//キャラデータパス
#define CSV_PATH_ENEMY			TEXT(".\\Data\\enemy.csv")

//キャラクタの書式指定子 (%[＾,]は文字列、%dは整数,まで読む)
#define CSV_CHARA_FORMAT		TEXT("%d,%[^,],%d,%d,%d,%d,%d,%d,%d")

//敵データ
#define ENEMY_MAX 8

//エラーメッセージ
#define SCORE_CREATE_ERR_TITLE	TEXT("スコアデータ作成エラー")
#define SCORE_LOAD_ERR_TITLE	TEXT("スコアデータ読み込みエラー")
#define SCORE_CREATE_TITLE		TEXT("スコアデータ作成OK")
#define SCORE_SAVE_TITLE		TEXT("スコアデータ保存OK")
#define SCORE_DELETE_TITLE		TEXT("スコアデータ削除OK")
#define SCORE_DELETE_ERR_TITLE	TEXT("スコアデータ削除エラー")

//スコアデータのパス（拡張子を変えることでスコアデータであることを隠す）
#define SCORE_DATA_PATH		TEXT(".\\Data\\score.a")	//ANSI文字コードで保存

#define SCORE_DATA_PATH2	TEXT(".\\Data\\System")	//自作のデータ

//データの書式指定し
#define SCORE_DATA_FORMAT TEXT("%[^,],%d,%[^,],%d,%[^,],%d,") //スコアデータの書式指定子（%[^,]は文字列）


//マップチップの画像ファイル
#define IMG_PATH_MAP1	TEXT(".\\Map\\mapchip.png")

//マップデータのファイルパス
#define CSV_PATH_MAP1_SHITA			TEXT(".\\Map\\map2._shita.csv")
#define CSV_PATH_MAP1_NAKA			TEXT(".\\Map\\map2._naka.csv")
#define CSV_PATH_MAP1_NAKA_ATARI	TEXT(".\\Map\\map2._naka_atari.csv")
#define CSV_PATH_MAP1_UE			TEXT(".\\Map\\map2._ue.csv")

//マップの書式指定子
#define  CSV_MAP_FORMAT			TEXT("%d,")

#define MAP1_YOKO_MAX	20	//マップ横サイズ
#define MAP1_TATE_MAX	20	//マップ縦サイズ

#define MAP1_YOKO_DIV	60	//マップ横分割
#define MAP1_TATE_DIV	60	//マップ縦分割

#define MAP_MOVE_ID		56	//通れるマップのID　　〇
#define MAP_STOP_ID		57	//通れないマップのID  ×
#define MAP_NONE_ID		58	//何もないマップのID　透明

//キャラデータ構造体（サンプル)
struct CHARA_DATA
{
	int No;				//No
	char Name[STR_MAX];	//名前

	//実際に使う値
	int HP;				//HP
	int ATK;			//攻撃力
	int DEF;			//防御力

	int MAX_HP;			//HP
	int MAX_ATK;		//攻撃力
	int MAX_DEF;		//防御力

	int Lv;		//レベル
};

//スコアデータ構造体（サンプル）
struct SCORE_DATA
{
	char path[PATH_MAX];	//パス
	char Name1[STR_MAX];	//名前１
	int Score1;				//スコア１
	char Name2[STR_MAX];	//名前２
	int Score2;				//スコア２
	char Name3[STR_MAX];	//名前３
	int Score3;				//スコア３
};

//マップデータ構造体(サンプル)
struct MAP_DATA
{
	//CSVデータ（分割画像のIDが入る）
	int CSV_shita[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int CSV_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int CSV_naka_atari[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int CSV_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];

	//マップハンドル
	int handle[MAP1_TATE_DIV * MAP1_YOKO_DIV];

	//マップの場所
	int x[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int y[MAP1_TATE_MAX][MAP1_YOKO_MAX];

	int width;
	int height;

	int DivMax;	//分割数　forで回す

	BOOL IsDraw = FALSE;	//描画するか

	//当たり判定
	RECT coll[MAP1_TATE_MAX][MAP1_YOKO_MAX];
};

//外部グローバル変数
extern CHARA_DATA enemy[ENEMY_MAX];	//敵データ（ENEMY_MAX数）
extern SCORE_DATA score_data;		//スコアデータ
extern SCORE_DATA score_dataInit;	//スコアデータ（初期化用）

//プロトタイプ宣言
//extern とは外部にも関数があることを示す
extern BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader);
extern BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader);

extern BOOL CreateScoreData(VOID);
extern BOOL SaveScoreData(VOID);
extern BOOL DeleteScoreData(VOID);
extern const char* GetScoreDataPath(VOID);
extern VOID SetScoreDataPath(const char* path);

extern BOOL LoadCSVMap(
	const char* ImgPath,
	const char* ShitaPath,
	const char* NakaPath,
	const char* NakaAtariPath,
	const char* UePath,
	MAP_DATA* map,
	int divYoko,
	int divTate
);

extern BOOL CollMap(RECT rect, MAP_DATA map);
extern VOID DrawMap(MAP_DATA map);