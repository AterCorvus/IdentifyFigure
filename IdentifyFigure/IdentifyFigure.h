#pragma once
#include <vector>

using namespace std;

struct Coordinate
{
		int lineNumber;
		int columnNumber;
};

bool operator==( Coordinate const & first_coord, Coordinate const & second_coord );

bool operator!=( Coordinate const & first_coord, Coordinate const & second_coord );

class Line
{
	public:
		Line( const Coordinate& line_begins, const int& line_size );
		Coordinate GetLineBegins();
		int GetLineSize();

	private:
		Coordinate lineBegins;
		int lineSize;

		Line( const Line& );
		Line operator=( const Line& );
};

enum FigureType
{
	FT_SQARE,
	FT_CIRCLE,
	FT_MAX
};

class Figure
{
	public:
						 Figure(  );

		FigureType   GetType();
		
	private:
					    Figure();
		  			    Figure( const Figure& );
			 Figure&  operator=( const Figure& );
};

class Circle : public Figure
{

};

class Sqare : public Figure
{

};
