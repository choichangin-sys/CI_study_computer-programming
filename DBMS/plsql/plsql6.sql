-- ���� �۾��� �ϴ� ������� ���̺��� Ŀ���� �����Ͽ� �ϰ�ó�� ����!! *** // �� ���� ����(fetch or for ����)

--��� ����� �̸��� �޿��� ����ϴ� Ŀ���� ����
declare
	cursor mycur is select saname, sapay from sawon;
begin
	for i in mycur loop
		dbms_output.put_line('�̸�:'|| i.saname || ', �޿�:'|| i.sapay);
	end loop;
end;
/							
----------------------------------------------
declare
	cursor mycur is select saname, sapay from sawon;
	v_name sawon.saname%type;
	v_pay    sawon.sapay%type;
begin
	if mycur%isopen then
		close mycur;
	end if;
	open mycur;
	loop
		fetch mycur into v_name, v_pay;
		exit when(mycur%notfound);
		�ݺ��� ��ɵ�...
	end loop;

	close mycur;
end;
/
----------------------------------------------

