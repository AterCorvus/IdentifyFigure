// Identify Figure.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <math.h>
#include "IdentifyFigure.h"

#define Matrix vector<vector<char>>

// Читаем файл по указанному пути
Matrix ReadFile( const string& file_path )
{
	// Необходим, что-бы даже в случае ошибки, усмпешно закрыть поток чтения
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
	if( !file_strm.fileStrm.is_open() )
		throw;

	// посимвольно читаем файл, построчно сохраняя его в вектор
	Matrix matrix;
	vector<char> vector; 
	char value = 0;
	while( ( value = static_cast<char>( file_strm.fileStrm.get() ) ) != EOF )
	{
		if( value != '\n' )
		{
			vector.push_back( value );
		}
		else
		{
			matrix.push_back( vector );
		}
	}
	
	return matrix;
}

// в изображении ищем фигуру и сохраяем в формате линий, отсеиваем шум
vector<Line> FindLines( Matrix& picture )
{
	vector<Line> figure;
	int line_numb = 0;
	for( Matrix::iterator pic_it = picture.begin(); pic_it != picture.end(); ++pic_it )
	{
		int column_numb = 0;
		int dot_in_row = 0;
		vector<char>& pic_line = *pic_it;
		for( vector<char>::iterator pic_line_it = pic_line.begin(); pic_line_it != pic_line.end(); ++pic_line_it )
		{
			if( *pic_line_it == '1' )
			{
				++dot_in_row;
			}
			else if( *pic_line_it == '0' && dot_in_row > 1 )
			{
				Coordinate line_begins;
				line_begins.columnNumber = column_numb - dot_in_row;
				line_begins.lineNumber = line_numb;
				Line figure_line( line_begins, dot_in_row );
				figure.push_back( figure_line );
			}
			++column_numb;
		}
		++line_numb;
	}

	return figure;
}

// Проверяем не квадрат ли это
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

int GetLineMiddle( Line& line )
{
	Coordinate first_line_begins = line.GetLineBegins();
	const int middle_column = first_line_begins.columnNumber + ceill( ( line.GetLineSize() / 2 ) - 1 );
	return middle_column;
}

// Проверяем не круг ли это
bool IsCircle( vector<Line>& figure )
{
	const int line_numb = figure.size();
	const int half_line_numb = ceill( line_numb / 2 );
	const int middle_colum = GetLineMiddle( figure[0] );
	int longest_line = 0;
	int area = 0;
	for( int count = 0; count <= half_line_numb; ++count )
	{
		// обрабатываем линию с начала
		const int line_size = figure[count].GetLineSize();
		if( line_size != figure[line_numb - count - 1].GetLineSize(); )
			return false;

		const int line_middle_column_from_beg = GetLineMiddle( figure[count] );
		if( line_middle_column_from_beg != middle_colum )
			return false;

		if( line_size >= figure[count + 1].GetLineSize() )
			return false;

		// обрабатываем линию с конца
		const int line_middle_loumn_from_end = GetLineMiddle( figure[line_numb - count - 1] );
		if( line_middle_loumn_from_end != middle_colum )
			return false;

	   if( line_size <= figure[line_numb - count - 2].GetLineSize() )
			return false;

		// сравниваем обе
		if( line_size > longest_line )
		{
			longest_line = line_size;
		}

		area =+ line_size;
	}
	if( area != ceil( ( 3,14 * ( longest_line * longest_line ) ) / 4 ))
		return false;

	return false;
}

// Идентифицируем фугуру по изображения
shared_ptr<Figure> IdentifyFigure( Matrix& picture )
{
	shared_ptr<Figure> figure_ptr;
	vector<Line> figure = FindLines( picture );
	const int size = figure.size();
	if( size < 5 || size > 10 )
		return nullptr;

	if( IsSquare )
	{
		figure_ptr = new Sqare();
		return figure_ptr;
	}
	else if( IsCircle )
	{
		figure_ptr = new Circle();
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
	}
	catch( ... )
	{
		cout << "Призошла неизвестная ошибка";
	}

   return 0;
}