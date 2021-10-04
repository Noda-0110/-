//ヘッダファイル読み込み
#include "game.h"
#include "data.h"
#include "shape.h"	//図形処理

//グローバル変数
CHARA_DATA enemy[ENEMY_MAX];	//敵データ

SCORE_DATA score_data;			//スコアデータ
SCORE_DATA score_dataInit = { SCORE_DATA_PATH,"NAME1",-1,"NAME2",-1,"NAME3",-1 };	//スコアデータ（初期化用）
SCORE_DATA score_dataInit2 = { SCORE_DATA_PATH2,"NAME1",-1,"NAME2",-1,"NAME3",-1 };	//スコアデータ（初期化用）


//    関数

/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <param name="path">CSVファイルのパス</param>
/// <param name="chara">キャラデータ構造体の先頭アドレス</param>
/// <param name="DataMax">CSVファイルの最大数</param>
/// <param name="IsHeader">CSVファイルの一行目がヘッダなら</param>
/// <returns>TRUE＝読み込めた　　FALSE＝失敗</returns>
BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader = FALSE)
{
	FILE* fp;					//ファイルポインタ
	char GetChar = '\0';		//所得する文字
	int LoopCnt = 0;			//ループカウンタ
	errno_t FileErr = NULL;		//ファイル読み込みエラーを確認
	int IsEOF = NULL;			//ファイルの終わりか確認（エンドオブファイル）

	FileErr = fopen_s(&fp, path, "r");		//ファイル読み込みモード（r）で開く（fopen）　　rで開くとないときにエラーが返る
	if (FileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
		return FALSE;
	}

	//以下　正常に読み込めた場合の処理

	//CSVの一行目がヘッダの場合
	if (IsHeader == TRUE)
	{
		//一文字ずつ取り出し、改行をヒントに一行目を読み飛ばす　一行目はデータではないので改行まで
		while (GetChar != '\n') { GetChar = fgetc(fp); }
	}

	//実際にデータを格納
	while (IsEOF != EOF)	//
	{
		IsEOF = fscanf_s(
			fp,
			CSV_CHARA_FORMAT,						//以下の値を入れていく
			&(chara + LoopCnt)->No,					//chara[LoopCnt]->No
			&(chara + LoopCnt)->Name[0], STR_MAX,
			&(chara + LoopCnt)->HP,
			&(chara + LoopCnt)->ATK,
			&(chara + LoopCnt)->DEF,
			&(chara + LoopCnt)->MAX_HP,
			&(chara + LoopCnt)->MAX_ATK,
			&(chara + LoopCnt)->MAX_DEF,
			&(chara + LoopCnt)->Lv
			//chara[LoopCnt].Noの様な物
		);

		//次のデータへ
		LoopCnt++;
	}

	//データの数が違うとき
	if (LoopCnt - 1 != DataMax)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_DATANUM_ERR_TITLE, MB_OK);
		return FALSE;
	}

	fclose(fp);	//ファイルを閉じる

	return TRUE;
}
/// <summary>
/// スコアデータを読み込む(SCORE_DATA)
/// </summary>
/// <param name="path">スコアデータのパス</param>
/// <param name="score">スコアデータ構造体の先頭アドレス</param>
/// <param name="IsHeader">CSVファイルの一行目がヘッダならTRUE</param>
/// <returns>TRUE＝読み込めた　　FALSE＝失敗</returns>
BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader = FALSE)
{
	FILE* fp;				//ファイルポインタ
	char GetChar = '\0';	//所得する文字
	errno_t FileErr = NULL;	//ファイル読み込みエラーを確認
	int IsEOF = NULL;		//ファイル終わりかチェック

	//パスをコピー
	SetScoreDataPath(path);

	FileErr = fopen_s(&fp, path, "r");	//ファイル読み込みモード（ｒ）で開く　　rで開くとないときにエラーが返る
	if (FileErr != NULL)
	{
		//スコアデータ作成
		if (CreateScoreData() == FALSE) { return FALSE; }

		//ここまででスコアデータ作成

		FileErr = fopen_s(&fp, path, "r");	//ファイル読み込みモード（ｒ）で開く　　rで開くとないときにエラーが返る
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), path, SCORE_LOAD_ERR_TITLE, MB_OK);	//読み込みエラー
			return FALSE;
		}
	}

	//ここ以降正常に読み込めた場合の処理

	//CSVの一行目がヘッダのとき
	if (IsHeader == TRUE)
	{
		//一文字ずつ取り出す、改行で読み飛ばす
		while (GetChar != '\n') { GetChar = fgetc(fp); }
	}

	//実際にデータを格納
	while (IsEOF != EOF)	//End Of File(ファイルの最後)でないとき
	{
		//CSVの一行分を読み取る
		IsEOF = fscanf_s(
			fp,
			SCORE_DATA_FORMAT,
			&(score)->Name1, STR_MAX,	//文字列を読み込む場合は、次の引数で文字列最大数を指定
			&(score)->Score1,
			&(score)->Name2, STR_MAX,	//文字列を読み込む場合は、次の引数で文字列最大数を指定
			&(score)->Score2,
			&(score)->Name3, STR_MAX,	//文字列を読み込む場合は、次の引数で文字列最大数を指定
			&(score)->Score3
		);
	}
	fclose(fp);

	return TRUE;
}


/// <summary>
/// スコアデータ作成
/// </summary>
/// <returns></returns>
BOOL CreateScoreData(VOID)
{
	//なければスコアデータを作る
	FILE* creFp;
	errno_t creFileErr = NULL;		//ファイル読み込みエラーの確認
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");	//ファイルを書き込みモード(ｗ)で開く(作成)　ないときは新規作成
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ヘッダを書き込み
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n");

	//空のスコアデータを書き込み
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_dataInit.Name1, score_dataInit.Score1,
		score_dataInit.Name2, score_dataInit.Score2,
		score_dataInit.Name3, score_dataInit.Score3);

	fclose(creFp);	//スコアデータを閉じる

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// スコアデータを保存
/// </summary>
/// <returns></returns>
BOOL SaveScoreData(VOID)
{
	//なければスコアデータを作る
	FILE* creFp;
	errno_t creFileErr = NULL;	//ファイル読み込みエラーを確認
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");		//ファイルを書き込みモード(ｗ)で開く(作成)　ないときは新規作成

	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//ヘッダを書き込み
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n");

	//スコアデータを書き込み
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_dataInit.Name1, score_dataInit.Score1,
		score_dataInit.Name2, score_dataInit.Score2,
		score_dataInit.Name3, score_dataInit.Score3);

	fclose(creFp);	//スコアデータを閉じる

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_SAVE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// スコアデータを削除
/// </summary>
/// <param name="path">スコアデータのパス</param>
BOOL DeleteScoreData(VOID)
{
	//ファイル削除
	if (remove(GetScoreDataPath()) != 0)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_ERR_TITLE, MB_OK);
	}
	else {
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_TITLE, MB_OK);
	}

	//スコアデータを作成
	return CreateScoreData();
}

/// <summary>
/// スコアデータのパスを返す
/// </summary>
/// <returns></returns>
const char* GetScoreDataPath(VOID)
{

	return score_data.path;
}

/// <summary>
/// スコアデータのパスを設定する
/// </summary>
/// <returns></returns>
void SetScoreDataPath(const char* path)	//文字列を受け取る場合、const char*(ポインタ)で受けとる
{
	strcpyDx(score_data.path, path);
	return;
}

/// <summary>
/// CSVファイルを読み込む
/// </summary>
/// <param name="ImgPath">マップチップの画像ファイルのパス</param>
/// <param name="ShitaPath"></param>
/// <param name="NakaAtariPath"></param>
/// <param name="UePath"></param>
/// <param name="map"></param>
/// <param name="divYoko"></param>
/// <param name="divTate"></param>
/// <returns></returns>
BOOL LoadCSVMap(const char* ImgPath, const char* ShitaPath, const char* NakaPath, const char* NakaAtariPath,
	const char* UePath, MAP_DATA* map, int divYoko, int divTate) {
	//マップチップ読み込み
		{
			int IsLoad = -1;	//画像を読み込めたか

			//一時的に画像のハンドルを用意する
			int TempHandle = LoadGraph(ImgPath);


			//読み込みエラー
			if (TempHandle == -1)
			{
				MessageBox(
					GetMainWindowHandle(),
					ImgPath,
					"画像読み込みエラー",
					MB_OK
				);
				return FALSE;
			}

			//画像の幅と高さ
			int width = -1;
			int height = -1;
			GetGraphSize(TempHandle, &width, &height);

			//分割して読みこみ
			IsLoad = LoadDivGraph(
				ImgPath,					//画像のパス
				divYoko * divTate,			//分割総数
				divYoko, divTate,			//横の分割,縦の分割
				width / divYoko, height / divTate,	//画像一つ分の幅、高さ
				map->handle					//連続で管理する配列の先頭アドレス
			);

			//分割エラー
			if (IsLoad == -1)
			{
				MessageBox(
					GetMainWindowHandle(),
					ImgPath,
					"画像分割エラー",
					MB_OK
				);

				return FALSE;	//読み込み失敗
			}

			//情報を設定
			map->DivMax = divYoko * divTate;
			GetGraphSize(map->handle[0], &map->width, &map->height);

			//画像を描画
			map->IsDraw = TRUE;

			//一時的に読みこんだハンドルを開放
			DeleteGraph(TempHandle);
		}

		FILE* fp;
		char GetChar = '\0';
		int LoopCnt = 0;
		errno_t FileErr = NULL;
		int IsEOF = NULL;

		//下CSVを読み取り
		{
			FileErr = fopen_s(&fp, ShitaPath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), ShitaPath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//以下正常に読み込んだ場合の処理

			//実際にデータを格納
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//ファイルの最後まで繰り返す
			{
				//ファイルから数値を一つ読み込み、配列に格納
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]は
				//例えば[3][3]の配列の時、LoopCntが５であれば
				//[5 / 3 = 1][5 % 3 = 2]となり、一次元配列の位置を二次元配列として変換できる
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//データが[XX,]で書かれていることがポイント
					&map->CSV_shita[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//次のデータへ
				LoopCnt++;
			}
			fclose(fp);
		}

		//中CSVを読み取り
		{
			FileErr = fopen_s(&fp, NakaPath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), NakaPath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//以下正常に読み込んだ場合の処理

			//実際にデータを格納
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//ファイルの最後まで繰り返す
			{
				//ファイルから数値を一つ読み込み、配列に格納
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]は
				//例えば[3][3]の配列の時、LoopCntが５であれば
				//[5 / 3 = 1][5 % 3 = 2]となり、一次元配列の位置を二次元配列として変換できる
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//データが[XX,]で書かれていることがポイント
					&map->CSV_naka[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//次のデータへ
				LoopCnt++;
			}
			fclose(fp);
		}

		//中あたりCSVを読み取り
		{
			FileErr = fopen_s(&fp, NakaAtariPath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), NakaAtariPath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//以下正常に読み込んだ場合の処理

			//実際にデータを格納
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//ファイルの最後まで繰り返す
			{
				//ファイルから数値を一つ読み込み、配列に格納
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]は
				//例えば[3][3]の配列の時、LoopCntが５であれば
				//[5 / 3 = 1][5 % 3 = 2]となり、一次元配列の位置を二次元配列として変換できる
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//データが[XX,]で書かれていることがポイント
					&map->CSV_naka_atari[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//次のデータへ
				LoopCnt++;
			}
			fclose(fp);
		}

		//上CSVを読み取り
		{
			FileErr = fopen_s(&fp, UePath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), UePath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//以下正常に読み込んだ場合の処理

			//実際にデータを格納
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//ファイルの最後まで繰り返す
			{
				//ファイルから数値を一つ読み込み、配列に格納
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]は
				//例えば[3][3]の配列の時、LoopCntが５であれば
				//[5 / 3 = 1][5 % 3 = 2]となり、一次元配列の位置を二次元配列として変換できる
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//データが[XX,]で書かれていることがポイント
					&map->CSV_ue[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//次のデータへ
				LoopCnt++;
			}
			fclose(fp);
		}

		//マップの当たり判定を作成
		{
			for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
				{
					//とおれないIDの場合
					if (map->CSV_naka_atari[tate][yoko] == MAP_STOP_ID)
					{
						//当たり判定を作成
						map->coll[tate][yoko].left = (yoko + 0) * map->width + 1;
						map->coll[tate][yoko].right = (yoko + 1) * map->width - 1;
						map->coll[tate][yoko].top = (tate + 0) * map->height + 1;
						map->coll[tate][yoko].bottom = (tate + 1) * map->height - 1;
					}
					else {
						map->coll[tate][yoko].left = 0;
						map->coll[tate][yoko].right = 0;
						map->coll[tate][yoko].top = 0;
						map->coll[tate][yoko].bottom = 0;
					}

					//マップの場所を指定
					map->x[tate][yoko] = (yoko + 0) * map->width;
					map->y[tate][yoko] = (tate + 0) * map->height;

				}
			}
		}

		return TRUE;
}

/// <summary>
/// マップ描画
/// </summary>
/// <param name="map">マップ構造体</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawMap(MAP_DATA map)
{
	//画像を描画できるとき
	if (map.IsDraw == TRUE)
	{
		//下レイヤ
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko],
					map.y[tate][yoko],
					map.handle[map.CSV_shita[tate][yoko]], TRUE);
			}
		}

		//中レイヤ
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko],
					map.y[tate][yoko],
					map.handle[map.CSV_naka[tate][yoko]], TRUE);
			}
		}

		//ここにプレイヤーの画像を描画
		DrawDivImageChara(&samplePlayerImg);

		//上レイヤ
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko],
					map.y[tate][yoko],
					map.handle[map.CSV_ue[tate][yoko]], TRUE);
			}
		}
	}

	//デバックモード時は
	if (GAME_DEBUG == TRUE)
	{
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawRect(map.coll[tate][yoko], GetColor(255, 255, 255), FALSE);
			}
		}
	}
	return;
}

BOOL CollMap(RECT rect, MAP_DATA map)
{
	//当たり判定チェック
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			if (CheckCollRectToRect(rect, map.coll[tate][yoko]) == TRUE)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}