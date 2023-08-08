#include "DxLib.h"

#define WINDOW_WIDETH (1600)
#define WINDOW_HEIGHT (900)

//�ʐ^�̍\����
struct Pic {
    int p;              //�ʐ^�n���h��
    int w;              //�ʐ^��
    int t;              //�ʐ^����
};

//�����`�̍\���̒�`
struct Ract {
    int x;                                  //x���W
    int y;                                  //y���W
    int w;                                  //��
    int t;                                  //����
    int k;                                  //���
    double r;                               //��]�p�x
    Pic p[e_Ani::e_Ani_Total];              //�ʐ^
    int a;                                  //�A�j���[�V����
    bool d;                                 //����
    int j;                                  //�W�����v�J�E���^
    bool c;                                 //�L�����N�^�[���ۂ��i�������ۂ��j
};

//�u���b�N�^�C�v��񋓑̒�`
enum e_Type {
    e_��,
    e_�n��,
    e_�v���C���[,
    e_�G,
};

//�摜���̏�ԗ񋓑ђ�`
enum e_Ani {
    e_Normal,
    e_Walk1,
    e_Walk2,
    e_Atack,
    e_Death,
    e_Ani_Total,
};

//�e�L�X�g�t�@�C������u���b�N����ǂݎ�邽�߂̍\���̒�`
struct Text {
    int k;                          //���
    int x;                          //���W
    int y;                          //���W
};

//�i�Q�����z��j
Text** Stage;

//�X�e�[�W�̍ő�l
int STAGE_TORTAL;
int STAGE_WIDTH;
int STAGE_HEIGHT;

//�w�i�F�̍\���̒�`
struct Color{
    int r;
    int g;
    int b;
};

//�w�i�F��`
Color Col;

//�u���b�N��`�i�P�����z��j
Ract* Block;

//�Q�[���J�n���̏����̊֐�
void Game_Ini() {
    //�e�L�X�g����X�e�[�W�̏����擾
    char name[] = { "StageFile/1-1.txt" };
    FILE* fp = NULL;
    errno_t error = NULL;

    //�X�e�[�W���̎擾
    if (error == NULL && fp != NULL) {
        
        //�w�i�F�擾
        fscanf_s(fp, "%d\n", &Col.r);
        fscanf_s(fp, "%d\n", &Col.g);
        fscanf_s(fp, "%d\n", &Col.b);
        SetBackgroundColor(Col.r, Col.g, Col.b);

        //�X�e�[�W�̑傫��
        fscanf_s(fp, "%d\n", &STAGE_TORTAL);
        fscanf_s(fp, "%d\n", &STAGE_WIDTH);
        fscanf_s(fp, "%d\n", &STAGE_HEIGHT);

        Stage = new Text * [STAGE_WIDTH];
        for (int i = 0; i < STAGE_WIDTH; i++) {
            Stage[i] = new Text[STAGE_HEIGHT];
        }

        //�u���b�N��x,y,��ނ̓ǂݍ���
        for (int y = 0; y < STAGE_HEIGHT; y++) {
            for (int x = 0; x < STAGE_WIDTH; x++) {
                
                fscanf_s(fp, "%d", &Stage[x][y].k);
                Stage[x][y].x = x;
                Stage[x][y].y = y;
            }
        }
        fclose(fp);
    }
    //�������m��
    Block = new Ract[STAGE_TORTAL];

    //Text�^����Ract�^�ɕϊ�
    int i = 0;
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            if (Stage[x][y].k == e_Type::e_��) {
                
                //�u���b�N�̏�����
                Block_Ini(&Block[i]);
            }
            else {
                //�u���b�N�̕��ƌ��݂��u���b�N�̎�ނ��画�f
            }
        }
    }
}
//�Q�[���I�����̏����̊֐�
void Game_End() {}
//�Q�[���v�Z�̏����̊֐�
void Game_Cal() {}
//�Q�[���̕`��̏����̊֐�
void Game_Draw() {}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // �E�B���h�E���[�h�ɐݒ�
    ChangeWindowMode(TRUE);

    // DX���C�u��������������
    if (DxLib_Init() < 0) {
        //�G���[�Ȃ�I������
        return -1;
    }

    //�`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // ��ʃ��[�h�̕ύX
    SetGraphMode(WINDOW_WIDETH, WINDOW_HEIGHT, 32);

    SetMainWindowText("�e�X�g�Q�[��");

    Game_Ini();

    // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        Game_Cal();

        DrawFormatString(0, 0, GetColor(255, 255, 255), "ESC�L�[�ŏI�����܂�");

        if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
            break;
        }

    }

    DxLib_End();    // DX���C�u�����I������
    return 0;
}