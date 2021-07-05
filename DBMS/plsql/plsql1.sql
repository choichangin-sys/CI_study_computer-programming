set serveroutput on

declare
--	int i = 10;
	i number(4) := 10;
begin
-- 	printf(i);

--패키지.프로시져 호출 (클래스.메소드)
	dbms_output.put_line('i의 값->'|| i);
end;
/