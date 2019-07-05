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
				{rootMenu.location.x + rootMenu.size.width * i, rootMenu.location.y + rootMenu.size.height } });
		}
	}
	std::vector<int> Show()
	{
		std::vector<MENU> childMenus;
		SetupChildMenu(childMenus);
		int row, col = 0;
		while (true)
		{
			rootMenu.ShowInHorizontal(-1);
			col = rootMenu.currentLine;
			row = childMenus[col].ShowInVertical();
			if (row < 0)
			{
				childMenus[col].ClearInVertical();
				if (row == -1) //left
				{
					if (rootMenu.currentLine > 0)
					{
						rootMenu.currentLine -= 1;
					}
					else
					{
						rootMenu.currentLine = rootMenu.totalLine - 1;
					}
				}
				else if (row == -2) //right
				{
					if (rootMenu.currentLine < rootMenu.totalLine - 1)
					{
						rootMenu.currentLine += 1;
					}
					else
					{
						rootMenu.currentLine = 0;
					}
				}
			}
			else
			{
				return { row, col };
			}
		}
	}
};