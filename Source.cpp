#include <iostream>
#include <bitset>
#include <locale>
#include <locale.h>
#include <clocale>

using namespace std;

bool CheckAddress(char* ip_)
{
	int points = 0, // ���������� �����
		numbers = 0; // �������� ������
	char* buff; // ����� ��� ������ ������
	buff = new char[3];
	for (int i = 0; ip_[i] != '\0'; i++)
	{ // ��� ������ IP-������
		if (ip_[i] <= '9' && ip_[i] >= '0') // ���� �����
		{
			if (numbers > 3) return false;
			//���� ������ ���� ����� � ������ � ������
			buff[numbers++] = ip_[i];
			//����������� � �����
		}
		else
			if (ip_[i] == '.') // ���� �����
			{
				if (atoi(buff) > 255)
					// ��������� �������� ������
					return false;
				if (numbers == 0)
					//���� ����� ��� - ������
					return false;
				numbers = 0;
				points++;
				delete[]buff;
				buff = new char[3];
			}
			else return false;
	}
	if (points != 3)
		// ���� ���������� ����� � IP-������ �� 3 - ������
		return false;
	if (numbers == 0 || numbers > 3)
		return false;
	return true;
}

unsigned long CharToLong(char* ip_)
{
	unsigned long out = 0;//����� ��� IP-������
	char* buff;
	buff = new char[3];
	//����� ��� �������� ������ ������
	for (int i = 0, j = 0, k = 0; ip_[i] != '\0'; i++, j++)
	{
		if (ip_[i] != '.') //���� �� �����
			buff[j] = ip_[i]; // �������� ������ � �����
		if (ip_[i] == '.' || ip_[i + 1] == '\0')
		{
			// ���� ��������� ����� ��� ���������
			out <<= 8; //�������� ����� �� 8 ���
			if (atoi(buff) > 255)
				return NULL;
			// �c�� ����� ������ 255 � ������
			out += (unsigned long)atoi(buff);
			//������������� � ��������
			//� ����� IP-������
			k++;
			j = -1;
			delete[]buff;
			buff = new char[3];
		}
	}
	return out;
}

bool CheckMask(int mask)
{

	std::string binary = std::bitset<32>(mask).to_string(); //to binary
	/*std::cout � binary � "\n";*/

	if (binary[0] == '0')
	{
		return false;
	}
	if (binary[0] == '1')
	{
		for (int i = 1; i <= binary.length() - 2; i++)
		{
			if (binary[i] == '0')
			{
				for (int k = i; k <= binary.length() - (i - 1); k++)
				{
					if (binary[k] == '1')
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

void inTwo(unsigned long number)
{
	int bin, mod;
	int mass[40];
	int mass2[40];
	int s = 0;

	while (number != 1)
	{
		if (number % 2 == 0)
		{
			number /= 2;
			mass[s] = 0;
			s++;
		}
		else
		{
			number -= 1;
			number /= 2;
			mass[s] = 1;
			s++;
		}
	}
	mass[s] = 1;
	s++;
	if (s != 32)
	{
		while (s != 32)
		{
			mass[s] = 0;
			s++;
		}
	}
	for (int i = s - 1, j = 0; i >= 0; i--, j++)
	{
		mass2[j] = mass[i];
	}
	int dir = 7;
	int num = 0;
	int point = 0;
	for (int i = 0; i < s; i++)
	{
		num += mass2[i] * pow(2, dir);
		dir--;
		if (dir == -1)
		{
			point++;
			if (point == 4)
				cout << num;
			else
				cout << num << '.';
			dir = 7;
			num = 0;
		}
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "rus");
	unsigned long ip, mask, host, subnet, broadcast;
	char* ip_, * mask_;
	bool flag = true;
	ip_ = new char[16];
	mask_ = new char[16];
	do
	{
		if (!flag) cout << "������� ����� �����!" << endl;
		cout << "IP: ";
		cin >> ip_;
	} while (!(flag = CheckAddress(ip_)));
	ip = CharToLong(ip_);
	flag = true;
	do
	{
		if (!flag) cout << "������������ �����!" << endl;
		flag = true;
		do
		{
			if (!flag) cout << "������� ������� �����!" << endl;
			cout << "�����: ";
			cin >> mask_;
		} while (!(flag = CheckAddress(mask_)));
		mask = CharToLong(mask_);
	} while (!(flag = CheckMask(mask)));

	subnet = ip & mask;
	host = ip & ~mask;
	broadcast = ip & mask | ~mask;

	cout << "ID �������: ";  inTwo(subnet);
	cout << "ID �����: "; inTwo(host);
	cout << "���������: "; inTwo(broadcast);
}