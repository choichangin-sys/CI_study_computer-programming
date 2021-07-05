-- 같은 작업을 하는 행단위의 테이블을 커서를 정의하여 일괄처리 가능!! *** // 행 단위 실행(fetch or for 선택)

--모든 사원의 이름과 급여를 출력하는 커서를 정의
declare
	cursor mycur is select saname, sapay from sawon;
begin
	for i in mycur loop
		dbms_output.put_line('이름:'|| i.saname || ', 급여:'|| i.sapay);
	end loop;
end;
/							
----------------------------------------------
declare
	cursor mycur is select saname, sapay from sawon;
	v_name sawon.saname%type;
	v_pay    sawon.sapay%type;
begin
	if mycur%isopen then
		close mycur;
	end if;
	open mycur;
	loop
		fetch mycur into v_name, v_pay;
		exit when(mycur%notfound);
		반복할 명령등...
	end loop;

	close mycur;
end;
/
----------------------------------------------

