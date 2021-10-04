//�w�b�_�t�@�C���ǂݍ���
#include "game.h"
#include "data.h"
#include "shape.h"	//�}�`����

//�O���[�o���ϐ�
CHARA_DATA enemy[ENEMY_MAX];	//�G�f�[�^

SCORE_DATA score_data;			//�X�R�A�f�[�^
SCORE_DATA score_dataInit = { SCORE_DATA_PATH,"NAME1",-1,"NAME2",-1,"NAME3",-1 };	//�X�R�A�f�[�^�i�������p�j
SCORE_DATA score_dataInit2 = { SCORE_DATA_PATH2,"NAME1",-1,"NAME2",-1,"NAME3",-1 };	//�X�R�A�f�[�^�i�������p�j


//    �֐�

/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
/// <param name="path">CSV�t�@�C���̃p�X</param>
/// <param name="chara">�L�����f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="DataMax">CSV�t�@�C���̍ő吔</param>
/// <param name="IsHeader">CSV�t�@�C���̈�s�ڂ��w�b�_�Ȃ�</param>
/// <returns>TRUE���ǂݍ��߂��@�@FALSE�����s</returns>
BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader = FALSE)
{
	FILE* fp;					//�t�@�C���|�C���^
	char GetChar = '\0';		//�������镶��
	int LoopCnt = 0;			//���[�v�J�E���^
	errno_t FileErr = NULL;		//�t�@�C���ǂݍ��݃G���[���m�F
	int IsEOF = NULL;			//�t�@�C���̏I��肩�m�F�i�G���h�I�u�t�@�C���j

	FileErr = fopen_s(&fp, path, "r");		//�t�@�C���ǂݍ��݃��[�h�ir�j�ŊJ���ifopen�j�@�@r�ŊJ���ƂȂ��Ƃ��ɃG���[���Ԃ�
	if (FileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//�ȉ��@����ɓǂݍ��߂��ꍇ�̏���

	//CSV�̈�s�ڂ��w�b�_�̏ꍇ
	if (IsHeader == TRUE)
	{
		//�ꕶ�������o���A���s���q���g�Ɉ�s�ڂ�ǂݔ�΂��@��s�ڂ̓f�[�^�ł͂Ȃ��̂ŉ��s�܂�
		while (GetChar != '\n') { GetChar = fgetc(fp); }
	}

	//���ۂɃf�[�^���i�[
	while (IsEOF != EOF)	//
	{
		IsEOF = fscanf_s(
			fp,
			CSV_CHARA_FORMAT,						//�ȉ��̒l�����Ă���
			&(chara + LoopCnt)->No,					//chara[LoopCnt]->No
			&(chara + LoopCnt)->Name[0], STR_MAX,
			&(chara + LoopCnt)->HP,
			&(chara + LoopCnt)->ATK,
			&(chara + LoopCnt)->DEF,
			&(chara + LoopCnt)->MAX_HP,
			&(chara + LoopCnt)->MAX_ATK,
			&(chara + LoopCnt)->MAX_DEF,
			&(chara + LoopCnt)->Lv
			//chara[LoopCnt].No�̗l�ȕ�
		);

		//���̃f�[�^��
		LoopCnt++;
	}

	//�f�[�^�̐����Ⴄ�Ƃ�
	if (LoopCnt - 1 != DataMax)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_DATANUM_ERR_TITLE, MB_OK);
		return FALSE;
	}

	fclose(fp);	//�t�@�C�������

	return TRUE;
}
/// <summary>
/// �X�R�A�f�[�^��ǂݍ���(SCORE_DATA)
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
/// <param name="score">�X�R�A�f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="IsHeader">CSV�t�@�C���̈�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE���ǂݍ��߂��@�@FALSE�����s</returns>
BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader = FALSE)
{
	FILE* fp;				//�t�@�C���|�C���^
	char GetChar = '\0';	//�������镶��
	errno_t FileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	int IsEOF = NULL;		//�t�@�C���I��肩�`�F�b�N

	//�p�X���R�s�[
	SetScoreDataPath(path);

	FileErr = fopen_s(&fp, path, "r");	//�t�@�C���ǂݍ��݃��[�h�i���j�ŊJ���@�@r�ŊJ���ƂȂ��Ƃ��ɃG���[���Ԃ�
	if (FileErr != NULL)
	{
		//�X�R�A�f�[�^�쐬
		if (CreateScoreData() == FALSE) { return FALSE; }

		//�����܂łŃX�R�A�f�[�^�쐬

		FileErr = fopen_s(&fp, path, "r");	//�t�@�C���ǂݍ��݃��[�h�i���j�ŊJ���@�@r�ŊJ���ƂȂ��Ƃ��ɃG���[���Ԃ�
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), path, SCORE_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
			return FALSE;
		}
	}

	//�����ȍ~����ɓǂݍ��߂��ꍇ�̏���

	//CSV�̈�s�ڂ��w�b�_�̂Ƃ�
	if (IsHeader == TRUE)
	{
		//�ꕶ�������o���A���s�œǂݔ�΂�
		while (GetChar != '\n') { GetChar = fgetc(fp); }
	}

	//���ۂɃf�[�^���i�[
	while (IsEOF != EOF)	//End Of File(�t�@�C���̍Ō�)�łȂ��Ƃ�
	{
		//CSV�̈�s����ǂݎ��
		IsEOF = fscanf_s(
			fp,
			SCORE_DATA_FORMAT,
			&(score)->Name1, STR_MAX,	//�������ǂݍ��ޏꍇ�́A���̈����ŕ�����ő吔���w��
			&(score)->Score1,
			&(score)->Name2, STR_MAX,	//�������ǂݍ��ޏꍇ�́A���̈����ŕ�����ő吔���w��
			&(score)->Score2,
			&(score)->Name3, STR_MAX,	//�������ǂݍ��ޏꍇ�́A���̈����ŕ�����ő吔���w��
			&(score)->Score3
		);
	}
	fclose(fp);

	return TRUE;
}


/// <summary>
/// �X�R�A�f�[�^�쐬
/// </summary>
/// <returns></returns>
BOOL CreateScoreData(VOID)
{
	//�Ȃ���΃X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;		//�t�@�C���ǂݍ��݃G���[�̊m�F
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");	//�t�@�C�����������݃��[�h(��)�ŊJ��(�쐬)�@�Ȃ��Ƃ��͐V�K�쐬
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n");

	//��̃X�R�A�f�[�^����������
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_dataInit.Name1, score_dataInit.Score1,
		score_dataInit.Name2, score_dataInit.Score2,
		score_dataInit.Name3, score_dataInit.Score3);

	fclose(creFp);	//�X�R�A�f�[�^�����

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^��ۑ�
/// </summary>
/// <returns></returns>
BOOL SaveScoreData(VOID)
{
	//�Ȃ���΃X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");		//�t�@�C�����������݃��[�h(��)�ŊJ��(�쐬)�@�Ȃ��Ƃ��͐V�K�쐬

	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n");

	//�X�R�A�f�[�^����������
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_dataInit.Name1, score_dataInit.Score1,
		score_dataInit.Name2, score_dataInit.Score2,
		score_dataInit.Name3, score_dataInit.Score3);

	fclose(creFp);	//�X�R�A�f�[�^�����

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_SAVE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^���폜
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
BOOL DeleteScoreData(VOID)
{
	//�t�@�C���폜
	if (remove(GetScoreDataPath()) != 0)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_ERR_TITLE, MB_OK);
	}
	else {
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_TITLE, MB_OK);
	}

	//�X�R�A�f�[�^���쐬
	return CreateScoreData();
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��Ԃ�
/// </summary>
/// <returns></returns>
const char* GetScoreDataPath(VOID)
{

	return score_data.path;
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��ݒ肷��
/// </summary>
/// <returns></returns>
void SetScoreDataPath(const char* path)	//��������󂯎��ꍇ�Aconst char*(�|�C���^)�Ŏ󂯂Ƃ�
{
	strcpyDx(score_data.path, path);
	return;
}

/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
/// <param name="ImgPath">�}�b�v�`�b�v�̉摜�t�@�C���̃p�X</param>
/// <param name="ShitaPath"></param>
/// <param name="NakaAtariPath"></param>
/// <param name="UePath"></param>
/// <param name="map"></param>
/// <param name="divYoko"></param>
/// <param name="divTate"></param>
/// <returns></returns>
BOOL LoadCSVMap(const char* ImgPath, const char* ShitaPath, const char* NakaPath, const char* NakaAtariPath,
	const char* UePath, MAP_DATA* map, int divYoko, int divTate) {
	//�}�b�v�`�b�v�ǂݍ���
		{
			int IsLoad = -1;	//�摜��ǂݍ��߂���

			//�ꎞ�I�ɉ摜�̃n���h����p�ӂ���
			int TempHandle = LoadGraph(ImgPath);


			//�ǂݍ��݃G���[
			if (TempHandle == -1)
			{
				MessageBox(
					GetMainWindowHandle(),
					ImgPath,
					"�摜�ǂݍ��݃G���[",
					MB_OK
				);
				return FALSE;
			}

			//�摜�̕��ƍ���
			int width = -1;
			int height = -1;
			GetGraphSize(TempHandle, &width, &height);

			//�������ēǂ݂���
			IsLoad = LoadDivGraph(
				ImgPath,					//�摜�̃p�X
				divYoko * divTate,			//��������
				divYoko, divTate,			//���̕���,�c�̕���
				width / divYoko, height / divTate,	//�摜����̕��A����
				map->handle					//�A���ŊǗ�����z��̐擪�A�h���X
			);

			//�����G���[
			if (IsLoad == -1)
			{
				MessageBox(
					GetMainWindowHandle(),
					ImgPath,
					"�摜�����G���[",
					MB_OK
				);

				return FALSE;	//�ǂݍ��ݎ��s
			}

			//����ݒ�
			map->DivMax = divYoko * divTate;
			GetGraphSize(map->handle[0], &map->width, &map->height);

			//�摜��`��
			map->IsDraw = TRUE;

			//�ꎞ�I�ɓǂ݂��񂾃n���h�����J��
			DeleteGraph(TempHandle);
		}

		FILE* fp;
		char GetChar = '\0';
		int LoopCnt = 0;
		errno_t FileErr = NULL;
		int IsEOF = NULL;

		//��CSV��ǂݎ��
		{
			FileErr = fopen_s(&fp, ShitaPath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), ShitaPath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//�ȉ�����ɓǂݍ��񂾏ꍇ�̏���

			//���ۂɃf�[�^���i�[
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//�t�@�C���̍Ō�܂ŌJ��Ԃ�
			{
				//�t�@�C�����琔�l����ǂݍ��݁A�z��Ɋi�[
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]��
				//�Ⴆ��[3][3]�̔z��̎��ALoopCnt���T�ł����
				//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A�ꎟ���z��̈ʒu��񎟌��z��Ƃ��ĕϊ��ł���
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//�f�[�^��[XX,]�ŏ�����Ă��邱�Ƃ��|�C���g
					&map->CSV_shita[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//���̃f�[�^��
				LoopCnt++;
			}
			fclose(fp);
		}

		//��CSV��ǂݎ��
		{
			FileErr = fopen_s(&fp, NakaPath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), NakaPath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//�ȉ�����ɓǂݍ��񂾏ꍇ�̏���

			//���ۂɃf�[�^���i�[
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//�t�@�C���̍Ō�܂ŌJ��Ԃ�
			{
				//�t�@�C�����琔�l����ǂݍ��݁A�z��Ɋi�[
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]��
				//�Ⴆ��[3][3]�̔z��̎��ALoopCnt���T�ł����
				//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A�ꎟ���z��̈ʒu��񎟌��z��Ƃ��ĕϊ��ł���
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//�f�[�^��[XX,]�ŏ�����Ă��邱�Ƃ��|�C���g
					&map->CSV_naka[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//���̃f�[�^��
				LoopCnt++;
			}
			fclose(fp);
		}

		//��������CSV��ǂݎ��
		{
			FileErr = fopen_s(&fp, NakaAtariPath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), NakaAtariPath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//�ȉ�����ɓǂݍ��񂾏ꍇ�̏���

			//���ۂɃf�[�^���i�[
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//�t�@�C���̍Ō�܂ŌJ��Ԃ�
			{
				//�t�@�C�����琔�l����ǂݍ��݁A�z��Ɋi�[
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]��
				//�Ⴆ��[3][3]�̔z��̎��ALoopCnt���T�ł����
				//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A�ꎟ���z��̈ʒu��񎟌��z��Ƃ��ĕϊ��ł���
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//�f�[�^��[XX,]�ŏ�����Ă��邱�Ƃ��|�C���g
					&map->CSV_naka_atari[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//���̃f�[�^��
				LoopCnt++;
			}
			fclose(fp);
		}

		//��CSV��ǂݎ��
		{
			FileErr = fopen_s(&fp, UePath, "r");
			if (FileErr != NULL)
			{
				MessageBox(GetMainWindowHandle(), UePath, CSV_LOAD_ERR_TITLE, MB_OK);
				return FALSE;
			}

			//�ȉ�����ɓǂݍ��񂾏ꍇ�̏���

			//���ۂɃf�[�^���i�[
			IsEOF = NULL; LoopCnt = 0;
			while (IsEOF != EOF)	//�t�@�C���̍Ō�܂ŌJ��Ԃ�
			{
				//�t�@�C�����琔�l����ǂݍ��݁A�z��Ɋi�[
				//[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]��
				//�Ⴆ��[3][3]�̔z��̎��ALoopCnt���T�ł����
				//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A�ꎟ���z��̈ʒu��񎟌��z��Ƃ��ĕϊ��ł���
				IsEOF = fscanf_s(
					fp,
					CSV_MAP_FORMAT,	//�f�[�^��[XX,]�ŏ�����Ă��邱�Ƃ��|�C���g
					&map->CSV_ue[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
				);
				//���̃f�[�^��
				LoopCnt++;
			}
			fclose(fp);
		}

		//�}�b�v�̓����蔻����쐬
		{
			for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
			{
				for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
				{
					//�Ƃ���Ȃ�ID�̏ꍇ
					if (map->CSV_naka_atari[tate][yoko] == MAP_STOP_ID)
					{
						//�����蔻����쐬
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

					//�}�b�v�̏ꏊ���w��
					map->x[tate][yoko] = (yoko + 0) * map->width;
					map->y[tate][yoko] = (tate + 0) * map->height;

				}
			}
		}

		return TRUE;
}

/// <summary>
/// �}�b�v�`��
/// </summary>
/// <param name="map">�}�b�v�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawMap(MAP_DATA map)
{
	//�摜��`��ł���Ƃ�
	if (map.IsDraw == TRUE)
	{
		//�����C��
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko],
					map.y[tate][yoko],
					map.handle[map.CSV_shita[tate][yoko]], TRUE);
			}
		}

		//�����C��
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko],
					map.y[tate][yoko],
					map.handle[map.CSV_naka[tate][yoko]], TRUE);
			}
		}

		//�����Ƀv���C���[�̉摜��`��
		DrawDivImageChara(&samplePlayerImg);

		//�ヌ�C��
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

	//�f�o�b�N���[�h����
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
	//�����蔻��`�F�b�N
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