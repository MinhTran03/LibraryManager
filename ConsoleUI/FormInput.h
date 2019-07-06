#pragma once
#include <conio.h>
#include <algorithm>
#include "TextHandler.h"
#include "CheckChar.h"
#include "Structs.h"
#include "DateTime.h"

#define widthBtn 8
#define heightBtn 1

struct FORMINPUT
{
	std::vector<std::string> OutputResults;
	std::vector<std::string> labels;
	std::vector<CONDITION> conditions;
	// Chua index y tuong ung voi vi tri label
	std::vector<int> rows;
	// CHua index x tuong ung voi vi tri text nguoi dung dang nhap vo
	std::vector<int> cols;
	std::vector<int> colsLabel;
	int currentLine;
	int totalLine;
	int xInputCol;
	std::string title;
	RECTANGLE rect;
	BORDER border;
	std::string textBtn1 = "OK";
	std::string textBtn2 = "CANCEL";

	FORMINPUT(std::vector<std::string> labels, std::vector<CONDITION> conditions, RECTANGLE rect, std::string title)
		: rect(rect), title(title), border(rect.location, rect.size)
	{
		this->labels = labels;
		this->currentLine = 0;
		this->totalLine = labels.size();
		this->xInputCol = MaxLengthLabel() + rect.location.x + 3;
		this->conditions = conditions;

		for (int i = 1; i <= totalLine; i++)
		{
			rows.push_back(rect.location.y + 2 * i + 2);
			colsLabel.push_back(rect.location.x + 2);
			cols.push_back(xInputCol);
			OutputResults.push_back("");
		}
	}

	void ParseData(std::vector<std::string> data)
	{
		OutputResults = data;
		for (size_t i = 0; i < data.size(); i++)
		{
			cols[i] += data[i].size();
		}
	}
	void ResetOutput()
	{
		for (size_t i = 0; i < OutputResults.size(); i++)
		{
			OutputResults[i] = "";
			cols[i] = xInputCol;
		}
	}
	void PrintLabelsTitle()
	{
		GoToXY(rect.location.x + rect.size.width / 2 - title.length() / 2 - title.length() % 2, rows[0] - 2);
		std::cout << title;
		// In label va text ra man hinh
		for (int i = 0; i < totalLine; i++)
		{
			SetTextColor(LABEL_TEXT_COLOR);
			GoToXY(colsLabel[i], rows[i]);
			std::cout << labels[i];
			SetTextColor(TEXT_INPUT_COLOR);
			if(conditions[i].mode == Default)
				SetTextColor(TEXT_INPUT_DEFAULT_COLOR);
			GoToXY(xInputCol, rows[i]);
			std::cout << OutputResults[i];
		}
	}
	int MaxLengthLabel()
	{
		size_t max = 0;
		for (auto label : labels)
		{
			if (label.length() > max) max = label.length();
		}
		return max;
	}
	bool IsValidCondition(char& c, int currentLine, std::string value)
	{
		auto condition = conditions[currentLine];
		// check maxLength
		if (value.size() >= condition.maxLength)
			return false;
		// check type
		switch (condition.type)
		{
		case WordType::Mix:
			return IsMixLetter(c);
			break;
		case WordType::Number_Only:
			return IsNumber(c);
			break;
		case WordType::Word_Only:
			return IsLetterOnly(c);
			break;
		case WordType::DateTime:
			return IsNumber(c);
			break;
		case WordType::Name:
			// tu in hoa sau khoang trang (' ')
			if (value.size() != 0 && value.at(value.size() - 1) == ' ')
				c = toupper(c);
			if (!IsLetterOnly(c)) return false;
			break;
		case WordType::Gender:
			switch (value.size())
			{
			case 0:
				return c == 'N' || c == 'n';
				break;
			case 1:
				return c == 'a' || c == 'u';
				break;
			case 2:
				if (value == "Na" || value == "na")
					return c == 'm';
				return false;
				break;
			default:
				break;
			}
			break;
		default: case WordType::All:
			return true;
			break;
		}
		return true;
	}
	std::vector<int> IsValidOutput()
	{
		std::vector<int> error;
		for (int i = 0; i < totalLine; i++)
		{
			// check min length
			if (OutputResults[i].length() < conditions[i].minLength)
			{
				error.push_back(i);
			}
			// gioi han ngay sinh khong duoc lon hon ngay hien tai
			else if (conditions[i].type == BirthDay/* && OutputResults[i].length() == conditions[i].minLength*/)
			{
				auto dateNow = DATETIME();
				dateNow.SetDateTimeNow();
				auto dateResult = DATETIME();
				dateResult = dateResult.ParseStringDate(OutputResults[i]);
				if (dateNow.SubDate(dateResult) < 0)
					error.push_back(i);
			}
			// year phai nho hon nam hien tai
			else if (conditions[i].type == Year/* && OutputResults[i].length() == conditions[i].minLength*/)
			{
				auto dateNow = DATETIME();
				dateNow.SetDateTimeNow();
				if((size_t)std::stoi(OutputResults[i]) > dateNow.year)
					error.push_back(i);
			}
		}
		return error;
	}

	bool Show()
	{
		border.Draw2Line(BORDER_COLOR);
		currentLine = 0;
		PrintLabelsTitle();

		// Ve button OK CANCEL
		int halfWidthForm = rect.size.width / 2 + rect.location.x;
		int x = rect.location.x + rect.size.width / 4 - widthBtn / 2 - widthBtn % 2;
		int y = rows[totalLine - 1] + 2;
		auto btnOK = BUTTON({ {x, y}, {widthBtn, heightBtn} }, textBtn1);
		btnOK.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
		rows.push_back(y);
		cols.push_back(x);
		x += rect.size.width / 2;
		auto btnCancel = BUTTON({ {x, y}, {widthBtn, heightBtn} }, textBtn2);
		btnCancel.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);

		// Dua con tro ve vi tri Input chuan bi nhap
		ShowPointer();
		GoToXY(cols[currentLine], rows[currentLine]);

		// Bat phim
		char inputKey = NULL;
		do
		{
			inputKey = _getch();
			if (inputKey == Key::_NULL) inputKey = _getch();
			// Xu ly con tro Up Down Left Right
			else if (inputKey == -32)
			{
				inputKey = _getch();
				if (inputKey == Key::UP && currentLine > 0)
				{
					// Con tro dang o vi tri cua OK hoac Cancel
					if (currentLine == totalLine)
					{
						// Set lai mau mac dinh
						btnOK.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
						btnCancel.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
						// Gan lai col cho button ben trai
						cols[currentLine] = btnOK.rect.location.x;
						ShowPointer();
					}
					currentLine--;
					GoToXY(cols[currentLine], rows[currentLine]);
				}
				else if (inputKey == Key::DOWN && currentLine < totalLine)
				{
					currentLine++;
					GoToXY(cols[currentLine], rows[currentLine]);
					// Con tro o line cua button
					if (currentLine == totalLine)
					{
						HidePointer();
						btnOK.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
					}
				}
				else if (inputKey == Key::RIGHT && cols[currentLine] < halfWidthForm && currentLine == totalLine)
				{
					GoToXY(btnCancel.rect.location.x, btnCancel.rect.location.y);
					btnOK.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
					btnCancel.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
					cols[currentLine] = btnCancel.rect.location.x;
				}
				else if (inputKey == Key::LEFT && cols[currentLine] > halfWidthForm && currentLine == totalLine)
				{
					GoToXY(btnOK.rect.location.x, btnOK.rect.location.y);
					btnCancel.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
					btnOK.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
					cols[currentLine] = btnOK.rect.location.x;
				}
				continue;
			}

			if (inputKey == Key::ENTER && currentLine <= totalLine)
			{
				// Xu ly Enter OK va CANCEL o day
				if (currentLine == totalLine)
				{
					// Phim OK duoc nhan
					if (cols[currentLine] < halfWidthForm)
					{
						// check length output
						auto errorsLength = IsValidOutput();
						// no error
						if (errorsLength.size() == 0)
						{
							return true;
							/*std::string text = "Ban chac chan muon luu thong tin?";
							auto confirm = CONFIRMDIALOG({ rect.location.x + rect.size.width / 2 - (int)text.length() / 2 - 4,
															rect.location.y + rect.size.height / 2 - 2 });
							confirm.Show(text, Yes_No);
							ClearScreen(Black);
							if (confirm.result == No)
							{
								ReDraw();
								btnOK.Draw(bgBtnSelectColor, textLabelColor);
							}
							else
							{
								cols[currentLine] = btnCancel.rect.location.x;
								ResetOutput();
								return;
							}*/
						}
						// error
						else
						{
							ClearScreen(BG_COLOR);
							ReDraw();
							SetBGColor(BG_COLOR);
							SetTextColor(WARNING_TEXT_COLOR);
							for (size_t i = 0; i < errorsLength.size(); i++)
							{
								GoToXY(xInputCol, rows[errorsLength[i]] + 1);
								std::string tempLabel = labels[errorsLength[i]];
								tempLabel.erase(std::remove(tempLabel.begin(), tempLabel.end(), ':'), tempLabel.end());
								std::cout << tempLabel << " khong hop le";
							}
							currentLine = errorsLength[0];
							GoToXY(cols[currentLine], rows[currentLine]);
							ShowPointer();
							//btnOK.Draw(selectColor, textLabelColor);
						}
					}
					// Phim Cancel duoc nhan
					else if (cols[currentLine] > halfWidthForm)
					{
						std::string text = "Ban chac chan muon huy?";
						auto confirm = CONFIRMDIALOG({ rect.location.x + rect.size.width / 2 - (int)text.length() / 2 - 4,
														rect.location.y + rect.size.height / 2 - 2 });
						confirm.Show(text, Yes_No);
						ClearScreen(BG_COLOR);
						if (confirm.result == No)
						{
							ReDraw();
							btnCancel.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
						}
						else
						{
							cols[currentLine] = btnOK.rect.location.x;
							ResetOutput();
							return false;
						}
					}
					continue;
				}
				currentLine++;
				GoToXY(cols[currentLine], rows[currentLine]);
				if (currentLine == totalLine)
				{
					HidePointer();
					btnOK.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
				}
			}
			else if (inputKey == Key::TAB)
			{
				// Con tro truoc do o vi tri cua button Cancel
				/*if (currentLine == -1)
				{
					currentLine++;
					btnOK.Draw(normalColor, Color::White);
					btnCancel.Draw(normalColor, Color::White);
					ShowPointer();
				}*/
				// Neu line hien tai < so dong => tang line
				//else if (currentLine < totalLine) currentLine++;
				/*GoToXY(cols[currentLine], rows[currentLine]);
				if (currentLine == totalLine)
				{
					HidePointer();
					if (cols[currentLine] < halfWidthForm)
					{
						btnOK.Draw(selectColor, Color::White);
						cols[currentLine] = btnCancel.rect.location.x;
					}
					else if (cols[currentLine] > halfWidthForm)
					{
						btnOK.Draw(normalColor, Color::White);
						btnCancel.Draw(selectColor, Color::White);
						cols[currentLine] = btnOK.rect.location.x;
						currentLine = -1;
					}
				}*/
			}
			else if (inputKey == Key::ESC)
			{
				std::string text = "Ban chac chan muon thoat?";
				auto confirm = CONFIRMDIALOG({ rect.location.x + rect.size.width / 2 - (int)text.length() / 2 - 4,
												rect.location.y + rect.size.height / 2 - 2 });
				confirm.Show(text, Yes_No);
				ClearScreen(Black);
				if (confirm.result == No)
				{
					ReDraw();
					GoToXY(cols[currentLine], rows[currentLine]);
					ShowPointer();
				}
				else
				{
					cols[currentLine] = btnOK.rect.location.x;
					ResetOutput();
					return false;
				}
			}
			// Xu ly chuoi nhap vo
			else if (IsAllLetter(inputKey) && conditions[currentLine].mode == CanChange)
			{
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				if (IsValidCondition(inputKey, currentLine, OutputResults[currentLine]))
				{
					// In hoa chu cai dau tien
					if (OutputResults[currentLine].size() == 0)
					{
						inputKey = toupper(inputKey);
					}
					// viet thuong het neu ko phai ten rieng
					else if(conditions[currentLine].type != Name)
					{
						inputKey = tolower(inputKey);
					}
					// Tu them '/'
					if (conditions[currentLine].type == DateTime)
					{
						if (OutputResults[currentLine].size() == 2 || OutputResults[currentLine].size() == 5)
						{
							OutputResults[currentLine] += '/';
							std::cout << '/';
							cols[currentLine]++;
						}
					}
					OutputResults[currentLine] += inputKey;
					std::cout << inputKey;
					cols[currentLine]++;
					if (conditions[currentLine].type == DateTime)
					{
						if (OutputResults[currentLine].size() == 2 || OutputResults[currentLine].size() == 5)
						{
							OutputResults[currentLine] += '/';
							std::cout << '/';
							cols[currentLine]++;
						}
					}
				}
			}
			// Xu ly xoa ky tu cuoi cung
			else if (inputKey == Key::BACKSPACE && cols[currentLine] > xInputCol && conditions[currentLine].mode == CanChange)
			{
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				int lengthCurrentValue = OutputResults[currentLine].length();
				auto end = OutputResults[currentLine].end();
				OutputResults[currentLine].erase(std::remove(end - 1, end, OutputResults[currentLine][lengthCurrentValue - 1]));
				cols[currentLine]--;

				GoToXY(cols[currentLine], rows[currentLine]);
				std::cout << std::string(1, ' ');
				GoToXY(cols[currentLine], rows[currentLine]);
			}

		} while (!_kbhit());
		return true;
	}
	void ReDraw()
	{
		border.Draw2Line(BORDER_COLOR);

		PrintLabelsTitle();

		// Ve button OK CANCEL
		int halfWidthForm = rect.size.width / 2;
		int x = rect.location.x + rect.size.width / 4 - widthBtn / 2 - widthBtn % 2;
		int y = rows[totalLine - 1] + 2;
		auto btnOK = BUTTON({ {x, y}, {widthBtn, heightBtn} }, textBtn1);
		auto btnCancel = BUTTON({ {x + halfWidthForm, y}, {widthBtn, heightBtn} }, textBtn2);

		btnOK.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
		btnCancel.Draw(BUTTON_BG_COLOR, BUTTON_TEXT_COLOR);
		rows.push_back(y);
		cols.push_back(x);

		// Dua con tro ve vi tri Input chuan bi nhap
		GoToXY(cols[currentLine], rows[currentLine]);
	}
};
