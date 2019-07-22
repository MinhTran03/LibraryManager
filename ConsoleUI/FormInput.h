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
	MYPOINT guildLocation = { 0,0 };
	string* OutputResults;
	string* Guilds;
	string* labels;
	CONDITION* conditions;
	// Chua index y tuong ung voi vi tri label
	vector<int> rows;
	// CHua index x tuong ung voi vi tri text nguoi dung dang nhap vo
	vector<int> cols;
	vector<int> colsLabel;
	int currentLine = 0;
	int totalLine;
	int xInputCol;
	string title;
	RECTANGLE rect;
	BORDER border;	
	string textBtn1 = "OK";
	string textBtn2 = "CANCEL";

	FORMINPUT(string* labels, CONDITION* conditions, RECTANGLE rect, string title, int totalLine)
		: rect(rect), title(title), border(rect.location, rect.size), totalLine(totalLine)
	{
		this->labels = labels;
		this->currentLine = 0;
		this->xInputCol = MaxLengthLabel() + rect.location.x + 3;
		this->conditions = conditions;
		guildLocation = { rect.location.x + 1, rect.location.y + rect.size.height };
		int count = 0;
		for (int i = 1; i <= totalLine; i++)
		{
			rows.push_back(rect.location.y + 2 * i + 2);
			colsLabel.push_back(rect.location.x + 2);
			cols.push_back(xInputCol);
			//OutputResults.push_back("");
			string te = "";
			PushBack(OutputResults, te, count);
		}
	}

	void ParseData(string* data)
	{
		OutputResults = data;
		for (int i = 0; i < this->totalLine; i++)
		{
			cols[i] += data[i].size();
		}
	}
	void ResetOutput()
	{
		for (int i = 0; i < this->totalLine; i++)
		{
			OutputResults[i] = "";
			cols[i] = xInputCol;
		}
	}
	void PrintLabelsTitle(int mode = 0, int mode2 = 0)
	{
		GoToXY(rect.location.x + rect.size.width / 2 - title.length() / 2 - title.length() % 2, rows[0] - 2);
		cout << title;
		
		// In label va text ra man hinh
		for (int i = 0; i < totalLine; i++)
		{
			SetTextColor(LABEL_TEXT_COLOR);
			GoToXY(colsLabel[i], rows[i]);
			cout << labels[i];
			SetTextColor(TEXT_INPUT_COLOR);
			if (conditions[i].mode == Default)
				SetTextColor(TEXT_INPUT_DEFAULT_COLOR);
			GoToXY(xInputCol, rows[i]);
			cout << OutputResults[i];
			if (conditions[i].type == Enum && mode != 0)
			{
				int num = OutputResults[i][0] - '0';
				int x = WhereX();
				GoToXY(x + 4, WhereY());
				// gender
				if (mode == 1)
				{
					if (num == 0)
					{
						cout << "Nam";
					}
					else if (num == 1)
					{
						cout << "Nu";
					}
				}
				// trang thai sach
				else if (mode == 2)
				{
					if (num == 0)
					{
						cout << "Cho muon duoc";
					}
					else if (num == 1)
					{
						cout << "Da muon";
					}
					else if (num == 2)
					{
						cout << "Da thanh ly";
					}
				}
				// trang thai muon tra
				else if (mode == 3)
				{
					if (num == 0)
					{
						cout << "Sach chua tra";
					}
					else if (num == 1)
					{
						cout << "Sach da tra";
					}
					else if (num == 2)
					{
						cout << "Lam mat sach";
					}
				}
				else if (mode == 4)
				{
					if (num == 0)
					{
						cout << "The bi khoa";
					}
					else if (num == 1)
					{
						cout << "Dang hoat dong";
					}
				}
				GoToXY(x, WhereY());
			}
			else if (conditions[i].type == Enum2 && mode2 != 0)
			{
				int num = OutputResults[i][0] - '0';
				int x = WhereX();
				GoToXY(x + 4, WhereY());
				// gender
				if (mode2 == 1)
				{
					if (num == 0)
					{
						cout << "Nam";
					}
					else if (num == 1)
					{
						cout << "Nu";
					}
				}
				// trang thai sach
				else if (mode2 == 2)
				{
					if (num == 0)
					{
						cout << "Cho muon duoc";
					}
					else if (num == 1)
					{
						cout << "Da muon";
					}
					else if (num == 2)
					{
						cout << "Da thanh ly";
					}
				}
				// trang thai muon tra
				else if (mode2 == 3)
				{
					if (num == 0)
					{
						cout << "Sach chua tra";
					}
					else if (num == 1)
					{
						cout << "Sach da tra";
					}
					else if (num == 2)
					{
						cout << "Lam mat sach";
					}
				}
				else if (mode2 == 4)
				{
					if (num == 0)
					{
						cout << "The bi khoa";
					}
					else if (num == 1)
					{
						cout << "Dang hoat dong";
					}
				}
				GoToXY(x, WhereY());
			}
		}
		// print guild
		if (currentLine >= totalLine) return;
		ShowGuildLine(currentLine);
	}
	int MaxLengthLabel()
	{
		size_t max = 0;
		for(int i = 0; i < this->totalLine; i++)
		{
			if (labels[i].length() > max) max = labels[i].length();
		}
		return max;
	}
	bool IsValidCondition(char& c, int currentLine, string value)
	{
		auto condition = conditions[currentLine];
		if (condition.type == Enum && value.size() >= 1)
			return false;
		// check maxLength
		else if (value.size() >= condition.maxLength)
			return false;
		// check type
		switch (condition.type)
		{
		case WordType::Enum:
		{
			string max = to_string(condition.maxLength);
			return IsNumber(c) && c >= 48 && c < max[0];
		}
		case WordType::Mix:
			return IsMixLetter(c);
			break;
		case WordType::Word_Only:
			return IsLetterOnly(c);
			break;
		case WordType::DateTime: case Year: case WordType::Number_Only:
			return IsNumber(c);
			break;
		case WordType::Name:
			// tu in hoa sau khoang trang (' ')
			if (value.size() != 0 && value.at(value.size() - 1) == ' ')
				c = toupper(c);
			if (!IsName(c)) return false;
			break;
		/*case WordType::Gender:
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
			break;*/
		default: case WordType::All:
			return true;
			break;
		}
		return true;
	}
	vector<int> IsValidOutput()
	{
		vector<int> error;
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
				if ((size_t)stoi(OutputResults[i]) > dateNow.year || (size_t)stoi(OutputResults[i]) < 1000)
					error.push_back(i);
			}
			else if (conditions[i].type == Number_Only)
			{
				char* temp = new char[OutputResults[i].size()];
				StringToCharArray(OutputResults[i], temp);
				int num = atoi(temp);
				if (num == 0)
					error.push_back(i);
				//delete temp;
			}
		}
		return error;
	}
	void ShowGuildLine(int currentLine)
	{
		//if (SizeOfT(Guilds) == 0) return;
		int x = WhereX();
		int y = WhereY();
		//ClearLine(guildLocation.y, guildLocation.x, guildLocation.x + rect.size.width);
		ClearArea(guildLocation.x, guildLocation.y, rect.size.width, 3);
		SetTextColor(TEXT_GUILD_COLOR);
		string* texts = Split(Guilds[currentLine], "\n");
		int temp = rect.size.width / 2 - texts[0].size() / 2 + guildLocation.x;
		for (int i = 0; i < totalLine; i++)
		{
			GoToXY(temp, guildLocation.y + i);
			cout << texts[i];
		}
		delete[] texts;
		SetTextColor(TEXT_INPUT_COLOR);
		GoToXY(x, y);
	}
	// mode = 0: default / mode = 1: enum la gender / mode = 2: enum la trang thai sach 
	// mode = 3: enum la tt muon tra / mode = 4: tt doc gia
	bool Show(int mode = 0, int mode2 = 0)
	{
		border.Draw2Line(BORDER_COLOR);
		//currentLine = 0;
		PrintLabelsTitle(mode, mode2);

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
					ShowGuildLine(currentLine - 1);
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
						ClearArea(guildLocation.x, guildLocation.y, rect.size.width, 3);
						btnOK.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
					}
					else
					{
						ShowGuildLine(currentLine);
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
							ClearForm();
							return true;
							/*string text = "Ban chac chan muon luu thong tin?";
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
							ClearForm();
							ReDraw(mode, mode2);
							SetBGColor(BG_COLOR);
							SetTextColor(WARNING_TEXT_COLOR);
							for (size_t i = 0; i < errorsLength.size(); i++)
							{
								GoToXY(xInputCol, rows[errorsLength[i]] + 1);
								string tempLabel = labels[errorsLength[i]];
								tempLabel.erase(remove(tempLabel.begin(), tempLabel.end(), ':'), tempLabel.end());
								cout << tempLabel << " khong hop le";
							}
							currentLine = errorsLength[0];
							ShowGuildLine(currentLine);
							GoToXY(cols[currentLine], rows[currentLine]);
							ShowPointer();
							//btnOK.Draw(selectColor, textLabelColor);
						}
					}
					// Phim Cancel duoc nhan
					else if (cols[currentLine] > halfWidthForm)
					{
						string text = "Ban chac chan muon huy?";
						auto confirm = CONFIRMDIALOG({ rect.location.x + rect.size.width / 2 - (int)text.length() / 2 - 6,
														rect.location.y + rect.size.height / 2 - 4 });
						confirm.Show(text, Yes_No);
						ClearForm();
						if (confirm.result == No)
						{
							ReDraw(mode, mode2);
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
					ClearArea(guildLocation.x, guildLocation.y, rect.size.width, 3);
					btnOK.Draw(BUTTON_HIGHLIGHT_BG_COLOR, BUTTON_HIGHLIGHT_TEXT_COLOR);
				}
				else
				{
					ShowGuildLine(currentLine);
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
				string text = "Ban chac chan muon thoat?";
				auto confirm = CONFIRMDIALOG({ rect.location.x + rect.size.width / 2 - (int)text.length() / 2 - 6,
												rect.location.y + rect.size.height / 2 - 4 });
				confirm.Show(text, Yes_No);
				ClearForm();
				if (confirm.result == No)
				{
					ReDraw(mode, mode2);
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
			else if (IsAllLetter(inputKey) && currentLine < totalLine && conditions[currentLine].mode == CanChange)
			{
				SetBGColor(BG_COLOR);
				SetTextColor(TEXT_INPUT_COLOR);
				if (IsValidCondition(inputKey, currentLine, OutputResults[currentLine]))
				{
					if (conditions[currentLine].type == Enum && mode != 0)
					{
						int num = inputKey - '0';
						int x = WhereX();
						GoToXY(x + 5, WhereY());
						// gender
						if (mode == 1)
						{
							if (num == 0)
							{
								cout << "Nam";
							}
							else if (num == 1)
							{
								cout << "Nu";
							}
						}
						// trang thai sach
						else if (mode == 2)
						{
							if (num == 0)
							{
								cout << "Cho muon duoc";
							}
							else if (num == 1)
							{
								cout << "Da muon";
							}
							else if (num == 2)
							{
								cout << "Da thanh ly";
							}
						}
						// trang thai muon tra
						else if (mode == 3)
						{
							if (num == 0)
							{
								cout << "Sach chua tra";
							}
							else if (num == 1)
							{
								cout << "Sach da tra";
							}
							else if (num == 2)
							{
								cout << "Lam mat sach";
							}
						}
						else if (mode == 4)
						{
							if (num == 0)
							{
								cout << "Dang hoat dong";
							}
							else if (num == 1)
							{
								cout << "The bi khoa";
							}
						}
						GoToXY(x, WhereY());
					}
					else if (conditions[currentLine].type == Enum2 && mode2 != 0)
					{
						int num = inputKey - '0';
						int x = WhereX();
						GoToXY(x + 5, WhereY());
						// gender
						if (mode2 == 1)
						{
							if (num == 0)
							{
								cout << "Nam";
							}
							else if (num == 1)
							{
								cout << "Nu";
							}
						}
						// trang thai sach
						else if (mode2 == 2)
						{
							if (num == 0)
							{
								cout << "Cho muon duoc";
							}
							else if (num == 1)
							{
								cout << "Da muon";
							}
							else if (num == 2)
							{
								cout << "Da thanh ly";
							}
						}
						// trang thai muon tra
						else if (mode2 == 3)
						{
							if (num == 0)
							{
								cout << "Sach chua tra";
							}
							else if (num == 1)
							{
								cout << "Sach da tra";
							}
							else if (num == 2)
							{
								cout << "Lam mat sach";
							}
						}
						else if (mode2 == 4)
						{
							if (num == 0)
							{
								cout << "Dang hoat dong";
							}
							else if (num == 1)
							{
								cout << "The bi khoa";
							}
						}
						GoToXY(x, WhereY());
					}
					// In hoa chu cai dau tien
					if (OutputResults[currentLine].size() == 0)
					{
						inputKey = toupper(inputKey);
					}
					// viet thuong het neu ko phai ten rieng va sau khoang trang
					else/* if(conditions[currentLine].type != Name)*/
					{
						auto temp = OutputResults[currentLine][OutputResults[currentLine].size() - 1];
						if (temp != ' ')
							inputKey = tolower(inputKey);
					}
					// Tu them '/'
					if (conditions[currentLine].type == DateTime)
					{
						if (OutputResults[currentLine].size() == 2 || OutputResults[currentLine].size() == 5)
						{
							OutputResults[currentLine] += '/';
							cout << '/';
							cols[currentLine]++;
						}
					}
					OutputResults[currentLine] += inputKey;
					cout << inputKey;
					cols[currentLine]++;
					if (conditions[currentLine].type == DateTime)
					{
						if (OutputResults[currentLine].size() == 2 || OutputResults[currentLine].size() == 5)
						{
							OutputResults[currentLine] += '/';
							cout << '/';
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

				if (conditions[currentLine].type == Enum && mode != 0)
				{
					int x = WhereX();
					GoToXY(x + 4, WhereY());
					cout << string(13, ' ');
					GoToXY(x, WhereY());
				}
				else if (conditions[currentLine].type == Enum2 && mode2 != 0)
				{
					int x = WhereX();
					GoToXY(x + 4, WhereY());
					cout << string(13, ' ');
					GoToXY(x, WhereY());
				}

				int lengthCurrentValue = OutputResults[currentLine].length();
				auto end = OutputResults[currentLine].end();
				OutputResults[currentLine].erase(remove(end - 1, end, OutputResults[currentLine][lengthCurrentValue - 1]));
				cols[currentLine]--;

				GoToXY(cols[currentLine], rows[currentLine]);
				cout << string(1, ' ');
				GoToXY(cols[currentLine], rows[currentLine]);
			}

		} while (!_kbhit());
		return true;
	}
	void ReDraw(int mode = 0, int mode2 = 0)
	{
		border.Draw2Line(BORDER_COLOR);

		PrintLabelsTitle(mode, mode2);

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
	void ClearForm()
	{
		SetTextColor(BG_COLOR);
		SetBGColor(BG_COLOR);
		int x = rect.location.x;
		int y = rect.location.y;
		int width = rect.size.width;
		for (int i = 0; i <= rect.size.height + 2; i++)
		{
			GoToXY(x, y + i);
			cout << string(width, char(219));
		}
		SetTextColor(TEXT_INPUT_COLOR);
	}
	void FreeData()
	{
		delete[] OutputResults;
	}
};
