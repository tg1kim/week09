#include <stdio.h>

#define M	11
#define N	15
#define Size	M * N
#pragma warning(disable: 4326 4996 6031)

typedef char Maze[M + 2][N + 2];		// Maze Ÿ���� �����Ѵ�.

typedef struct {
	int nRow;
	int nCol;
	int nDir;
}	Item;

typedef struct  {
	int nRow;
	int nCol;
}	Offsets;

Offsets nMoves[8] = {
	{-1, 0},	// ��
	{-1, 1},	// �ϵ�
	{0, 1},		// ��
	{1, 1},		// ����
	{1, 0},		// ��
	{1, -1},	// ����
	{0, -1},	// ��
	{-1, -1}};	// �ϼ�

int nTop;
Item aStack[Size];

Maze maze = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
	{1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1},
	{1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
	{1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
Maze mark;

void main()
{
	int FindPath(void);
	void PrintPath(void);

	for (int i = 0; i < M + 2; i++)
		for (int j =0; j < N + 2; j++)
			mark[i][j] = 0;				// 0���� �ʱ�ȭ
	if (FindPath())						// ���� ã�Ҵ�.
		PrintPath();
	else								// ���� ����.
		printf("No path has been found.\n");
}

int FindPath()	// �̷ο��� ���� ã�ƶ�.
{
	void Push(Item aPos);
	int IsEmptyStack();
	Item Pop(void);
	void PrintTrial(int nDir, int nRow, int nCol, const char *sMsg);

	Item aPos = {1, 1, 0};
	mark[1][1] = 1;
	nTop = -1;
	Push(aPos);
	while (IsEmptyStack() == false) {
		aPos = Pop();
		PrintTrial(-1, aPos.nRow, aPos.nCol, "<<<Back");
		while (aPos.nDir < 8) {
			int nDir = aPos.nDir;
			int nextRow = aPos.nRow + nMoves[nDir].nRow;
			int nextCol = aPos.nCol + nMoves[nDir].nCol;
			if (nextRow == M && nextCol == N) {
				PrintTrial(nDir, nextRow, nextCol, "Success!!!");
				Push(aPos);
				return true;
			}
			else if (maze[nextRow][nextCol] == 0 &&
					 mark[nextRow][nextCol] == 0) {
				PrintTrial(nDir, nextRow, nextCol, ">>>Go");
				mark[nextRow][nextCol] = 1;
				aPos.nDir++;
				Push(aPos);
				aPos.nRow = nextRow;
				aPos.nCol = nextCol;
				aPos.nDir = 0;
			}
			else {
				PrintTrial(nDir, nextRow, nextCol, 
					(maze[nextRow][nextCol] == 0) ? "Marked" : "Stop");
				aPos.nDir++;
			}
		}
	}
	return false;
}

void PrintPath()		// ���ÿ� ����� ���� ����϶�.
{
	for (int i = 0; i <= nTop; i++)
		printf("Position(%d, %d)\n", aStack[i].nRow, aStack[i].nCol);
	printf("Position(%d, %d)\n\n", M, N);
}

void PrintTrial(int nDir, int nRow, int nCol, const char *sMsg)
{
	static int nTrial;
	printf("[%03d] ", ++nTrial);
	for (int i = 0; i <= nTop; i++)
		putchar((i & 1) ? '|' : 0x20);

	printf("[%c](%d, %d) %s\n", (nDir < 0) ? '-' : nDir + 0x30, nRow, nCol, sMsg);
}

/*
 * Stack operations
 */

int IsEmptyStack()
{
	return nTop < 0;
}

int IsFullStack()
{
	return nTop >= Size - 1;
}

void Push(Item aPos)
{
	if (IsFullStack())
		return;
	aStack[++nTop] = aPos;
}

Item Pop()
{
	if (IsEmptyStack())
		return aStack[0];
	return aStack[nTop--];
}
