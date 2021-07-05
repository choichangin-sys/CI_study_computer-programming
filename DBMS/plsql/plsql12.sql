--사원 테이블에 사원 정보를 입력하는 프로시져
--사번은 시퀀스를 이용하고(201~299, 2씩증가)
--입사일은 현재날짜로 입력되고
--커미션은 급여의 조건에 따라 입력(부서가 영업부 또는 관리부->급여의 10%, 그 외의 부서->0)	
--exec p_sawon_in('홍동우', 3000, '대리', '남자', 2, '영업부')

create sequence seq_sawon_sabun
increment by 2
start with 201
maxvalue 299;

create procedure p_sawon_in(name sawon.saname%type,
                 pay sawon.sapay%type,
                 job sawon.sajob%type,
                 sex sawon.sasex%type,
                 mgr sawon.samgr%type,
                 dename dept.dname%type)
is
--	dno dept.deptno%type;
begin
--	select deptno into dno from dept where dname='영업부';

   	insert into sawon(sabun,saname,deptno,sajob,sapay,sahire,sasex,samgr,comm) values
		           (seq_sawon_sabun.nextval,name, (select deptno from dept where dname = dename),
         		            job,pay,sysdate,sex,mgr,
         		            case dename when '영업부' then pay*0.1 when '관리부' then pay*0.1 else 0 end);
end;
/
