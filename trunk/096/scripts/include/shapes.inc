/*
 * $Id*
 *
 */
 
use uo;
use os;

/*
 * GetCoordsInSquare(mid_x, mid_y, radius)
 *
 * Purpose
 * Retrieves the coordinates in the area of a square.
 *
 * Parameters
 * mid_x:	X coordinate of the middle of the square.
 * mid_y:	Y coordinate of the middle of the square.
 * radius:	Size of the square
 *
 * Return value
 * Array of structs (.x, .y)
 * 
 */
function GetCoordsInSquare(mid_x, mid_y, radius)
	var x_row := mid_x-radius;
	var y_col := mid_y-radius;
	var stop_x := mid_x+radius;
	var stop_y := mid_y+radius;

	var point_list := array{};
	var coord := struct;
	coord.+x;
	coord.+y;

	for ( x_row:=(mid_x-radius); x_row<=stop_x; x_row:=x_row+1 )
		sleepms(2);
		for ( y_col:=(mid_y-radius); y_col<=stop_y; y_col:=y_col+1 )
			coord.x := x_row;
			coord.y := y_col;
			point_list.Append(coord);
			sleepms(2);
		endfor
	endfor
	
	return point_list;
endfunction

/*
 * GetCoordsInRect(x1, y1, x2, y2)
 *
 * Purpose
 * Retrieves the coordinates in the area of a rectangle.
 *
 * Parameters
 * x1:	Upper left X coordinate
 * y1:	Upper left Y coordinate
 * x2:	Lower right X coordinate
 * y2:	Lower right Y coordinate
 *
 * Return value
 * Array of structs (.x, .y)
 * 
 */
function GetCoordsInRect(x1, y1, x2, y2)
	var point_list := array{};
	var coord := struct;
	coord.+x;
	coord.+y;
	
	if ( x2 < x1 )
		return error;
	elseif ( y2 < y1 )
		return error;
	endif

	for ( x1; x1<=x2; x1:=x1+1 )
		for ( y1; y1<=y2; y1:=y1+1 )
			coord.x := x1;
			coord.y := y1;
			point_list.Append(coord);
			sleepms(2);
		endfor
		sleepms(2);
	endfor

	return point_list;
endfunction

/*
 * GetCoordsInCircle(mid_x, mid_y, radius)
 *
 * Purpose
 * Retrieves the coordinates in the area of a circle.
 *
 * Parameters
 * mid_x:	X coordinate of the middle of the square.
 * mid_y:	Y coordinate of the middle of the square.
 * radius:	Size of the circle
 *
 * Return value
 * Array of structs (.x, .y)
 * 
 */
function GetCoordsInCircle(mid_x, mid_y, radius)
	mid_x := mid_x;
	mid_y := mid_y;
	radius := radius;
	return error{"errortext":="Hasn't been coded yet!"};
endfunction
