/** $Id$
 *
 * Purpose
 * Provide various functions for array handling.
 *
 */
use basic;
use math;
use os;
use uo;

/*
 * GetArrayRange(the_array, start, stop)
 * 
 * Purpose
 * Retrieves a range from the array.
 *
 * Parameters
 * the_array:	The array to extract data from.
 * start:	Start index to get data from.
 * stop:	End index to get data from.
 *		If stop is 0, will go until the end of the array is reached.
 *
 * Return value
 * Returns an array on success.
 * Returns an error on failure.
 *
 */
function GetArrayRange(byref the_array, start, stop:=0)
	if ( Lower(TypeOf(the_array)) != "array" )
		return error{"errortext":="Object passed was not an array."};
	endif
	
	start := CInt(start);
	stop := CInt(stop);

	if ( start < 1 )
		start := 1;
	endif
	if ( !stop )
		stop := the_array.size();
	elseif ( stop > the_array.size() )
		stop := the_array.size();
	endif

	var new_array := array{};
	for ( start; start<=stop; start:=start+1 )
		new_array.append(the_array[start]);
		sleepms(2);
	endfor

	return new_array;
endfunction

/* 
 * BreakArray(the_array, size)
 *
 * Purpose
 * Breaks an array up into smaller arrays.
 *
 * Parameters
 * the_array:	The array that will be broken up.
 * size:	Size of the new arrays.
 *
 * Return value
 * Returns an array of arrays
 * 
 */
function BreakArray(byref the_array, size:=1)
	if ( Lower(TypeOf(the_array)) != "array" )
		return error{"errortext":="Object passed was not an array."};
	endif
	
	if ( the_array.size() > size )
		var new_arrays := array();
		var arrays_needed := Ceil(CDbl(the_array.size()) / CDbl(size));

		var i := 1;
		var start := i;
		var stop := size;
		for ( i; i<=arrays_needed; i:=i+1 )
			new_arrays.Append(GetArrayRange(the_array, start, stop));
			start := stop+1;
			stop := stop+size;
			sleepms(2);
		endfor

		return new_arrays;
	else
		return array{the_array};
	endif
endfunction

/*
 * FindInArray(byref the_array, find_what) 
 *
 * Purpose
 * Finds the first instance of something in an array.
 *
 * Parameters
 * the_array:	Array to search.
 * find_what:	What to look for.
 * 
 * Return value
 * Returns > 1 (the index) if it is found.
 * Returns 0 if 'find_what' was not found.
 *
 */
function FindInArray(byref the_array, find_what)
	if ( Lower(TypeOf(the_array)) != "array" )
		return error{"errortext":="Object passed was not an array."};
	endif
	
	foreach index in the_array
		if ( index == find_what )
			return _index_iter;
		endif
		sleepms(2);
	endforeach
	
	return 0;
endfunction


/*-------------------
  ( OLDER FUNCTIONS )
  ------------------*/

/**
 * GetIndex(byref the_array, byref to_find)
 *
 * Parameters	the_array containing the element
 *		what to find
 * 
 * Errortext	<Element not found>.
 *
 * Return
 * the element's index if found, error otherwise
 *
 */
function GetIndex(byref the_array, byref to_find)
	var max := the_array.Size();
	if( !max )
		var ret := error;
		ret.+errortext := "Element not found";
		return ret;
	endif
	
	var ctr;
	var min := 1;
	if( the_array[1].IsA(POLCLASS_UOBJECT) )
		while( min <= max )
			ctr := Cint((min+max)/2);
			if( the_array[ctr].serial == to_find.serial )
				return ctr;
			elseif( the_array[ctr].serial < to_find.serial )
				min := ctr + 1;
			else
				max := ctr - 1;
			endif
		endwhile
		
		var ret := error;
		ret.+errortext := "Element not found";
		return ret;
	else
		while( min <= max )
			ctr := Cint((min+max)/2);
			if( the_array[ctr] == to_find )
				return ctr;
			elseif( the_array[ctr] < to_find )
				min := ctr + 1;
			else
				max := ctr - 1;
			endif
		endwhile
		
		var ret := error;
		ret.+errortext := "Element not found";
		return ret;	
	endif
	
endfunction

/**
 * InsertElementInSortedArray(byref the_array, byref to_find)
 *
 * Parameters	the_array containing the element
 *		what to insert
 * Errortext	<Element <element> already exist in the array>
 *		<Couldn't insert element <element>>
 * Purpose
 * Insert an element at the good index, must be the only one
 * instance of that element in the array, no dupe allowed.
 *
 * Return
 * non-zero if the element could be insert, error otherwise.
 *
 */
function InsertInSortedArray( byref the_array, byref element )

	var max := the_array.Size();
	if( !max )
		return the_array.Append(element);
	endif
	
	var ctr;
	var min := 1;
	if( the_array[1].IsA(POLCLASS_UOBJECT) )
		while( min <= max )
			ctr := Cint((min+max)/2);
			if( the_array[ctr].serial == element.serial )
				var ret := error;
				ret.+errortext := "Element " + element + " already exist in array";
				return ret;
			elseif( the_array[ctr].serial < element.serial )
				min := ctr + 1;
			else
				max := ctr - 1;
			endif
		endwhile
	else
		while( min <= max )
			ctr := Cint((min+max)/2);
			if( the_array[ctr] == element )
				var ret := error;
				ret.+errortext := "Element " + element + " already exist in array";
				return ret;
			elseif( the_array[ctr] < element )
				min := ctr + 1;
			else
				max := ctr - 1;
			endif
		endwhile
	endif

	return the_array.Insert( min, element );
	
endfunction


/**
 * RemoveElement(byref the_array, byref element)
 *
 * Parameters
 * the_array:	containing the element
 * element:	the element to remove
 *
 * Return
 * 1 is the elment was successfully removed
 * An error otherwise
 *
 */
function RemoveElement( byref the_array, byref element )

	var index := GetIndex( the_array, element );
	if( index )
		return the_array.Erase(index);
	else
		return index;
	endif

endfunction


/**
 * SortArray(byref the_array)
 *
 * Purpose
 * Sort the array, even array of uobject.
 *
 * Parameters
 * the_array:	to sort
 *
 * Return
 * 1 if the sorting was success, 0 otherwise.
 *
 */
function SortArray( byref the_array )

	var length := the_array.Size();
	if( length )
		if( the_array[1].IsA(POLCLASS_UOBJECT) )
			var i;
			var j;
			var temp;
			var old_prio := set_priority(50);
			for( i := 1; i < length; i := i + 1 )
				for( j := 2; j <= (length-i+1); j := j + 1 )
					if( the_array[j].serial < the_array[j-1].serial )
						temp := the_array[j];
						the_array[j]	:= the_array[j-1];
						the_array[j-1]	:= temp;
					endif
				endfor
			endfor
			set_priority(old_prio);
		else
			return the_array.Sort();
		endif
	endif
	
	return 1;
	
endfunction


/**
 * fill_array(starts, ends, incr := 1)
 *
 * you don't want to send this non-integers. Error checking isn't at the moment.
 * This function is handed start and end numbers, and increments. If you send it
 * (1,5,1), for instance, it will return an array {1,2,3,4,5}. (5,1,-2) will return
 * {5,3,1}. (1,5,3) will return {1,4}.
 * Added by Madman Across the Water
 *
 */
function fill_array(starts, ends, incr := 1)

	var newarray := array;
	if (incr == 0)
	     return starts;
	elseif (incr > 0)
	     var i:= 1;
	     while (1)
	         newarray[i] := starts;
	         starts := starts + incr;
	         if (starts > ends)
	         	return newarray;
	         endif
	         i := i + 1;
	     endwhile
	else
	     var i := 1;
	     while (1)
	         newarray[i] := starts;
	         starts := starts + incr;
	         if (starts < ends)
	         	return newarray;
	         endif
	         i := i + 1;
	     endwhile
	endif
	
	return 0;
endfunction
