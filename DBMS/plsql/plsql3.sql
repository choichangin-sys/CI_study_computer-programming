--accept 변수 prompt '문자열'	// 값이 입력되면 변수에 담아서 프로그램 내에서 사용 : [&변수]형태로 사용

-- 입력받은 구구단 출력

set serveroutput on
set verify off

accept num prompt '숫자를 입력->'
begin
	dbms_output.put_line('입력된 단 : '|| &num);
	for i in 1..9 loop
		dbms_output.put_line(&num || 'x' || i || '=' || (&num)*i);
	end loop;
end;
/
