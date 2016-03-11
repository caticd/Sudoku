#pragma once

class SodukuIndi
{
public:
	int num=0;
	bool possible[9] = {true,true,true,true, true,true, true,true, true };
	SodukuIndi();
	~SodukuIndi();
	void getNum(int num);

private:

};

class Soduku
{
public:
	SodukuIndi indi[9][9];
	Soduku();
	~Soduku();
	void getNum();
	void Calculate();
	int DeepCalculate();
	void Show();
private:
	void CheckNum(int i, int j, int num);
	int ReturnableCheckNum(int i, int j, int num,int *arr);
	void ReturnCheckNum(int changedcount,int *arr);
};

