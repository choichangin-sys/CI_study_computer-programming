--out mode�� �ִ� ���ν���
--�Ի�⵵�� ������ ��ձ޿��� �ο����� ��ȯ�ϴ� ���ν���
create or replace procedure p_state
	(v_hire varchar2,
	 v_res  out varchar2)
is
	hire varchar2(10);
	ave number(10);
	cnt number(10);
begin
	select  to_char(sahire,'yyyy'), round(avg(sapay),0), count(*)  into hire, ave, cnt from sawon
	where to_char(sahire,'yyyy')=v_hire
	group by to_char(sahire,'yyyy');

	v_res := '�Ի�⵵ : '||hire||', '||'��ձ޿�:'||ave||', '||'�ο��� :'||cnt;
end;
/

-- out mode �ִ� ���ν��� ȣ��
SQL> variable result varchar2(100)		//
SQL> exec p_state(1990, :result)		//

PL/SQL ó���� ���������� �Ϸ�Ǿ����ϴ�.

SQL> print result				//

RESULT
--------------------------------------------
�Ի�⵵ : 1990, ��ձ޿�:2500, �ο��� :3