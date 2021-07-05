--사번, 사원명, 입사일, 급여 정보를 가지고, 근무기간(xx년 xx개월)과 급여순위를 계산하여 
--sawon_result 테이블에 입력하는 커서를 정의

create table sawon_result(
		sabun number(10) primary key,
		sname varchar2(10) not null,
		hiredate date,
		sal   number(10),
		hiredate_work varchar2(20),
		sal_rank number(5)
		);

declare
	cursor mycur is select sabun, saname, sahire, sapay from sawon;
	v_hire_work sawon_result.hiredate_work%type;
	v_sal_rank  sawon_result.sal_rank%type;
begin
	for i in mycur loop
--2.근무기간 구하기
		v_hire_work := floor(months_between(sysdate,i.sahire)/12)||'년 '||
				floor(mod(months_between(sysdate,i.sahire),12))||'개월';
--3.급여순위 구하기
		v_sal_rank := 0;
		select count(*) into v_sal_rank from sawon where sapay > i.sapay;
		v_sal_rank := v_sal_rank + 1;

--4.sawon_result 테이블에 입력하기
		insert into sawon_result(sabun,sname,hiredate,sal,hiredate_work,sal_rank)
				values(i.sabun,i.saname,i.sahire,i.sapay,v_hire_work,v_sal_rank);
	end loop;
	commit;
end;
/