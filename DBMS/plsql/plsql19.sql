--create table dept_info(info varchar2(20));

--dept_ex table에 insert가 발생하면 dept_info table에 [부서삭제] 문자열을 입력

create or replace trigger t_dept_ex
	after insert on dept_ex
	for each row
begin
	insert into dept_info values('부서입력');
end;
/
