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
bool operator==( Coordinate & first_coord, Coordinate & second_coord );

// Определение неравенства двух координат
bool operator!=( Coordinate & first_coord, Coordinate & second_coord );

// Горизонтальная линия изображения (фигуры)
class Line
{
	public:
								 Line( Coordinate& line_begins, const int& line_size );
								 Line( const Line& line );

								 // Получить координату начала линии
		const Coordinate   GetLineBegins();
								 // Получить длинну линии
		const			 int   GetLineSize();

	private:
								 // Координата начала линии
				Coordinate   lineBegins;
								 // Длинна линии
						 int   lineSize;

								 Line();
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
		virtual		  void   DisplayFigureInf();

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
	  					  Square( Coordinate& upper_left_corner, const int& side_length );

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
						 Circle( Coordinate& centre_coord, const int& diameter );

						 // см. MyParent
				void   DisplayFigureInf();

	private:
						 // Координата центра
		Coordinate   centreCoord;
						 // Диаметр круга
				 int   diametrCircle;
};