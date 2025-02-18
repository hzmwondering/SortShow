// Sorts.cpp	具体的排序算法成员函数定义（相应的函数声明在文件SortShow.h的SortShow类中）
#include "SortShow.h"
#include <conio.h>

void SortShow::BubbleSort()
{
	int lastExchangeIndex = 0;				// 记录最后一次交换的位置
	int sortBorder = length - 1;			// 无序数列的边界，每次比较只需要进行到此
	bool isSorted;
	
	for(int i=0; i<length; i++)
	{
		isSorted = true;					// 有序标记，每一轮的初始是true
		for(int j=0; j<sortBorder; j++)
		{
			if(array[j] > array[j+1])		// 有元素需要交换时
			{
				SWAP(array, j, j+1);		// 此函数采用带颜色、声音地显示数据 array[j]和array[j+1]
				isSorted = false;			// 则标记变为false
				lastExchangeIndex = j;		// 并且将无序数列的边界更新为最后一次交换元素的位置
			}
		}
		sortBorder = lastExchangeIndex;
		if(isSorted) break;
	}
}

void SortShow::SelectionSort()				// 选择排序
{
	int minpos, maxpos, i, left=0, right=length-1;

	while(left < right)
	{
		minpos = maxpos = left;
		for(i=left; i<=right; i++)			// 确定最大值下标以及最小值下标
		{
			if(array[i] > array[maxpos])
				maxpos = i;
			if(array[i] < array[minpos])
				minpos = i;
		}
		if(maxpos != right)					// 将最大值插到最后
			SWAP(array, maxpos, right);
		if(minpos == right)					// 如果此时最小值的位置恰好在最右边，由于上一语句，已经将最小值换至maxpos位置了。
			minpos = maxpos;				// 故需要更新minpos。例如：3(left), 4(maxpos), 2, 1(minpos,right) 则上一语句交换成 3(left), 1(maxpos), 2, 4(minpos)
											// 当然需要变成，3(left), 1(minpos), 2, 4
		if(minpos != left)					// 将根据新的minpos及left执行交换: 1, 3, 2, 4
			SWAP(array, minpos, left);
		left++;								// 1, 3(left), 2(right), 4。然后进入下一轮循环
		right--;
	}
}

void SortShow::QuickSort(int *a, int size)
{
	if(size<=1) return ;
	if(size==2)
	{
		if(a[0]>a[1]) SWAP(a, 0, 1);
		return;
	}
	ShowText(3, a-array+1, 7, 0, "[");			// 递归分段起点
	ShowText(3, a-array+size, 7, 0, "*");		// 递归分段终点，该处的元素值作为分界的轴心值
	
	int left=0, right=size-1;
	int pivot = a[right];
	do
	{
		while(left<right && a[left] <= pivot)
			left++;
		while(left<right && a[right] >= pivot)
			right--;
		if(left < right)
			SWAP(a, left, right);
	}while(left<right);
	SWAP(a, size-1, left);

	ShowText(3, a-array+left+1, 7, 0, "-"); 
	MidiOutMessage(hMidiOut, 0x90, 0x09, 69, 127);		// 通道0x09特指打击乐（69, 82 Shaker 沙锤）
	Sleep(200);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 82, 127);		// 通道0x09特指打击乐（69, 82 Shaker 沙锤）
	for(int key=0; key!='g' && key!='G'; )
		key = _getch();
	
	QuickSort(a, left);
	QuickSort(a+left+1, size-left-1);
}
