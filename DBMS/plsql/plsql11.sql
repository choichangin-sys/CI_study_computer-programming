--사번을 입력하면 그 사원 데이터 삭제하는 프로시져

create or replace procedure p_sawon_ex_del
	(v_sabun sawon.sabun%type)
is
begin
	delete sawon_ex where sabun=v_sabun;
	commit;
end;
/

--호출형태
--exec p_sawon_ex_del(12)


