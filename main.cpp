#include "DxLib.h"

#define WINDOW_WIDETH (1600)
#define WINDOW_HEIGHT (900)

//写真の構造体
struct Pic {
    int p;              //写真ハンドル
    int w;              //写真幅
    int t;              //写真厚み
};

//長方形の構造体定義
struct Ract {
    int x;                                  //x座標
    int y;                                  //y座標
    int w;                                  //幅
    int t;                                  //厚み
    int k;                                  //種類
    double r;                               //回転角度
    Pic p[e_Ani::e_Ani_Total];              //写真
    int a;                                  //アニメーション
    bool d;                                 //向き
    int j;                                  //ジャンプカウンタ
    bool c;                                 //キャラクターか否か（動くか否か）
};

//ブロックタイプを列挙体定義
enum e_Type {
    e_空,
    e_地面,
    e_プレイヤー,
    e_敵,
};

//画像所の状態列挙帯定義
enum e_Ani {
    e_Normal,
    e_Walk1,
    e_Walk2,
    e_Atack,
    e_Death,
    e_Ani_Total,
};

//テキストファイルからブロック情報を読み取るための構造体定義
struct Text {
    int k;                          //種類
    int x;                          //座標
    int y;                          //座標
};

//（２次元配列）
Text** Stage;

//ステージの最大値
int STAGE_TORTAL;
int STAGE_WIDTH;
int STAGE_HEIGHT;

//背景色の構造体定義
struct Color{
    int r;
    int g;
    int b;
};

//背景色定義
Color Col;

//ブロック定義（１次元配列）
Ract* Block;

//ゲーム開始時の処理の関数
void Game_Ini() {
    //テキストからステージの情報を取得
    char name[] = { "StageFile/1-1.txt" };
    FILE* fp = NULL;
    errno_t error = NULL;

    //ステージ情報の取得
    if (error == NULL && fp != NULL) {
        
        //背景色取得
        fscanf_s(fp, "%d\n", &Col.r);
        fscanf_s(fp, "%d\n", &Col.g);
        fscanf_s(fp, "%d\n", &Col.b);
        SetBackgroundColor(Col.r, Col.g, Col.b);

        //ステージの大きさ
        fscanf_s(fp, "%d\n", &STAGE_TORTAL);
        fscanf_s(fp, "%d\n", &STAGE_WIDTH);
        fscanf_s(fp, "%d\n", &STAGE_HEIGHT);

        Stage = new Text * [STAGE_WIDTH];
        for (int i = 0; i < STAGE_WIDTH; i++) {
            Stage[i] = new Text[STAGE_HEIGHT];
        }

        //ブロックのx,y,種類の読み込み
        for (int y = 0; y < STAGE_HEIGHT; y++) {
            for (int x = 0; x < STAGE_WIDTH; x++) {
                
                fscanf_s(fp, "%d", &Stage[x][y].k);
                Stage[x][y].x = x;
                Stage[x][y].y = y;
            }
        }
        fclose(fp);
    }
    //メモリ確保
    Block = new Ract[STAGE_TORTAL];

    //Text型からRact型に変換
    int i = 0;
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            if (Stage[x][y].k == e_Type::e_空) {
                
                //ブロックの初期化
                Block_Ini(&Block[i]);
            }
            else {
                //ブロックの幅と厚みをブロックの種類から判断
            }
        }
    }
}
//ゲーム終了時の処理の関数
void Game_End() {}
//ゲーム計算の処理の関数
void Game_Cal() {}
//ゲームの描画の処理の関数
void Game_Draw() {}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ウィンドウモードに設定
    ChangeWindowMode(TRUE);

    // DXライブラリ初期化処理
    if (DxLib_Init() < 0) {
        //エラーなら終了する
        return -1;
    }

    //描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // 画面モードの変更
    SetGraphMode(WINDOW_WIDETH, WINDOW_HEIGHT, 32);

    SetMainWindowText("テストゲーム");

    Game_Ini();

    // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        Game_Cal();

        DrawFormatString(0, 0, GetColor(255, 255, 255), "ESCキーで終了します");

        if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
            break;
        }

    }

    DxLib_End();    // DXライブラリ終了処理
    return 0;
}