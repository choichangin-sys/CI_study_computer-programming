-- 트리거를 이용한 복제구현(동기화구현)
create table dept_bk as select * from dept;

--dept table에 insert가 발생하면, dept_bk table에 insert가 발생
create or replace trigger t_dept_bk 
	after insert or delete or update on dept	
	row each row
begin
	if inserting then
		insert into dept_bk values(:new.deptno, :new.dname, :new.loc);
	elsif deleting then
		delete dept_bk where deptno=:old.deptno;
	elsif updating then 
		update dept_bk 
		set deptno=:new.deptno, dname=:new.dname, loc=:new.loc
		where deptno=:old.deptno;
	end if;
end;
/

--입력된 테이블의 행의 컬럼값 - [:new.컬럼명]
--삭제된 케이블의 행의 컬럼값 - [:old.컬럼명]