#include "StackApplication.h"

void algorithm::StackApplication::CheckMatching(const char* filename)
{
	cout << '[' << filename << ']' << ": ���� ��ȣ ���� �˻�" << endl;
	ifstream ifs(filename);

	if (!ifs.is_open())
	{
		cout << "������ ���µ� �����߽��ϴ�." << endl;
		return;
	}

	bkDS::Stack<char> stack;
	unsigned int nLine = 0;
	unsigned int nChar = 0;

	while (!ifs.eof())
	{
		char c = ifs.get();
		//new line check
		if (c == '\n')
		{
			nLine++;
			continue;
		}
		else
		{
			nChar++;
		}

		//single quotation marks check
		if (c == '\'')
		{
			c = ifs.get();
			while (!(c == '\''))
			{
				if (ifs.eof())
				{
					CheckMatchingErrMsg(nLine, nChar, eCheckMatchingError::Missing_Single_Quotation_Mark);
					ifs.close();
					return;
				}

				if (c == '\n')
				{
					nLine++;
				}
				else
				{
					nChar++;
				}
				c = ifs.get();
			}
			nChar++;
			continue;
		}

		//double quotation marks check
		if (c == '\"')
		{
			c = ifs.get();
			while (!(c == '\"'))
			{
				if (ifs.eof())
				{
					CheckMatchingErrMsg(nLine, nChar, eCheckMatchingError::Missing_Double_Quotation_Mark);
					ifs.close();
					return;
				}

				if (c == '\n')
				{
					nLine++;
				}
				else
				{
					nChar++;
				}
				c = ifs.get();
			}
			nChar++;
			continue;
		}

		//Comment
		if (c == '/')
		{
			c = ifs.get();
			if (c == '\n')
			{
				nLine++;
				continue;
			}
			else
			{
				nChar++;
			}

			if (c == '/')
			{
				while (!(c == '\n'))
				{
					c = ifs.get();
					if (ifs.eof())
					{
						ifs.close();
						return;
					}
					nChar++;
				}
				continue;
			}

			if (c == '*')
			{
				while (true)
				{
					c = ifs.get();
					if (ifs.eof())
					{
						ifs.close();
						return;
					}
					nChar++;
					if (c == '*')
					{
						c = ifs.get();
						if (ifs.eof())
						{
							ifs.close();
							return;
						}
						nChar++;
						if (c == '/')
						{
							break;
						}
					}
				}
				continue;
			}
		}
		
		//bracket check
		switch (c)
		{
		case '[':
			stack.Push(c);
			break;

		case '{':
			stack.Push(c);
			break;

		case '(':
			stack.Push(c);
			break;

		default:
			break;
		}

		switch (c)
		{
		case ']':
			if (stack.IsEmpty() || !(stack.Peek() == '['))
			{
				CheckMatchingErrMsg(nLine, nChar, eCheckMatchingError::Missing_Bracket);
				ifs.close();
				return;
			}
			else
			{
				stack.Pop();
			}
			break;

		case '}':
			if (stack.IsEmpty() || !(stack.Peek() == '{'))
			{
				CheckMatchingErrMsg(nLine, nChar, eCheckMatchingError::Missing_Bracket);
				ifs.close();
				return;
			}
			else
			{
				stack.Pop();
			}
			break;

		case ')':
			if (stack.IsEmpty() || !(stack.Peek() == '('))
			{
				CheckMatchingErrMsg(nLine, nChar, eCheckMatchingError::Missing_Bracket);
				ifs.close();
				return;
			}
			else
			{
				stack.Pop();
			}
			break;

		default:
			break;
		}
	}

	cout << "���� �̰���" << endl << endl;
	ifs.close();
}

void algorithm::StackApplication::CheckMatchingErrMsg(const unsigned int nLine, const unsigned int nChar, const eCheckMatchingError err)
{
	switch (err)
	{
	case eCheckMatchingError::Missing_Bracket:
		cout << "��ȣ ����ġ �߻�." << endl;
		break;

	case eCheckMatchingError::Missing_Single_Quotation_Mark:
		cout << "���� ����ǥ�� ã�� ���߽��ϴ�." << endl;
		break;

	case eCheckMatchingError::Missing_Double_Quotation_Mark:
		cout << "ū ����ǥ�� ã�� ���߽��ϴ�." << endl;
		break;

	default:
		break;
	}

	cout << nLine << "��° �� " << nChar << "��° ���ڿ� ���� �߻�" << endl << endl;
}
