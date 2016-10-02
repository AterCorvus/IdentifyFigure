#pragma once
#include <vector>

using namespace std;

// Определенная точка на матрице
struct Coordinate
{
		// Номер строки или высота
		int lineNumber;
		// Номер столбца или широта
		int columnNumber;
};

// Определение равенства двух координат
bool operator==( Coordinate const & first_coord, Coordinate const & second_coord );

// Определение неравенства двух координат
bool operator!=( Coordinate const & first_coord, Coordinate const & second_coord );

// Горизонтальная линия изображения (фигуры)
class Line
{
	public:
						 Line( const Coordinate& line_begins, const int& line_size );

						 // Получить координату начала линии
		Coordinate   GetLineBegins();
						 // Получить длинну линии
				 int   GetLineSize();

	private:
						 // Координата начала линии
		Coordinate   lineBegins;
						 // Длинна линии
				 int   lineSize;

						 Line();
						 Line( const Line& );
				Line&  operator=( const Line& );
};

// Тип фигуры
enum FigureType
{
	FT_SQARE, /*Квадрат*/
	FT_CIRCLE, /*Круг*/
	FT_MAX /*Тип фигруры неизвестен*/
};

// Абстрактный класс, предназначенный для реализации патерна "Фабрика"(Factory)
class Figure
{
	public:
									// Получить тип фигуры 
				  FigureType   GetType();
									// Отобразить в командной строке приложения иформацию о фигуре
				virtual void   DisplayFigureInf();

	protected:
									// Тип фигуры
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
	  					  Square( const Coordinate& upper_left_corner, const int& side_length );

						  // см. MyParent
				 void   DisplayFigureInf();

	private:
						  // Координата левого верхнего угла
		 Coordinate   upperLeftCorner;
						  // Длинна стороны
				  int   sideLength;
};

class Circle : public Figure
{
	public:
						 Circle( const Coordinate& centre_coord, const int& diameter );

						 // см. MyParent
				void   DisplayFigureInf();

	private:
						 // Координата центра
		Coordinate   centreCoord;
						 // Диаметр круга
				 int   diametrCircle;
};
