#pragma once
#include "Menu.h"

struct SLIDEMENUS
{
	std::vector<std::vector<std::string>> childLabels;
	MENU rootMenu;
	//std::vector<MENU> childMenus;

	SLIDEMENUS(std::vector<std::vector<std::string>> childLabels, MENU rootMenu)
		: childLabels(childLabels), rootMenu(rootMenu)
	{
		this->rootMenu.selectColor = Color::Light_Magenta;
	}
	void SetupChildMenu(std::vector<MENU>& childMenus)
	{
		for (size_t i = 0; i < childLabels.size(); i++)
		{
			childMenus.push_back({ childLabels[i],
				{rootMenu.location.x + rootMenu.btnSize.width, rootMenu.location.y} });
			
		}
	}
	std::vector<int> Show(int rootLine = -1, int childLine = -1)
	{
		std::vector<MENU> childMenus;
		SetupChildMenu(childMenus);
		// Hien thi line dong
		if (rootLine != -1)
			rootMenu.currentLine = rootLine;
		rootMenu.ShowInVertical(Show_Only);
		while (true)
		{
			// Chua co thong tin line duoc chon
			if(rootLine == -1)
				rootLine = rootMenu.ShowInVertical(GetKey_Only);
			// bo qua esc o root menu
			if (rootLine == Key::ESC) continue;
			rootLine = rootMenu.currentLine;
			if (childLine != -1)
				childMenus[rootLine].currentLine = childLine;
			childLine = childMenus[rootLine].ShowInVertical(Menu_Mode::Both);
			if (childLine == Key::ESC)
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
			else
			{
				return { rootLine, childLine };
			}
			rootLine = -1;
			childLine = -1;
		}
	}
	void Clear()
	{
		rootMenu.ClearInVertical();
		/*for (auto item : childMenus)
		{
			item.ClearInVertical();
		}*/
	}
};