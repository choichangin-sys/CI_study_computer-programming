--���, �����, �Ի���, �޿� ������ ������, �ٹ��Ⱓ(xx�� xx����)�� �޿������� ����Ͽ� 
--sawon_result ���̺� �Է��ϴ� Ŀ���� ����

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
--2.�ٹ��Ⱓ ���ϱ�
		v_hire_work := floor(months_between(sysdate,i.sahire)/12)||'�� '||
				floor(mod(months_between(sysdate,i.sahire),12))||'����';
--3.�޿����� ���ϱ�
		v_sal_rank := 0;
		select count(*) into v_sal_rank from sawon where sapay > i.sapay;
		v_sal_rank := v_sal_rank + 1;

--4.sawon_result ���̺� �Է��ϱ�
		insert into sawon_result(sabun,sname,hiredate,sal,hiredate_work,sal_rank)
				values(i.sabun,i.saname,i.sahire,i.sapay,v_hire_work,v_sal_rank);
	end loop;
	commit;
end;
/