#include "stdafx.h"
#include"Sudoku.h"

int main()
{
	//freopen("C:\\Users\\ZYC\\Desktop\\inexp.txt", "r", stdin);
	Soduku sudo;
	sudo.getNum();
	sudo.Calculate();
	if(sudo.DeepCalculate())
		sudo.Show();
	else
	{
		printf("нч╫Б");
	}
	return 0;
}