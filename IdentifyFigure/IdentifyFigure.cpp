// Identify Figure.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include "IdentifyFigure.h"

#define Matrix vector<vector<char>>

// Struct Coordinate

bool operator==( Coordinate & first_coord, Coordinate & second_coord )
{
	if( ( first_coord.columnNumber == second_coord.columnNumber ) && ( first_coord.lineNumber == second_coord.lineNumber ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator!=( Coordinate & first_coord, Coordinate & second_coord )
{
	return !( first_coord == second_coord );
}

// struct Coordinate

// Class Line

Line::Line( const Coordinate& line_begins, const int& line_size )
	: lineBegins( line_begins ), lineSize( line_size )
{
}

Coordinate Line::GetLineBegins()
{
	return lineBegins;
}

int Line::GetLineSize()
{
	return lineSize;
}

// class Line

// Class Figure

// ������ ���� �� ���������� ����
Matrix ReadFile( const string& file_path )
{
	// ���������, ��� �� ���� � ������ ������, �������� �������� ����� ������
	class File_Strm
	{
		public:
			ifstream fileStrm;

			File_Strm( const string& file_path )
				: fileStrm( file_path )
			{
			}

		  ~File_Strm()
		   {
			   fileStrm.close();
		   }
	};

	File_Strm file_strm( file_path );
	// TODO ����������� ���������� ����� ������
	if( !file_strm.fileStrm.is_open() )
		throw;

	// ����������� ������ ����, ��������� �������� ��� � ������
	Matrix matrix;
	vector<char> vector; 
	char value = 0;
	while( ( value = static_cast<char>( file_strm.fileStrm.get() ) ) != EOF )
	{
		if( value != '\n' )
		{
			// ��������� ������ � ������
			vector.push_back( value );
		}
		else
		{
			// ������ � �������
			matrix.push_back( vector );
		}
	}
	
	return matrix;
}

// ������ ����������� ���� ����� � ���������, ��������� ���
vector<Line> FindLines( Matrix& picture )
{
	vector<Line> figure;
	int line_numb = 0;
	// ���������� ������
	for( Matrix::iterator pic_it = picture.begin(); pic_it != picture.end(); ++pic_it )
	{
		int column_numb = 0;
		int dot_in_row = 0;
		vector<char>& pic_line = *pic_it;
		// ���������� ������� ������ ������
		for( vector<char>::iterator pic_line_it = pic_line.begin(); pic_line_it != pic_line.end(); ++pic_line_it )
		{
			if( *pic_line_it == '1' )
			{
				++dot_in_row;
			}
			else if( *pic_line_it == '0' )
			{
				if( dot_in_row > 1 )
				{
					Coordinate line_begins;
					line_begins.columnNumber = column_numb - dot_in_row;
					line_begins.lineNumber = line_numb;
					Line figure_line( line_begins, dot_in_row );
					figure.push_back( figure_line );
				}

				dot_in_row = 0;
			}
			++column_numb;
		}
		++line_numb;
	}

	return figure;
}

// ��������� �� ������� �� ���
bool IsSquare( vector<Line>& figure )
{
	int count = 0;
	int size = figure.size();
	for( vector<Line>::iterator line_it = figure.begin(); line_it != figure.end(); ++line_it )
	{
		const int line_size = line_it->GetLineSize;
		if( line_size > 5 || line_size < 10 )
			return false;

		if( line_it != figure.begin() )
		{
			if( ( line_it->GetLineBegins() != figure[count - 1].GetLineBegins() ) || ( line_size != figure[count - 1].GetLineSize() ) )
			{
				return false;
			}
		}
		++count;
	}

	return true;
}

// �������� ������� ����������� ����� �����, � ����������� � ������� �������
int CalculateLineMiddle( Line& line )
{
	Coordinate first_line_begins = line.GetLineBegins();
	return first_line_begins.columnNumber + ceill( ( line.GetLineSize() / 2 ) - 1 );
}

// ��������� �� ���� �� ���
bool IsCircle( vector<Line>& figure )
{
	const int line_numb = figure.size();
	const int half_line_numb = ceill( line_numb / 2 );
	const int middle_colum = CalculateLineMiddle( figure[0] );
	int longest_line = 0;
	int area = 0;
	for( int count = 0; count <= half_line_numb; ++count )
	{
		// ������������ ����� � ������
		const int line_size = figure[count].GetLineSize();

		// ��������� ������������� ����� � ������ � �����
		if( line_size != figure[line_numb - count - 1].GetLineSize(); )
			return false;

		// ���������, ��� ����� ��������� � ������ ������
		const int line_middle_column_from_beg = CalculateLineMiddle( figure[count] );
		if( line_middle_column_from_beg != middle_colum )
			return false;

		// ���������, ��� ����� ������ ��� ����� ���������
		if( line_size >= figure[count + 1].GetLineSize() )
			return false;

		// ������������ ����� � �����
		const int line_middle_loumn_from_end = CalculateLineMiddle( figure[line_numb - count - 1] );

		// ���������, ��� ����� ��������� � ������ ������
		if( line_middle_loumn_from_end != middle_colum )
			return false;

		// ���������, ��� �� ������ ��� ����� ����������
	   if( line_size <= figure[line_numb - count - 2].GetLineSize() )
			return false;

		// ���� ����� ������� �����
		if( line_size > longest_line )
		{
			longest_line = line_size;
		}

		// ��������� �������� �������
		area =+ line_size * 2;
	}

	// ���������, ��� ������ ����� ������
	if( longest_line != line_numb )
		return false;

	// ����, ��� �� ��������� ����� ����� �������� ���������� ����������� �������������
   /*const int real_area = ceil( ( 3,14 * ( longest_line * longest_line ) ) / 4 );
		return false;*/

	return true;
}

// ������� �������
shared_ptr<Figure> CreateSquare( vector<Line> figure )
{
	Coordinate upper_left_corner( figure[0].GetLineBegins() );
	const int side_length = figure.size();
	shared_ptr<Figure> square_ptr = new Square( upper_left_corner, side_length );
	return square_ptr;
}

// ������� ����
shared_ptr<Figure> CreateCIrcle( vector<Line> figure )
{
	const int center_line = ceil( figure.size() / 2 );
	const int center_column = CalculateLineMiddle( figure[center_line] );
	Coordinate centre_coord;
	centre_coord.lineNumber = center_line;
	centre_coord.columnNumber = center_column;
	const int diameter = figure.size();
	shared_ptr<Figure> circle_ptr = new Circle( centre_coord, diameter );
	return circle_ptr;
}

// �������������� ������ �� �����������
shared_ptr<Figure> IdentifyFigure( Matrix& picture )
{
	shared_ptr<Figure> figure_ptr;
	vector<Line> figure = FindLines( picture );
	const int size = figure.size();
	if( size < 5 || size > 10 )
		return nullptr;

	if( IsSquare( figure ) )
	{
		figure_ptr = CreateSquare( figure );
		return figure_ptr;
	}
	else if( IsCircle( figure ) )
	{
		figure_ptr = CreateCIrcle( figure );
		return figure_ptr;
	}
	else
	{
		return nullptr;
	}
}

int main()
{
	string file_path("");
	cout << "Please enter path to a file" << endl;
	cin >> file_path;
	try
	{
		Matrix picture = ReadFile( file_path );
		shared_ptr<Figure> figure = IdentifyFigure( picture );
		if( figure != nullptr )
		{
			figure->DisplayFigureInf();
		}
		else
		{
			cout << "����������� ������.";
		}
	}
	catch( ... )
	{
		cout << "�������� ����������� ������";
	}

   return 0;
}