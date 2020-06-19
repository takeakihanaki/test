#include <iostream>
#include <time.h>

// 柱の数 
const static int PILLAR_W = 10; 
const static int PILLAR_H = 10; 

// 迷路のサイズ （柱の数＊2+3で迷路の数になる）
const static int MAZE_W = PILLAR_W * 2 + 3; 
const static int MAZE_H = PILLAR_H * 2 + 3;

// 迷路データ（trueは壁） 
bool g_maze[MAZE_H][MAZE_W];



// 位置の構造体
struct Point
{
	int x;
	int y;
};

// 方向の列挙体
enum DIR
{
	UP,
	RIGHT,
	LEFT,
	DOWN,

	DIR_NUM
};


// 方向のオフセットを返す関数 
Point GetDirOffset(DIR dir)
{ 
	// 調べる方向へのオフセット値
	Point offset[DIR_NUM] = 
	{   //  上      右      下       左 
		{ 0, -1 },{ 1, 0 },{ 0, 1 },{ -1, 0 }, 
	};  
	
	return offset[dir];
} 

// 迷路の初期化
void InitializeMaze()
{
	//上下の壁を作る
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

// 壁を作る方向を決める関数 
DIR GetBuildDir(int x, int y, bool check[])
{
	// 壁を作ることができる方向を調べる 
	int cnt = 0;
	for (int i = 0; i < DIR_NUM; i++)
	{
		Point offset = GetDirOffset(static_cast<DIR>(i));
		// すでに壁があるのでfalseにする  
		if (g_maze[y + offset.y][x + offset.x] == true) check[i] = false;
		// 作ることができる方向の数を増やす  
		if (check[i] == true) cnt++;
	}
	// ランダムで壁を作る方向を決める 
	int idx = rand() % cnt;
	int dir;
	for (dir = 0; dir < DIR_NUM; dir++)
	{
		// 壁を作れる方向なら 
		if (check[dir] == true)
		{
			if (idx == 0) break;
			idx--;
		}
	}
	return static_cast<DIR>(dir);
}



// 迷路の作成
void CreateMaze()
{
	// 等間隔に柱を作る
	for (int i = 0; i < PILLAR_H; i++)
	{
		for (int j = 0; j < PILLAR_W; j++)
		{
			// 2個間隔で設置されているのでそれぞれ配置
			int x = 2 + 2 * j;
			int y = 2 + 2 * i;
			g_maze[y][x] = true;

			// チェックする方向   UP(×) RIGHT DOWN  LEFT  
			bool check[DIR_NUM] = { false, true, true, true }; 

			// 一列目なら上もチェック対象にする   
			if (j == 0)
			{
				check[UP] = true;
			}
		
			// 壁を作る方向を決めて壁を作る   
			Point offset = GetDirOffset(GetBuildDir(x, y, check));
			g_maze[y + offset.y][x + offset.x] = true;   
		}
	}
}

// 迷路の描画
void DrawMaze()
{
	//上下の壁を作る
	for (int i = 0; i < MAZE_H; i++)
	{
		for (int j = 0; j < MAZE_W; j++)
		{
			if (g_maze[i][j])
			{
				std::cout << "■";
			}
			else
			{
				std::cout << "　";
			}
		}
		std::cout << std::endl;
	}
}





int main()
{
	// 乱数の初期化
	srand((unsigned)time(NULL));

	// 迷路の初期化
	InitializeMaze();
	// 迷路の作成
	CreateMaze();
	// 迷路の描画
	DrawMaze();

	system("pause");

	return 0;
}



