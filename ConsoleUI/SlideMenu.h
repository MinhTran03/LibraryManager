#pragma once
#include "Menu.h"

struct SLIDEMENUS
{
	std::vector<std::vector<std::string>> childLabels;
	MENU rootMenu;

	SLIDEMENUS(std::vector<std::vector<std::string>> childLabels, MENU rootMenu)
		: childLabels(childLabels), rootMenu(rootMenu)
	{

	}
	void SetupChildMenu(std::vector<MENU>& childMenus)
	{
		for (int i = 0; i < childLabels.size(); i++)
		{
			childMenus.push_back({ childLabels[i],
				{rootMenu.location.x + rootMenu.size.width, rootMenu.location.y} });
		}
	}
	std::vector<int> Show()
	{
		std::vector<MENU> childMenus;
		SetupChildMenu(childMenus);
		int rootLine, childLine = 0;
		rootMenu.ShowInVertical(Show_Only);
		while (true)
		{
			rootMenu.ShowInVertical(GetKey_Only);
			rootLine = rootMenu.currentLine;
			childLine = childMenus[rootLine].ShowInVertical(Menu_Mode::Both);
			if (childLine == -1)
			{
				childMenus[rootLine].ClearInVertical();
				//if (row == -1) //left
				//{
				//	if (rootMenu.currentLine > 0)
				//	{
				//		rootMenu.currentLine -= 1;
				//	}
				//	else
				//	{
				//		rootMenu.currentLine = rootMenu.totalLine - 1;
				//	}
				//}
				//else if (row == -2) //right
				//{
				//	if (rootMenu.currentLine < rootMenu.totalLine - 1)
				//	{
				//		rootMenu.currentLine += 1;
				//	}
				//	else
				//	{
				//		rootMenu.currentLine = 0;
				//	}
				//}
			}
			else if(childLine > 0)
			{
				return { rootLine, childLine };
			}
		}
	}
};