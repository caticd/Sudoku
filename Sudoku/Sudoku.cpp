// Soduku.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Sudoku.h"

SodukuIndi::SodukuIndi()
{
}

SodukuIndi::~SodukuIndi()
{
}

void SodukuIndi::getNum(int num)
{
	this->num = num;
}


Soduku::Soduku()
{
}

Soduku::~Soduku()
{
}

void Soduku::getNum()
{
	int tempnum;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			scanf("%d", &tempnum);
			if (tempnum!=0)
			{
				this->CheckNum(i,j,tempnum-1);
			}
		}
	}
}

void Soduku::Calculate()
{
	for (int i = 0;i < 9; i++)
	{
		for (int j = 0;j < 9; j++)
		{
			int possibleCount = 0;
			int possible = 0;
			for (int k = 0; k < 9; k++)
			{
				if (this->indi[i][j].possible[k] == true)
				{
					possibleCount++;
					possible = k;
				}
			}
			if (possibleCount == 1&&this->indi[i][j].num==0)
			{
				this->CheckNum(i, j, possible);
				i = j = 0;
			}
		}
	}
}

int Soduku::DeepCalculate()
{
	//static int DeepCalculateCalledNum = 1;
	//printf("DeepCalculate called %d\n", DeepCalculateCalledNum++);
	//检测是否结束
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int k = 0; k < 9; k++)
			{
				if (this->indi[i][j].possible[k]==true)
				{
					count++;
				}
			}
		}
	}
	if (count==0)
	{
		return 1;
	}
	//检测是否有解
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (this->indi[i][j].num == 0)
			{
				int possiblecount = 0;
				for (int k = 0; k < 9; k++)
				{
					if (this->indi[i][j].possible[k]==true)
					{
						possiblecount++;
					}
				}
				if (possiblecount == 0)
				{
					//无解
					return 0;
				}
			}
		}
	}
	//此时继续进行猜测

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (this->indi[i][j].num==0)
			{
				for (int k = 0; k < 9; k++)
				{
					if (this->indi[i][j].possible[k]==true)
					{
						int changedcount=0;
						int arr[27];
						changedcount=ReturnableCheckNum(i, j, k,arr);
						//Calculate?
						if (this->DeepCalculate())
						{
							return 1;
						}
						else
						{
							//把num置零
							this->indi[i][j].num = 0;
							this->ReturnCheckNum(changedcount, arr);
						}
					}
				}
				return 0;
			}
		}
	}
	return 0;
}

void Soduku::CheckNum(int i, int j, int num)
{
	//col为第几行，row为第几列
	int col, row;
	this->indi[i][j].getNum(num+1);
	for (int k = 0; k < 9; k++)
	{
		this->indi[i][k].possible[num] = false;
		this->indi[k][j].possible[num] = false;
	}
	//对于与之同块的possible
	col = i / 3;
	row = j / 3;
	col *= 3;
	row *= 3;
	for (int m = 0; m < 3; m++)
	{
		for (int n = 0; n < 3; n++)
		{
			this->indi[col + m][row + n].possible[num] = false;
		}
	}
}

int Soduku::ReturnableCheckNum(int i, int j, int num, int *arr)
{
	//col为第几行，row为第几列
	int col, row;
	int count = 0;
	this->indi[i][j].getNum(num+1);
	for (int k = 0; k < 9; k++)
	{
		if (this->indi[i][k].possible[num] == true)
		{
			arr[count++] = i * 100 + k * 10 + num;
		}
		this->indi[i][k].possible[num] = false;
		if (this->indi[k][j].possible[num] == true)
		{
			arr[count++] = k * 100 + j * 10 + num;
		}
		this->indi[k][j].possible[num] = false;
	}
	//对于与之同块的possible
	col = i / 3;
	row = j / 3;
	col *= 3;
	row *= 3;
	for (int m = 0; m < 3; m++)
	{
		for (int n = 0; n < 3; n++)
		{
			if (this->indi[col + m][row + n].possible[num] == true)
			{
				arr[count++] = (col + m) * 100 + (row + n) * 10 + num;
			}
			this->indi[col + m][row + n].possible[num] = false;
		}
	}
	return count;
}

void Soduku::ReturnCheckNum(int changedcount, int * arr)
{
	int m, n, k;
	for (int i = 0; i < changedcount; i++)
	{
		k = arr[i] % 10;
		arr[i] /= 10;
		n = arr[i] % 10;
		m = arr[i] / 10;
		this->indi[m][n].possible[k] = true;
	}
}

void Soduku::Show()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			printf("%d ", this->indi[i][j].num);
		}
		printf("\n");
	}
}
