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

// Struct Coordinate

bool operator==( Coordinate& first_coord, Coordinate& second_coord )
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

bool operator!=( Coordinate& first_coord, Coordinate & second_coord )
{
	return !( first_coord == second_coord );
}

// struct Coordinate

// Class Line

Line::Line( Coordinate& line_begins, const int& line_size )
	: lineBegins( line_begins ), lineSize( line_size )
{
}

Line::Line( const Line& line )
	: lineBegins( line.lineBegins ), lineSize( line.lineSize )
{
}

const Coordinate Line::GetLineBegins()
{
	return lineBegins;
}

const int Line::GetLineSize()
{
	return lineSize;
}

// class Line

// Class Figure

Figure::Figure( const FigureType& figure_type )
	: figureType( figure_type )
{
}

FigureType Figure::GetType()
{
	return figureType;
}

void Figure::DisplayFigureInf()
{
	system( "pause" );
}

// class Figure

// Class Square

Square::Square( Coordinate& upper_left_corner, const int& side_length )
	: upperLeftCorner( upper_left_corner ), sideLength( side_length ), Figure( FT_SQARE )
{
}

void Square::DisplayFigureInf()
{
	cout << "Квадрат, длинна стороны - " << sideLength << "; координты левого верхнего угла строка - " << upperLeftCorner.lineNumber 
		  << ", стольбец - " << upperLeftCorner.columnNumber << "." << endl;

	Figure::DisplayFigureInf();
}

// class Square

// Class Circle

Circle::Circle( Coordinate& centre_coord, const int& diameter )
	: centreCoord( centre_coord ) , diametrCircle( diameter ), Figure( FT_CIRCLE )
{
}

void Circle::DisplayFigureInf()
{
	cout << "Круг, диаметр - " << diametrCircle << "; координаты центра строка - " <<  centreCoord.lineNumber << ", столбец - "
		  << centreCoord.columnNumber << "." << endl;

	Figure::DisplayFigureInf();
}

// class circle

// Читаем файл по указанному пути
Matrix ReadFile( const string& file_path )
{
	// Необходим, что бы даже в случае ошибки, усмпешно закрылся поток чтения
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
	// TODO релаизовать адекватный вывод ошибок
	if( !file_strm.fileStrm.is_open() )
		throw;

	// Посимвольно читаем файл, построчно сохраняя его в вектор
	Matrix matrix;
	vector<char> vector; 
	char value = 0;
	while( ( value = static_cast<char>( file_strm.fileStrm.get() ) ) != EOF )
	{
		if( value != '\n' )
		{
			// Сохраняем символ в строку
			vector.push_back( value );
		}
		else
		{
			// строку в матрицу
			matrix.push_back( vector );
			vector.clear();
		}
	}
	
	return matrix;
}

// Внутри изображения ищем линии и сохряняем, отсеиваем шум
vector<Line> FindLines( Matrix& picture )
{
	vector<Line> figure;
	int line_numb = 0;
	// Перебираем строки
	for( Matrix::iterator pic_it = picture.begin(); pic_it != picture.end(); ++pic_it )
	{
		int column_numb = 0;
		int dot_in_row = 0;
		vector<char>& pic_line = *pic_it;
		// Перебираем символы внутри строки
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

// Проверяем не квадрат ли это
bool IsSquare( vector<Line>& figure )
{
	const int height = figure.size();
	const int line_begins = figure[0].GetLineBegins().columnNumber;
	for( vector<Line>::iterator line_it = figure.begin(); line_it != figure.end(); ++line_it )
	{
		const int line_size = line_it->GetLineSize();
		if( line_size < 5 || line_size > 10 )
			return false;

		if( line_it != figure.begin() )
		{
			// Проверяем, что точка начала строки находится в том-же столлбце и размер строк одинаковый
			if( ( line_it->GetLineBegins().columnNumber != line_begins ) || ( line_size != height ) )
			{
				return false;
			}
		}
	}

	return true;
}

// Получить позицию центральной точки линии, с округлением в большую сторону
int CalculateLineMiddle( Line& line )
{
	Coordinate line_begins = line.GetLineBegins();
	return static_cast<int>( line_begins.columnNumber + ceill( ( line.GetLineSize() / 2 ) ) );
}

// Проверяем не круг ли это
bool IsCircle( vector<Line>& figure )
{
	const int line_numb = figure.size();
	const int half_line_numb = static_cast<int>( ceill( line_numb / 2 ) );
	const int middle_colum = CalculateLineMiddle( figure[0] );
	int longest_line = 0;
	int area = 0;
	for( int count = 0; count <= half_line_numb - 1; ++count )
	{
		// Обрабатываем линию с начала
		const int line_size = figure[count].GetLineSize();

		// Проверяем симетричность линий с начала и конца
		if( line_size != figure[line_numb - count - 1].GetLineSize() )
			return false;

		// Проверяем, что линия находится в центре фигуры
		const int line_middle_column_from_beg = CalculateLineMiddle( figure[count] );
		if( line_middle_column_from_beg != middle_colum )
			return false;

		// Проверяем, что линия не больше следующей
		if( line_size > figure[count + 1].GetLineSize() )
			return false;

		// Обрабатываем линию с конца
		const int line_middle_loumn_from_end = CalculateLineMiddle( figure[line_numb - count - 1] );

		// Проверяем, что линия находится в центре фигуры
		if( line_middle_loumn_from_end != middle_colum )
			return false;

		// Проверяем, что линия не больше предыдущей
	   if( line_size > figure[line_numb - count - 2].GetLineSize() )
			return false;

		// Ищем самую длинную линию
		if( line_size > longest_line )
		{
			longest_line = line_size;
		}

		// Вычисляем реальную площадь
		area =+ line_size * 2;
	}

	// Проверяем, что высота равна ширине
	if( longest_line != line_numb )
		return false;

	// Пока, что не актуально введу когда появятся верятность правильного распознавания
   /*const int real_area = ceil( ( 3,14 * ( longest_line * longest_line ) ) / 4 );
		return false;*/

	return true;
}

// Создать квадрат
shared_ptr<Figure> CreateSquare( vector<Line> figure )
{
	Coordinate upper_left_corner( figure[0].GetLineBegins() );
	const int side_length = figure.size();
	shared_ptr<Figure> square_ptr( new Square( upper_left_corner, side_length ));
	return square_ptr;
}

// Создать круг
shared_ptr<Figure> CreateCIrcle( vector<Line> figure )
{
	const int figure_center_line = static_cast<int>( ceil( figure.size() / 2 ) );
	Coordinate centre_coord;
	centre_coord.lineNumber = figure[figure_center_line].GetLineBegins().lineNumber;
	centre_coord.columnNumber = CalculateLineMiddle( figure[figure_center_line] );
	const int diameter = figure.size();
	shared_ptr<Figure> circle_ptr( new Circle( centre_coord, diameter ) );
	return circle_ptr;
}

// Идентифицируем фугуру по изображения
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
	setlocale( LC_ALL, "Russian" );

	string file_path("");
	cout << "Пожалуйста введите путь к файлу." << endl;
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
			cout << "Неизветсная фигруа." << endl;
			system( "pause" );
		}
	}
	catch( ... )
	{
		cout << "Призошла неизвестная ошибка" << endl;
		system( "pause" );
	}

   return 0;
}