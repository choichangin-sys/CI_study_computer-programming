--create table dept_info(info varchar2(20));

--dept_ex table�� insert�� �߻��ϸ� dept_info table�� [�μ�����] ���ڿ��� �Է�

create or replace trigger t_dept_ex
	after insert on dept_ex
	for each row
begin
	insert into dept_info values('�μ��Է�');
end;
/
