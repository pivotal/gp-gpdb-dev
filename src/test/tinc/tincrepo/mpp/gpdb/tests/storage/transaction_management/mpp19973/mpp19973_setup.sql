DROP TABLE IF EXISTS foo;
CREATE TABLE foo(a, b) AS VALUES(1, 10), (2, 20);

CREATE OR REPLACE FUNCTION testfn() RETURNS bool AS $$
DECLARE

BEGIN
  BEGIN
    CREATE TEMP TABLE foo_stg2 AS SELECT 10/0 FROM foo;
  EXCEPTION
    WHEN division_by_zero THEN RETURN false;
    RETURN false;
  END;
  RETURN true;
END;
$$ LANGUAGE plpgsql;