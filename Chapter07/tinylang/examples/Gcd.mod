MODULE Point;

TYPE Point = RECORD X, Y: INTEGER END;

VAR p: Point;

PROCEDURE AssignX(a: INTEGER);
BEGIN
  p.X := a;
END AssignX;

TYPE Shape = RECORD color: INTEGER;
PROCEDURE (VAR s: Shape) GetColor():INTEGER;
PROCEDURE (VAR s: Shape) Area(): REAL;
END;

END Point.
