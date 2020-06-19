#include <iostream>
#include <time.h>

// ���̐� 
const static int PILLAR_W = 10; 
const static int PILLAR_H = 10; 

// ���H�̃T�C�Y �i���̐���2+3�Ŗ��H�̐��ɂȂ�j
const static int MAZE_W = PILLAR_W * 2 + 3; 
const static int MAZE_H = PILLAR_H * 2 + 3;

// ���H�f�[�^�itrue�͕ǁj 
bool g_maze[MAZE_H][MAZE_W];



// �ʒu�̍\����
struct Point
{
	int x;
	int y;
};

// �����̗񋓑�
enum DIR
{
	UP,
	RIGHT,
	LEFT,
	DOWN,

	DIR_NUM
};


// �����̃I�t�Z�b�g��Ԃ��֐� 
Point GetDirOffset(DIR dir)
{ 
	// ���ׂ�����ւ̃I�t�Z�b�g�l
	Point offset[DIR_NUM] = 
	{   //  ��      �E      ��       �� 
		{ 0, -1 },{ 1, 0 },{ 0, 1 },{ -1, 0 }, 
	};  
	
	return offset[dir];
} 

// ���H�̏�����
void InitializeMaze()
{
	//�㉺�̕ǂ����
	for (int i = 0; i < MAZE_H; i++)
	{
		for (int j = 0; j < MAZE_W; j++)
		{
			if (i == 0 || i == MAZE_H - 1 || j == 0 || j == MAZE_W - 1)
			{
				g_maze[i][j] = true;
			}
			else
			{
				g_maze[i][j] = false;
			}
		}
	}
}

// �ǂ������������߂�֐� 
DIR GetBuildDir(int x, int y, bool check[])
{
	// �ǂ���邱�Ƃ��ł�������𒲂ׂ� 
	int cnt = 0;
	for (int i = 0; i < DIR_NUM; i++)
	{
		Point offset = GetDirOffset(static_cast<DIR>(i));
		// ���łɕǂ�����̂�false�ɂ���  
		if (g_maze[y + offset.y][x + offset.x] == true) check[i] = false;
		// ��邱�Ƃ��ł�������̐��𑝂₷  
		if (check[i] == true) cnt++;
	}
	// �����_���ŕǂ������������߂� 
	int idx = rand() % cnt;
	int dir;
	for (dir = 0; dir < DIR_NUM; dir++)
	{
		// �ǂ���������Ȃ� 
		if (check[dir] == true)
		{
			if (idx == 0) break;
			idx--;
		}
	}
	return static_cast<DIR>(dir);
}



// ���H�̍쐬
void CreateMaze()
{
	// ���Ԋu�ɒ������
	for (int i = 0; i < PILLAR_H; i++)
	{
		for (int j = 0; j < PILLAR_W; j++)
		{
			// 2�Ԋu�Őݒu����Ă���̂ł��ꂼ��z�u
			int x = 2 + 2 * j;
			int y = 2 + 2 * i;
			g_maze[y][x] = true;

			// �`�F�b�N�������   UP(�~) RIGHT DOWN  LEFT  
			bool check[DIR_NUM] = { false, true, true, true }; 

			// ���ڂȂ����`�F�b�N�Ώۂɂ���   
			if (j == 0)
			{
				check[UP] = true;
			}
		
			// �ǂ������������߂ĕǂ����   
			Point offset = GetDirOffset(GetBuildDir(x, y, check));
			g_maze[y + offset.y][x + offset.x] = true;   
		}
	}
}

// ���H�̕`��
void DrawMaze()
{
	//�㉺�̕ǂ����
	for (int i = 0; i < MAZE_H; i++)
	{
		for (int j = 0; j < MAZE_W; j++)
		{
			if (g_maze[i][j])
			{
				std::cout << "��";
			}
			else
			{
				std::cout << "�@";
			}
		}
		std::cout << std::endl;
	}
}





int main()
{
	// �����̏�����
	srand((unsigned)time(NULL));

	// ���H�̏�����
	InitializeMaze();
	// ���H�̍쐬
	CreateMaze();
	// ���H�̕`��
	DrawMaze();

	system("pause");

	return 0;
}



