create table emp(empid number(5) constraint emp_id_pk primary key, 
		ename varchar2(15), 
		loan_ck char(2) default 'N');

create table loan(eid number(5) constraint loan_id_fk references emp(empid), 
		amount number(30), 
		loan_date date default sysdate);

insert into emp(empid, ename) values(1, '홍동우');
insert into emp(empid, ename) values(2, '홍다은');
insert into emp(empid, ename) values(3, '차승원');
insert into emp(empid, ename) values(4, '주원');

-- 대출 테이블에 입력 또는 삭제, 변경이 발생하면 사원 테이블의 대출여부 컬럼이 자동 변경되는 트리거
create or replace trigger emp_loan_check
	after insert or delete or update of eid on loan
	for each row
begin
	if inserting then
		update emp set loan_ck='Y' where empid=:new.eid;
	elsif deleting then
		update emp set loan_ck='N' where empid=:old.eid;
	elsif updating then 
		update emp set loan_ck='N' where empid=:old.eid;
		update emp set loan_ck='Y' where empid=:new.eid;
	end if;
end;
/
