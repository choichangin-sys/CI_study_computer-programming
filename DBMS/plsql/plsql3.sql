--accept ���� prompt '���ڿ�'	// ���� �ԷµǸ� ������ ��Ƽ� ���α׷� ������ ��� : [&����]���·� ���

-- �Է¹��� ������ ���

set serveroutput on
set verify off

accept num prompt '���ڸ� �Է�->'
begin
	dbms_output.put_line('�Էµ� �� : '|| &num);
	for i in 1..9 loop
		dbms_output.put_line(&num || 'x' || i || '=' || (&num)*i);
	end loop;
end;
/
