/******************************************************************************************
Date.hpp:
	Copyright (c) Bit Software, Inc.(2013), All rights reserved.

Purpose:
	������ʵ��һ��������

�Ѷȣ�***

Author:
	xxx

Created Time:
	2015-4-26
******************************************************************************************/

class Date
{
public:
	Date (int year = 1900, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		// ��������������ǷǷ�ʱ�䣬���ʼ��Ϊ1900-1-1
		if (CheckIsInvaildDate())
		{
			year = 1900;
			month = 1;
			day = 1;
		}
	}

	Date (const Date& d)
		:_year(d._year)
		,_month(d._month)
		,_day(d._day)
	{}

	Date& operator= (const Date& d)
	{
		if (this != &d)
		{
			this->_year = d._year;
			this->_month = d._month;
			this->_day = d._day;
		}

		return *this;
	}

	// ���ʱ���Ƿ���Ч
	bool CheckIsInvaildDate ()
	{
		if (_year < 1
			|| (_month < 1 || _month > 12)
			|| (_day < 1   || _day > DateOfMonth(_year, _month)))
		{  
			return true;
		}

		return false;
	}

	void Display ()
	{
		cout<<_year<<"-"<<_month<<"-"<<_day<<endl<<endl;
	}

public:
	// �����ڷǷ�
	static int DateOfMonth (int year, int month)
	{
		if (year < 1 || month < 1 || month > 12)
			return 0;

		static int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

		// �����2����29��
		monthDays[2] += IsLeapYear(year);

		return monthDays[month];
	}

	// �ж��Ƿ�Ϊ���ꡣ
	static bool IsLeapYear (int year)
	{
		// ��˼��Ϊʲô�������������㣬����ֱ����year % 4 == 0�������ꣿ
		if ((year % 4 == 0 && year % 100 != 0)
			|| year % 400 == 0)
		{
			return true;
		}

		return false;
	}
public:
	bool operator == (const Date& d)
	{
		return _year == d._year
			&& _month == d._month
			&& _day == d._day;
	}

	bool operator != (const Date& d)
	{
		return !(*this == d);
	}

	bool operator > (const Date& d)
	{
		if(_year > d._year)
			return true;

		if (_year == d._year)
		{
			if (_month > d._month)
			{
				return true;
			}

			if (_month == d._month)
			{
				if (_day > d._day)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool operator >= (const Date& d)
	{
		return *this > d || *this == d;
	}

	bool operator < (const Date& d)
	{
		return !(*this >= d);
	}

	bool operator <= (const Date& d)
	{
		return !(*this > d);
	}

	// ������ת��Ϊ��ȷ������
	void _ToCrrectDate()
	{
		while(_day <= 0)
		{
			if (_month == 1)
			{
				_year--;
				_month = 12;
			}
			else
			{
				_month--;
			}

			_day += DateOfMonth (_year, _month);
		}

		while (_day > DateOfMonth(_year, _month))
		{
			_day -= DateOfMonth (_year, _month);

			if (_month == 12)
			{
				_year++;
				_month = 1;
			}
			else
			{
				_month++;
			}
		}
	}

	//
	// ����һ�����ڼӼ�һ�������Ժ�����ڡ�
	//

	Date operator+(int day)
	{
		Date d(*this);
		d._day += day;
		d._ToCrrectDate();
		return d;
	}

	Date operator-(int day)
	{
		Date d(*this);
		d._day -= day;
		d._ToCrrectDate();
		return d;
	}

	Date& operator-=(int day)
	{
		this->_day -= day;
		this->_ToCrrectDate();
		return *this;
	}

	Date& operator+=(int day)
	{
		this->_day += day;
		this->_ToCrrectDate();
		return *this;
	}

	 // ǰ��++
	const Date& operator++()
	{
		*this += 1;
		return *this;
	}

	// ����++
	Date operator++(int)
	{
		Date tmp(*this);
		*this += 1;
		return tmp;
	}

	// ǰ��--
	const Date& operator--()
	{
		*this -= 1;
		return *this;
	}

	 // ����--
	Date operator--(int)
	{
		Date tmp(*this);
		*this -= 1;
		return tmp;
	}

	//
	// �����������û������
	// ����������������Ժ�Ĳ������
	//

	int operator-(const Date& d)
	{
		int flag = 1;
		Date x1 = *this, x2 = d;
		if (x1 < x2)
		{
			flag = -1;
			x1 = d;
			x2 = *this;
		}
		
		int gapDays = 0;
		while (x1 != x2)
		{
			++x2;
			gapDays++;
		}

		return gapDays*flag;
	}

	friend istream& operator>>(istream& in, Date& d);
	friend ostream& operator<<(ostream& out, Date& d);
private:
	int _year;
	int _month;
	int _day;
};

istream& operator>>(istream& in, Date& d)
{
	cout<<"�������������ڵ���-��-��"<<endl;
	in>>d._year;
	in>>d._month;
	in>>d._day;

	return in;
}

ostream& operator<<(ostream& out, Date& d)
{
	out<<d._year<<"-";
	out<<d._month<<"-";
	out<<d._day;

	return out;
}

void PromptInfo()
{
	cout<<"==============���ڼ�����================"<<endl;
	cout<<"1.�ƺ��������"<<endl;
	cout<<"2.�������ڲ�"<<endl;
	cout<<"0.�˳�"<<endl;
	cout<<"========================================"<<endl;
}

void TestDate ()
{
	Date d1, d2;
	int option, days;
	do {
		PromptInfo();
		cin>>option;

		switch(option)
		{
		case 0:
			break;
		case 1:
			cin>>d1;
			if (d1.CheckIsInvaildDate())
			{
				cout<<"�������ڷǷ���"<<endl;
				break;
			}
			cout<<"���������ƺ������"<<endl;
			cin>>days;
			d1+=days;
			cout<<d1<<endl;
			break;
		case 2:
			cin>>d1;
			if (d1.CheckIsInvaildDate())
			{
				cout<<"�������ڷǷ���"<<endl;
				break;
			}
			cin>>d2;
			if (d2.CheckIsInvaildDate())
			{
				cout<<"�������ڷǷ���"<<endl;
				break;
			}
			days = d1 - d2;
			cout<<"��������:"<<days<<endl;
			break;
		default:
			cout<<"ѡ�����������ѡ��"<<endl;
			break;
		}
	}while(option != 0);
}