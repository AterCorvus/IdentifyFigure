#pragma once
#include <vector>

using namespace std;

// ������������ ����� �� �������
struct Coordinate
{
		// ����� ������ ��� ������
		int lineNumber;
		// ����� ������� ��� ������
		int columnNumber;
};

// ����������� ��������� ���� ���������
bool operator==( Coordinate & first_coord, Coordinate & second_coord );

// ����������� ����������� ���� ���������
bool operator!=( Coordinate & first_coord, Coordinate & second_coord );

// �������������� ����� ����������� (������)
class Line
{
	public:
								 Line( Coordinate& line_begins, const int& line_size );
								 Line( const Line& line );

								 // �������� ���������� ������ �����
		const Coordinate   GetLineBegins();
								 // �������� ������ �����
		const			 int   GetLineSize();

	private:
								 // ���������� ������ �����
				Coordinate   lineBegins;
								 // ������ �����
						 int   lineSize;

								 Line();
						Line&  operator=( const Line& );
};

// ��� ������
enum FigureType
{
	FT_SQARE, /*�������*/
	FT_CIRCLE, /*����*/
	FT_MAX /*��� ������� ����������*/
};

// ����������� �����, ��������������� ��� ���������� ������� "�������"(Factory)
class Figure
{
	public:
									// �������� ��� ������ 
				  FigureType   GetType();
									// ���������� � ��������� ������ ���������� ��������� � ������
		virtual		  void   DisplayFigureInf();

	protected:
									// ��� ������
				  FigureType   figureType;

									Figure( const FigureType& figure_type );

	private:
									Figure();
		  						   Figure( const Figure& );
					   Figure&  operator=( const Figure& );
};

class Square : public Figure
{
	public:
	  					  Square( Coordinate& upper_left_corner, const int& side_length );

						  // ��. MyParent
				 void   DisplayFigureInf();

	private:
						  // ���������� ������ �������� ����
		 Coordinate   upperLeftCorner;
						  // ������ �������
				  int   sideLength;
};

class Circle : public Figure
{
	public:
						 Circle( Coordinate& centre_coord, const int& diameter );

						 // ��. MyParent
				void   DisplayFigureInf();

	private:
						 // ���������� ������
		Coordinate   centreCoord;
						 // ������� �����
				 int   diametrCircle;
};