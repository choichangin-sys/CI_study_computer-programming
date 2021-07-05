--out mode가 있는 프로시져
--입사년도를 가지고 평균급여와 인원수를 반환하는 프로시져
create or replace procedure p_state
	(v_hire varchar2,
	 v_res  out varchar2)
is
	hire varchar2(10);
	ave number(10);
	cnt number(10);
begin
	select  to_char(sahire,'yyyy'), round(avg(sapay),0), count(*)  into hire, ave, cnt from sawon
	where to_char(sahire,'yyyy')=v_hire
	group by to_char(sahire,'yyyy');

	v_res := '입사년도 : '||hire||', '||'평균급여:'||ave||', '||'인원수 :'||cnt;
end;
/

-- out mode 있는 프로시져 호출
SQL> variable result varchar2(100)		//
SQL> exec p_state(1990, :result)		//

PL/SQL 처리가 정상적으로 완료되었습니다.

SQL> print result				//

RESULT
--------------------------------------------
입사년도 : 1990, 평균급여:2500, 인원수 :3