-- update cascade 구현

-- 부서 테이블에 부서번호가 변경되면, 사원 테이블의 그 부서를 참조하는 사원들의 부서번호도 함께 변경
create or replace trigger t_deptno
	after update of deptno on dept
	for each row
begin
	update sawon set deptno=:new.deptno where deptno=:old.deptno;
end;
/




