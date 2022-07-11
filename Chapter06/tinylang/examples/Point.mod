MODULE Point;

TYPE Point = RECORD X, Y: INTEGER END;

VAR p: Point;

PROCEDURE AssignX(a: INTEGER);
BEGIN
  p.X := a;
END AssignX;

TYPE Shape = RECORD color: INTEGER END;

PROCEDURE GetColor(s: Shape):INTEGER;
BEGIN
END GetColor;

PROCEDURE Area(s: Shape): INTEGER;
BEGIN
    RETURN 2 * radius * radius; 
END Area;


END Point.
