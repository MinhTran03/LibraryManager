#pragma once
#include "Menu.h"

struct SLIDEMENUS
{
	std::vector<std::vector<std::string>> childLabels;
	MENU rootMenu;
	std::vector<MENU> childMenus;

	SLIDEMENUS(std::vector<std::vector<std::string>> childLabels, MENU rootMenu)
		: childLabels(childLabels), rootMenu(rootMenu)
	{
		this->rootMenu.AddButton("THOAT");
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
	int* Show(int rootLine = -1, int childLine = -1)
	{
		//std::vector<MENU> childMenus;
		int* result = new int[2];
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
			//rootMenu.ShowDisableModeInVertical();
			// bo qua esc o root menu
			if (rootLine == Key::ESC) 
			{
				rootLine = -1;
				childLine = -1;
				continue; 
			}
			// Thoat
			if (rootLine == rootMenu.totalLine - 1) 
			{
				result[0] = rootLine;
				result[1] = -1;
				return result;
			}
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
				result[0] = rootLine;
				result[1] = childLine;
				return result;
			}
			rootLine = -1;
			childLine = -1;
		}
	}
	void Clear()
	{
		rootMenu.ClearInVertical();
		for (auto item : childMenus)
		{
			item.ClearInVertical();
		}
	}
};