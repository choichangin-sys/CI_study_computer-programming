--* ���̺��� ���� ��������(������) : �÷����� ������ ����� �� ����
--select �÷���,... into ����,... from ���̺��,...;

declare
	name sawon.saname%type;
begin
	select saname into name from sawon where sabun=13;
	dbms_output.put_line('�̸�:'|| name);
end;
/

--PL/SQL������ ���� ���� ���
v_loc	varchar2(10) := 'seoul';
v_name	sawon.saname%type;		// sawon.saname�� ���� type(����) ����
v_comm	emp.comm%type not null :=100;
v_sal	constant emp.sal%type := 1000;	// ���� ������ �� ���� ����(�ݵ�� �ʱⰪ)
i	sawon%rowtype;			// i.sabun, i.saname, i.sapay, ....�� �� ���� ����